

#include "LoggerPool.hpp"


LoggerPool::LoggerPool(){

}
LoggerPool::~LoggerPool(){
    
}

LoggerPool* LoggerPool::getInstance()
{
    
    m_mutex.lock();
    if(m_instance == nullptr)
    {
        std::cout << "Create new object LoggerPool successfully" << std::endl;
        m_instance = new LoggerPool();
    }
    else
        std::cout << "Existing object LoggerPool, return it" << std::endl;
    m_mutex.unlock();
    return m_instance;
}

void LoggerPool::deleteInstance()
{
    if(m_instance) delete m_instance;
}

std::mutex LoggerPool::m_mutex ;
LoggerPool* LoggerPool::m_instance = nullptr; 
