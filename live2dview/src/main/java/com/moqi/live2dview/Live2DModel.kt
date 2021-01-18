package com.moqi.live2dview

class Live2DModel private constructor(private val modelDir: String, private val isAsset: Boolean){



    external fun getLive2DModelInfo(buffer: ByteArray): Live2DModelInfo

    companion object{
        @JvmStatic
        fun createFormAsset(assetName: String): Live2DModel{
            return Live2DModel(assetName, true)
        }

        @JvmStatic
        fun createFormFile(filePath: String): Live2DModel{
            return Live2DModel(filePath, false)
        }

        // JNI 初始化
        private val LIBRARY_NAME = "live2dview"
        init {
            System.loadLibrary(LIBRARY_NAME)
        }
    }


    /**
     * 模型信息，从 *.model3.json 读取
     * 为保证和数据解析和 SDK 中的 CubismModelSettingJson，这个对象要经由 native 层创建
     */
    data class Live2DModelInfo(
        val name: String,
    )
}