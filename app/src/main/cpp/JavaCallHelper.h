//
// Created by root on 2021/4/3.
//

#ifndef MIKOPLAYER_JAVACALLHELPER_H
#define MIKOPLAYER_JAVACALLHELPER_H

#include <jni.h>


namespace miko{
    class JavaCallHelper {
    private:
        JavaVM* vm;
        JNIEnv* env;
        jobject thiz;

        jmethodID mFail;
        jmethodID mPrepare;

    public:
        JavaCallHelper(JavaVM* vm, JNIEnv* env, jobject thiz);
        ~JavaCallHelper();

        void onFail(int thread, int ret);
        void onPrepare(int thread);
    };
}


#endif //MIKOPLAYER_JAVACALLHELPER_H
