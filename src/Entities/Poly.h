#ifndef POLY_H
#define POLY_H

#include <stdio.h>
#include <vector>
#include "Utils/Vec2.h"
#include "Managers/RenderManager.h"
#include "Managers/CollisionManager.h"
#include "Managers/CameraManager.h"
#include "Utils/GeometryAux.h"

class Poly : public Renderable
{
    public:
        Poly();
        Poly(float x, float y);
        Poly(float x, float y, float RGB[3]);

        void SetAnchor(float x, float y);
        void SetAnchor(Pnt2* Anchor);
        void SetOrientation(float x, float y);
        void AddVertex(Vec2* vertex);
        void AddVertex(float x, float y);
        void Resize(float scalar);
        void virtual Rotate(float degrees);
        void RotateRad(float radians);
        void Transform(float matrix[2][2]);
        void virtual Move(float speed);
        void virtual Move(Vec2* directionVector, float speed);
        bool HasCollision(float x, float y);


        void SetBackgroundColor(float* color);
        void Render();
    protected:
        float background_color[4];
        float border_color[4];
        float rotation;

        Pnt2* Anchor;
        Vec2* OrientationVector;
        std::vector<Vec2*> Vertexes;

        void RenderBody();
        void RenderBorder();
        void RenderVertexes();

    public:
        Vec2 Offset;
        Vec2 StaticOffset;
        void SetOffset(float x, float y)
        {
            Offset.x = x;
            Offset.y = y;
        }
        void SetStaticOffset(float x, float y)
        {
            StaticOffset.x = x;
            StaticOffset.y = y;
        }
        Vec2* GetOrientation(){return this->OrientationVector;}
        Poly* GetCopy()
        {
            float RGBCopy[3] = {background_color[0], background_color[1], background_color[2]};
            Poly* polyCopy = new Poly(this->Anchor->x, this->Anchor->y);
            polyCopy->SetBackgroundColor(RGBCopy);
            polyCopy->SetOffset(Offset.x, Offset.y);
            int i = 0;
            for(i = 0; i < Vertexes.size(); i++)
            {
                polyCopy->AddVertex(Vertexes.at(i)->GetCopy());
            }
            return polyCopy;
        }

};

#endif // POLYGON_H
