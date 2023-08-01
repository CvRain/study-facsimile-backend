#include <drogon/drogon.h>
#include <loguru/loguru.hpp>
#include <json/json.h>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include "services/database.hpp"

int main(int argc, char** argv) {
    loguru::init(argc, argv);
    LOG_F(INFO ,"Init service");

    const std::filesystem::path setting_path{"./settings.json"};
    //check settings file exist
    if(!std::filesystem::exists(setting_path)){

        Json::Value mongodb_setting{};
        mongodb_setting["host"] = "127.0.0.1";
        mongodb_setting["port"] = "27017";
        mongodb_setting["user"] = "admin";
        mongodb_setting["password"] = "admin";

        Json::Value server_setting{};
        server_setting["host"] = "127.0.0.1";
        server_setting["listen"] = 5280;

        Json::Value server_total{};
        server_total["server"] = server_setting;
        server_total["mongodb"] = mongodb_setting;

        std::ofstream file_writer(setting_path, std::ios::out | std::ios::binary);
        if(!file_writer.is_open()){
            LOG_F(ERROR, "Could not create setting file");
            return EXIT_FAILURE;
        }
        file_writer << server_total.toStyledString();
        LOG_F(INFO, "Create default setting file");
        file_writer.close();
    }

    //load settings.json
    std::ifstream file_reader(setting_path, std::ios::in | std::ios::binary);
    if(!file_reader.is_open()){
        LOG_F(ERROR, "Cloud not op setting.json");
        return EXIT_FAILURE;
    }
    std::stringstream read_buffer{};
    read_buffer << file_reader.rdbuf();

    Json::Reader setting_reader{};
    Json::Value server_total{};

    if(!setting_reader.parse(read_buffer.str(), server_total)){
        LOG_F(ERROR, "Could not parse setting file");
        return EXIT_FAILURE;
    }

    const auto mongo_setting = server_total["mongodb"];
    const auto server_setting = server_total["server"];

    const auto mongo_host = mongo_setting["host"].asString();
    const auto mongo_port = mongo_setting["port"].asString();
    const auto mongo_user = mongo_setting["user"].asString();
    const auto mongo_password = mongo_setting["password"].asString();

    const Services::MongoLinkStruct link_struct{
        .host = mongo_host,
        .port = mongo_port,
        .user = mongo_user,
        .password = mongo_password
    };
    Services::MongoDatabase mongo_database{link_struct};

    const auto server_host = server_setting["host"].asString();
    const auto server_listen = server_setting["listen"].asInt();

    drogon::app().addListener(server_host,server_listen);
    LOG_F(INFO, "Listening on port %d", server_listen);
    drogon::app().run();
    return 0;
}
