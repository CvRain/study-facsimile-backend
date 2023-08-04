//
// Created by cvrain on 23-8-1.
//

#include "account_service.hpp"

namespace Services {
    AccountService::AccountService() {
        const auto &settings = SettingService::Create();
        auto &database = MongoDatabase::Create(settings.GetSetting().value().mongodb_setting);
        if (const auto collection = database.GetClient(CollectionName::ACCOUNT); collection.has_value()) {
            account_collection = collection.value();
        }
    }

    void AccountService::CreateBlankAccount() {
        Models::Account::Account account{
                .id = {},
                .name = "Unknown",
                .password = "qwe123",
                .nbt = {}
        };
        const auto result = account_collection.insert_one(account.to_document());
    }
}  // namespace Services
