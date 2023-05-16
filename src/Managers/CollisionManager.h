#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
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
        Character* VerifyCollisionNPCs(float x, float y);
        Character* VerifyCollisionPlayer(float x, float y);
    protected:

    private:
        Character* player_character;
        std::vector<Character*> npcs;
};

#endif // COLLISIONMANAGER_H
