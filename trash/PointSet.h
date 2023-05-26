#ifndef POINTSET_H
#define POINTSET_H

#include <vector>
#include "Utils/Pnt2.h"
#include "Utils/Vec2.h"
#include "Abstract/Renderable.h"

class PointSet : public Renderable
{
    public:
        PointSet();

        void SetColor(float* rgb);
        void AddPoint(float x, float y);
        void RemovePoint(float x, float y);

        void Render();

    protected:
        float RGB[3];
        std::vector<Pnt2*> Points;

        Pnt2* Anchor;
        Vec2 Offset;
        Vec2 StaticOffset;

    public:
        virtual void SetOffset(float x, float y)
        {
            Offset.x = x;
            Offset.y = y;
        }
        void SetStaticOffset(float x, float y)
        {
            StaticOffset.x = x;
            StaticOffset.y = y;
        }
        void SetAnchor(Pnt2* Anchor) {this->Anchor = Anchor;}
;
};

#endif // POINTSET_H
