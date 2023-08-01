#include "database.hpp"

Services::MongoDatabase::MongoDatabase(const Services::MongoLinkStruct &link_struct) {
    const auto instance = mongocxx::instance{};
    const auto url = mongocxx::uri{link_struct.to_string()};
    mongocxx::client client{url};

    if (!client) {
        LOG_F(FATAL, "Connect to MongoDB failed");
        return;
    }
    LOG_F(INFO, "Connect to MongoDB successfully");

    for (const auto &it: client.list_database_names()) {
        LOG_F(INFO, "Find database: %s", it.data());
    }

    database = client.database("StudyFacsimile");
}

std::optional<mongocxx::collection> Services::MongoDatabase::GetClient(Services::CollectionName collectionName) {
    if (Services::CollectionToString.find(collectionName) == Services::CollectionToString.end()) {
        LOG_F(FATAL, "Collection name not found");
        return std::nullopt;
    }

    const auto name = CollectionToString.at(collectionName);
    LOG_F(INFO, "MongoDatabase::GetClient: %s", name.data());
    return database.collection(name);
}
