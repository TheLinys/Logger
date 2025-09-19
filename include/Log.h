#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include <mutex>

enum class LogLevel {
    DEBUG,
    TRACE,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class Log 
{
private:
    std::string appName;
    std::string logFilePath;
    std::ofstream logFile;
    static std::mutex logMutex;

    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }

    std::string getLevelString(LogLevel level) {
        switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
        }
    }

    std::string getConsoleColor(LogLevel level) {
        switch (level) {
        case LogLevel::FATAL: return "\033[31m";
        case LogLevel::ERROR: return "\033[91m";
        case LogLevel::WARN: return "\033[33m";
        case LogLevel::INFO: return "\033[0m";
        case LogLevel::TRACE: return "\033[37m";
        case LogLevel::DEBUG: return "\033[94m";
        default: return "\033[0m";
        }
    }

    std::string resetConsoleColor() {
        return "\033[0m";
    }

public:
    Log(const std::string& appName, const std::string& filePath = "")
        : appName(appName), logFilePath(filePath) {

        if (!logFilePath.empty()) {
            logFile.open(logFilePath, std::ios::out | std::ios::app);
            if (!logFile.is_open()) {
                std::cerr << "Failed to open log file: " << logFilePath << std::endl;
            }
        }
    }

    ~Log() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex);

        std::string timeStr = getCurrentTime();
        std::string levelStr = getLevelString(level);
        std::string colorCode = getConsoleColor(level);
        std::string resetCode = resetConsoleColor();

        std::stringstream logMessage;
        logMessage << "[" << timeStr << "] " << appName << " " << levelStr << ": " << message;

        std::cout << colorCode << logMessage.str() << resetCode << std::endl;

        if (logFile.is_open()) {
            logFile << logMessage.str() << std::endl;
        }
    }

    void debug(const std::string& message) { log(LogLevel::DEBUG, message); }
    void trace(const std::string& message) { log(LogLevel::TRACE, message); }
    void info(const std::string& message) { log(LogLevel::INFO, message); }
    void warn(const std::string& message) { log(LogLevel::WARN, message); }
    void error(const std::string& message) { log(LogLevel::ERROR, message); }
    void fatal(const std::string& message) { log(LogLevel::FATAL, message); }
};

std::mutex Log::logMutex;