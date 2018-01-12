package ndk.llh.com.ffmpegstudy;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
//D:\test\NdkDemo\ffmpeg_study\src\main\java>javah -classpath . -jni ndk.llh.com.ffmpegstudy.MainActivity

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("avcodec-57");
        System.loadLibrary("avfilter-6");
        System.loadLibrary("avformat-57");
        System.loadLibrary("avutil-55");
        System.loadLibrary("swresample-2");
        System.loadLibrary("swscale-4");
        System.loadLibrary("ffmpegdemo");
    }

    //JNI
    public native String avformatinfo();
    public native String avcodecinfo();
    public native String avfilterinfo();
    public native String configurationinfo();

    private TextView textView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.textview);
    }
    public void format(View view){
        textView.setText(avformatinfo());
    }

    public void codec(View view){
        textView.setText(avcodecinfo());
    }

    public void filter(View view){
        textView.setText(avfilterinfo());
    }

    public void config(View view){
        textView.setText(configurationinfo());
    }
}
