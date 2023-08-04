//
// Created by cvrain on 23-8-1.
//

#ifndef STUDY_FACSIMILE_DATABASE_HPP
#define STUDY_FACSIMILE_DATABASE_HPP

#include <bsoncxx/json.hpp>
#include <loguru/loguru.hpp>
#include <map>
#include <memory>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <optional>
#include <string>

#include "setting_service.hpp"

namespace Services {
    using CollectionName = enum CollectionName {
        ACCOUNT, COURSE_SETTING
    };

    static const std::map<CollectionName, std::string_view> CollectionToString{
            std::make_pair(CollectionName::ACCOUNT, "Account"),
            std::make_pair(CollectionName::COURSE_SETTING, "CourseSetting")};

    class MongoDatabase {
    public:
        static MongoDatabase &Create(const MongoLinkStruct &link_struct);

        std::optional<mongocxx::collection> GetClient(CollectionName collectionName);

    private:
        explicit MongoDatabase(const MongoLinkStruct &link_struct);

        ~MongoDatabase() = default;

        MongoDatabase(const MongoDatabase &) = delete;

        MongoDatabase &operator=(const MongoDatabase &) = delete;

    private:
        mongocxx::instance instance{};
        mongocxx::client client;
        mongocxx::database database;
    };
}  // namespace Services

#endif  // STUDY_FACSIMILE_DATABASE_HPP
