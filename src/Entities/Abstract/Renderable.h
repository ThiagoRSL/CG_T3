#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Utils/Pnt2.h"
#include "Managers/CameraManager.h"

class Renderable
{
    public:
        Renderable();
        virtual void Render()=0;
        void Static(bool isStatic){this->isStatic = isStatic;}
        bool Static(){return this->isStatic;}

    protected:
        Pnt2* CameraOffsetRef;
        bool isStatic;

    private:

};

#endif // RENDERABLE_H
