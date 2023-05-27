#ifndef CURVES_H
#define CURVES_H

#include "gl_canvas2d.h"
#include <vector>
#include "Entities/Abstract/Renderable.h"
#include "Pnt2.h"
#include "GeometryAux.h"

class BSpline : public Renderable
{
    public:
        BSpline();

        void AddControlPoint(Pnt2* point);
        void Render();
        void SetColor(float* color) {Color[0] = color[0];Color[1] = color[1];Color[2] = color[2];}
        void SetShowControlGraph(bool show) {show_control_graph = show;}
        void SetShowWithLines(bool show) {show_with_lines = show;}
        void SetCurveResolution(bool resolution) {curve_resolution = resolution;}
        void GenerateCurvePoints();
        Pnt2* NearPoint(Pnt2 point, float distanceMin);

    private:
        bool show_control_graph;
        bool show_with_lines;
        int curve_resolution;
        float Color[3];
        std::vector<Pnt2*> ControlPoints;
        std::vector<Pnt2*> CurvePoints;
        void RenderWithLines();
        void RenderWithPoints();
};

#endif // CURVES_H
