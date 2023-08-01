#pragma once

#include <drogon/HttpSimpleController.h>
#include <json/json.h>
#include <chrono>

using namespace drogon;

class [[maybe_unused]] HelloWorld final : public drogon::HttpSimpleController<HelloWorld>
{
  public:
    void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
        PATH_ADD("/", Get, Post);
        PATH_ADD("/hello", Get, Post);
    PATH_LIST_END
};
