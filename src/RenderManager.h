#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "MouseManager.h"
#include "Renderable.h"

typedef void (*callback_function)(void);

class RenderManager
{
    public:
        static RenderManager &shared_instance() {static RenderManager renderManager; return renderManager;}
        RenderManager();
        void RenderAll();
        void AddRenderableToList(Renderable* element);
        void RemoveRenderableFromList(Renderable* element);
        void SetFirstPosition(Renderable* element);
        //AddToRenderQueue(Renderizable element, int priority_level);

    protected:

    private:
        std::vector<Renderable*> renderList;


};

#endif // RENDERMANAGER_H

