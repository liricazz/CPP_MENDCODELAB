#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() {}
};

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {
        if (w <= 0 || h <= 0) {
            throw "Ошибка: стороны прямоугольника должны быть положительными!";
        }
    }
    
    double area() const override {
        return width * height;
    }
    
    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {
        if (r <= 0) {
            throw "Ошибка: радиус должен быть положительным!";
        }
    }
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double getRadius() const { return radius; }
};

class Triangle : public Shape {
private:
    double a, b, c;
    
public:
    Triangle(double s1, double s2, double s3) : a(s1), b(s2), c(s3) {
        if (s1 <= 0 || s2 <= 0 || s3 <= 0) {
            throw "Ошибка: стороны должны быть положительными!";
        }
        if (s1 + s2 <= s3 || s1 + s3 <= s2 || s2 + s3 <= s1) {
            throw "Ошибка: треугольник с такими сторонами не существует!";
        }
    }
    
    double area() const override {
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    
    double getSideA() const { return a; }
    double getSideB() const { return b; }
    double getSideC() const { return c; }
};

class Color {
private:
    string colorName;

public:
    Color(string c = "белый") : colorName(c) {}
    void setColor(string c) { colorName = c; }
    string getColor() const { return colorName; }
};

class ColoredShape : public Shape, public Color {
private:
    Shape* shape;

public:
    ColoredShape(Shape* s, string c) : shape(s), Color(c) {}
    
    double area() const override {
        return shape->area();
    }
    
    ~ColoredShape() {
        delete shape;
    }
};

class ShapePrinter {
public:
    static void print(const Rectangle& r) {
        cout << "Прямоугольник: ширина = " << r.getWidth() 
             << ", высота = " << r.getHeight()
             << ", площадь = " << r.area() << endl;
    }
    
    static void print(const Circle& c) {
        cout << "Круг: радиус = " << c.getRadius()
             << ", площадь = " << c.area() << endl;
    }
    
    static void print(const Triangle& t) {
        cout << "Треугольник: стороны = " << t.getSideA() << ", " 
             << t.getSideB() << ", " << t.getSideC()
             << ", площадь = " << t.area() << endl;
    }
};

int main() {
    try {
        cout << "Введите стороны прямоугольника (ширина и высота): ";
        double w, h;
        cin >> w >> h;
        Rectangle rect(w, h);
        
        cout << "Введите радиус круга: ";
        double r;
        cin >> r;
        Circle circle(r);
        
        cout << "Введите стороны треугольника (a, b, c): ";
        double a, b, c;
        cin >> a >> b >> c;
        Triangle triangle(a, b, c);

        cout << "\n--- ИНФОРМАЦИЯ О ФИГУРАХ ---" << endl;
        ShapePrinter::print(rect);
        ShapePrinter::print(circle);
        ShapePrinter::print(triangle);

        cout << "\n--- ЦВЕТНЫЕ ФИГУРЫ ---" << endl;
        cout << "Введите цвет для прямоугольника: ";
        string color;
        cin >> color;
        ColoredShape coloredRect(new Rectangle(w, h), color);
        cout << coloredRect.getColor() << " прямоугольник, площадь = " 
             << coloredRect.area() << endl;

        double (Shape::*areaPtr)() const = &Shape::area;
        cout << "Площадь прямоугольника через указатель: " 
             << (rect.*areaPtr)() << endl;
        cout << "Площадь круга через указатель: " 
             << (circle.*areaPtr)() << endl;
        
    } catch (const char* msg) {
        cout << msg << endl;
    }
    
    return 0;
}