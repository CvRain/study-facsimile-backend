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
        Models::Account::Account account{
                .id = bsoncxx::oid{},
                .name = "Unknown",
                .password = "qwe123",
                .nbt = {}
        };
        try {
            using bsoncxx::builder::basic::kvp;
            const auto account_document = bsoncxx::builder::basic::make_document(
                    kvp("name","123"),
                    kvp("password","qwe123!@#")
                    );

            const auto result = account_collection.insert_one(account_document.view());
        }catch (const std::exception& e){
            LOG_F(ERROR, "%s", e.what());
        }
    }
}  // namespace Services
