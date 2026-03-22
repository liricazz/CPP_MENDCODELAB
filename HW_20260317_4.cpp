#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace Company {

class Employee {
private:
    string name;
    int id;
    
protected:
    double salary;
    
public:
    Employee(string n, int i, double s) : name(n), id(i), salary(s) {
        if (s < 0) {
            throw "Зарплата не может быть отрицательной!";
        }
        if (name.empty()) {
            throw "Имя не может быть пустым!";
        }
        cout << "  [Создан] Сотрудник " << name << " (ID: " << id << ")" << endl;
    }
    
    virtual ~Employee() {
        cout << "  [Удален] Сотрудник " << name << endl;
    }
    
    string getName() const { return name; }
    int getId() const { return id; }
    double getSalary() const { return salary; }
    
    virtual double calculateBonus() const = 0;
    
    Employee& operator=(const Employee& other) {
        if (this != &other) {
            name = other.name;
            id = other.id;
            salary = other.salary;
        }
        return *this;
    }
    
    virtual void info() const {
        cout << "  " << name << " (ID: " << id << ", з/п: " << salary << " руб.)";
    }
};

class Manager : public Employee {
    int teamSize;
    
public:
    Manager(string n, int i, double s, int team) 
        : Employee(n, i, s), teamSize(team) {
        cout << "    Должность: Менеджер, команда " << team << " чел." << endl;
    }
    
    double calculateBonus() const override {
        return salary * 0.2 + teamSize * 500;
    }
    
    void info() const override {
        Employee::info();
        cout << " - Менеджер (команда: " << teamSize << ")" << endl;
    }
};

class Developer : public Employee {
    string language;
    
public:
    Developer(string n, int i, double s, string lang) 
        : Employee(n, i, s), language(lang) {
        cout << "    Должность: Разработчик, язык: " << lang << endl;
    }
    
    double calculateBonus() const override {
        return salary * 0.15;
    }
    
    void info() const override {
        Employee::info();
        cout << " - Разработчик (" << language << ")" << endl;
    }
};

class Intern : public Employee {
    int months;
    
public:
    Intern(string n, int i, double s, int m) 
        : Employee(n, i, s), months(m) {
        cout << "    Должность: Стажёр, длительность: " << m << " мес." << endl;
    }
    
    double calculateBonus() const override {
        return salary * 0.05 * months;
    }
    
    void info() const override {
        Employee::info();
        cout << " - Стажёр (" << months << " мес.)" << endl;
    }
};

double totalBonus(const vector<Employee*>& staff) {
    double sum = 0;
    for (auto emp : staff) {
        sum += emp->calculateBonus();
    }
    return sum;
}

void countByType(const vector<Employee*>& staff) {
    int managers = 0, devs = 0, interns = 0;
    
    for (auto emp : staff) {
        if (dynamic_cast<Manager*>(emp)) {
            managers++;
        } else if (dynamic_cast<Developer*>(emp)) {
            devs++;
        } else if (dynamic_cast<Intern*>(emp)) {
            interns++;
        }
    }
    
    cout << "  Менеджеров: " << managers << endl;
    cout << "  Разработчиков: " << devs << endl;
    cout << "  Стажёров: " << interns << endl;
}

}

int main() {

    try {
        using namespace Company;
        
        cout << "1. СОЗДАНИЕ СОТРУДНИКОВ:" << endl;
        vector<Employee*> staff;
        
        staff.push_back(new Manager("Иван Петров", 101, 100000, 5));
        staff.push_back(new Developer("Мария Смирнова", 102, 80000, "C++"));
        staff.push_back(new Developer("Алексей Иванов", 103, 90000, "Java"));
        staff.push_back(new Intern("Петр Сидоров", 104, 30000, 3));
        staff.push_back(new Intern("Елена Козлова", 105, 30000, 2));
        
        cout << "\n2. ИНФОРМАЦИЯ О СОТРУДНИКАХ:" << endl;
        for (auto emp : staff) {
            emp->info();
        }
        
        cout << "\n3. РАСЧЕТ БОНУСОВ:" << endl;
        for (auto emp : staff) {
            cout << "  " << emp->getName() << ": бонус = " 
                 << emp->calculateBonus() << " руб." << endl;
        }
        
        cout << "\n4. ОБЩИЙ БОНУС:" << endl;
        cout << "  Суммарный бонус всех сотрудников = " 
             << totalBonus(staff) << " руб." << endl;
        
        cout << "\n5. СТАТИСТИКА ПО ТИПАМ (dynamic_cast):" << endl;
        countByType(staff);
        
        cout << "\n6. ПРОВЕРКА ИСКЛЮЧЕНИЙ:" << endl;
        try {
            cout << "  Попытка создать сотрудника с отрицательной зарплатой..." << endl;
            Employee* bad = new Manager("Тест", 999, -1000, 1);
            delete bad;
        } catch (const char* msg) {
            cout << "  Ошибка: " << msg << endl;
        }
        
        try {
            cout << "\n  Попытка создать сотрудника с пустым именем..." << endl;
            Employee* bad = new Developer("", 998, 50000, "Python");
            delete bad;
        } catch (const char* msg) {
            cout << "  Ошибка: " << msg << endl;
        }
        
        cout << "\n7. ОПЕРАТОР ПРИСВАИВАНИЯ:" << endl;
        Manager m1("Оригинал", 201, 120000, 8);
        Manager m2("Копия", 202, 0, 0);
        
        cout << "  До присваивания:" << endl;
        m1.info();
        m2.info();
        
        m2 = m1;
        
        cout << "  После присваивания m2 = m1:" << endl;
        m2.info();
        
        cout << "\n8. ОЧИСТКА ПАМЯТИ:" << endl;
        for (auto emp : staff) {
            delete emp;
        }
        
    } catch (const char* msg) {
        cout << "Ошибка: " << msg << endl;
    }
    
    return 0;
}