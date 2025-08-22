//
// Created by murph on 8/18/25.
//

#ifndef INFOTECS_LOG_LEVEL_H
#define INFOTECS_LOG_LEVEL_H

#include <string>
#include <algorithm>

namespace IFTlogs {
    /**
     * @brief Уровни логирования в порядке возрастания важности
     */
    enum class LogLevel {
        DEBUG = 0,
        INFO = 1,
        ERROR = 2
    };

    /**
     * @brief Команды для управления библиотекой
     */
    enum class LogCommands {
        NONE = 0,
        MESSAGE = 1,
        CHANGE_LEVEL = 2,
        GET_LEVEL = 3,
        QUIT = 4
    };

    /**
     * @brief Преобразование уровня логирования в строку
     */
    inline std::string lvl_to_string(LogLevel level) {
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
    inline LogLevel lvl_from_string(const std::string &str) {
        if (str == "DEBUG") return LogLevel::DEBUG;
        if (str == "INFO") return LogLevel::INFO;
        if (str == "ERROR") return LogLevel::ERROR;
        return LogLevel::INFO;
    }

    /**
 * @brief Преобразование строки в команду
 */
    inline LogCommands command_from_string(const std::string &str) {
        std::string temp_string = str;
        std::transform(temp_string.begin(), temp_string.end(), temp_string.begin(), ::toupper);
        if (temp_string == "MESSAGE") return LogCommands::MESSAGE;
        if (temp_string == "CHANGE_LEVEL") return LogCommands::CHANGE_LEVEL;
        if (temp_string == "GET_LEVEL") return LogCommands::GET_LEVEL;
        return LogCommands::NONE;
    }

} // namespace logging

#endif //INFOTECS_LOG_LEVEL_H
