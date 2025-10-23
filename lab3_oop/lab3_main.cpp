#include "./include/lab3.h"
#include <iostream>
#include <limits>

void showMenu() {
    std::cout << "\n=== МЕНЮ ===\n";
    std::cout << "1. Добавить квадрат\n";
    std::cout << "2. Добавить прямоугольник\n";
    std::cout << "3. Добавить трапецию\n";
    std::cout << "4. Удалить фигуру по индексу\n";
    std::cout << "5. Показать все фигуры\n";
    std::cout << "6. Показать общую площадь\n";
    std::cout << "7. Выход\n";
    std::cout << "Выберите действие: ";
}

int main() {
    Array figures;
    int choice;
    
    while (true) {
        showMenu();
        std::cin >> choice;
        
        try {
            switch (choice) {
                case 1: {
                    std::cout << "Введите 8 координат квадрата (x1 y1 x2 y2 x3 y3 x4 y4): ";
                    Square* square = new Square();
                    std::cin >> *square;
                    figures.add(square);
                    std::cout << "✓ Квадрат добавлен\n";
                    break;
                }
                case 2: {
                    std::cout << "Введите 8 координат прямоугольника (x1 y1 x2 y2 x3 y3 x4 y4): ";
                    Rectangle* rect = new Rectangle();
                    std::cin >> *rect;
                    figures.add(rect);
                    std::cout << "✓ Прямоугольник добавлен\n";
                    break;
                }
                case 3: {
                    std::cout << "Введите 8 координат трапеции (x1 y1 x2 y2 x3 y3 x4 y4): ";
                    Trapezoid* trap = new Trapezoid();
                    std::cin >> *trap;
                    figures.add(trap);
                    std::cout << "✓ Трапеция добавлена\n";
                    break;
                }
                case 4: {
                    if (figures.getSize() == 0) {
                        std::cout << "Нет фигур для удаления\n";
                        break;
                    }
                    std::cout << "Текущие фигуры:\n";
                    figures.printAll();
                    std::cout << "Введите индекс для удаления: ";
                    int index;
                    std::cin >> index;
                    figures.remove(index);
                    std::cout << "Фигура удалена\n";
                    break;
                }
                case 5: {
                    if (figures.getSize() == 0) {
                        std::cout << "Нет фигур для отображения\n";
                    } else {
                        std::cout << "Список всех фигур:\n";
                        figures.printAll();
                    }
                    break;
                }
                case 6: {
                    if (figures.getSize() == 0) {
                        std::cout << "Нет фигур для вычисления площади\n";
                    } else {
                        std::cout << "Общая площадь всех фигур: " << figures.totalArea() << "\n";
                    }
                    break;
                }
                case 7: {
                    std::cout << "Выход из программы...\n";
                    return 0;
                }
                default: {
                    std::cout << "Неверный выбор. Попробуйте снова.\n";
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    return 0;
}