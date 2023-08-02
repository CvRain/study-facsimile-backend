//
// Created by cvrain on 23-8-2.
//

#ifndef STUDY_FACSIMILE_SETTING_SERVICE_HPP
#define STUDY_FACSIMILE_SETTING_SERVICE_HPP

#include <json/json.h>
#include <loguru/loguru.hpp>
#include <fstream>
#include <filesystem>
#include <string>
#include <optional>

namespace Services {

    using MongoLinkStruct = struct MongoLinkStruct {
        std::string host = "localhost";
        std::string port = "27017";
        std::string user = "admin";
        std::string password = "admin";

        [[nodiscard]] std::string to_string() const {
            return "mongodb://" + user + ":" + password + "@" + host + ":" + port;
        }
    };

    using ServerSettingStruct = struct ServerSettingStruct {
        std::string host = "127.0.0.1";
        int listen = 5280;
    };

    using ServerTotalSetting = struct ServerTotalSetting {
        MongoLinkStruct mongodb_setting;
        ServerSettingStruct server_setting;
    };

    class SettingService final {
    public:
        static SettingService& Create(const std::string& settingPath = "./settings.json");
        [[nodiscard]] std::optional<ServerTotalSetting> GetSetting() const;

    private:
        explicit SettingService(const std::string& settingPath = "./settings.json");

        ~SettingService() = default;

        SettingService(const SettingService &) = default;

        SettingService &operator=(const SettingService &) = default;

    private:
        std::optional<ServerTotalSetting> server_total;
    };

}


#endif //STUDY_FACSIMILE_SETTING_SERVICE_HPP
