#include <iostream>
#include "SPDLogger.h"
#include "LoggerPool.hpp"
#include "thread2_write_cam.hpp"
#include <future>
#include <atomic>
int main(){

    
    // Init logger
    bool stdout = true;
	unsigned char log_target_bitmask = LOG_TARGET_ROTATE;
	if (stdout) {
		log_target_bitmask |= LOG_TARGET_CONSOLE;
	}
    bool debug = true;
    ELogLevel log_level = LOG_LEVEL_INFO;
        if (debug) {
        log_level = LOG_LEVEL_DEBUG;
        }

    std::string APP_ID = "_test_logger";
    ILogger* app_logger;
    app_logger = new SPDLogger("app"+APP_ID, "main", "./output/" + APP_ID + ".log",
                               log_target_bitmask, log_level);
    
    std::unordered_map<std::string, ILogger*> cam_logger;
    std::string moduleid = "cam_test_logger";
    cam_logger[moduleid] = new SPDLogger("app" + APP_ID, moduleid, "./output/" + moduleid + ".log",
                                      log_target_bitmask, log_level);

    app_logger->info("Starting app...");
    cam_logger[moduleid]->info("Starting cam  %d...", 0);


    LoggerPool* logger_pool;
    logger_pool = LoggerPool::getInstance();

    logger_pool->add_logger_module("app"+APP_ID, "module1", "./output/" + moduleid + ".log",
                                      log_target_bitmask, log_level);

    logger_pool->add_logger_module("app"+APP_ID, "module2", "./output/" + moduleid + ".log",
                                      log_target_bitmask, log_level);

    auto loggers = logger_pool->get_loggers();
    std::cout << "number of loggers in main: " << loggers.size() << std::endl;

   
    std::vector<std::future<void>> logger_thread;
    for(int i = 0; i < 100; ++i){
        auto result = std::async(std::launch::async, write_log, i);
        logger_thread.emplace_back(std::move(result));
    }
    for(int i = 0; i < 100; ++i){
        logger_thread[i].get();
    }
    std::cout << "done\n";
    
    return 0;
}
