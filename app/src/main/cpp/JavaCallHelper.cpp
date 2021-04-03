//
// Created by root on 2021/4/3.
//

#include "JavaCallHelper.h"
#include "macro.h"

using namespace miko;

JavaCallHelper::JavaCallHelper(JavaVM *vm, JNIEnv *env, jobject thiz) {
    // 跨线程回调
    this->vm = vm;
    // 主线程回调
    this->env = env;
    // 涉及跨方法和跨进程访问的时候就要new全局引用
    this->thiz = env->NewGlobalRef(thiz);

    jclass clazz = env->GetObjectClass(thiz);
    this->mFail = env->GetMethodID(clazz, "onFail", "(I)V");
    this->mPrepare = env->GetMethodID(clazz, "onPrepare", "()V");


}

JavaCallHelper::~JavaCallHelper() {
    env->DeleteGlobalRef(thiz);
}

void JavaCallHelper::onFail(int thread, int ret) {
    // thread表示当前线程ID
    if(thread==THREAD_MAIN){
        env->CallVoidMethod(thiz, mFail, ret);
    }else{
        // 子线程操作
        JNIEnv* env = nullptr;
        vm->AttachCurrentThread(&env, nullptr);
        env->CallVoidMethod(thiz, mFail, ret);
        vm->DetachCurrentThread();
    }
}

void JavaCallHelper::onPrepare(int thread) {
    if (thread == THREAD_MAIN){
        env->CallVoidMethod(thiz,mPrepare);
    } else{
        //子线程操作
        JNIEnv *env;

        vm->AttachCurrentThread(&env,0);
        env->CallVoidMethod(thiz,mPrepare);
        vm->DetachCurrentThread();
    }

}
