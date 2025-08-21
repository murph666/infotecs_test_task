//
// Created by murph on 8/20/25.
//

#ifndef INFOTECS_IMODEL_H
#define INFOTECS_IMODEL_H


#include "log_level.h"

class IModel {
public:
    virtual ~IModel() = default;

//    virtual bool addLogMessage(const std::string& message, IFTlogs::LogLevel level);
//
//    /**
//     * @brief Изменение уровня важности логгера
//     * @param level Новый уровень
//     */
//    virtual void changeLogLevel(IFTlogs::LogLevel level);
//
    /**
     * @brief Получение текущего уровня важности
     * @return Текущий уровень
     */
    [[nodiscard]] virtual IFTlogs::LogLevel getCurrentLevel() const = 0;
//
//    /**
//     * @brief Проверка готовности модели к работе
//     * @return true если логгер готов к работе
//     */
//    virtual bool isReady() const;
};

#endif //INFOTECS_IMODEL_H
