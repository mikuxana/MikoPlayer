//
// Created by root on 2021/4/3.
//

#ifndef MIKOPLAYER_VIDEOCHANNEL_H
#define MIKOPLAYER_VIDEOCHANNEL_H

#include "Channel.h"

namespace miko{
    class VideoChannel: public Channel{
    public:
        VideoChannel(int index);
        ~VideoChannel();

    };
}


#endif //MIKOPLAYER_VIDEOCHANNEL_H
