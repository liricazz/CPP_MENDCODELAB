#include <iostream>
#include <string>
using namespace std;

class Item {
protected:
    int id;
    string title;
    int year;
    static int totalCount;

public:
    Item(int i, string t, int y) : id(i), title(t), year(y) {
        totalCount++;
    }

    virtual ~Item() {
        totalCount--;
    }


    virtual void show() const = 0;

    char& operator[](int index) {
        if (index < 0 || index >= title.length()) {
            throw "Индекс вне диапазона!";
        }
        return title[index];
    }

    static int getCount() { return totalCount; }

    friend void compareYear(const Item& a, const Item& b);
};

int Item::totalCount = 0;

class Book : public Item {
    string author;
    static int bookCount;

public:
    Book(int i, string t, int y, string a) : Item(i, t, y), author(a) {
        bookCount++;
    }

    ~Book() {
        bookCount--;
    }

    void show() const override {
        cout << "Книга: " << title << ", автор: " << author
             << ", год: " << year << ", ID:" << id << endl;
    }

    static int getBookCount() { return bookCount; }
};

int Book::bookCount = 0;

class Magazine : public Item {
    int issueNum;
    static int magCount;

public:
    Magazine(int i, string t, int y, int num) : Item(i, t, y), issueNum(num) {
        magCount++;
    }

    ~Magazine() {
        magCount--;
    }

    void show() const override {
        cout << "Журнал: " << title << ", выпуск №" << issueNum
             << ", год: " << year << ", ID:" << id << endl;
    }

    static int getMagCount() { return magCount; }
};

int Magazine::magCount = 0;

class DVD : public Item {
    int minutes;
    static int dvdCount;

public:
    DVD(int i, string t, int y, int m) : Item(i, t, y), minutes(m) {
        dvdCount++;
    }

    ~DVD() {
        dvdCount--;
    }

    void show() const override {
        cout << "DVD: " << title << ", длительность: " << minutes
             << " мин, год: " << year << ", ID:" << id << endl;
    }

    static int getDVDCount() { return dvdCount; }
};

int DVD::dvdCount = 0;

void compareYear(const Item& a, const Item& b) {
    if (a.year < b.year) {
        cout << "Более старый объект: ";
        a.show();
    } else if (b.year < a.year) {
        cout << "Более старый объект: ";
        b.show();
    } else {
        cout << "Одинаковый год выпуска" << endl;
    }
}

int main() {

  try {
    Book book1(101, "Война и мир", 1869, "Лев Толстой");
    Book book2(102, "Преступление и наказание", 1866, "Ф. Достоевский");
    Magazine mag1(201, "National Geographic", 2023, 150);
    DVD dvd1(301, "Начало", 2010, 148);

    cout << "\n ИНФОРМАЦИЯ ОБ ОБЪЕКТАХ" << endl;
    book1.show();
    cout << endl;
    book2.show();
    cout << endl;
    mag1.show();
    cout << endl;
    dvd1.show();


    // Работа с индексацией
    cout << "Название первой книги: \"" << book1[0];
    for(int i = 1; i < 10; i++) {
        cout << book1[i];
    }
    cout << "\"" << endl;

    cout << "5-й символ названия журнала: '" << mag1[4] << "'" << endl;

    // Работа с исключениями
    try {
        cout << "Пробуем получить 100-й символ: ";
        cout << book1[100] << endl;
    } catch (const char* msg) {
        cout << "Ошибка: " << msg << endl;
    }

    // Сравнение объектов
    compareYear(book1, book2);
    compareYear(mag1, dvd1);

    // Вывод статистики (для себя)
    cout << "Всего создано объектов: " << Item::getCount() << endl;
    cout << "Из них:" << endl;
    cout << "  - Книг: " << Book::getBookCount() << endl;
    cout << "  - Журналов: " << Magazine::getMagCount() << endl;
    cout << "  - DVD: " << DVD::getDVDCount() << endl;

    // Работа с временным объектом
    {
        Book temp(103, "Временная книга", 2026, "Тест Автор");
        cout << "Создана временная книга:" << endl;
        temp.show();
        cout << "Текущее количество книг: " << Book::getBookCount() << endl;
    }
    cout << "Временная книга удалена" << endl;
    cout << "Книг осталось: " << Book::getBookCount() << endl;

} catch (const char* msg) {
    cout << "Ошибка: " << msg << endl;
}

    return 0;
}
