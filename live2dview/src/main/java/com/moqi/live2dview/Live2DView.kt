package com.moqi.live2dview

import android.annotation.SuppressLint
import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.view.MotionEvent
import android.view.ViewGroup
import android.widget.FrameLayout
import android.widget.Toast
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class Live2DView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : FrameLayout(context, attrs, defStyleAttr) {

    private val surfaceView = GLSurfaceView(context)
    private val renderer = object: GLSurfaceView.Renderer{
        override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
            JNIBridge.nativeOnSurfaceCreated()
        }

        override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
            JNIBridge.nativeOnSurfaceChanged(width, height)
        }

        override fun onDrawFrame(gl: GL10?) {
            JNIBridge.nativeOnDrawFrame()
        }
    }

    private var model: Live2DModel? = null


    init {
        surfaceView.setRenderer(renderer)
        addView(surfaceView, LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT))
    }

//    fun setModelPath(filePath: String){
//
//
//    }

    fun setModelAssetName(assetName: String){
        if (model != null){
//            model.release()
        }

        model = Live2DModel.createFormAsset(context, assetName)
        if (model == null){
            // todo: 处理模型加载失败的问题，看看是在createFormAsset抛出异常还是在这里报错？
            onLoadModelError("错误信息？")
        }
        // 设置后需要更新，应该可以在 onDrawFrame 里进行测试
    }

    private fun onLoadModelError(errorMsg: String){
        // fixme
        Toast.makeText(context, errorMsg, Toast.LENGTH_SHORT).show()
    }

    @SuppressLint("ClickableViewAccessibility")
    override fun onTouchEvent(event: MotionEvent?): Boolean {
        val x = event?.x?:0f
        val y = event?.y?:0f
        when(event?.actionMasked){
            MotionEvent.ACTION_DOWN -> {
                JNIBridge.onTouchDown(x, y)
            }
            MotionEvent.ACTION_UP -> {
                JNIBridge.onTouchUp(x, y)
            }
            MotionEvent.ACTION_MOVE -> {
                JNIBridge.onTouchMove(x, y)
            }
        }
        return super.onTouchEvent(event)
    }
}