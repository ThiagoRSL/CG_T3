#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include <map>
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
        void addWall(Curve2d* wall);
        Character* VerifyCollisionNPCs(float x, float y);
        Character* VerifyCollisionPlayer(float x, float y);
        void CheckCollisions();
        bool VerifyCollisionWalls(Character* character);

    protected:

    private:
        std::vector<std::map<Character*, int>*> CharactersWallNearestPoint;
        Character* player_character;
        std::vector<Character*> Characters;
        std::vector<Curve2d*> Walls;
};

#endif // COLLISIONMANAGER_H
