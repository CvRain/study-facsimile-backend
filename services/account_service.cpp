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
        auto* account = new Models::Account();
        account->name = "Default user";
        account->password = "qwe123";
        account->email = "default@default.com";
        std::cout << account->name << std::endl;
        std::cout << account->password << std::endl;
        std::cout << account->email << std::endl;

        auto account2 = new Models::Account();
        account2->from_document(account->to_document());
        std::cout << account2->name << std::endl;
        std::cout << account2->password << std::endl;
        std::cout << account2->email << std::endl;

        try {
            const auto result = account_collection.insert_one(account->to_document().view());
        }catch (const std::exception& e){
            LOG_F(ERROR, "%s", e.what());
        }
    }
}  // namespace Services
