#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Character/Character.h"

class PlayerManager
{
    public:
        PlayerManager();
        static PlayerManager &shared_instance() {static PlayerManager playerManager; return playerManager;}

        void SetPlayerCharacter(Character* character);
        void CheckInteraction();

    protected:

    private:
        Character* PlayerCharacter;
};

#endif // PLAYERMANAGER_H
