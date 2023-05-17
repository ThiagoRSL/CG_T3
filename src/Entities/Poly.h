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
        void Rotate(float degrees);
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

        Vec2 Offset;
        Pnt2* Anchor;
        Vec2* OrientationVector;
        std::vector<Vec2*> Vertexes;

        void RenderBody();
        void RenderBorder();
        void RenderVertexes();

    public:
        void SetOffset(float x, float y)
        {
            Offset.x = x;
            Offset.y = y;
        }
        Vec2* GetOrientation(){return this->OrientationVector;}

};

#endif // POLYGON_H
