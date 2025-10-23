#include <gtest/gtest.h>
#include "../include/lab3.h"
#include <sstream>

TEST(FigureTest, PointComparison) {
    Point p1(1.0, 2.0);
    Point p2(1.0, 2.0);
    Point p3(1.5, 2.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(FigureTest, SquareCreationAndValidation) {
    Square square;
    EXPECT_EQ(square.area(), 1.0);
    
    Point center = square.center();
    EXPECT_DOUBLE_EQ(center.x, 0.5);
    EXPECT_DOUBLE_EQ(center.y, 0.5);
    
    Square validSquare;
    std::istringstream validInput("0 0 2 0 2 2 0 2");
    EXPECT_NO_THROW(validSquare.read(validInput));
    
    Square invalidSquare;
    std::istringstream invalidInput("0 0 3 0 3 2 0 2");
    EXPECT_THROW(invalidSquare.read(invalidInput), std::invalid_argument);
}

TEST(FigureTest, RectangleCreationAndValidation) {
    Rectangle rect;
    EXPECT_EQ(rect.area(), 2.0);
    
    Point center = rect.center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 0.5);
    
    Rectangle validRect;
    std::istringstream validInput("0 0 4 0 4 2 0 2");
    EXPECT_NO_THROW(validRect.read(validInput));
}

TEST(FigureTest, TrapezoidCreationAndValidation) {
    Trapezoid trap;
    EXPECT_GT(trap.area(), 0);
    
    Trapezoid validTrap;
    std::istringstream validInput("0 0 5 0 4 3 1 3");
    EXPECT_NO_THROW(validTrap.read(validInput));
}

TEST(FigureTest, OperatorDouble) {
    Square square;
    std::istringstream input("0 0 4 0 4 4 0 4");
    square.read(input);
    
    double area = static_cast<double>(square);
    EXPECT_DOUBLE_EQ(area, 16.0);
}

TEST(FigureTest, InputOutputOperators) {
    Square square;
    std::istringstream input("1 1 3 1 3 3 1 3");
    input >> square;
    
    std::ostringstream output;
    output << square;
    EXPECT_EQ(output.str(), "1 1 3 1 3 3 1 3");
}

TEST(ArrayTest, BasicOperations) {
    Array array;
    
    EXPECT_EQ(array.getSize(), 0);
    EXPECT_EQ(array.totalArea(), 0.0);
    
    Square* square = new Square();
    std::istringstream squareInput("0 0 2 0 2 2 0 2");
    squareInput >> *square;
    array.add(square);
    
    EXPECT_EQ(array.getSize(), 1);
    EXPECT_DOUBLE_EQ(array.totalArea(), 4.0);
    
    array.remove(0);
    EXPECT_EQ(array.getSize(), 0);
    EXPECT_DOUBLE_EQ(array.totalArea(), 0.0);
}

TEST(ArrayTest, MultipleAdditions) {
    Array array;
    
    for (int i = 0; i < 5; ++i) {
        Square* square = new Square();
        std::istringstream input("0 0 1 0 1 1 0 1");
        input >> *square;
        array.add(square);
    }
    
    EXPECT_EQ(array.getSize(), 5);
    EXPECT_DOUBLE_EQ(array.totalArea(), 5.0);
}

TEST(FigureTest, GeometricCenters) {
    Square square;
    std::istringstream squareInput("0 0 4 0 4 4 0 4");
    squareInput >> square;
    
    Point squareCenter = square.center();
    EXPECT_DOUBLE_EQ(squareCenter.x, 2.0);
    EXPECT_DOUBLE_EQ(squareCenter.y, 2.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}