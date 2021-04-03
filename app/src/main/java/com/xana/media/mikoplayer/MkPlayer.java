package com.xana.media.mikoplayer;

import android.os.Debug;
import android.support.annotation.NonNull;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class MkPlayer implements SurfaceHolder.Callback {
    static {
        System.loadLibrary("native-lib");
    }

    private String url;

    private SurfaceHolder holder;
    private PrepareListener listener;

    /**
     * 设置文件或者直播地址
     */
    public void setUrl(String url){
        this.url = url;
    }
    public void start(){
        cppStart();
    }
    public void stop(){

    }
    public void release(){
        holder.removeCallback(this);
    }

    /**
     * 设置画布
     * @param surfaceView
     */
    public void setView(SurfaceView surfaceView) {
        holder = surfaceView.getHolder();
        holder.addCallback(this);
    }

    /**
     * 预处理
     */
    public void prepare() {
        cppPrepare(this.url);
    }


    public void onFail(int code){

    }

    public void onSuccess(){

    }

    public void onPrepare(){
        if(listener!=null)
            listener.onPrepare();
    }


    public void setPrepareListener(PrepareListener listener){
        this.listener = listener;
    }


    public interface PrepareListener{
        void onPrepare();
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {

    }

    /**
     * 画布发生变化
     * 横竖屏切换 / 按home键
     * @param holder
     * @param format
     * @param width
     * @param height
     */
    @Override
    public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int width, int height) {

    }

    /**
     *  画布不可见时
     * @param holder
     */
    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder holder) {

    }


    native void cppPrepare(String url);
    native void cppStart();
}
