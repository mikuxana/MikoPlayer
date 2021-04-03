package com.xana.media.mikoplayer;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceView;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private MkPlayer mkPlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SurfaceView surfaceView =  findViewById(R.id.sv_palyer);


        mkPlayer = new MkPlayer();
        mkPlayer.setView(surfaceView);
        mkPlayer.setUrl("http://1251316161.vod2.myqcloud.com/007a649dvodcq1251316161/8c3785775285890808198017973/g33AvJvA1mEA.mp4");
        mkPlayer.setPrepareListener(new MkPlayer.PrepareListener() {
            @Override
            public void onPrepare() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(MainActivity.this, "可以开始播放了", Toast.LENGTH_SHORT).show();
                    }
                });
                mkPlayer.start();
            }
        });
    }

    public void onPlay(View view) {
        mkPlayer.prepare();
    }
}
