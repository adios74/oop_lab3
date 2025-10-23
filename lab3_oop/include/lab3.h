#ifndef LAB3_H
#define LAB3_H

#include <iostream>
#include <cmath>

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0);
    bool operator==(const Point& other) const;
};

class Figure {
public:
    virtual ~Figure() = default;
    virtual Point center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual bool operator==(const Figure& other) const = 0;
    virtual Figure* clone() const = 0;
    
    operator double() const;
};

class Square : public Figure {
private:
    Point vertices[4];
    void validate() const;
    
public:
    Square();
    Square(const Square& other);
    Square(Square&& other) noexcept;
    Square& operator=(const Square& other);
    Square& operator=(Square&& other) noexcept;
    
    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    bool operator==(const Figure& other) const override;
    Figure* clone() const override;
};

class Rectangle : public Figure {
private:
    Point vertices[4];
    void validate() const;
    
public:
    Rectangle();
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;
    
    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    bool operator==(const Figure& other) const override;
    Figure* clone() const override;
};

class Trapezoid : public Figure {
private:
    Point vertices[4];
    void validate() const;
    
public:
    Trapezoid();
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;
    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;
    
    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    bool operator==(const Figure& other) const override;
    Figure* clone() const override;
};

class Array {
private:
    Figure** figures;
    int size;
    int capacity;
    
public:
    Array();
    ~Array();
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;
    Array(Array&&) = delete;
    Array& operator=(Array&&) = delete;
    
    void add(Figure* f);
    void remove(int index);
    void printAll() const;
    double totalArea() const;
    int getSize() const;
};

std::ostream& operator<<(std::ostream& os, const Figure& fig);
std::istream& operator>>(std::istream& is, Figure& fig);

#endif