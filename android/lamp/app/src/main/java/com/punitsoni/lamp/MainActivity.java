package com.punitsoni.lamp;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.webkit.WebSettings;
import android.webkit.WebView;


public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        WebView w = (WebView) findViewById(R.id.webView);

        WebSettings webSettings = w.getSettings();
        webSettings.setJavaScriptEnabled(true);

        w.loadUrl("file:///android_asset/index.html");
    }
}

