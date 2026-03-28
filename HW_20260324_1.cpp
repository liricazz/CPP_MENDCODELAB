#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() {}
};

template<typename T>
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
};

template<typename T>
class Polygon : public Shape {
protected:
    vector<Point<T>> points;
    static int polygonCount;

public:
    Polygon(const vector<Point<T>>& pts) : points(pts) {
        if (pts.size() < 3) {
            throw "Ошибка: многоугольник должен иметь минимум 3 точки!!!";
        }
        polygonCount++;
    }

    Polygon(const Polygon& other) : points(other.points) {
        polygonCount++;
    }

    Polygon& operator=(const Polygon& other) {
        if (this != &other) {
            points = other.points;
        }
        return *this;
    }

    virtual ~Polygon() {
        polygonCount--;
    }

    friend void printPolygon(const Polygon& p) {
        cout << "Многоугольник с " << p.points.size() << " точками:" << endl;
        for (size_t i = 0; i < p.points.size(); i++) {
            cout << "  Точка " << i+1 << ": (" << p.points[i].x << ", " << p.points[i].y << ")" << endl;
        }
    }
    
    static int getPolygonCount() { return polygonCount; }
};

template<typename T>
int Polygon<T>::polygonCount = 0;

template<typename T>
class Triangle : public Polygon<T> {
public:
    Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) 
        : Polygon<T>({p1, p2, p3}) {}
    
    double area() const override {
        const auto& pts = this->points;
        T x1 = pts[0].x, y1 = pts[0].y;
        T x2 = pts[1].x, y2 = pts[1].y;
        T x3 = pts[2].x, y3 = pts[2].y;
        
        return abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
    }
    
    friend void printTriangle(const Triangle& t) {
        cout << "Треугольник с вершинами:" << endl;
        for (size_t i = 0; i < t.points.size(); i++) {
            cout << "  (" << t.points[i].x << ", " << t.points[i].y << ")" << endl;
        }
        cout << "Площадь: " << t.area() << endl;
    }
};

template<typename T>
class Rectangle : public Polygon<T> {
public:
    Rectangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) 
        : Polygon<T>({p1, p2, p3, p4}) {
    }
    
    double area() const override {
        const auto& pts = this->points;
        T width = abs(pts[1].x - pts[0].x);
        T height = abs(pts[2].y - pts[1].y);
        return width * height;
    }
    
    friend void printRectangle(const Rectangle& r) {
        cout << "Прямоугольник с вершинами:" << endl;
        for (size_t i = 0; i < r.points.size(); i++) {
            cout << "  (" << r.points[i].x << ", " << r.points[i].y << ")" << endl;
        }
        cout << "Площадь: " << r.area() << endl;
    }
};

int main() {
    try {
        try {
            cout << "Введите координаты треугольника (x1 y1 x2 y2 x3 y3): ";
            double x1, y1, x2, y2, x3, y3;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            
            Point<double> p1(x1, y1), p2(x2, y2), p3(x3, y3);
            Triangle<double> triangle(p1, p2, p3);

            cout << "Введите координаты прямоугольника (x1 y1 x2 y2 x3 y3 x4 y4): ";
            double x4, y4, x5, y5, x6, y6, x7, y7;
            cin >> x4 >> y4 >> x5 >> y5 >> x6 >> y6 >> x7 >> y7;
            
            Point<double> p4(x4, y4), p5(x5, y5), p6(x6, y6), p7(x7, y7);
            Rectangle<double> rectangle(p4, p5, p6, p7);

            cout << "\n ИНФОРМАЦИЯ О ФИГУРАХ: " << endl;
            printTriangle(triangle);
            cout << endl;
            printRectangle(rectangle);

            cout << "\n СТАТИСТИКА:" << endl;
            cout << "Всего многоугольников: " << Polygon<double>::getPolygonCount() << endl;
            
        } catch (const char* msg) {
            cout << "Внутренний catch: " << msg << endl;
            throw;
        }
        
    } catch (const char* msg) {
        cout << "Внешний catch: " << msg << endl;
    }
    
    return 0;
}
