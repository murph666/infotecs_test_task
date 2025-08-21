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

    bool Logger::log(const std::string &message, LogLevel level) {
        if (level < m_defaultLevel.load()) {
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

            std::ostringstream oss;
            oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

            m_file << "[" << oss.str() << "] "
                  << "[" << to_string(level) << "] "
                  << message << std::endl;

            m_file.flush(); // Принудительная запись на диск
            return true;
        } catch (...) {
            return false;
        }
    }

    bool Logger::log(const std::string &message) {
        return log(message, m_defaultLevel.load());
    }

    void Logger::setDefaultLevel(LogLevel level) {
        m_defaultLevel = level;
    }

    LogLevel Logger::getDefaultLevel() const {
        return m_defaultLevel;
    }


}