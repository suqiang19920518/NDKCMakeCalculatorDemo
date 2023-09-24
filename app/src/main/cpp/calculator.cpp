#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>

extern "C"

jint addNumber(JNIEnv *env, jclass clazz, jint a, jint b) {
    __android_log_print(ANDROID_LOG_DEBUG,"JNI", "native: addNumber ###");
    return a + b;
}

jint subNumber(JNIEnv *env, jclass clazz, jint a, jint b) {
    __android_log_print(ANDROID_LOG_DEBUG,"JNI", "native: subNumber ###");
    return a - b;
}

jint mulNumber(JNIEnv *env, jclass clazz, jint a, jint b) {
    __android_log_print(ANDROID_LOG_DEBUG,"JNI", "native: mulNumber ###");
    return a * b;
}

jint divNumber(JNIEnv *env, jclass clazz, jint a, jint b) {
    __android_log_print(ANDROID_LOG_DEBUG,"JNI", "native: divNumber ###");
    return a / b;
}

//注册四个方法，注意签名
const JNINativeMethod method[]={
        {"add","(II)I",(void*)addNumber},
        {"sub","(II)I",(void*)subNumber},
        {"mul","(II)I",(void*)mulNumber},
        {"div","(II)I",(void*)divNumber}
};

//找到对应的JNITools类
static const char *className = "com/example/ndkcalculatordemo/JNITools";

static int jniRegisterNativeMethods(JNIEnv* env, const char* className,
                                    const JNINativeMethod* gMethods, int numMethods) {

    jclass clazz;

    __android_log_print(ANDROID_LOG_DEBUG, "JNI", "Registering %s natives\n", className);
    clazz = (env)->FindClass(className);
    if (clazz == NULL) {
        __android_log_print(ANDROID_LOG_DEBUG,"JNI","Native registration unable to find class '%s'\n", className);
        return -1;
    }

    int result = 0;
    //开始注册
    if ((env)->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        __android_log_print(ANDROID_LOG_DEBUG,"JNI","RegisterNatives failed for '%s'\n", className);
        result = -1;
    }

    (env)->DeleteLocalRef(clazz);
    return result;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved){

    //打印日志，说明已经进来了
    __android_log_print(ANDROID_LOG_DEBUG,"JNI", "enter jni_onload");

    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }

    jint ret = jniRegisterNativeMethods(env, className, method, sizeof(method) / sizeof(JNINativeMethod));

    if (ret != JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, "JNI", "jni_register Error");
        return -1;
    }

    return JNI_VERSION_1_6;
}
