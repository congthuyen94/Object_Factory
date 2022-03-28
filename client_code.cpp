#include <iostream>
#include "factory.h"

enum SHAPE_TYPE
{
    LINE = 1,
    RECT = 2,
};

class Shape
{
public:
    virtual void Draw() = 0;
};
class Line : public Shape
{
    void Draw();
};

void Line::Draw()
{
    std::cout << "Draw a line\n";
}

Shape *CreateLine()
{
    return new Line;
}

typedef Shape *(*CreateShapeCallback)();

int main()
{
    // Create a factory of shape
    Factory<Shape, SHAPE_TYPE, CreateShapeCallback> shape_factory;
    shape_factory.Register(SHAPE_TYPE::LINE, CreateLine);
    try {
        Shape *s = shape_factory.CreateObject(SHAPE_TYPE::LINE);
        s->Draw();
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << "\n";
    }
    return 0;
}