#ifndef SHIPPART_H
#define SHIPPART_H

#include <Poly.h>
#include <vector>
#include "Slot.h"


class ShipPart : public Poly
{
    public:
        ShipPart(float x, float y, float* RGB);

        void AddModifier(int modifier_id);
        void AddWeaponSlot(Pnt2 offset);
        void AddMotorSlot(Pnt2 offset);


    private:
        int part_type_id;
        Character* AttachedTo;
        std::vector<WeaponSlot*> WeaponSlots;
        std::vector<int> modifiers;
        //std::vector<Modifier*> Modifiers;
        //std::vector<MotorSlot*> MotorSlots;

    public:
        void AppendToCharacter(Character* character);
        Character* PartOf(){ return this->AttachedTo;}
        std::vector<WeaponSlot*> GetWeaponSlots() {return this->WeaponSlots;}
        void SetPartTypeId(int id) {this->part_type_id = id;}
        int GetPartTypeId() {return part_type_id;}

    public:
        static const int SHIP_BODY_PART_TYPE_ID = 1;
        static const int RIGHT_WING_PART_TYPE_ID = 2;
        static const int LEFT_WING_PART_TYPE_ID = 3;
};

#endif // SHIPPART_H
