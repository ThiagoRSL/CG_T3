#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>
#include "Entities/Poly.h"
#include "Entities/Weapon/Weapon.h"
#include "Entities/Weapon/Projectile.h"

class Character : public Poly
{
    public:
        Character(float x, float y, float RGB[3]);

        void virtual AdjustAim();
        void SetRotating(float degree);
        void SetMoving(float movement);
        void Shoot();
        void ReceiveDamage(float damage);
        void AnimateDeath();
        void Die();


        void RefreshWeaponsCooldown();
        void ResetControls();

        void Render();
        void RenderWeapons();
        void UpdateWeaponPosition();

        void MoveDirection(Vec2 directionVector, float speed);

    protected:
        Weapon* PrimaryWeapon;
        Vec2* AimVector;
        //Control Variables
        float rotating;
        float moving;

        //Base stats
        float movement_speed;
        float rotation_speed;
        float speed;
        float energy_max;
        float energy;

        // Life
        float hit_points_max;
        float hit_points;
        bool dying;
        bool dead;

        //Autonomy
        float aim_accuracy;
        Character* Target;
        Pnt2* target_last_known_location;
        bool autonomous;
        float view_range;

        // Death Animation
        int death_frame;
        float death_rgb_save[3];
        float last_death_frame;

        void AutonomousThinking();
    //Getters e Setters
    public:
        bool IsDying() {return this->dying;}
        bool IsDead() {return this->dead;}
        Pnt2* GetAnchor() {return this->Anchor;}
        Vec2* GetAimVector() {return this->AimVector;}

        void SetAutonomous(bool autonomous){this->autonomous = autonomous;}
        bool SetTarget(Character* target) {this->Target = target;}
};

#endif // CHARACTER_H
