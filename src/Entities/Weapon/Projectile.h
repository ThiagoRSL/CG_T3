#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Managers/FPSManager.h"
#include "Entities/Poly.h"

class Character;

class Projectile : public Poly
{
    public:
        Projectile(float x, float y, float damage, float speed, Character* Owner);
        void DestroyProjectile();

        void Render();
    protected:
        float damage;
        float speed;

        Character* Owner;

    private:
};

#endif // PROJECTILE_H
