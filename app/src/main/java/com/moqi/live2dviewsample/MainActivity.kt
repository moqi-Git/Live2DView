package com.moqi.live2dviewsample

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.moqi.live2dviewsample.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var vb: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        vb.live2dView.setModelAssetName("Hiyori")
    }
}