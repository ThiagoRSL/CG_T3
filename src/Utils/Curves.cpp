#include "Curves.h"

Curve2d::Curve2d()
{
    show_control_graph = false;
    curve_resolution = 1;
    show_with_lines = false;
    this->Anchor = new Pnt2(0,0);
}

BSpline::BSpline()
    :Curve2d()
{

}

Bezier::Bezier()
    :Curve2d()
{

}


void Curve2d::AddControlPoint(Pnt2* point)
{
    ControlPoints.push_back(point);
}

void Curve2d::Render()
{
    float virtualX, virtualY;
    if(!this->isStatic)
    {
        virtualX = Anchor->x;
        virtualX += Offset.x;
        virtualX -= CameraOffsetRef->x;
        virtualY = Anchor->y + Offset.y - CameraOffsetRef->y;
    }
    else
    {
        virtualX = StaticOffset.x + Offset.x;
        virtualY = StaticOffset.y + Offset.y;
    }

    int i;
    if(show_control_graph)
    {
        CV::color(1, 0, 0);
        for(i = 0; i < ControlPoints.size()-1; i++)
        {
            Pnt2* c0 = ControlPoints.at(i);
            Pnt2* c1 = ControlPoints.at(i+1);
            CV::line(c0->x + virtualX, c0->y + virtualY, c1->x + virtualX, c1->y + virtualY);
        }
    }
    if(show_with_lines)
    {
        RenderWithLines();
    }
    else
    {
        RenderWithPoints();
    }
}

void Curve2d::RenderWithLines()
{
    float virtualX, virtualY;
    if(!this->isStatic)
    {
        virtualX = Anchor->x;
        virtualX += Offset.x;
        virtualX -= CameraOffsetRef->x;
        virtualY = Anchor->y + Offset.y - CameraOffsetRef->y;
    }
    else
    {
        virtualX = StaticOffset.x + Offset.x;
        virtualY = StaticOffset.y + Offset.y;
    }

    int i, j;
    float t, div = ControlPoints.size()*curve_resolution;
    glColor3f(Color[0], Color[1], Color[2]);
    glBegin(GL_LINES);
    for(i = 0; i < CurvePoints.size()-1; i++)
    {
        Pnt2* point = CurvePoints.at(i);
        Pnt2* pointPlus = CurvePoints.at(i+1);
        glVertex2d(point->x + virtualX, point->y + virtualY);
        glVertex2d(pointPlus->x + virtualX, pointPlus->y + virtualY);
    }
    glEnd();
}

void Curve2d::RenderWithPoints()
{
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

    int i, j;
    float t, div = ControlPoints.size()*curve_resolution;
    glColor3f(Color[0], Color[1], Color[2]);
    glBegin(GL_POINTS);
    for(i = 0; i < CurvePoints.size(); i++)
    {
        Pnt2* point = CurvePoints.at(i);

        glVertex2d(point->x + virtualX, point->y + virtualY);
    }
    glEnd();
}

Pnt2* Curve2d::GetCurvePoint(int i)
{
    if(i < 0 || i >= CurvePoints.size()) return nullptr;
    return CurvePoints.at(i);
}

Pnt2* Curve2d::NearPoint(Pnt2 point, float distanceMin)
{
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
    for(i = 0; i < CurvePoints.size(); i++)
    {
        CV::color(3);
        Pnt2 p = Pnt2(CurvePoints.at(i)->x + virtualX, CurvePoints.at(i)->y + virtualY);
        //CV::point(p.x, p.y);
        //CV::point(point.x, point.y);
        if(GeometryAux::DistanceBetween(&p, &point) < distanceMin)
        {
            return new Pnt2(CurvePoints.at(i)->x + virtualX, CurvePoints.at(i)->y + virtualY);
        }
    }
    return nullptr;
}

void BSpline::GenerateCurvePoints()
{
    int i, j;
    float t, div = ControlPoints.size()*curve_resolution;

    for(i = 0; i < ControlPoints.size()-3; i++)
    {
        for(t = 0.0; t < 1; t += 1/div)
        {
            Pnt2* p0 = ControlPoints.at(i);
            Pnt2* p1 = ControlPoints.at(i+1);
            Pnt2* p2 = ControlPoints.at(i+2);
            Pnt2* p3 = ControlPoints.at(i+3);

            float px = ((1 - t)*(1 - t)*(1 - t)/6)*p0->x + (((3*t*t*t) - 6*t*t + 4)/6)*p1->x + (((-3*t*t*t) + (3*t*t) + (3*t) + 1)/6)*p2->x + ((t*t*t)/6)*p3->x;
            float py = ((1 - t)*(1 - t)*(1 - t)/6)*p0->y + (((3*t*t*t) - 6*t*t + 4)/6)*p1->y + (((-3*t*t*t) + (3*t*t) + (3*t) + 1)/6)*p2->y + ((t*t*t)/6)*p3->y;
            Pnt2* newPoint = new Pnt2(px, py);
            CurvePoints.push_back(newPoint);
        }
    }
}

void Bezier::GenerateCurvePoints()
{
    int i, j;
    float t, div = ControlPoints.size()*curve_resolution;

    Pnt2* p0 = ControlPoints.at(0);
    Pnt2* p1 = ControlPoints.at(1);
    Pnt2* p2 = ControlPoints.at(2);

    for(t = 0.0; t < 1; t += 1/div)
    {
        float px = p0->x*(1 - t)*(1 - t) + p1->x*(2*t*(1-t)) + p2->x*(t*t);
        float py = p0->y*(1 - t)*(1 - t) + p1->y*(2*t*(1-t)) + p2->y*(t*t);
        Pnt2* newPoint = new Pnt2(px, py);
        CurvePoints.push_back(newPoint);
    }
}
