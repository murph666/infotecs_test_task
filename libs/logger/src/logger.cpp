//
// Created by murph on 8/18/25.
//
#include <iomanip>
#include "logger.h"


namespace IFTlogs {
    Logger::Logger(const std::string &filename, LogLevel default_level) : m_defaultLevel(default_level) {
        try {
            m_file.open(filename, std::ios::app);
            if (m_file.is_open()) {
                m_isOpen.store(true);
                m_workerThread = std::thread(&Logger::workerThread, this);
            } else {
                throw std::runtime_error("Failed to open log file: " + filename);
            }
        }
        catch (const std::exception &e) {
            std::cerr << "Error occurred: " << e.what() << std::endl;
        }
    }

    Logger::~Logger() {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_file.is_open()) {
            m_file.close();
        }
    }

    int Logger::addLogMessage(const std::string &message, LogLevel level) {
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);

            if (m_messageQueue.size() >= MAX_QUEUE_SIZE) {
                m_messageQueue.pop();
            }

            // Добавление нового сообщения
            m_messageQueue.emplace(message, level);
        }

        m_condition.notify_one();
        return 0;
    }


    bool Logger::log(const LogMessage &message) {
        if (message.level < m_defaultLevel.load()) {
            return true;
        }

        if (!m_isOpen.load()) {
            return false;
        }

        std::lock_guard<std::mutex> lock(m_mutex);

        if (!m_file.is_open()) {
            return false;
        }

        try {
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);

            m_file << "[" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << "] " << "[" << lvl_to_string(message.level) << "] " << message.text << std::endl;

            m_file.flush(); // Принудительная запись на диск
            return true;
        } catch (...) {
            return false;
        }
    }

    int Logger::setDefaultLevel(LogLevel level) {
        m_defaultLevel = level;
        return 1;
    }

    LogLevel Logger::getDefaultLevel() const {
        return m_defaultLevel;
    }

    void Logger::workerThread() {
        while (!m_shouldStop.load()) {
            std::unique_lock<std::mutex> lock(m_queueMutex);

            // Ожидание сообщений или сигнала остановки
            m_condition.wait(lock, [this] {
                return !m_messageQueue.empty() || m_shouldStop.load();
            });

            // Обработка всех доступных сообщений
            while (!m_messageQueue.empty() && !m_shouldStop.load()) {
                LogMessage msg = m_messageQueue.front();
                m_messageQueue.pop();
                lock.unlock();

                // Запись в файл (без удержания мьютекса)
                log(msg);

                lock.lock();
            }
        }

        // Обработка оставшихся сообщений при завершении
        std::lock_guard<std::mutex> lock(m_queueMutex);
        while (!m_messageQueue.empty()) {
            LogMessage msg = m_messageQueue.front();
            m_messageQueue.pop();
            log(msg);
        }
    }


}