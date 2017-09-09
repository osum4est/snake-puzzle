package com.eightbitforest.snakepuzzle.network;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Net;
import com.badlogic.gdx.utils.JsonReader;
import com.badlogic.gdx.utils.JsonValue;
import com.eightbitforest.snakepuzzle.utils.ICallback;

public class HttpClient {
    public static void getLevel(String filename, ICallback<String> callback) {
        Net.HttpRequest request = new Net.HttpRequest(Net.HttpMethods.GET);
        request.setUrl("http://lb.8bitforest.com/get_file/" + filename + "/");
        System.out.println("Getting: " + request.getUrl());

        Gdx.net.sendHttpRequest(request, new Net.HttpResponseListener() {
            @Override
            public void handleHttpResponse(Net.HttpResponse httpResponse) {
                JsonValue json = new JsonReader().parse(httpResponse.getResultAsString());
                Gdx.app.postRunnable(() ->
                        callback.callback(json.getString("file"))
                );
            }

            @Override
            public void failed(Throwable t) {
                System.out.println(t.toString());
            }

            @Override
            public void cancelled() {

            }
        });
    }
}
