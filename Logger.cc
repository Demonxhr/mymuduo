#include "Logger.h"
#include <iostream>

// 获取日志唯一的实例对象
Logger &Logger::instance()
{
    static Logger logger;   //饿汉   ，c++11，局部静态变量的初始化是线程安全的 
    return logger;
}
// 设置日志级别
void Logger::setLogLevel(int level)
{
    logLevel_ = level;
}
// 写日志 [日志级别] time ： msg
void Logger::log(std::string msg)
{
    //打印日志级别
    switch (logLevel_)
    {
    case INFO:
        std::cout << "[INFO]";
        break;
    case ERROR:
        std::cout << "[ERROR]";
        break;
    case FATAL:
        std::cout << "[FATAL]";
        break;
    case DEBUG:
        std::cout << "[DEBUG]";
        break;        
    default:
        break;
    }

    //打印时间time和msg 
    std::cout << "print time" << " : " << msg << std::endl;
}