//
// Created by murph on 8/19/25.
//

#include "tui_layer.h"

void tui_layer::showWelcome() const {
    std::cout << "=== Logger Application ===" << std::endl;
    std::cout << "Введите сообщение для записи в лог." << std::endl;
    std::cout << "Формат: <сообщение> [уровень]" << std::endl;
    std::cout << "Уровни: INFO, WARNING, ERROR" << std::endl;
    std::cout << "Специальные команды:" << std::endl;
    std::cout << "  quit - выход из программы" << std::endl;
    std::cout << "  level - показать минимальный уровень логирования" << std::endl;
    std::cout << "  level <уровень> - изменить минимальный уровень логирования" << std::endl;
    std::cout << "  help - показать справку" << std::endl;
    std::cout << std::endl;
}

void tui_layer::showHelp() const {
    std::cout << "\n=== Справка ===" << std::endl;
    std::cout << "Примеры использования:" << std::endl;
    std::cout << "  Привет мир INFO" << std::endl;
    std::cout << "  Произошла ошибка ERROR" << std::endl;
    std::cout << "  Простое сообщение (будет использован уровень по умолчанию)" << std::endl;
    std::cout << "  level WARNING (изменить минимальный уровень на WARNING)" << std::endl;
    std::cout << "  quit (выход)" << std::endl;
    std::cout << std::endl;
}

UserInput tui_layer::getUserInput() const {
    std::cout << "> ";
    UserInput input;

    std::string line;

    if (!std::getline(std::cin, line)) {
        return getUserInput();
    }

    std::vector<std::string> tokens;
    std::stringstream check(line);

    std::string token;

    while (std::getline(check, token, ' ')) {
        tokens.push_back(token);
    }
    switch (tokens.size()) {
        case 0:
            return getUserInput();
        case 1:
            if (line == "quit" || line == "exit") {
                input.command = IFTlogs::LogCommands::QUIT;
                return input;
            } else if (line == "help") {
                showHelp();
                return getUserInput();
            } else if (line == "level") {
                input.command = IFTlogs::LogCommands::GET_LEVEL;
            }else {
                input.message = tokens[0];
                input.command = IFTlogs::LogCommands::MESSAGE;
            }
            break;
        case 2:
            input.command = IFTlogs::LogCommands::MESSAGE;
            input.level = IFTlogs::lvl_from_string(tokens[1]);
            input.message = tokens[0];
            break;
        default:
            if (tokens.size() > 2) {
                std::cout << "Неправильный ввод" << std::endl;
                return getUserInput();
            }
            break;
    }

    return input;
}

void tui_layer::showSuccess(const std::string &message) const {
    std::cout << "Записанно: " << message << std::endl;
}

void tui_layer::showError(const std::string &message) const {
    std::cout << "Ошибка: " << message << std::endl;
}

void tui_layer::showCurrentLevel(IFTlogs::LogLevel level) const {
    std::cout << "Текущий уровень логирования по умолчанию: "
              << IFTlogs::to_string(level) << std::endl;
}
