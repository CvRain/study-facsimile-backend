//
// Created by cvrain on 23-8-18.
//

#include "account.hpp"

namespace Models{
    bsoncxx::builder::basic::document Account::to_document() {
        auto document = bsoncxx::builder::basic::document{};
        document.append(bsoncxx::builder::basic::kvp("_id", id));
        document.append(bsoncxx::builder::basic::kvp("name", name));
        document.append(bsoncxx::builder::basic::kvp("email", email));
        document.append(bsoncxx::builder::basic::kvp("password", password));
        return document;
    }

    void Account::from_document(const bsoncxx::document::view &document) {
        Account tempAccount;
        if(const auto element = document.find("_id"); element != document.end()){
            tempAccount.id = document["_id"].get_oid().value;
        }else{
            LOG_F(ERROR, "Account::from_document: _id not found");
            return;
        }

        if(const auto element = document.find("name"); element != document.end()){
            tempAccount.name = document["name"].get_string();
        }else{
            LOG_F(ERROR, "Account::from_document: name not found");
            return;
        }

        if(const auto element = document.find("password"); element != document.end()){
            tempAccount.password = document["password"].get_string();
        }else{
            LOG_F(ERROR, "Account::from_document: password not found");
            return;
        }

        if(const auto element = document.find("email"); element != document.end()){
            tempAccount.email = document["email"].get_string();
        }else{
            LOG_F(ERROR, "Account::from_document: email not found");
            return;
        }

        this->id = tempAccount.id;
        this->name = tempAccount.name;
        this->password = tempAccount.password;
        this->email = tempAccount.email;
    }

    Account::Account(const Account &account)
        : id(account.id), name(account.name), password(account.password), email(account.email) {

    }

    Account Account::operator=(const Account &account) {
        return account;
    }
}