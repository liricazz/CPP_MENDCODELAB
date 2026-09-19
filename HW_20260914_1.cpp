// Task 1
#include <iostream>
#include <string>

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }


    Logger& log(const std::string& message) {
        ++total_logs;
        std::cout << "[LOG #" << total_logs << "] " << message << '\n';
        return *this;
    }

    static int getTotalLogs() { return total_logs; }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger() = default;
    ~Logger() = default;

    static int total_logs;
};

int Logger::total_logs = 0;

int main() {
    Logger::getInstance().log("Start").log("Process").log("Finish");
    std::cout << "Total logs: " << Logger::getTotalLogs() << '\n';

    return 0;
}