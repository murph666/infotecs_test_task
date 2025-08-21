//
// Created by murph on 8/19/25.
//

#ifndef INFOTECS_IVIEW_H
#define INFOTECS_IVIEW_H

#include "log_level.h"

/**
 * @brief Структура для пользовательского ввода
 */
struct UserInput {
    std::optional<IFTlogs::LogCommands> command;
    std::optional<IFTlogs::LogLevel> level;
    std::string message;

    UserInput() = default;
};

class IView {
public:
    virtual ~IView() = default;

    /**
     * @brief Показать приветственное сообщение
     */
    virtual void showWelcome() const = 0;

    /**
     * @brief Показать справку по командам
     */
    virtual void showHelp() const = 0;

    /**
     * @brief Получить ввод от пользователя
     * @return Структура с данными ввода
     */
    [[nodiscard]] virtual UserInput getUserInput() const = 0;

    /**
     * @brief Показать сообщение об успехе
     * @param message Текст сообщения
     */
    virtual void showSuccess(const std::string &message) const = 0;

    /**
     * @brief Показать сообщение об ошибке
     * @param message Текст ошибки
     */
    virtual void showError(const std::string &message) const = 0;

    /**
     * @brief Показать текущий уровень логирования
     * @param level Текущий уровень
     */
    virtual void showCurrentLevel(IFTlogs::LogLevel level) const = 0;
};

#endif //INFOTECS_IVIEW_H
