//
// Created by murph on 8/19/25.
//

#include "presenter_layer.h"


int presenter_layer::handleUserCommand(UserInput &userInput) {
    // Проверяем, что команда установлена
    if (!userInput.command.has_value()) {
        m_view.showError("Команда не распознана");
        return 1;
    }

    switch (userInput.command.value()) {
        case IFTlogs::LogCommands::MESSAGE:
            // Проверяем, что уровень установлен для сообщения
            if (!userInput.level.has_value()) {
                m_view.showError("Уровень логирования не установлен для сообщения");
                return 1;
            }
            handleLogInput(userInput.message, userInput.level.value());
            break;
        case IFTlogs::LogCommands::GET_LEVEL:
            m_view.showCurrentLevel(m_model.getCurrentLevel());
            break;
        case IFTlogs::LogCommands::CHANGE_LEVEL:
            // Проверяем, что уровень установлен для изменения
            if (!userInput.level.has_value()) {
                m_view.showError("Новый уровень логирования не указан");
                return 1;
            }
            if (handleChangeLevelCommand(userInput.level.value()) > 0) {
                m_view.showSuccess("Уровень логирования изменен на " +
                                   IFTlogs::lvl_to_string(userInput.level.value()));
            } else {
                m_view.showError("Ошибка изменения уровня логирования");
                return 1;
            }
            break;
        case IFTlogs::LogCommands::QUIT:
            break;
        default:
            m_view.showError("Неподдерживаемая команда");
            return 1;
    }

    return 0;
}

void presenter_layer::handleLogInput(const std::string &message, IFTlogs::LogLevel level) {
    m_model.addLogMessage(message, level);
}

int presenter_layer::handleChangeLevelCommand(IFTlogs::LogLevel level) {
    return m_model.changeLogLevel(level);
}
