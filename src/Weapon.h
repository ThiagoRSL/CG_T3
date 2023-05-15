#ifndef WEAPON_H
#define WEAPON_H

#include <Poly.h>

class Character;

class Weapon : public Poly
{
    public:
        Weapon(Character* Wielder);
        void AdjustWeapon();

    protected:

    private:
};

#endif // WEAPON_H
