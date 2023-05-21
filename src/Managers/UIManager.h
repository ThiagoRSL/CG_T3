#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <stdio.h>
#include <vector>

#include "Entity.h"
#include "PlayerManager.h"
#include "RenderManager.h"

class UIManager
{
    public:
        UIManager();
        static UIManager &shared_instance() {static UIManager uiManager; return uiManager;}

        void OpenInventory();
        void OpenCharacterStats();

    private:
        bool show_inventory;
        bool show_character_stats;
        //std::vector<ShipPart*>
        Entity* CharacterProjection;

};

#endif // UIMANAGER_H
