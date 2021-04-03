//
// Created by root on 2021/4/3.
//

#ifndef MIKOPLAYER_CHANNEL_H
#define MIKOPLAYER_CHANNEL_H


extern "C"{
#include <libavcodec/avcodec.h>
};

#include "safe_queue.h"


namespace miko {
    class Channel {
    public:
        int id;
        safe_queue<AVPacket*> packets;

        //释放资源AVPacket*
        static void release(AVPacket*& packet){
            if(packet){
                av_packet_free(&packet);
                packet = 0;
            }
        }

        Channel(int index);

        virtual ~Channel();
    };

}


#endif //MIKOPLAYER_CHANNEL_H
