import functions;

#include <iostream>
#include <cstdio>

int main() {
#if 0
    int x = 10;
    int y = 5;

    std::cout << "x + y = " << add(x, y) << std::endl;
    std::cout << "x - y = " << subtract(x, y) << std::endl;
    std::cout << "x + y = " << add(10.5, 1.2) << std::endl;
    //std::cout << "x * y = " << multiply(x, y) << std::endl;
#endif
    Point p1 = createPoint(3, 4);
    Point p2 = {1, 2};

    std::cout << "p1.x = " << p1.x << ", p1.y = " << p1.y << std::endl;
    std::cout << "p2.x = " << p2.x << ", p2.y = " << p2.y << std::endl;
    Line line{1,2};
    line.print();
    printMessage();
    print_msg();
    return 0;
}
