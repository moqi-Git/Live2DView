/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include <jni.h>
#include "JniBridgeC.hpp"
#include "LAppAllocator.hpp"
#include "LAppDefine.hpp"
#include "LAppPal.hpp"
#include "LAppModel.hpp"
#include <android/log.h>
#include <CubismModelSettingJson.hpp>


#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "Live2DModel" ,__VA_ARGS__)

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
JNIEXPORT jint JNICALL
Java_com_moqi_live2dview_Live2DModel_createModel(JNIEnv *env, jobject thiz,
                                                 jbyteArray model_config_json, jint buffer_size) {
    LOGE("Cubism SDK init");
    LAppAllocator _cubismAllocator;
    Csm::CubismFramework::Option _cubismOption{};
    _cubismOption.LogFunction = LAppPal::PrintMessage;
    _cubismOption.LoggingLevel = LAppDefine::CubismLoggingLevel;
    Csm::CubismFramework::CleanUp();
    Csm::CubismFramework::StartUp(&_cubismAllocator, &_cubismOption);

    LOGE("createModel start");
    Live2D::Cubism::Framework::csmSizeInt size = buffer_size;
    LOGE("read byte buffer, size=%d", buffer_size);
    char* bytes = new char[size];
    env->GetByteArrayRegion(model_config_json, 0, size, reinterpret_cast<jbyte *>(bytes));
    auto* buffer = reinterpret_cast<Live2D::Cubism::Framework::csmByte *>(bytes);
    if (buffer == nullptr){
        LOGE("buffer cast to unsigned char* failed");
    }
    LOGE("convert buffer to ICubismModelSetting start");
    Live2D::Cubism::Framework::ICubismModelSetting* setting = new Live2D::Cubism::Framework::CubismModelSettingJson(buffer, size);
    LOGE("convert buffer to ICubismModelSetting end");
    delete[] bytes;
    delete[] buffer;

    LOGE("ICubismModelSetting name: %s", setting->GetModelFileName());

    jclass live2dmodel = env->GetObjectClass(thiz);
    jmethodID loadFile = env->GetMethodID(live2dmodel, "loadFile", "(Ljava/lang/String;)[B");

    LOGE("native load model file start");
//    Csm::CubismMoc* moc = Csm::CubismMoc::Create();
//    auto* model = new Csm::CubismUserModel();
    if (strcmp(setting->GetModelFileName(), "") != 0){
        jstring mocName = env->NewStringUTF(setting->GetModelFileName());
        LOGE("native load moc file: %s", setting->GetModelFileName());
        auto file = (jbyteArray)env->CallObjectMethod(thiz, loadFile, mocName);
        int modelFileSize = env->GetArrayLength(file);
        char* modelFileBuffer = new char[modelFileSize];
        env->GetByteArrayRegion(file, 0, size, reinterpret_cast<jbyte *>(modelFileBuffer));
        Csm::CubismMoc* moc = Csm::CubismMoc::Create(
                reinterpret_cast<const Live2D::Cubism::Framework::csmByte *>(modelFileBuffer), modelFileSize);
//        model->LoadModel(reinterpret_cast<const Live2D::Cubism::Framework::csmByte *>(modelFileBuffer), size);
        LOGE("native load moc file end");
        Csm::CubismModel* model = moc->CreateModel();
        LOGE("model info: w=%f,h=%f", model->GetCanvasWidth(), model->GetCanvasHeight());
    }
//    LOGE("model info: w=%f,h=%f", model->GetModel()->GetCanvasWidth(), model->GetModel()->GetCanvasHeight());

    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_moqi_live2dview_Live2DModel_releaseModel(JNIEnv *env, jobject thiz, jint model_id) {

}
