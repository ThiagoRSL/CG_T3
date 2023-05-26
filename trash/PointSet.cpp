#include "PointSet.h"

PointSet::PointSet()
{

}

void PointSet::SetColor(float* rgb)
{
    this->RGB[0] = rgb[0];
    this->RGB[1] = rgb[1];
    this->RGB[2] = rgb[2];
    return;
}

void PointSet::AddPoint(float x, float y)
{
    Points.push_back(new Pnt2(x, y));
}

void PointSet::RemovePoint(float x, float y)
{
    int i;
    for (i = 0; i < Points.size(); i++)
    {
        if(Points.at(i)->x == x && Points.at(i)->y == y)
        {
            Points.erase(Points.begin()+i);
            return;
        }
    }
}

void PointSet::Render()
{
    glColor4f(this->RGB[0], this->RGB[1], this->RGB[2], 1);

    float virtualX, virtualY;
    if(!this->isStatic)
    {
        virtualX = Anchor->x + Offset.x - CameraOffsetRef->x;
        virtualY = Anchor->y + Offset.y - CameraOffsetRef->y;
    }
    else
    {
        virtualX = StaticOffset.x + Offset.x;
        virtualY = StaticOffset.y + Offset.y;
    }
    int i;
    glBegin(GL_POINTS);
    for(i = 0; i < Points.size(); i++)
    {
        Pnt2* p = Points.at(i);
        glVertex2d(virtualX + p->x, virtualY + p->y);
    }
    glEnd();

}
