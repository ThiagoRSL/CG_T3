#include "Entity.h"


Entity::Entity(float x, float y)
{
    this->Anchor = new Pnt2(x, y);
    this->OrientationVector = new Vec2(0, 1);
    this->OrientationVector->SetAnchor(this->Anchor);
    this->Parts = std::vector<Poly*>();
}

void Entity::Move(float speed)
{
    Vec2 moveVec = (*OrientationVector * speed);
    this->Anchor->ApplyVec2(moveVec);
}

void Entity::Resize(float scalar)
{
    int i;
    for (i = 0; i < Parts.size(); i++)
    {
        Parts.at(i)->Resize(scalar);
    }
}

void Entity::Rotate(float degrees)
{
    int i;
    for (i = 0; i < Parts.size(); i++)
    {
        Parts.at(i)->Rotate(degrees);
    }
    OrientationVector->RotateDegrees(degrees);
}

void Entity::AppendPoly(Poly* poly)
{
    Parts.push_back(poly);
    poly->SetAnchor(this->Anchor);
    poly->SetBackgroundColor(this->background_color);
}

std::vector<Poly*>* Entity::GetPartsCopy()
{
    std::vector<Poly*>* coppies = new std::vector<Poly*>();
    int i;
    for(i = 0; i < Parts.size(); i++)
    {
        coppies->push_back(Parts.at(i)->GetCopy());
    }
    return coppies;
}

Entity* Entity::GetCopy()
{
    Entity* entityCopy = new Entity(this->Anchor->x, this->Anchor->y);
    int i;
    for(i = 0; i < Parts.size(); i++)
    {
        entityCopy->AppendPoly(Parts.at(i)->GetCopy());
    }
    return entityCopy;
}

void Entity::Render()
{
    CV::color(0.5, 0.5, 0.5);
    int i;
    for (i = 0; i < Parts.size(); i++)
    {
        Parts.at(i)->Render();
    }
}

Pnt2* Entity::GetAnchor()
{
    return Anchor;
}
