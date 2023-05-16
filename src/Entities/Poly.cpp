#include "Poly.h"

Poly::Poly()
{
    this->Anchor = new Pnt2(0, 0);
    this->OrientationVector = new Vec2();
    this->OrientationVector->SetAnchor(this->Anchor);
    rotation = 0;
}

Poly::Poly(float x, float y)
{
    this->Anchor = new Pnt2(x, y);
    this->OrientationVector = new Vec2(0, 1);
    this->OrientationVector->SetAnchor(this->Anchor);
    rotation = 0;
}

Poly::Poly(float x, float y, float RGB[3])
{
    this->Anchor = new Pnt2(x, y);
    this->OrientationVector = new Vec2(0, 1);
    this->OrientationVector->SetAnchor(this->Anchor);
    background_color[0] = RGB[0];
    background_color[1] = RGB[1];
    background_color[2] = RGB[2];
    rotation = 0;
}

void Poly::Move(float speed)
{
    Vec2 moveVec = (*OrientationVector * speed);
    this->Anchor->ApplyVec2(moveVec);
}
void Poly::Move(Vec2 directionVector, float speed)
{
    Vec2 moveVec = (directionVector * speed);
    this->Anchor->ApplyVec2(moveVec);
}

void Poly::SetAnchor(float x, float y)
{
    this->Anchor->x = x;
    this->Anchor->y = y;
}
void Poly::SetAnchor(Pnt2* Anchor)
{
    this->Anchor = Anchor; //MEMORY
}

void Poly::SetOrientation(float x, float y)
{
    this->OrientationVector->x = x;
    this->OrientationVector->y = y;
}

void Poly::AddVertex(Vec2* vertex)
{
    vertex->SetAnchor(this->Anchor);
    this->Vertexes.push_back(vertex);
}

void Poly::AddVertex(float x, float y)
{
    Vec2* vertex = new Vec2(x, y);
    vertex->SetAnchor(this->Anchor);
    this->Vertexes.push_back(vertex);
}

void Poly::Resize(float scalar)
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->Mult(scalar);
    }
}

void Poly::RotateRad(float radians)
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->RotateRadians(radians);
    }
    OrientationVector->RotateRadians(radians);
}

void Poly::Rotate(float degrees)
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->RotateDegrees(degrees);
    }
    OrientationVector->RotateDegrees(degrees);

    rotation += degrees;

    if(rotation > 360)
        rotation -= 360;
    else if(rotation < 0)
        rotation += 360;
}

void Poly::Transform(float matrix[2][2])
{
    int i;
    float x, y, newX, newY;
    for(i = 0; i < Vertexes.size(); i++)
    {
        x = Vertexes.at(i)->x;
        y = Vertexes.at(i)->y;
        newX = x * matrix[0][0] + y * matrix[0][1];
        newY = x * matrix[1][0] + y * matrix[1][1];
        Vertexes.at(i)->x = newX;
        Vertexes.at(i)->y = newY;
    }
}

void Poly::Render()
{
    //this->RenderVertex();
    this->RenderBody();
    //this->RenderBorder();
}

void Poly::RenderBody()
{
    CV::color(background_color[0], background_color[1], background_color[2]);
    int i, a;
    for(i = 0; i < Vertexes.size(); i++)
    {
        if(i != Vertexes.size()-1)
            a = i+1;
        else
            a = 0;

        float vx[3] = {Anchor->x, Anchor->x + Vertexes.at(i)->x, Anchor->x + Vertexes.at(a)->x};
        float vy[3] = {Anchor->y, Anchor->y + Vertexes.at(i)->y, Anchor->y + Vertexes.at(a)->y};
        CV::polygonFill(vx, vy, 3);
    }
}

void Poly::RenderBorder()
{

}

void Poly::RenderVertexes()
{
    int i;
    for(i = 0; i < Vertexes.size(); i++)
    {
        Vertexes.at(i)->Render();
    }
}

bool Poly::HasCollision(float x, float y)
{
    int i, a;
    for(i = 0; i < Vertexes.size(); i++)
    {
        if(i != Vertexes.size()-1)
            a = i+1;
        else
            a = 0;

        int counter = 0;
        if(GeometryAux::Intercept(8000, 8000, x, y, this->Anchor->x, this->Anchor->y, Anchor->x + this->Vertexes.at(i)->x, Anchor->y + this->Vertexes.at(i)->y))
        {
            counter += 1;
        }
        if(GeometryAux::Intercept(8000, 8000, x, y, this->Anchor->x, this->Anchor->y, Anchor->x + this->Vertexes.at(a)->x, Anchor->y + this->Vertexes.at(a)->y))
        {
            counter += 1;
        }
        if(GeometryAux::Intercept(8000, 8000, x, y, Anchor->x + this->Vertexes.at(i)->x, Anchor->y + this->Vertexes.at(i)->y, Anchor->x + this->Vertexes.at(a)->x, Anchor->y + this->Vertexes.at(a)->y))
        {
            counter += 1;
        }
        if(counter%2 == 1) return true;
    }

    return false;
}
