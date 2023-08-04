//
// Created by cvrain on 23-8-1.
//

#ifndef STUDY_FACSIMILE_ACCOUNT_SERVICE_HPP
#define STUDY_FACSIMILE_ACCOUNT_SERVICE_HPP

#include <bsoncxx/json.hpp>
#include <mongocxx/collection.hpp>

#include "database.hpp"
#include "models/account.hpp"
#include "setting_service.hpp"

namespace Services {

class AccountService {
public:
    explicit AccountService();
    void CreateBlankAccount();

private:
    mongocxx::collection account_collection;
};
}  // namespace Services

#endif  // STUDY_FACSIMILE_ACCOUNT_SERVICE_HPP
