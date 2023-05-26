#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "Utils/Pnt2.h"
#include "Managers/CameraManager.h"

class Renderable
{
    public:
        Renderable();
        virtual void Render()=0;

    protected:
        Pnt2* CameraOffsetRef;
        bool isStatic;

    public:
        void Static(bool isStatic){this->isStatic = isStatic;}
        bool Static(){return this->isStatic;}

};

#endif // RENDERABLE_H
