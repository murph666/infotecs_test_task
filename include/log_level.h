//
// Created by murph on 8/18/25.
//

#ifndef INFOTECS_LOG_LEVEL_H
#define INFOTECS_LOG_LEVEL_H

#include <string>

namespace logging {
/**
 * @brief Уровни логирования в порядке возрастания важности
 */
    enum class LogLevel {
        DEBUG = 0,
        INFO = 1,
        ERROR = 2
    };

/**
 * @brief Преобразование уровня логирования в строку
 */
    inline std::string to_string(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::ERROR:
                return "ERROR";
            default:
                return "UNKNOWN";
        }
    }

/**
 * @brief Преобразование строки в уровень логирования
 */
    inline LogLevel from_string(const std::string &str) {
        if (str == "DEBUG") return LogLevel::DEBUG;
        if (str == "INFO") return LogLevel::INFO;
        if (str == "ERROR") return LogLevel::ERROR;
        return LogLevel::INFO;
    }

} // namespace logging

#endif //INFOTECS_LOG_LEVEL_H
