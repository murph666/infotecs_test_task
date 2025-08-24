//
// Created by murph on 8/19/25.
//

#ifndef INFOTECS_MODEL_LAYER_H
#define INFOTECS_MODEL_LAYER_H


#include "threadwrapper.h"
#include "IModel.h"
#include "log_level.h"
#include "logger.h"

class model_layer : public IModel {
public:
    model_layer(std::string log_filename, std::string log_level);

    void addLogMessage(const std::string &message, IFTlogs::LogLevel level) override;

    int changeLogLevel(IFTlogs::LogLevel level) override;

    [[nodiscard]] IFTlogs::LogLevel getCurrentLevel() const override;


private:
    std::unique_ptr<ThreadWrapper> m_ActionsThread;
    std::unique_ptr<IFTlogs::Logger> m_logger;
};


#endif //INFOTECS_MODEL_LAYER_H
