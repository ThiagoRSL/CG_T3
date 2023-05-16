#include "Pnt2.h"
#include "Vec2.h"

Pnt2::Pnt2()
{
    //ctor
}

Pnt2::Pnt2(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Pnt2::ApplyVec2(Vec2 vec)
{
    this->x = this->x + vec.x;
    this->y = this->y + vec.y;
}

/*
Pnt2 Pnt2::operator+ (const Vec2& vec)
{
    Pnt2 aux(x + vec.x, y + vec.y);
    return (aux);
}
Pnt2 Pnt2::operator+= (const Vec2& vec)
{
    this->x = this->x + vec.x;
    this->y = this->y + vec.y;
}*/
