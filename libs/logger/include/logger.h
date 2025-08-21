//
// Created by murph on 8/18/25.
//

#ifndef INFOTECS_LOGGER_H
#define INFOTECS_LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <atomic>
#include "log_level.h"

namespace IFTlogs {
    class Logger {
    public:
        explicit Logger(const std::string &filename, LogLevel default_level = LogLevel::INFO);

        ~Logger();

        /**
         * @brief Запись сообщения в журнал
         * @param message Текст сообщения
         * @param level Уровень важности
         * @return true в случае успеха, false при ошибке
         */
        bool log(const std::string &message, LogLevel level);


        /**
          * @brief Запись сообщения в журнал c уровнем по умолчанию.
          * @param message Текст сообщения
          * @return true в случае успеха, false при ошибке
          */
        bool log(const std::string &message);

        /**
        * @brief Установка нового уровня важности по умолчанию
        * @param level Новый уровень
        */
        void setDefaultLevel(LogLevel level);

        /**
         * @brief Получение текущего уровня по умолчанию
         * @return Текущий уровень по умолчанию
         */
        LogLevel getDefaultLevel() const;

    private:
        std::ofstream m_file;
        std::mutex m_mutex;
        std::atomic<LogLevel> m_defaultLevel;
        std::atomic<bool> m_isOpen{false};
    };
}
#endif //INFOTECS_LOGGER_H
