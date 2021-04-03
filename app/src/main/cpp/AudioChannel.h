//
// Created by root on 2021/4/3.
//

#ifndef MIKOPLAYER_AUDIOCHANNEL_H
#define MIKOPLAYER_AUDIOCHANNEL_H


#include "Channel.h"

namespace miko{
    class AudioChannel : public Channel{
    public:
        AudioChannel(int index);
        ~AudioChannel();
    };
}




#endif //MIKOPLAYER_AUDIOCHANNEL_H
