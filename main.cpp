#include "src/app/application.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {

    std::string log_filename = "app.log";
    std::string log_level = "INFO";

    if (argc >= 2) log_filename = argv[1];
    if (argc >= 3) log_level = argv[2];

    Application app(log_filename, log_level);
    app.run();
    return 0;
}