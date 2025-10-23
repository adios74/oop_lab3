#include "../include/lab3.h"
#include <iostream>
#include <stdexcept>

Point::Point(double x, double y) : x(x), y(y) {}

bool Point::operator==(const Point& other) const {
    return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
}

Figure::operator double() const { 
    return area(); 
}

Square::Square() {
    vertices[0] = Point(0, 0);
    vertices[1] = Point(1, 0);
    vertices[2] = Point(1, 1);
    vertices[3] = Point(0, 1);
}

Square::Square(const Square& other) {
    for (int i = 0; i < 4; i++) {
        vertices[i] = other.vertices[i];
    }
}

Square::Square(Square&& other) noexcept {
    for (int i = 0; i < 4; i++) {
        vertices[i] = other.vertices[i];
    }
}

Square& Square::operator=(const Square& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

Square& Square::operator=(Square&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

void Square::validate() const {
    double side1 = std::sqrt(std::pow(vertices[1].x - vertices[0].x, 2) + 
                            std::pow(vertices[1].y - vertices[0].y, 2));
    double side2 = std::sqrt(std::pow(vertices[2].x - vertices[1].x, 2) + 
                            std::pow(vertices[2].y - vertices[1].y, 2));
    double side3 = std::sqrt(std::pow(vertices[3].x - vertices[2].x, 2) + 
                            std::pow(vertices[3].y - vertices[2].y, 2));
    double side4 = std::sqrt(std::pow(vertices[0].x - vertices[3].x, 2) + 
                            std::pow(vertices[0].y - vertices[3].y, 2));
    
    if (std::abs(side1 - side2) > 1e-9 || std::abs(side2 - side3) > 1e-9 || 
        std::abs(side3 - side4) > 1e-9) {
        throw std::invalid_argument("У квадрата должны быть равные стороны");
    }
    
    double dot1 = (vertices[1].x - vertices[0].x) * (vertices[2].x - vertices[1].x) +
                  (vertices[1].y - vertices[0].y) * (vertices[2].y - vertices[1].y);
    double dot2 = (vertices[2].x - vertices[1].x) * (vertices[3].x - vertices[2].x) +
                  (vertices[2].y - vertices[1].y) * (vertices[3].y - vertices[2].y);
    
    if (std::abs(dot1) > 1e-9 || std::abs(dot2) > 1e-9) {
        throw std::invalid_argument("Углы квадрата должны быть прямыми");
    }
}

Point Square::center() const {
    double cx = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) / 4;
    double cy = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) / 4;
    return Point(cx, cy);
}

double Square::area() const {
    double side = std::sqrt(std::pow(vertices[1].x - vertices[0].x, 2) + 
                           std::pow(vertices[1].y - vertices[0].y, 2));
    return side * side;
}

void Square::print(std::ostream& os) const {
    for (int i = 0; i < 4; i++) {
        os << vertices[i].x << " " << vertices[i].y;
        if (i < 3) os << " ";
    }
}

void Square::read(std::istream& is) {
    for (int i = 0; i < 4; i++) {
        if (!(is >> vertices[i].x >> vertices[i].y)) {
            throw std::runtime_error("Невозможно обработать координаты квадрата");
        }
    }
    validate();
}

bool Square::operator==(const Figure& other) const {
    const Square* s = dynamic_cast<const Square*>(&other);
    if (!s) return false;
    
    for (int i = 0; i < 4; i++) {
        if (!(vertices[i] == s->vertices[i])) {
            return false;
        }
    }
    return true;
}

Figure* Square::clone() const {
    return new Square(*this);
}

Rectangle::Rectangle() {
    vertices[0] = Point(0, 0);
    vertices[1] = Point(2, 0);
    vertices[2] = Point(2, 1);
    vertices[3] = Point(0, 1);
}

Rectangle::Rectangle(const Rectangle& other) {
    for (int i = 0; i < 4; i++) {
        vertices[i] = other.vertices[i];
    }
}

Rectangle::Rectangle(Rectangle&& other) noexcept {
    for (int i = 0; i < 4; i++) {
        vertices[i] = other.vertices[i];
    }
}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

void Rectangle::validate() const {
    double side1 = std::sqrt(std::pow(vertices[1].x - vertices[0].x, 2) + 
                            std::pow(vertices[1].y - vertices[0].y, 2));
    double side2 = std::sqrt(std::pow(vertices[2].x - vertices[3].x, 2) + 
                            std::pow(vertices[2].y - vertices[3].y, 2));
    double side3 = std::sqrt(std::pow(vertices[2].x - vertices[1].x, 2) + 
                            std::pow(vertices[2].y - vertices[1].y, 2));
    double side4 = std::sqrt(std::pow(vertices[3].x - vertices[0].x, 2) + 
                            std::pow(vertices[3].y - vertices[0].y, 2));
    
    if (std::abs(side1 - side2) > 1e-9 || std::abs(side3 - side4) > 1e-9) {
        throw std::invalid_argument("Противоположные стороны прямоугольника не равны");
    }
    
    double dot = (vertices[1].x - vertices[0].x) * (vertices[2].x - vertices[1].x) +
                 (vertices[1].y - vertices[0].y) * (vertices[2].y - vertices[1].y);
    
    if (std::abs(dot) > 1e-9) {
        throw std::invalid_argument("Углы прямоугольника не прямые");
    }
}

