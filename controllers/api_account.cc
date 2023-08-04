//
// Created by cvrain on 23-8-4.
//

#include "api_account.hpp"

using namespace Api;

void AccountController::create_blank_account(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    LOG_F(INFO, "AccountController::create_blank_account");
//    try {
//        Services::AccountService::Create().CreateBlankAccount();
//    }catch (const std::exception& e){
//        LOG_F(ERROR, "AccountController::create_blank");
//        LOG_F(ERROR, "%s", e.what());
//    }

    Json::Value result{};
    result["action"] = "Account::Create";
    result["status"] = 200;
    result["description"] = "create a blank account";
    const auto response = HttpResponse::newHttpJsonResponse(result);
    callback(response);
}
