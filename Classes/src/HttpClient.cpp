//
// Created by osum4est on 8/13/17.
//

#include <iostream>
#include <src/objects/definitions/GameObjectDefinition.h>
#include "HttpClient.h"
#include <json.hpp>
#include <src/util/Utils.h>

using namespace nlohmann;

// TODO: Use callbacks somehow
void HttpClient::getFile(std::string filename, LevelLoader* loader) {
    this->loader = loader;

    network::HttpRequest* request = new network::HttpRequest();
    request->setUrl("http://lb.8bitforest.com/get_file/" + filename + "/");
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(HttpClient::httpResponseCallback, this));
    request->setTag("GET remotelevel");
    network::HttpClient::getInstance()->send(request);
    request->release();
}

void HttpClient::httpResponseCallback(network::HttpClient *sender, network::HttpResponse *response) {

    auto buffer = response->getResponseData();
    std::string responseString = "";
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        responseString += (*buffer)[i];
    }
    auto responseJson = json::parse(responseString);

    loader->remoteLevelLoaded(Utils::split(responseJson["file"], '\n'));
}