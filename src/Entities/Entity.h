#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <vector>
#include "Utils/Pnt2.h"
#include "Utils/Vec2.h"
#include "Poly.h"

class Entity : public Renderable
{
    public:
        Entity(float x, float y);
        void AppendPoly(Poly* poly);
        void Render();

        void Move(float speed);
        void Resize(float scalar);
        virtual void Rotate(float degrees);

    protected:
        Pnt2* Anchor;
        Vec2* OrientationVector;
        std::vector<Poly*> Parts;

        float background_color[3];

    public:
        Pnt2* GetAnchor() {return this->Anchor;}
};

#endif // ENTITY_H
