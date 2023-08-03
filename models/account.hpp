#pragma once

#include <mongocxx/collection.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <string>
#include <map>
#include <vector>

namespace Models::Account {
    using Account = struct Account {
        bsoncxx::oid id;
        std::string name;
        std::string password;
        std::map<std::string, std::vector<std::string>> nbt;

        bsoncxx::document::view to_document() {
            using bsoncxx::builder::basic::kvp;
            using bsoncxx::builder::stream::document;
            using bsoncxx::builder::stream::finalize;
            using bsoncxx::builder::stream::open_document;
            using bsoncxx::builder::stream::close_document;

            bsoncxx::builder::stream::document doc{};

            doc << "_id" << id
                << "name" << name
                << "password" << password;

            for (const auto& [key, value] : nbt) {
                doc << key << open_document;
                for (const auto& v : value) {
                    doc << v << true;
                }
                doc << close_document;
            }
            const auto bson = doc << finalize;
            return bson.view();
        }
    };
}

