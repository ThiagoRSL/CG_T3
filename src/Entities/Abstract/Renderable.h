#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Utils/Pnt2.h"
#include "Managers/CameraManager.h"

class Renderable
{
    public:
        Renderable();
        virtual void Render()=0;

    protected:
        Pnt2* CameraOffsetRef;

    private:
};

#endif // RENDERABLE_H
