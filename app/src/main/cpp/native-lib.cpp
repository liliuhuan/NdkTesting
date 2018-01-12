#include <jni.h>
#include <string>


extern "C"
JNIEXPORT jstring JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_addFromJni(JNIEnv *env, jobject instance, jint x, jint y) {
    jint z = x + y;
    return z;
}extern "C"
JNIEXPORT void JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_updateContent(JNIEnv *env, jobject obj) {
    jclass objClass = env->GetObjectClass(obj);
    jfieldID fieldId = env->GetFieldID(objClass, "content", "Ljava/lang/String;");
    if (fieldId == NULL) { return; }
    jstring str = (jstring) env->GetObjectField(obj, fieldId);
    str = env->NewStringUTF("hello，I form c++");
    if (str == NULL) { return; }
    env->SetObjectField(obj, fieldId, str);
}
extern "C"
JNIEXPORT void JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_updateStaticContent(JNIEnv *env, jobject obj) {
    jclass objC = env->GetObjectClass(obj);
    /*
     * 字段描述符用来表示JVM中的字段类型，字符串的内容由字段被声明的类型决定。
     * 例如，用 I 来表示 int类型字段，用 F 来表示float类型字段，用 D 来表示 double类型字段，用 Z来表示 boolean类型字段等等。
      像String这样的引用类型，描述符都是以L开头，然后跟包名/类名，最后以分号结尾。
      数组类型描述符以【 标识。例如整形数组（int[]），字段描述符为 【I。
     */
    jfieldID fieldId = env->GetStaticFieldID(objC, "num", "I");
    if (fieldId == NULL) return;
    //获取，设置静态变量内容
    jint result = env->GetStaticIntField(objC, fieldId);
    env->SetStaticIntField(objC, fieldId, 10);
}

extern "C"
JNIEXPORT void JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_callBack(JNIEnv *env, jobject instance) {
    jclass objC = env->GetObjectClass(instance);
    jmethodID mid = env->GetMethodID(objC, "show", "()V");
    if (mid == NULL)return;
    env->CallVoidMethod(objC, mid);
}
/**
 *  （参数类型描述符）返回值类型描述符
  例如：public void getName()方法的描述符为：（）V；
  public String getString(String name)方法的描述符为：（Ljava/lang/String;）Ljava/lang/String;
  public void setArray（int[] arrays）方法的描述符为：（[I）V
 */
extern "C"
JNIEXPORT void JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_callBackStatic(JNIEnv *env, jobject instance) {
    jclass objC = env->GetObjectClass(instance);
    jmethodID mid = env->GetStaticMethodID(objC, "show", "(I)V");
    if (mid == NULL)return;
    env->CallStaticVoidMethod(objC, mid);
}

extern "C"
JNIEXPORT void JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_callConstct(JNIEnv *env, jobject instance) {
    jclass clzString = env->FindClass("Ljava/lang/String;");
    jmethodID mid = env->GetMethodID(clzString, "<init>", "([C)V");
    jcharArray array;
    jstring result = (jstring) env->NewObject(clzString, mid, array);
    /**
     *    char[] array = new char[10];
          String result = new String(array);
     */
}

/**
 * ID被使用的时刻获取
 * 把ID存储在静态变量中，当本地方法被重复调用时，不必重新搜索ID
 * 多个线程同时调用该方法时，可能会导致代码混乱。不过没事，多个线程计算的ID其实是相同的。
 */
extern "C"
JNIEXPORT void JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_cacheFieldId(JNIEnv *env, jobject instance) {
    static jfieldID fid;
    jclass objC = env->GetObjectClass(instance);
    if (fid == NULL) {
        fid = env->GetFieldID(objC, "content", "Ljava/lang/String;");
        if (fid == NULL) {
            return;
        }
    }
    jstring str = (jstring) env->GetObjectField(objC, fid);
    const char *result = env->GetStringUTFChars(str, NULL);
    if (result == NULL)return;
    if (env->ExceptionCheck()) {
        env->ReleaseStringUTFChars(str, result);
        env->ThrowNew(objC, "throw a new Exception : NullPointerException");
    }
    env->ReleaseStringUTFChars(str, result);
    str = env->NewStringUTF("HELLO WORLD");
    env->SetObjectField(objC, fid, str);

}
/**
 * 类加载是获取filedId
 */
jfieldID FID_MAINACTIVTY_instance;
extern "C"
JNIEXPORT void JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_initIds(JNIEnv *env, jobject instance) {
    jclass objC = env->GetObjectClass(instance);
    FID_MAINACTIVTY_instance = env->GetFieldID(objC, "content", "Ljava/lang/String;");
}

extern "C"
JNIEXPORT void JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_staticCache(JNIEnv *env, jobject instance) {
    jstring str = env->NewStringUTF("HELLO");
    env->SetObjectField(instance, FID_MAINACTIVTY_instance, str);

    jclass object = (jclass) env->NewLocalRef(instance);
    env->NewGlobalRef(instance);
    env->DeleteLocalRef(instance);
    // env->IsSameObject()

    jarray array = env->NewIntArray(10);
    int len = env->GetArrayLength(array);
//    for (int i = 0; i < len; i++) {
//        jint number = (jint) env->GetObjectArrayElement((jobjectArray) array, i);
//        env->DeleteLocalRef((jobject) number);
//    }
}

extern "C"
JNIEXPORT void JNICALL
Java_ndk_llh_com_ndkdemo_MainActivity_sncy(JNIEnv *env, jobject instance) {

//    （1）MonitorEnter：进入同步代码块
//    （2）MonitorExit：退出同步代码块

    if (env->MonitorEnter(instance) != JNI_OK) {
        //处理错误
    }
    /*
     * 同步代码块业务逻辑处理
     *
     */
    if (env->MonitorExit(instance) != JNI_OK) {
        //处理错误
    }
}
//extern "C"
//JNIEXPORT jstring JNICALL
//Java_ndk_llh_com_ndkdemo_MainActivity_avformatinfo(JNIEnv *env, jobject instance) {
//    char info[40000] = {0};
//
//    av_register_all();
//
//    AVInputFormat *if_temp = av_iformat_next(NULL);
//    AVOutputFormat *of_temp = av_oformat_next(NULL);
//    //Input
//    while (if_temp != NULL) {
//        sprintf(info, "%s[In ][%10s]\n", info, if_temp->name);
//        if_temp = if_temp->next;
//    }
//    //Output
//    while (of_temp != NULL) {
//        sprintf(info, "%s[Out][%10s]\n", info, of_temp->name);
//        of_temp = of_temp->next;
//    }
//    //LOGE("%s", info);
//    return env->NewStringUTF(info);
//}