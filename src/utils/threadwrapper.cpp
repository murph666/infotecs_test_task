//
// Created by murph on 8/19/25.
//

#include "threadwrapper.h"


ThreadWrapper::~ThreadWrapper() { Detach(); }

void ThreadWrapper::Attach(std::thread &&thread) {
    Detach();
    m_Thread = std::forward<std::thread &&>(thread);
}

void ThreadWrapper::Detach() {
    if (m_Thread.joinable()) {
        m_Thread.join();
    }
}

