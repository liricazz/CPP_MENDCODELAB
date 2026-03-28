#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(const string& n, int a) : name(n), age(a) {
        if (a < 0) {
            throw "Ошибка: возраст не может быть отрицательным!";
        }
        if (n.empty()) {
            throw "Ошибка: имя не может быть пустым!";
        }
    }

    virtual ~Person() {}

    virtual void printInfo() const {
        cout << "Имя: " << name << ", Возраст: " << age;
    }

    int getAge() const { return age; }
    string getName() const { return name; }

    friend bool compareAge(const Person& p1, const Person& p2);
};

class Employee : virtual public Person {
protected:
    double salary;

public:
    Employee(const string& n, int a, double s) : Person(n, a), salary(s) {
        if (s < 0) {
            throw "Ошибка: зарплата не может быть отрицательной!";
        }
    }

    virtual ~Employee() {}

    void printInfo() const override {
        Person::printInfo();
        cout << ", Зарплата: " << salary;
    }
};

class Student : virtual public Person {
protected:
    double averageGrade;

public:
    Student(const string& n, int a, double grade) : Person(n, a), averageGrade(grade) {
        if (grade < 0 || grade > 5) {
            throw "Ошибка: средний балл должен быть от 0 до 5!";
        }
    }

    virtual ~Student() {}

    void printInfo() const override {
        Person::printInfo();
        cout << ", Средний балл: " << averageGrade;
    }
};

class WorkingStudent : public Employee, public Student {
public:
    WorkingStudent(const string& n, int a, double s, double grade)
        : Person(n, a), Employee(n, a, s), Student(n, a, grade) {}

    void printInfo() const override {
        Person::printInfo();
        cout << ", Зарплата: " << salary << ", Средний балл: " << averageGrade;
    }
};

bool compareAge(const Person& p1, const Person& p2) {
    return p1.age < p2.age;
}

int main() {
    try {
        vector<Person*> persons;

        cout << "Введите данные сотрудника (имя, возраст, зарплата): ";
        string name1;
        int age1;
        double salary;
        cin >> name1 >> age1 >> salary;
        persons.push_back(new Employee(name1, age1, salary));

        cout << "Введите данные студента (имя, возраст, средний балл): ";
        string name2;
        int age2;
        double grade;
        cin >> name2 >> age2 >> grade;
        persons.push_back(new Student(name2, age2, grade));

        cout << "Введите данные работающего студента (имя, возраст, зарплата, средний балл): ";
        string name3;
        int age3;
        double salary2, grade2;
        cin >> name3 >> age3 >> salary2 >> grade2;
        persons.push_back(new WorkingStudent(name3, age3, salary2, grade2));

        cout << "\nИНФОРМАЦИЯ О ЛЮДЯХ:" << endl;
        for (size_t i = 0; i < persons.size(); i++) {
            cout << i+1 << ". ";
            persons[i]->printInfo();
            cout << endl;
        }

        // dynamic_cast
        cout << "\nПРОВЕРКА ТИПОВ:" << endl;
        for (size_t i = 0; i < persons.size(); i++) {
            if (dynamic_cast<WorkingStudent*>(persons[i])) {
                cout << persons[i]->getName() << " - работающий студент" << endl;
            } else if (dynamic_cast<Employee*>(persons[i])) {
                cout << persons[i]->getName() << " - сотрудник" << endl;
            } else if (dynamic_cast<Student*>(persons[i])) {
                cout << persons[i]->getName() << " - студент" << endl;
            }
        }

        if (persons.size() >= 2) {
            cout << "\nСРАВНЕНИЕ ПО ВОЗРАСТУ:" << endl;
            if (compareAge(*persons[0], *persons[1])) {
                cout << persons[0]->getName() << " младше " << persons[1]->getName() << endl;
            } else {
                cout << persons[1]->getName() << " младше " << persons[0]->getName() << endl;
            }
        }

        for (size_t i = 0; i < persons.size(); i++) {
            delete persons[i];
        }

    } catch (const char* msg) {
        cout << "Ошибка: " << msg << endl;
    }

    return 0;
}
