#include "SPDLogger.h"
#include <iostream>
#include <iomanip>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"

#define LOG_PATTERN         "[%Y-%m-%d %H:%M:%S][%l][" + app_name_ + "][" + module_name_ + "]%v"
#define MAX_LOG_FILE_SIZE   1048576 * 5
#define MAX_LOG_FILE_NUM    3

SPDLogger::SPDLogger(
        const std::string &strAppName,
        const std::string &strModuleName,
		const std::string &strFilePath,
		unsigned char eLogTargetFlag,
        ELogLevel eLogLevel)
	: ILogger(strAppName, strFilePath, eLogTargetFlag, eLogLevel),
	m_pLogger(NULL)
{
    app_name_ = strAppName;
    module_name_ = strModuleName;

	m_pLogger = std::make_shared<spdlog::logger>(m_strName , spdlog::sinks_init_list{});

	if (m_eDefaultTargetFlag & LOG_TARGET_ROTATE) {
        auto fileLog = std::make_shared<spdlog::sinks::daily_file_sink_mt>(strFilePath, 0, 0);
        fileLog->set_pattern(LOG_PATTERN);
        m_pLogger->sinks().push_back(fileLog);
    }

    console_ = false;
    if (m_eDefaultTargetFlag & LOG_TARGET_CONSOLE) {
        auto consoleLog = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleLog->set_pattern(LOG_PATTERN);
        m_pLogger->sinks().push_back(consoleLog);
        console_ = true;
    }

    debug_ = false;
    switch(eLogLevel) {
        case LOG_LEVEL_INFO: m_pLogger->set_level(spdlog::level::info); break;
        case LOG_LEVEL_WARNING: m_pLogger->set_level(spdlog::level::warn); break;
        case LOG_LEVEL_ERROR: m_pLogger->set_level(spdlog::level::err); break;
        case LOG_LEVEL_DEBUG: {
            m_pLogger->set_level(spdlog::level::debug);
            debug_ = true;
            break;
        }
    }

	spdlog::flush_every (std::chrono::seconds(5));
}

void SPDLogger::info(const std::string &strMessage) {
    m_pLogger->info(strMessage);
}

void SPDLogger::warn(const std::string &strMessage) {
    m_pLogger->warn(strMessage);
}    

void SPDLogger::error(const std::string &strMessage) {
    m_pLogger->error(strMessage);
}    

void SPDLogger::debug(const std::string &strMessage) {
    m_pLogger->debug(strMessage);
}    

void SPDLogger::update_level(bool debug, bool console) {
    if (debug != debug_) {
        std::cout << "[SPDLogger][" << app_name_ << "] Changing Log level: debug = " << debug << " ..." << std::endl;
        debug_ = debug;
        if (debug_)
            m_pLogger->set_level(spdlog::level::debug);
        else
            m_pLogger->set_level(spdlog::level::info);
    }

    if (console != console_) {
        std::cout << "[SPDLogger][" << app_name_ << "] Changing console mode: console = " << console << " ..." << std::endl;
        console_ = console;
        if (console_) {
            std::cout << "[SPDLogger][" << app_name_ << "] -- Adding console handler ..." << std::endl;
            auto consoleLog = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            consoleLog->set_pattern(LOG_PATTERN);
            m_pLogger->sinks().push_back(consoleLog);
        } else {
            std::cout << "[SPDLogger][" << app_name_ << "] -- Removing console handler ..." << std::endl;
            m_pLogger->sinks().pop_back();
        }
    }
}