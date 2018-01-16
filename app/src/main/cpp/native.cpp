#include <jni.h>
#include <string.h>
#include <stdio.h>
#include "sum.h"


extern "C"
JNIEXPORT jstring

JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_stringGetNumber(
        JNIEnv *env,
        jobject instance,jint x, jint y) {
    jint res = sumNumber(x,y);
    char char_arr [100];
    sprintf(char_arr, "%d", res);
    return env->NewStringUTF(char_arr);
}

