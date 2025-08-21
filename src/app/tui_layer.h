//
// Created by murph on 8/19/25.
//

#ifndef INFOTECS_TUI_LAYER_H
#define INFOTECS_TUI_LAYER_H

#include "IView.h"
#include "threadwrapper.h"
#include "log_level.h"

#include <sstream>


class tui_layer : public IView {
public:
    tui_layer() = default;

    ~tui_layer() override = default;

    void showWelcome() const override;

    void showHelp() const override;

    [[nodiscard]] UserInput getUserInput() const override;

    void showSuccess(const std::string &message) const override;

    void showError(const std::string &message) const override;

    void showCurrentLevel(IFTlogs::LogLevel level) const override;

private:
    std::unique_ptr<ThreadWrapper> m_PollingThread;
};


#endif //INFOTECS_TUI_LAYER_H
