#include <jni.h>

#include "Tester.h"

JNIEXPORT jstring JNICALL
Java_com_example_punits_hellondk_MainActivity_getMsgFromJni(JNIEnv *env, jobject instance) {

    // TODO

    hello();
    return (*env)->NewStringUTF(env, "Hello from JNI");
}