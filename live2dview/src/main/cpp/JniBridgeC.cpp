/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include <jni.h>
#include "JniBridgeC.hpp"
#include <android/log.h>


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

