#ifndef SLOT_H
#define SLOT_H


class Slot
{
    public:
        Slot();

    protected:

    private:
};


class WeaponSlot : public Renderable
{
    public:
        Weapon* EquippedWeapon;
        Pnt2 Position;

    public:
        WeaponSlot()
        {
            EquippedWeapon = nullptr;
        }
        void SetOffset(float x, float y)
        {
            this->Position.x = x;
            this->Position.y = y;
        }
        void SetWeapon(Weapon* weapon)
        {
            this->EquippedWeapon = weapon;
            this->EquippedWeapon->SetOffset(Position.x, Position.y);
        }
        bool HasWeapon()
        {
            if(EquippedWeapon != nullptr) return true;
            return false;
        }
        void Render()
        {
            if(HasWeapon()) EquippedWeapon->Render();
        }
};
#endif // SLOTS_H
