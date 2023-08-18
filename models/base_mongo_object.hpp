//
// Created by cvrain on 23-8-18.
//

#pragma once

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>

namespace Models{
    class BaseMongoObject{
    public:
        virtual bsoncxx::document::view to_document() = 0;
        virtual void from_document(const bsoncxx::document::view& document) = 0;
        virtual ~BaseMongoObject() = default;
    };
}