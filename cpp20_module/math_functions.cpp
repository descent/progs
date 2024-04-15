export module functions;

import <iostream>;

export int int_add(int a, int b) {
    return a + b;
}

#if 0
export int subtract(int a, int b) {
    return a - b;
}

export int multiply(int a, int b) {
    return a * b;
}
#endif

export template<typename T>
T add(T a, T b) {
    return a + b;
}

export template<typename T>
T subtract(T a, T b) {
    return a - b;
}

// export module math_functions;

export struct Point 
{
    int x;
    int y;
};

export Point createPoint(int x, int y) 
{
    return {x, y};
}

export 
class Line
{
  public:
    Line(int x, int y):x_(x), y_(y)
    {
    }
    void print()
    {
      printf("x_: %d, y_: %d\n", x_, y_);
      std::cout << "x_: " << x_ << std::endl;
    }
  private:
    int x_;
    int y_;
};



export void printMessage() 
{
  std::cout << "Hello again from math_functions.cpp by iostream" << std::endl;
}

export void print_msg() 
{
  std::printf("Hello again from math_functions.cpp by printf!\n");
}
