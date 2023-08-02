#include <drogon/drogon.h>
#include <loguru/loguru.hpp>
#include <string>
#include "services/setting_service.hpp"

int main(int argc, char** argv) {
    loguru::init(argc, argv);
    LOG_F(INFO ,"Init service");

    try {
        const auto& setting_service = Services::SettingService::Create("./settings.json");
        const auto settings = setting_service.GetSetting();
        if(!settings.has_value()){
            LOG_F(ERROR, "Init service failed: missing setting file");
            return EXIT_FAILURE;
        }

        drogon::app().addListener(settings.value().server_setting.host, settings.value().server_setting.listen);
        LOG_F(INFO, "Listening on port %d", settings.value().server_setting.listen);
        drogon::app().run();

    }catch (std::exception& e){
        LOG_F(ERROR, "%s", e.what());
    }

    return EXIT_SUCCESS;
}
