//
// Created by cvrain on 23-8-1.
//

#include "account_service.hpp"

namespace Services {
    AccountService::AccountService() {
        const auto &settings = SettingService::Create();
        LOG_F(INFO, "Start loading SettingService::Create");

        auto &database = MongoDatabase::Create(settings.GetSetting().value().mongodb_setting);
        LOG_F(INFO, "Get MongoDatabase");

        if (const auto collection = database.GetClient(CollectionName::ACCOUNT); collection.has_value()) {
            account_collection = collection.value();
        }else{
            LOG_F(ERROR, "Couldn't get account collection");
            return;
        }
    }

    AccountService &AccountService::Create() {
        static auto singleton  = AccountService();
        return singleton;
    }

    void AccountService::CreateBlankAccount() {
        auto account = new Models::Account();
        account->id = bsoncxx::oid{};
        account->name = "Default user";
        account->password = "qwe123";

        try {
            const auto view = account->to_document();
            std::cout << view.find("name")->get_string().value << std::endl;
            //LOG_F(INFO, "Account: %s", view["name"].get_string().value);
            const auto result = account_collection.insert_one(view);
        }catch (const std::exception& e){
            LOG_F(ERROR, "%s", e.what());
        }
    }
}  // namespace Services
