//
// Created by osum4est on 8/13/17.
//

#ifndef SNAKE_PUZZLE_HTTPCLIENT_H
#define SNAKE_PUZZLE_HTTPCLIENT_H

#include <cocos2d.h>
#include <network/HttpClient.h>
#include "LevelLoader.h"

USING_NS_CC;

class HttpClient {
public:
    void getFile(std::string filename, LevelLoader* loader);
    void httpResponseCallback(network::HttpClient *sender, network::HttpResponse *response);

private:
    LevelLoader* loader;
};


#endif //SNAKE_PUZZLE_HTTPCLIENT_H
