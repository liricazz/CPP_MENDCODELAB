#include <iostream>
using namespace std;

namespace SmartPtr {

class NullPointerException : public exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: попытка доступа к неинициализированному указателю!";
    }
};

template<typename T>
class SmartPointer {
private:
    T* ptr;
    int* refCount;
    
public:
    SmartPointer(T* p = nullptr) : ptr(p), refCount(new int(1)) {
        if (p == nullptr) {
            *refCount = 0;
        }
    }

    SmartPointer(const SmartPointer& other) : ptr(other.ptr), refCount(other.refCount) {
        if (ptr != nullptr) {
            (*refCount)++;
        }
    }

    SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
            if (ptr != nullptr) {
                (*refCount)--;
                if (*refCount == 0) {
                    delete ptr;
                    delete refCount;
                }
            }

            ptr = other.ptr;
            refCount = other.refCount;
            if (ptr != nullptr) {
                (*refCount)++;
            }
        }
        return *this;
    }

    ~SmartPointer() {
        if (ptr != nullptr) {
            (*refCount)--;
            if (*refCount == 0) {
                delete ptr;
                delete refCount;
            }
        }
    }

    T& operator*() {
        if (ptr == nullptr) {
            throw NullPointerException();
        }
        return *ptr;
    }
    
    const T& operator*() const {
        if (ptr == nullptr) {
            throw NullPointerException();
        }
        return *ptr;
    }

    T* operator->() {
        if (ptr == nullptr) {
            throw NullPointerException();
        }
        return ptr;
    }
    
    const T* operator->() const {
        if (ptr == nullptr) {
            throw NullPointerException();
        }
        return ptr;
    }

    int getRefCount() const {
        return (ptr != nullptr) ? *refCount : 0;
    }
};

template<typename T>
class SmartPointer<T[]> {
private:
    T* ptr;
    int* refCount;
    int size;
    
public:
    SmartPointer(int s = 0) : ptr(new T[s]()), refCount(new int(1)), size(s) {
        if (s == 0) {
            *refCount = 0;
        }
    }
    
    SmartPointer(const SmartPointer& other) : ptr(other.ptr), refCount(other.refCount), size(other.size) {
        if (ptr != nullptr) {
            (*refCount)++;
        }
    }
    
    SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
            if (ptr != nullptr) {
                (*refCount)--;
                if (*refCount == 0) {
                    delete[] ptr;
                    delete refCount;
                }
            }
            
            ptr = other.ptr;
            refCount = other.refCount;
            size = other.size;
            if (ptr != nullptr) {
                (*refCount)++;
            }
        }
        return *this;
    }
    
    ~SmartPointer() {
        if (ptr != nullptr) {
            (*refCount)--;
            if (*refCount == 0) {
                delete[] ptr;
                delete refCount;
            }
        }
    }
    
    T& operator[](int index) {
        if (ptr == nullptr) {
            throw NullPointerException();
        }
        if (index < 0 || index >= size) {
            throw out_of_range("Индекс вне диапазона!");
        }
        return ptr[index];
    }
    
    int getRefCount() const {
        return (ptr != nullptr) ? *refCount : 0;
    }
    
    int getSize() const { return size; }
};

class TestClass {
public:
    int value;
    TestClass(int v = 0) : value(v) {}
    void show() const { cout << "Значение: " << value << endl; }
};

}

int main() {
    using namespace SmartPtr;
    
    try {
        try {
            cout << "SMART POINTER ДЛЯ ОДИНОЧНОГО ОБЪЕКТА" << endl;
            SmartPointer<TestClass> sp1(new TestClass(42));
            cout << "Счётчик ссылок sp1: " << sp1.getRefCount() << endl;
            
            {
                SmartPointer<TestClass> sp2 = sp1;
                cout << "Счётчик ссылок после копирования: " << sp1.getRefCount() << endl;
                sp2->show();
                (*sp2).show();
            }
            
            cout << "Счётчик ссылок после удаления sp2: " << sp1.getRefCount() << endl;

            cout << "\nУКАЗАТЕЛИ НА МЕТОДЫ:" << endl;
            void (TestClass::*methodPtr)() const = &TestClass::show;
            (sp1.get()->*methodPtr)();

            cout << "\nSMART POINTER ДЛЯ МАССИВА:" << endl;
            SmartPointer<int[]> arr(5);
            for (int i = 0; i < 5; i++) {
                arr[i] = (i + 1) * 10;
            }
            cout << "Элементы массива: ";
            for (int i = 0; i < 5; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            cout << "Счётчик ссылок массива: " << arr.getRefCount() << endl;

            cout << "\nПРОВЕРКА ИСКЛЮЧЕНИЙ:" << endl;
            SmartPointer<TestClass> empty;
            try {
                empty->show();
            } catch (const NullPointerException& e) {
                cout << "Внутренний catch: " << e.what() << endl;
                throw;
            }
            
        } catch (const NullPointerException& e) {
            cout << "Внешний catch: " << e.what() << endl;
        }
        
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    
    return 0;
}