//
// Created by cvrain on 23-8-2.
//

#include "setting_service.hpp"


namespace Services {

    SettingService &SettingService::Create(const std::string &settingPath) {
        static auto singleton_instance = SettingService(settingPath);
        return singleton_instance;
    }

    std::optional<ServerTotalSetting> SettingService::GetSetting() const {
        if (!server_total.has_value()) {
            LOG_F(WARNING, "Server total is empty");
        }
        return server_total;
    }

    SettingService::SettingService(const std::string &settingPath) : server_total{} {
        const std::filesystem::path setting_path{settingPath};
        //check settings file exist
        if (!std::filesystem::exists(setting_path)) {

            Json::Value mongodb_setting{};
            mongodb_setting["host"] = "127.0.0.1";
            mongodb_setting["port"] = "27017";
            mongodb_setting["user"] = "admin";
            mongodb_setting["password"] = "admin";

            Json::Value server_setting{};
            server_setting["host"] = "127.0.0.1";
            server_setting["listen"] = 5280;

            Json::Value value{};
            value["server"] = server_setting;
            value["mongodb"] = mongodb_setting;

            std::ofstream file_writer(setting_path, std::ios::out | std::ios::binary);
            if (!file_writer.is_open()) {
                LOG_F(ERROR, "Could not create setting file");
                return;
            }
            file_writer << value.toStyledString();
            LOG_F(INFO, "Create default setting file");
            file_writer.close();
        }

        //load settings.json
        std::ifstream file_reader(setting_path, std::ios::in | std::ios::binary);
        if (!file_reader.is_open()) {
            LOG_F(ERROR, "Cloud not op setting.json");
            return;
        }
        std::stringstream read_buffer{};
        read_buffer << file_reader.rdbuf();

        Json::Reader setting_reader{};
        Json::Value root{};

        if (!setting_reader.parse(read_buffer.str(), root)) {
            LOG_F(ERROR, "Could not parse setting file");
            return;
        }

        const auto mongo_setting = root["mongodb"];
        const auto server_setting = root["server"];

        const auto mongodb_setting = MongoLinkStruct{
                .host = mongo_setting["host"].asString(),
                .port = mongo_setting["port"].asString(),
                .user = mongo_setting["user"].asString(),
                .password = mongo_setting["password"].asString()
        };

        const auto server_config = ServerSettingStruct{
                .host = server_setting["host"].asString(),
                .listen =  server_setting["listen"].asInt()
        };

        server_total = std::make_optional<ServerTotalSetting>({
            .mongodb_setting = mongodb_setting,
            .server_setting = server_config
        });
    }
}
