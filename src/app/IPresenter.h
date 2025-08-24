//
// Created by murph on 8/19/25.
//

#ifndef INFOTECS_IPRESENTER_H
#define INFOTECS_IPRESENTER_H

#include "log_level.h"

struct UserInput;

class IPresenter {
public:
    virtual ~IPresenter() = default;

    // Обработка команд от пользователя
    virtual int handleUserCommand(UserInput &userInput) = 0;

private:
    /**
     * @brief Обработка ввода лог-сообщения
     * @param message Текст сообщения
     * @param level Уровень важности
     */
    virtual void handleLogInput(const std::string &message, IFTlogs::LogLevel level) = 0;

    /**
     * @brief Изменение уровня логирования
     * @param message Текст сообщения
     */
    virtual int handleChangeLevelCommand(IFTlogs::LogLevel level) = 0;

};

#endif //INFOTECS_IPRESENTER_H
