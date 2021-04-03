//
// Created by root on 2021/4/3.
//

#ifndef MIKOPLAYER_MKFFMPEG_H
#define MIKOPLAYER_MKFFMPEG_H

#include "JavaCallHelper.h"
#include "VideoChannel.h"
#include "AudioChannel.h"

extern "C" {
#include <libavformat/avformat.h>
};

namespace miko {
    class MkFfmpeg {

    private:
        char *url = nullptr;

        pthread_t pid;
        pthread_t pid_play;

        AVFormatContext *context;
        JavaCallHelper *call;

        VideoChannel *videoChannel = nullptr;
        AudioChannel *audioChannel = nullptr;

        bool isPlaying;


    public:
        MkFfmpeg(JavaCallHelper *call, const char *url);

        virtual ~MkFfmpeg();

        const char *getUrl() const;

        void setUrl(const char *url);

        void prepare();

        void _prepare();

        void start();


        void _play();
    };

}

#endif //MIKOPLAYER_MKFFMPEG_H
