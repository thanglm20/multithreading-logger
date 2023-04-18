#ifndef __ILOGGER_H__
#define __ILOGGER_H__

#include <memory>
#include <string>
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "LogUtil.h"
#include "string_utils.h"

enum ELogTargetFlag {
	LOG_TARGET_NONE = 0x000,
	LOG_TARGET_CONSOLE = 0x001,
	LOG_TARGET_ROTATE = 0x010
};

enum ELogLevel {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_DEBUG
};

class ILogger {
public:
	ILogger(const std::string &strName = "",
			const std::string &strFilePath = "",
			unsigned char eLogTargetFlag = LOG_TARGET_NONE,
            ELogLevel eLogLevel = LOG_LEVEL_WARNING);
    
    template<typename ... Args>
    void info(const std::string &msg, Args ... args) {
        info(string_format(msg, args ...));        
    }
    virtual void info(const std::string &strMessage) = 0;    
    
    template<typename ... Args>
    void warn(const std::string &msg, Args ... args) {
        warn(string_format(msg, args ...));        
    }
    virtual void warn(const std::string &strMessage) = 0;    
    
    template<typename ... Args>
    void error(const std::string &msg, Args ... args) {
        error(string_format(msg, args ...));        
    }
    virtual void error(const std::string &strMessage) = 0;    
    
    template<typename ... Args>
    void debug(const std::string &msg, Args ... args) {
        debug(string_format(msg, args ...));        
    }
    virtual void debug(const std::string &strMessage) = 0;    

    virtual void update_level(bool debug, bool console) = 0;

protected:
	std::string m_strName;
	std::string m_strLogFilepath;
	unsigned char m_eDefaultTargetFlag;
    ELogLevel m_eLogLevel;
};

#endif
