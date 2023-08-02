#pragma once

#include <mongocxx/collection.hpp>
#include <string>
#include <map>
#include <vector>

namespace Models::Account{
    using Account = struct Account{
        std::string id;
        std::string name;
        std::string password;
        std::map<std::string, std::vector<std::string>> nbt;
    };
}

