//
// Created by cvrain on 23-8-4.
//

#pragma once

#include <drogon/HttpController.h>
#include <loguru/loguru.hpp>

#include "models/account.hpp"
#include "services/account_service.hpp"

using namespace drogon;

namespace Api {
    class AccountController : public drogon::HttpController<AccountController> {
    public:
        METHOD_LIST_BEGIN
            // use METHOD_ADD to add your custom processing function here;
            // METHOD_ADD(Account::get, "/{2}/{1}", Get); // path is /Api/Account/{arg2}/{arg1}
            // METHOD_ADD(Account::your_method_name, "/{1}/{2}/list", Get); // path is /Api/Account/{arg1}/{arg2}/list
            // ADD_METHOD_TO(Account::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
            METHOD_ADD(AccountController::create_blank_account, "/create", Post);

        METHOD_LIST_END
        // your declaration of processing function maybe like this:
        // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
        // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;

        void create_blank_account(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    private:
       //std::shared_ptr<Services::AccountService> account_service;
    };
}
