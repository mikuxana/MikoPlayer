//
// Created by root on 2021/4/3.
//

#include "Channel.h"
using miko::Channel;

Channel::Channel(int index) {

    this->id = index;

}

Channel::~Channel() {
    packets.set_callback(release);
    packets.clear();


}

