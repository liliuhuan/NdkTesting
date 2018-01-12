//
// Created by liqin on 2018/1/12.
//

#include <stdio.h>
#include <jni.h>
#include "sum.h"

jstring JNICALL Java_ndk_llh_com_ndkdemo_MainActivity_stringGetNumber
        (JNIEnv *env, jobject this, jint x, jint y) {
    char char_arr [100];
    int res = sumNumber(x,y);
    sprintf(char_arr, "%d", res);
    return (*env)->NewStringUTF(env, char_arr);
}