Point Rectangle::center() const {
    double cx = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) / 4;
    double cy = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) / 4;
    return Point(cx, cy);
}

double Rectangle::area() const {
    double width = std::sqrt(std::pow(vertices[1].x - vertices[0].x, 2) + 
                            std::pow(vertices[1].y - vertices[0].y, 2));
    double height = std::sqrt(std::pow(vertices[2].x - vertices[1].x, 2) + 
                             std::pow(vertices[2].y - vertices[1].y, 2));
    return width * height;
}

void Rectangle::print(std::ostream& os) const {
    for (int i = 0; i < 4; i++) {
        os << vertices[i].x << " " << vertices[i].y;
        if (i < 3) os << " ";
    }
}

void Rectangle::read(std::istream& is) {
    for (int i = 0; i < 4; i++) {
        if (!(is >> vertices[i].x >> vertices[i].y)) {
            throw std::runtime_error("Невозможно прочитать координаты прямоугольника");
        }
    }
    validate();
}

bool Rectangle::operator==(const Figure& other) const {
    const Rectangle* r = dynamic_cast<const Rectangle*>(&other);
    if (!r) return false;
    
    for (int i = 0; i < 4; i++) {
        if (!(vertices[i] == r->vertices[i])) {
            return false;
        }
    }
    return true;
}

Figure* Rectangle::clone() const {
    return new Rectangle(*this);
}

Trapezoid::Trapezoid() {
    vertices[0] = Point(0, 0);
    vertices[1] = Point(4, 0);
    vertices[2] = Point(3, 2);
    vertices[3] = Point(1, 2);
}

Trapezoid::Trapezoid(const Trapezoid& other) {
    for (int i = 0; i < 4; i++) {
        vertices[i] = other.vertices[i];
    }
}

Trapezoid::Trapezoid(Trapezoid&& other) noexcept {
    for (int i = 0; i < 4; i++) {
        vertices[i] = other.vertices[i];
    }
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

void Trapezoid::validate() const {
    double dx1 = vertices[1].x - vertices[0].x;
    double dy1 = vertices[1].y - vertices[0].y;
    double dx2 = vertices[2].x - vertices[3].x;
    double dy2 = vertices[2].y - vertices[3].y;
    
    double cross = dx1 * dy2 - dy1 * dx2;
    
    if (std::abs(cross) > 1e-9) {
        throw std::invalid_argument("Основания трапеции не параллельны");
    }
}

Point Trapezoid::center() const {
    double cx = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) / 4;
    double cy = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) / 4;
    return Point(cx, cy);
}

double Trapezoid::area() const {
    double base1 = std::sqrt(std::pow(vertices[1].x - vertices[0].x, 2) + 
                            std::pow(vertices[1].y - vertices[0].y, 2));
    double base2 = std::sqrt(std::pow(vertices[2].x - vertices[3].x, 2) + 
                            std::pow(vertices[2].y - vertices[3].y, 2));
    double height = std::abs(vertices[2].y - vertices[0].y);
    return (base1 + base2) * height / 2;
}

void Trapezoid::print(std::ostream& os) const {
    for (int i = 0; i < 4; i++) {
        os << vertices[i].x << " " << vertices[i].y;
        if (i < 3) os << " ";
    }
}

void Trapezoid::read(std::istream& is) {
    for (int i = 0; i < 4; i++) {
        if (!(is >> vertices[i].x >> vertices[i].y)) {
            throw std::runtime_error("Невозможно обработать координаты трапеции");
        }
    }
    validate();
}

bool Trapezoid::operator==(const Figure& other) const {
    const Trapezoid* t = dynamic_cast<const Trapezoid*>(&other);
    if (!t) return false;
    
    for (int i = 0; i < 4; i++) {
        if (!(vertices[i] == t->vertices[i])) {
            return false;
        }
    }
    return true;
}

Figure* Trapezoid::clone() const {
    return new Trapezoid(*this);
}

Array::Array() : figures(new Figure*[10]), size(0), capacity(10) {
    for (int i = 0; i < capacity; i++) {
        figures[i] = nullptr;
    }
}

Array::~Array() {
    for (int i = 0; i < size; i++) {
        delete figures[i];
    }
    delete[] figures;
}

void Array::add(Figure* f) {
    if (size == capacity) {
        capacity *= 2;
        Figure** newArray = new Figure*[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = figures[i];
        }
        for (int i = size; i < capacity; i++) {
            newArray[i] = nullptr;
        }
        delete[] figures;
        figures = newArray;
    }
    figures[size++] = f;
}

void Array::remove(int index) {
    if (index < 0 || index >= size) return;
    
    delete figures[index];
    for (int i = index; i < size - 1; i++) {
        figures[i] = figures[i + 1];
    }
    figures[--size] = nullptr;
}

void Array::printAll() const {
    for (int i = 0; i < size; i++) {
        std::cout << "Figure " << i << ": ";
        figures[i]->print(std::cout);
        Point center = figures[i]->center();
        std::cout << " Center: (" << center.x << "," << center.y 
                  << ") Area: " << figures[i]->area() << std::endl;
    }
}

double Array::totalArea() const {
    double total = 0;
    for (int i = 0; i < size; i++) {
        total += figures[i]->area();
    }
    return total;
}

int Array::getSize() const {
    return size;
}

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.read(is);
    return is;
}