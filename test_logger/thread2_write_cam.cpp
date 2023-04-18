
#ifndef thread_write_cam_hpp
#define thread_write_cam_hpp

#include <iostream>
#include "LoggerPool.hpp"



LoggerPool* logger_pool = LoggerPool::getInstance();
auto loggers = logger_pool->get_loggers();


void write_log(int thread_id)
{
    
    for(int i = 0; i < 10; ++i){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        logger_pool->get_loggers()["cam_pool_0"]->info("Thread %d is writing log %d...", thread_id, i);
    }
}

#endif