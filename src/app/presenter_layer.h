//
// Created by murph on 8/19/25.
//

#ifndef INFOTECS_PRESENTER_LAYER_H
#define INFOTECS_PRESENTER_LAYER_H


#include "IView.h"
#include "IModel.h"
#include "IPresenter.h"


class presenter_layer : public IPresenter {
public:
    presenter_layer(IView &view, IModel &model) : m_view(view), m_model(model) {};


    int handleUserCommand(UserInput &command) override {

        switch (command.message)

    }

    void handleLogInput(const std::string &message, IFTlogs::LogLevel level, const std::string &recipient) override {

    }

//    void handleDefaultLogLevelChange(IFTlogs::LogLevel newLevel) override {
//
//    }

private:
    IView &m_view;
    IModel &m_model;
};


#endif //INFOTECS_PRESENTER_LAYER_H
