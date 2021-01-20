package com.moqi.live2dview

class JNIBridge {

    companion object{
        private val LIBRARY_NAME = "live2dview"

        init {
            System.loadLibrary(LIBRARY_NAME)
        }

//        @JvmStatic
//        external fun nativeOnSurfaceCreated()
//
//        @JvmStatic
//        external fun nativeOnSurfaceChanged(width: Int, height: Int)
//
//        @JvmStatic
//        external fun nativeOnDrawFrame()
//
//        @JvmStatic
//        external fun onTouchDown(pointX: Float, pointY: Float)
//
//        @JvmStatic
//        external fun onTouchUp(pointX: Float, pointY: Float)
//
//        @JvmStatic
//        external fun onTouchMove(pointX: Float, pointY: Float)
    }


}