#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Managers/FPSManager.h"
#include "Entities/Poly.h"
#include "Particle.h"

class Character;
class PlayerManager;

class Projectile : public Poly
{
    public:
        Projectile(float x, float y, float damage, float speed, float maxDistance, float *RGB, Character* Owner);
        void DestroyProjectile();

        void Render();
    protected:
        float damage;
        float speed;
        float max_distance;
        Pnt2 CreatedAt;

        Character* Owner;
        Particle* Trail;

    private:
        float RGB[3];
};

#endif // PROJECTILE_H
