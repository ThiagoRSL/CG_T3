#include "Weapon.h"
#include "Character.h"

Weapon::Weapon(Character* Wielder)
    :Poly()
{
    this->Anchor = Wielder->GetAnchor();
    Vec2* wielderAim = Wielder->GetAimVector();
    this->OrientationVector = new Vec2(wielderAim->x, wielderAim->y);
    Poly::AddVertex(- 5, - 25);
    Poly::AddVertex(+ 5, - 25);
    Poly::AddVertex(+ 5, + 5);
    Poly::AddVertex(- 5, + 5);
    Poly::Render();
}
