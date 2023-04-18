#ifndef __SPDLOGGER_H__
#define __SPDLOGGER_H__

#include "ILogger.h"
#include "spdlog/spdlog.h"

class SPDLogger : public ILogger {
public:
	SPDLogger(const std::string &strAppName = "",
            const std::string &strModuleName = "",
			const std::string &strFilePath = "",
			unsigned char eLogTargetFlag = LOG_TARGET_NONE,
            ELogLevel eLogLevel = LOG_LEVEL_WARNING);
    
    virtual void info(const std::string &strMessage) override;    
    virtual void warn(const std::string &strMessage) override;    
    virtual void error(const std::string &strMessage) override;    
    virtual void debug(const std::string &strMessage) override;    
    virtual void update_level(bool debug, bool console) override;

private:
    std::shared_ptr<spdlog::logger> m_pLogger;
    std::string app_name_;
    std::string module_name_;
    bool debug_;
    bool console_;
};
#endif
