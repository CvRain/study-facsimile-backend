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

namespace Services {
    using MongoLinkStruct = struct MongoLinkStruct {
        std::string host = "localhost";
        std::string port = "27017";
        std::string user = "admin";
        std::string password = "admin";

        [[nodiscard]] std::string to_string() const{
            return "mongodb://" + user + ":" + password + "@" + host + ":" + port;
        }

    };

    using CollectionName = enum{
        ACCOUNT,COURSE_SETTING
    };

    static const std::map<CollectionName, std::string_view> CollectionToString{
        std::make_pair(CollectionName::ACCOUNT, "Account"),
        std::make_pair(CollectionName::COURSE_SETTING, "CourseSetting")
    };

    class MongoDatabase {
    public:
        explicit MongoDatabase(const MongoLinkStruct& link_struct);
        std::optional<mongocxx::collection> GetClient(CollectionName collectionName);
    private:
        mongocxx::database database;
    };
}

#endif //STUDY_FACSIMILE_DATABASE_HPP
