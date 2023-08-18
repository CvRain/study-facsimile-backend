#include "services/setting_service.hpp"
#include "services/account_service.hpp"
#include <drogon/drogon.h>
#include <loguru/loguru.hpp>
#include <string>
#include <csignal>

void receive_sigsegv(int sig){
    std::cout <<  "SIGSEGV: " << sig << std::endl;
    exit(-1);
}

int main(int argc, char** argv) {
    loguru::init(argc, argv);
    signal(SIGSEGV, receive_sigsegv);

    LOG_F(INFO, "Init service");

    try {
        const auto& setting_service = Services::SettingService::Create("./settings.json");
        const auto settings = setting_service.GetSetting();
        if (!settings.has_value()) {
            LOG_F(ERROR, "Init service failed: missing setting file");
            return EXIT_FAILURE;
        }

        try{
            auto account_service = Services::AccountService();
            account_service.CreateBlankAccount();
            LOG_F(INFO, "Try to create a blank account");
        }catch (const std::exception& e){
            LOG_F(ERROR, "%s", e.what());
            return EXIT_FAILURE;
        }


        drogon::app().addListener(settings.value().server_setting.host,
                                  settings.value().server_setting.listen);
        LOG_F(INFO, "Listening on port %d", settings.value().server_setting.listen);
        drogon::app().run();

    } catch (std::exception& e) {
        LOG_F(ERROR, "%s", e.what());
    }

    return EXIT_SUCCESS;
}
