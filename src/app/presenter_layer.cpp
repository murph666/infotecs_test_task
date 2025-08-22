//
// Created by murph on 8/19/25.
//

#include "presenter_layer.h"


int presenter_layer::handleUserCommand(UserInput &userInput) {
    switch (userInput.command.value()) {
        case IFTlogs::LogCommands::MESSAGE:
            return handleLogInput(userInput.message, userInput.level.value());
        case IFTlogs::LogCommands::GET_LEVEL:
            m_view.showCurrentLevel(m_model.getCurrentLevel());
            return 0;
        case IFTlogs::LogCommands::CHANGE_LEVEL:
            return handleChangeLevelCommand(userInput.level.value());
        case IFTlogs::LogCommands::QUIT:
            break;
        default:
            m_view.showError("Неподдерживаемая команда");
            return 1;
    }

    return 0;
}

bool presenter_layer::handleLogInput(const std::string &message, IFTlogs::LogLevel level) {
    return m_model.addLogMessage(message, level);
}

int presenter_layer::handleChangeLevelCommand(IFTlogs::LogLevel level) {
    return m_model.changeLogLevel(level);
}
