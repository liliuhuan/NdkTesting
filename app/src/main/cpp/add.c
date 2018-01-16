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
    jclass  jclass1 = (*env)->GetObjectClass(env,this);
    jfieldID  jfieldID1 = (*env)->GetFieldID(env,jclass1,"content","Ljava/lang/String;");
    jstring  jstr = (*env)->GetObjectField(env,this,jfieldID1);
    const char *chars = "I am from c";
    jstr = (*env)->NewStringUTF(env, chars);
    (*env)->SetObjectField(env,this,jfieldID1,jstr);
    return (*env)->NewStringUTF(env, char_arr);
}