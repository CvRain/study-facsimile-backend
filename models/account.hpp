#pragma once

#include "base_mongo_object.hpp"

#include <mongocxx/collection.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <loguru/loguru.hpp>

#include <string>
#include <map>
#include <vector>

namespace Models {
    class Account{
    public:
        Account() = default;
        Account(const Account& account);
        Account operator =  (const Account& account);
        bsoncxx::oid id{};
        std::string name;
        std::string password;
        std::string email;
        bsoncxx::builder::basic::document to_document();
        void from_document(const bsoncxx::document::view& document);
    };
}

