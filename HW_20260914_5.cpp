// Task 5
#include <iostream>
#include <string>

class Config {
public:
    Config(int maxUsers, const std::string& appName)
        : max_users(maxUsers), app_name(appName) {}

    std::string getAppName() const {
        return app_name;
    }

    int getMaxUsers() const {
        return max_users;
    }

    void printConfig() const {
        std::cout << "App: " << app_name
                  << ", max_users: " << max_users << '\n';
    }

    Config clone() const {
        return *this;
    }

    void setMaxUsers(int value) {
        max_users = value;
    }

private:
    int max_users;
    const std::string app_name;
};

int main() {
    const Config myConfig(100, "MyApp");

    std::cout << "App name: " << myConfig.getAppName() << '\n';
    myConfig.printConfig();

    Config copy = myConfig.clone();
    copy.setMaxUsers(200);
    std::cout << "\nOriginal:\n";
    myConfig.printConfig();
    std::cout << "Clone (after setMaxUsers(200)):\n";
    copy.printConfig();


    return 0;
}