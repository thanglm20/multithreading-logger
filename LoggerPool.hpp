
#ifndef LoggerPool_hpp
#define LoggerPool_hpp

#include <queue>
#include <unordered_map>
#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <memory>

#include "SPDLogger.h"

class LogWorker{
private:
    std::shared_ptr<ILogger> m_logger;
    std::queue<std::pair<std::string, std::string>> m_logs_queue;
    std::thread m_worker;
    std::mutex m_mutex;
    bool m_is_running = true;
public:
    explicit LogWorker(const std::string &strAppName,
        const std::string &strModuleName,
		const std::string &strFilePath,
		unsigned char eLogTargetFlag,
        ELogLevel eLogLevel)
        :
        m_logger(std::make_shared<SPDLogger>(strAppName, strModuleName, 
                                            strFilePath, eLogTargetFlag, eLogLevel))
        {
            m_worker = std::thread(process_log, this);
            m_worker.detach();
            
        }
        ~LogWorker(){
            m_is_running = false;
            if(m_worker.joinable()){
                m_worker.join();
            }
        }
        static void process_log(LogWorker* log_worker){
            while(log_worker->m_is_running){
                if(!log_worker->m_logs_queue.empty()){
                    std::lock_guard<std::mutex> lk(log_worker->m_mutex);
                    auto log = log_worker->m_logs_queue.front();
                    if(log.first == "info"){
                        log_worker->m_logger->info(log.second);
                    }
                    else if(log.first == "debug"){
                            log_worker->m_logger->debug(log.second);
                    }
                    else if(log.first == "warn"){
                        log_worker->m_logger->warn(log.second);
                    }
                    else if(log.first == "error"){
                        log_worker->m_logger->error(log.second);
                    }
                    log_worker->m_logs_queue.pop();
                }
                
            }
        }
        
        template<typename ... Args>
        void info(const std::string &msg, Args ... args) {
            info(string_format(msg, args ...));        
        }
        void info(const std::string &strMessage){
            std::lock_guard<std::mutex> lk(m_mutex);
            m_logs_queue.push({"info", strMessage});
        }

        template<typename ... Args>
        void warn(const std::string &msg, Args ... args) {
            warn(string_format(msg, args ...));        
        }
        void warn(const std::string &strMessage){
            std::lock_guard<std::mutex> lk(m_mutex);
            m_logs_queue.push({"warn", strMessage});
        }

        template<typename ... Args>
        void debug(const std::string &msg, Args ... args) {
            debug(string_format(msg, args ...));        
        }
        void debug(const std::string &strMessage){
            std::lock_guard<std::mutex> lk(m_mutex);
            m_logs_queue.push({"debug", strMessage});
        }

        template<typename ... Args>
        void error(const std::string &msg, Args ... args) {
            error(string_format(msg, args ...));        
        }
        void error(const std::string &strMessage){
            std::lock_guard<std::mutex> lk(m_mutex);
            m_logs_queue.push({"error", strMessage});
        }
        
};


class LoggerPool{
private:
    std::unordered_map<std::string, std::shared_ptr<LogWorker>> m_list_loggers;
    LoggerPool();
    ~LoggerPool();
public:
    static LoggerPool* m_instance;
    static std::mutex m_mutex;
    static LoggerPool* getInstance();
    static void deleteInstance();
    void add_logger_module(const std::string &strAppName,
        const std::string &strModuleName,
		const std::string &strFilePath,
		unsigned char eLogTargetFlag,
        ELogLevel eLogLevel){
            m_list_loggers[strModuleName] = std::make_shared<LogWorker>(strAppName, strModuleName, 
                                             strFilePath, eLogTargetFlag, eLogLevel);
        }
    std::unordered_map<std::string, std::shared_ptr<LogWorker>> get_loggers(){
        return m_instance->m_list_loggers;
    }
    std::shared_ptr<LogWorker> operator[](const std::string& strModuleName){
        return m_instance->m_list_loggers[strModuleName]; 
    }
};



#endif