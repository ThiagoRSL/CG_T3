#ifndef HOOMINGPROJECTILE_H
#define HOOMINGPROJECTILE_H

#include "Projectile.h"


class HoomingProjectile : public Projectile
{
    public:
        HoomingProjectile(float x, float y, float damage, float speed, float maxDistance, float *RGB, Character* Owner);

        void Render();

    protected:

    private:
        float lastFrame;
};

#endif // HOOMINGPROJECTILE_H
