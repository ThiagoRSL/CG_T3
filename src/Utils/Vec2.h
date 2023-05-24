#ifndef VEC2_H
#define VEC2_H

#include <math.h>
#include "Entities/Abstract/Renderable.h"
#include "gl_canvas2d.h"
#include "Utils/Pnt2.h"

class GeometryAux;


class Vec2 : public Renderable
{
    public:
        Pnt2* anchor;
        float x, y;
        float RelativeX(){return this->anchor->x + x;}
        float RelativeY(){return this->anchor->y + y;}

        Vec2();
        Vec2(float v[2]);
        Vec2(float x, float y);
        Vec2(float x, float y, Pnt2* anchor);

        // Setters
        void SetAnchor(Pnt2* point);
        // Getters
        float GetNorm();
        float DotProduct(Vec2* v);
        float Determinant(Vec2* v);

        float GetAngleBetween(Vec2* v);

        Vec2 operator* (const float& scalar)
        {
            Vec2 aux(x * scalar, y * scalar);
            return (aux);
        }
        Vec2 operator+ (const Vec2& vec)
        {
            Vec2 aux(x + vec.x, y + vec.y);
            return (aux);
        }
        // Opera��es no pr�prio vetor
        void Mult(float scalar);
        void Sum(float scalar);
        void Sum(Vec2& v2);
        void Sum(Vec2* v2);
        void Sub(Vec2* v2);

        void ApplyAtPoint();
        // Normaliza o proprio vetor
        void Normalize();
        // Rotaciona o vetor em alguns graus
        void RotateDegrees(float degrees);
        void RotateRadians(float radians);

        void Render();

    public:
        Vec2* GetCopy()
        {
            Vec2* vecCopy = new Vec2(this->x, this->y);
            Pnt2* anchorCopy = new Pnt2(this->anchor->x, this->anchor->y);
            vecCopy->SetAnchor(anchorCopy);
            return vecCopy;
        }

};

#endif // VEC2_H
