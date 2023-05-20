#ifndef WEAPON_H
#define WEAPON_H

#include <Entities/Poly.h>
#include <Entities/Weapon/Projectile.h>

class Character;
class WeaponSlot;

class Weapon : public Poly
{
    public:
        Weapon();
        void AdjustWeapon();

        void EquipOn(WeaponSlot* slot);
        void Shoot();
        float CalcShotDamage();

        void RefreshShotCooldown();
    protected:

    private:
        Character* Wielder;
        WeaponSlot* SlottedOn;

        float shot_cooldown_base;
        float damage_base;
        float energy_cost_base;
        float accuracy_base;
        float max_ammo_base;

        float shot_cooldown_val;
        float ammo_temp;

        float last_shot_frame;
};

#endif // WEAPON_H
