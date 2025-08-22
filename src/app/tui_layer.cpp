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

    // Разделяем строку на токены
    std::vector<std::string> tokens;
    std::stringstream check(line);
    std::string token;

    while (std::getline(check, token, ' ')) {
        if (!token.empty()) { // Пропускаем пустые токены
            tokens.push_back(token);
        }
    }

    if (tokens.empty()) {
        return getUserInput(); // Если ввод пустой, запрашиваем заново
    }

    // Обработка команд
    if (tokens[0] == "quit" || tokens[0] == "exit") {
        input.command = IFTlogs::LogCommands::QUIT;
        return input;
    }

    if (tokens[0] == "help") {
        showHelp();
        return getUserInput();
    }

    if (tokens[0] == "level") {
        if (tokens.size() == 1) {
            input.command = IFTlogs::LogCommands::GET_LEVEL;
        } else if (tokens.size() == 2) {
            input.command = IFTlogs::LogCommands::CHANGE_LEVEL;
            input.level = IFTlogs::lvl_from_string(tokens[1]);
        } else {
            std::cout << "Неправильный формат команды level" << std::endl;
            return getUserInput();
        }
        return input;
    }

    // Обработка лог-сообщений
    input.command = IFTlogs::LogCommands::MESSAGE;

    if (tokens.size() == 1) {
        // Только сообщение, используем уровень default
        input.message = tokens[0];
    } else if (tokens.size() >= 2) {
        // Проверяем, является ли последний токен уровнем логирования
        std::string lastToken = tokens.back();
        std::transform(lastToken.begin(), lastToken.end(), lastToken.begin(), ::toupper);
        if (lastToken == "DEBUG" || lastToken == "INFO" || lastToken == "ERROR") {
            input.level = IFTlogs::lvl_from_string(lastToken);

            // Собираем сообщение из всех токенов кроме последнего
            for (size_t i = 0; i < tokens.size() - 1; i++) {
                input.message += tokens[i];
                if (i < tokens.size() - 2) {
                    input.message += " ";
                }
            }
        } else {
            // Уровня нет, используем весь ввод как сообщение с уровнем default
            input.message = line;
        }
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
              << IFTlogs::lvl_to_string(level) << std::endl;
}
