//
// Created by murph on 8/19/25.
//

#ifndef INFOTECS_THREADWRAPPER_H
#define INFOTECS_THREADWRAPPER_H

#include <thread>

class ThreadWrapper {
public:
    ThreadWrapper() = default;

    ~ThreadWrapper();

    void Attach(std::thread &&thread);

    void Detach();

private:
    std::thread m_Thread{};
};

#endif //INFOTECS_THREADWRAPPER_H
