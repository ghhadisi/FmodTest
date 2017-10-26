package com.dbgs.fmodtest;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import java.io.File;

public class MainActivity extends AppCompatActivity {
    public static final int MODE_NORMAL = 0;
    public static final int MODE_LUOLI = 1;
    public static final int MODE_DASHU = 2;
    public static final int MODE_JINGSONG = 3;
    public static final int MODE_GAOGUAI = 4;
    public static final int MODE_KONGLING = 5;


    static{
        System.loadLibrary("fmod");
        System.loadLibrary("fmodL");
        System.loadLibrary("hssfmod-lib");
    }
    int type;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        org.fmod.FMOD.init(this);

        findViewById(R.id.tv_name).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                voice();
            }
        });
    }

     public   native void  playSound(String path,int type);

    void voice(){
        String path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "singing.wav";
        playSound(path, type++);
        if (type > MODE_KONGLING){
            type = MODE_NORMAL;
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        org.fmod.FMOD.close();
    }
}
