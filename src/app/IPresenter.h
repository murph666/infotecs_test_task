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
    virtual int handleUserCommand(UserInput &command) = 0;


private:
    // Обработка ввода лог-сообщения
    virtual void handleLogInput(const std::string &message, IFTlogs::LogLevel level, const std::string &recipient = "") = 0;

//    // Обработка изменения уровня логирования
//    virtual void handleDefaultLogLevelChange(IFTlogs::LogLevel newLevel) = 0;
};

#endif //INFOTECS_IPRESENTER_H
