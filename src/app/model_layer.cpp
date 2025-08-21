//
// Created by murph on 8/19/25.
//

#include "model_layer.h"

model_layer::model_layer(std::string log_filename, std::string log_level) :
        m_ActionsThread(std::make_unique<ThreadWrapper>()),
        m_logger(std::make_unique<IFTlogs::Logger>(log_filename, IFTlogs::from_string(log_level))) {
}


//bool model_layer::addLogMessage(const std::string &message, IFTlogs::LogLevel level) {
//      return IModel::addLogMessage(message, level);
//}
//
//void model_layer::changeLogLevel(IFTlogs::LogLevel level) {
//    IModel::changeLogLevel(level);
//}
//
IFTlogs::LogLevel model_layer::getCurrentLevel() const {
    return m_logger->getDefaultLevel();
}
//
//bool model_layer::isReady() const {
//    return IModel::isReady();
//}

void model_layer::workerThread() {

}
