#include "HelloWorld.hpp"

void HelloWorld::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    const auto now = std::chrono::system_clock::now();
    const auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    const auto value = now_ms.time_since_epoch();
    const long duration = value.count();

    Json::Value result{};
    result["action"] = "hello";
    result["status"] = 200;
    result["description"] = "hello world! " + std::to_string(duration);
    const auto response = HttpResponse::newHttpJsonResponse(result);
    callback(response);
}
