#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>
#include "Poly.h"
#include "Weapon.h"
#include "Projectile.h"

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


        void RefreshShotCooldown();
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
        float base_damage;
        float speed;
        float aim_accuracy;
        float energy_max;
        float energy;
        float shot_cooldown_max;
        float shot_cooldown;

        // Life
        float hit_points_max;
        float hit_points;
        bool dying;
        bool dead;

        //Autonomy
        Character* Target;
        Pnt2* target_last_known_location;
        bool autonomous;
        float view_range;

        // Shot control
        float last_shot_frame;

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
