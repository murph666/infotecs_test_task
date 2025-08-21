//
// Created by murph on 8/19/25.
//

#ifndef INFOTECS_APPLICATION_H
#define INFOTECS_APPLICATION_H

#include "IModel.h"
#include "IPresenter.h"
#include "IView.h"

class Application {
public:
    Application(std::string log_filename, std::string log_level);

    ~Application() = default;

    int run();


private:
    bool m_initialization{true};

    std::unique_ptr<IView> m_tui;
    std::unique_ptr<IModel> m_model;
    std::unique_ptr<IPresenter> m_presenter;
};

#endif //INFOTECS_APPLICATION_H
