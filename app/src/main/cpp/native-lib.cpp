#include <jni.h>
#include <string>
#include "MkFfmpeg.h"

using namespace miko;

MkFfmpeg* mkFfmpeg = nullptr;

JavaVM* jvm = nullptr;

jint JNI_OnLoad(JavaVM* vm, void* args){
    jvm = vm;
    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_xana_media_mikoplayer_MkPlayer_cppPrepare(JNIEnv *env, jobject thiz, jstring url_) {
    const char* url = env->GetStringUTFChars(url_, nullptr);
    // 解析流媒体
    JavaCallHelper* call = new JavaCallHelper(jvm, env, thiz);
    mkFfmpeg =  new MkFfmpeg(call, url);
    mkFfmpeg->prepare();

    env->ReleaseStringUTFChars(url_, url);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_xana_media_mikoplayer_MkPlayer_cppStart(JNIEnv *env, jobject thiz) {
    mkFfmpeg->start();
}