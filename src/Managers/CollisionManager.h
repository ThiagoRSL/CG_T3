#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "Curves.h"
class Character;

class CollisionManager
{
    public:
        static CollisionManager &shared_instance() {static CollisionManager collisionManager; return collisionManager;}
        CollisionManager();

        Character* GetPlayerCharacter();
        void SetPlayerCharacter(Character* player_character);
        void AddNPC(Character* character);
        void RemoveNPC(Character* character);
        void addWall(BSpline* wall);
        Character* VerifyCollisionNPCs(float x, float y);
        Character* VerifyCollisionPlayer(float x, float y);
        bool VerifyCollisionWalls(Character* character, int distance);

    protected:

    private:
        Character* player_character;
        std::vector<Character*> npcs;
        std::vector<BSpline*> Walls;
};

#endif // COLLISIONMANAGER_H
