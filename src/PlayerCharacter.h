#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include <Character.h>


class PlayerCharacter : public Character
{
    public:
        PlayerCharacter(float x, float y, float RGB[3]);
        void AdjustAim();


    protected:

    private:
};

#endif // PLAYERCHARACTER_H
