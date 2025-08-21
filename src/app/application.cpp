//
// Created by murph on 8/19/25.
//

#include "application.h"
#include <utility>

#include "presenter_layer.h"
#include "tui_layer.h"
#include "model_layer.h"


Application::Application(std::string log_filename, std::string log_level) {
    try {
        m_model = std::make_unique<model_layer>(std::move(log_filename), std::move(log_level));
        m_tui = std::make_unique<tui_layer>();
        m_presenter = std::make_unique<presenter_layer>(*m_tui, *m_model);
    } catch (const std::exception &e) {
        std::cerr << "Application initialization failed: " << e.what() << std::endl;
        m_initialization = false;
    }
}

int Application::run() {
    if (!m_initialization || !m_model || !m_tui || !m_presenter) {
        return 1;
    }

    m_tui->showWelcome();
    m_tui->showCurrentLevel(m_model->getCurrentLevel());

    while (true) {
        UserInput input = m_tui->getUserInput();

        if (input.command == IFTlogs::LogCommands::QUIT) {
            m_tui->showSuccess("До свидания!");
            break;
        }

        if (!m_presenter->handleUserCommand(input)) {
            // Обработка ошибки от presenter
            m_tui->showError("Ошибка обработки команды");
        }
    }

    return 0;
}
