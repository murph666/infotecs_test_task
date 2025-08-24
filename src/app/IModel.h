//
// Created by murph on 8/20/25.
//

#ifndef INFOTECS_IMODEL_H
#define INFOTECS_IMODEL_H


#include "log_level.h"

class IModel {
public:
    virtual ~IModel() = default;

    /**
     * @brief Добавление сообщения в лог
     * @param message Текст сообщения
     * @param level Ууровень
     */
    virtual void addLogMessage(const std::string& message, IFTlogs::LogLevel level) = 0;

    /**
     * @brief Изменение уровня важности логгера
     * @param level Новый уровень
     */
    virtual int changeLogLevel(IFTlogs::LogLevel level) = 0;

    /**
     * @brief Получение текущего уровня важности
     * @return Текущий уровень
     */
    [[nodiscard]] virtual IFTlogs::LogLevel getCurrentLevel() const = 0;
};

#endif //INFOTECS_IMODEL_H
