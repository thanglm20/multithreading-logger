#include "ILogger.h"

ILogger::ILogger(const std::string &strName,
		const std::string &strFilePath,
		unsigned char eLogTargetFlag,
        ELogLevel eLogLevel)
	: m_strName(strName),
	m_strLogFilepath(strFilePath),
    m_eDefaultTargetFlag(eLogTargetFlag),
    m_eLogLevel(eLogLevel)
{}
