//
// Created by murph on 8/18/25.
//

#ifndef INFOTECS_LOGGER_H
#define INFOTECS_LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <atomic>
#include <queue>
#include <condition_variable>
#include <thread>
#include <utility>
#include "log_level.h"

namespace IFTlogs {
    struct LogMessage {
        std::string text;
        LogLevel level;

        LogMessage(std::string msg, LogLevel lvl) : text(std::move(msg)), level(lvl) {}
    };

    class Logger {
    public:
        explicit Logger(const std::string &filename, LogLevel default_level = LogLevel::INFO);

        ~Logger();

        /**
        * @brief Установка нового уровня важности по умолчанию
        * @param level Новый уровень
        */
        void addLogMessage(const std::string &message, LogLevel level);

        /**
        * @brief Установка нового уровня важности по умолчанию
        * @param level Новый уровень
        */
        int setDefaultLevel(LogLevel level);

        /**
         * @brief Получение текущего уровня по умолчанию
         * @return Текущий уровень по умолчанию
         */
        LogLevel getDefaultLevel() const;

    private:
        void workerThread();

        /**
          * @brief Запись сообщения в журнал c уровнем по умолчанию.
          * @param message Текст сообщения
          * @return true в случае успеха, false при ошибке
          */
        bool log(const LogMessage &message);


    private:
        std::ofstream m_file;
        std::mutex m_mutex;
        std::atomic<LogLevel> m_defaultLevel;
        std::atomic<bool> m_isOpen{false};

        // Потокобезопасная очередь
        std::queue<LogMessage> m_messageQueue;
        mutable std::mutex m_queueMutex;
        std::condition_variable m_condition;

        // Рабочий поток
        std::thread m_workerThread;
        std::atomic<bool> m_shouldStop{false};

        size_t MAX_QUEUE_SIZE = 100;

    };
}
#endif //INFOTECS_LOGGER_H
