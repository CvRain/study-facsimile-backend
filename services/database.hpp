//
// Created by cvrain on 23-8-1.
//

#ifndef STUDY_FACSIMILE_DATABASE_HPP
#define STUDY_FACSIMILE_DATABASE_HPP

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <optional>
#include <loguru/loguru.hpp>
#include <memory>
#include <string>
#include <map>

#include "setting_service.hpp"

namespace Services {
    using CollectionName = enum {
        ACCOUNT, COURSE_SETTING
    };

    static const std::map<CollectionName, std::string_view> CollectionToString{
            std::make_pair(CollectionName::ACCOUNT, "Account"),
            std::make_pair(CollectionName::COURSE_SETTING, "CourseSetting")
    };

    class MongoDatabase {
    public:
        static MongoDatabase &Create(const MongoLinkStruct &link_struct);

        std::optional<mongocxx::collection> GetClient(CollectionName collectionName);

    private:
        explicit MongoDatabase(const MongoLinkStruct &link_struct);

        ~MongoDatabase() = default;

        MongoDatabase(const MongoDatabase &) = default;

        MongoDatabase &operator=(const MongoDatabase &) = default;

    private:
        mongocxx::database database;
    };
}

#endif //STUDY_FACSIMILE_DATABASE_HPP
