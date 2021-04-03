#include "MkFfmpeg.h"
#include "JavaCallHelper.h"
#include "macro.h"
#include <pthread.h>


using miko::MkFfmpeg;


void *task_prepare(void *args) {
    MkFfmpeg *mkFfmpeg = static_cast<MkFfmpeg *>(args);
    mkFfmpeg->_prepare();

    return 0;
}

MkFfmpeg::MkFfmpeg(JavaCallHelper *call, const char *url) {
    this->call = call;
    size_t len = strlen(url);
    this->url = new char[len + 1];
    strcpy(this->url, url);
}

MkFfmpeg::~MkFfmpeg() {
    DELETE(url);
    DELETE(call);
}

const char *MkFfmpeg::getUrl() const {
    return this->url;
}

void MkFfmpeg::prepare() {
    pthread_create(&this->pid, nullptr, task_prepare, this);
}

void MkFfmpeg::_prepare() {
    avformat_network_init();

    // 包含了视频信息
    context = nullptr;
    // 返回0 success, url不正确或者网络异常
    int ret = avformat_open_input(&context, url, nullptr, nullptr);
    if (ret) {
        LOGE("打开媒体失败：%s", av_err2str(ret));
        call->onFail(THREAD_CHILD, FFMPEG_CAN_NOT_OPEN_URL);
        return;
    }
    // 查找媒体中的音视频流 ret>0 success
    ret = avformat_find_stream_info(context, nullptr);
    if (ret < 0) {
        call->onFail(THREAD_CHILD, FFMPEG_CAN_NOT_FIND_STREAMS);
        return;
    }

    for (int i = 0; i < context->nb_streams; ++i) {
        // 可能时视频流也可能是音频流
        AVStream *stream = context->streams[i];
        //包含了解码这段流的各种信息
        AVCodecParameters *codecpar = stream->codecpar;


        // 处理
        // 1、获取解码器
        AVCodec *dec = avcodec_find_decoder(codecpar->codec_id);
        if (dec == nullptr) {
            call->onFail(THREAD_CHILD, FFMPEG_FIND_DECODER_FAIL);
            return;
        }

        // 2、获得解码器上下文
        AVCodecContext *codecContext = avcodec_alloc_context3(dec);
        if (codecContext == nullptr) {
            call->onFail(THREAD_CHILD, FFMPEG_ALLOC_CODEC_CONTEXT_FAIL);
            return;
        }
        // 3、设置上下文的一些参数
        ret = avcodec_parameters_to_context(codecContext, codecpar);
        if (ret < 0) {
            call->onFail(THREAD_CHILD, FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL);
            return;
        }

        // 4、打开解码器
        ret = avcodec_open2(codecContext, dec, nullptr);
        if (ret) {
            call->onFail(THREAD_CHILD, FFMPEG_OPEN_DECODER_FAIL);
            return;
        }

        switch (codecpar->codec_type) {
            case AVMEDIA_TYPE_AUDIO:
                audioChannel = new AudioChannel(i);
                break;
            case AVMEDIA_TYPE_VIDEO:
                videoChannel = new VideoChannel(i);
                break;
        }
    }

    // 没有音视频
    if (!audioChannel && !videoChannel) {
        call->onFail(THREAD_CHILD, FFMPEG_NOMEDIA);
        return;
    }
    // 准备完了, 通知Java随时可以播放
    call->onPrepare(THREAD_CHILD);

}

void *task_play(void *args) {
    // 读取媒体数据包
    // 解码
    MkFfmpeg *mkFfmpeg = static_cast<MkFfmpeg *>(args);
    mkFfmpeg->_play();

    return 0;
}

void MkFfmpeg::start() {
    isPlaying = true;
    pthread_create(&pid_play, nullptr, task_play, this);
}

void MkFfmpeg::_play() {
    while (isPlaying) {
        AVPacket *packet = av_packet_alloc();
        int ret = av_read_frame(context, packet);
        // 流可能是音频数据也有可能是视频数据
        if (ret == 0) {
            if (audioChannel && packet->stream_index == audioChannel->id) {


            } else if (videoChannel && packet->stream_index == videoChannel->id) {
                videoChannel->packets.push(packet);
            }

        } else if (ret == AVERROR_EOF) { // 读取完成，可能没有播放完成

        } else {

        }
    }
}
