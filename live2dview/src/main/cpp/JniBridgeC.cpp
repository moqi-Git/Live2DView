/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include <jni.h>
#include "JniBridgeC.hpp"
#include <android/log.h>
//#include "LAppDelegate.hpp"
//#include "LAppPal.hpp"


#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "TAG" ,__VA_ARGS__)

//using namespace Csm;

static JavaVM *g_JVM; // JavaVM is valid for all threads, so just save it globally

JNIEnv *GetEnv() {
    JNIEnv *env = NULL;
    g_JVM->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    return env;
}

// The VM calls JNI_OnLoad when the native library is loaded
jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    g_JVM = vm;

    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}

void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

}

extern "C"
{
//    JNIEXPORT void JNICALL
//    Java_com_live2d_demo_JniBridgeJava_nativeOnStart(JNIEnv *env, jclass type)
//    {
////        LAppDelegate::GetInstance()->OnStart();
//    }

//    JNIEXPORT void JNICALL
//    Java_com_live2d_demo_JniBridgeJava_nativeOnPause(JNIEnv *env, jclass type)
//    {
////        LAppDelegate::GetInstance()->OnPause();
//    }

//    JNIEXPORT void JNICALL
//    Java_com_live2d_demo_JniBridgeJava_nativeOnStop(JNIEnv *env, jclass type)
//    {
////        LAppDelegate::GetInstance()->OnStop();
//    }

//    JNIEXPORT void JNICALL
//    Java_com_live2d_demo_JniBridgeJava_nativeOnDestroy(JNIEnv *env, jclass type)
//    {
////        LAppDelegate::GetInstance()->OnDestroy();
//    }

JNIEXPORT void JNICALL
Java_com_moqi_live2dview_JNIBridge_nativeOnSurfaceCreated(JNIEnv *env, jclass type) {
//        LAppDelegate::GetInstance()->OnSurfaceCreate();
}

JNIEXPORT void JNICALL
Java_com_moqi_live2dview_JNIBridge_nativeOnSurfaceChanged(JNIEnv *env, jclass type, jint width,
                                                          jint height) {
//        LAppDelegate::GetInstance()->OnSurfaceChanged(width, height);
}

JNIEXPORT void JNICALL
Java_com_moqi_live2dview_JNIBridge_nativeOnDrawFrame(JNIEnv *env, jclass type) {
//        LAppDelegate::GetInstance()->Run();
}

JNIEXPORT void JNICALL
Java_com_moqi_live2dview_JNIBridge_onTouchDown(JNIEnv *env, jclass type, jfloat pointX,
                                               jfloat pointY) {
//        LAppDelegate::GetInstance()->OnTouchBegan(pointX, pointY);
    LOGE("onTouchDown: %f, %f", pointX, pointY);
}

JNIEXPORT void JNICALL
Java_com_moqi_live2dview_JNIBridge_onTouchUp(JNIEnv *env, jclass type, jfloat pointX,
                                             jfloat pointY) {
//        LAppDelegate::GetInstance()->OnTouchEnded(pointX, pointY);
}

JNIEXPORT void JNICALL
Java_com_moqi_live2dview_JNIBridge_onTouchMove(JNIEnv *env, jclass type, jfloat pointX,
                                               jfloat pointY) {
//        LAppDelegate::GetInstance()->OnTouchMoved(pointX, pointY);
}
}

