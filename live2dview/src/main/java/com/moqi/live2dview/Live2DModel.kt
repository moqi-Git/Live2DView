package com.moqi.live2dview

import android.content.Context
import android.util.Log
import java.io.File
import java.io.FileInputStream
import java.io.InputStream
import java.lang.Exception

class Live2DModel private constructor(
    private val context: Context,
    private val modelDir: String,
    private val isAsset: Boolean
) {

    private var modelId = -1

    init {
        val modelConfigName = modelDir.split("/").last() + ".model3.json"
        Log.e("asdfg", "modelConfigName = $modelConfigName")
        val modelConfigJson = loadFile(modelConfigName)
        if (modelConfigJson != null){
            modelId = createModel(modelConfigJson, modelConfigJson.size)
        } else {
            throw IllegalArgumentException("wrong model")
        }
    }



    fun release(){
        releaseModel(modelId)
    }

    // *** *** *** ***

    fun loadFile(fileName: String): ByteArray? {
        var inputStream: InputStream? = null
        try {
            if (isAsset) {
                Log.e("asdfg", "asset name = $fileName")
                inputStream = context.assets.open("$modelDir/$fileName")
            } else {
                inputStream = FileInputStream(File("$modelDir/$fileName"))
            }
            val fileSize = inputStream.available()
            val buffer = ByteArray(fileSize)
            inputStream.read(buffer, 0, fileSize)
            return buffer
        } catch (e: Exception){
            return null
        } finally {
            inputStream?.close()
        }
    }

    external fun createModel(modelConfigJson: ByteArray, bufferSize: Int): Int

    external fun releaseModel(modelId: Int)

    companion object {
        @JvmStatic
        fun createFormAsset(context: Context, assetName: String): Live2DModel {
            return Live2DModel(context, assetName, true)
        }

        @JvmStatic
        fun createFormFile(context: Context, filePath: String): Live2DModel {
            return Live2DModel(context, filePath, false)
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