//
// Created by cvrain on 23-8-18.
//

#include "account.hpp"

namespace Models{
    bsoncxx::document::view Account::to_document() {
        using bsoncxx::builder::basic::kvp;
        using bsoncxx::builder::basic::make_document;

        bsoncxx::builder::basic::document doc{};

        doc.append(kvp("_id", id));
        doc.append(kvp("name", name));
        doc.append(kvp("password", password));

        return doc.view();
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
    }
}