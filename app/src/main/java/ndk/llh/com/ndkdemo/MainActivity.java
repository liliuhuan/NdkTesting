package ndk.llh.com.ndkdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

/**
 *   JNI提供了访问父类的实例方法函数。流程如下：
 1. 使用GetMethodID从一个指向父类的引用当中获取方法ID。
 2. 传入对象，父类，方法ID和参数，调用CallNonvirtualXXXMethod方法即可。
 一般情况下，在java中调用父类很方便，super.x()即可。所以该方式使用较少。
 */
public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
//        System.loadLibrary("native");
//        initIds();//类静态初始化过程中缓存ID：VM在调用一个类的方法和字段之前，都会执行类的静态初始化过程
    }
    private String content = "hello world ";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
       // updateContent();
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
       // tv.setText(stringFromJNI()+stringGetNumber()+"1+2="+addFromJni(1,2));
        tv.setText(stringGetNumber(4,2));
        tv.append("\n"+content);
    }

//    public native void updateContent() ;
//    public native void updateStaticContent();
//    public native void callBack();
//    public native void sncy();
//    public native void callBackStatic();
//    public native void callConstct();//调用构造函数和调用实例方法基本类似
//    //缓存的两种方式：需要时缓存数据，类加载时缓存数据（推荐）
//    /**
//     * 缺点：
//     1、使用时缓存的话，每次都需要检查是否为NULL，即是否已缓存。
//     2、ID在类被卸载时就会失效，所以必须确保本地代码依赖该ID值，那么该类不被卸载。如果缓存发生在类静态初始化时，当类被卸载或重新加载时，ID会被重新计算。
//     */
//    public native void cacheFieldId();
//    private static native void initIds();
//    public native void staticCache();
//    /**
//     * A native method that is implemented by the 'native-lib' native library,
//     * which is packaged with this application.
//     */
//    public native String stringFromJNI();
    public native String stringGetNumber(int x, int y);
  //  public native int addFromJni(int x,int y);

}
