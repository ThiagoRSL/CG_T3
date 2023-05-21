#include "UIManager.h"

UIManager::UIManager()
{

}

void UIManager::OpenInventory()
{
    if(!show_inventory)
    {
        CharacterProjection = PlayerManager::shared_instance().GetPlayerCharacter()->GetCopy();
        CharacterProjection->Resize(2);
        CharacterProjection->SetStatic(true);
        CharacterProjection->SetStaticOffset(300,300);
        UIManager::shared_instance().AddRenderableToList(CharacterProjection);
        printf("\nOpening inventory...");
        show_inventory = true;
    }
    else
    {
        UIManager::shared_instance().RemoveRenderableFromList(CharacterProjection);
        delete CharacterProjection;
        printf("\nClosing inventory...");
        show_inventory = false;
    }
}

void UIManager::OpenCharacterStats()
{
    if(!show_character_stats)
    {
        printf("\nOpening character information...");
        show_character_stats = true;
    }
    else
    {
        printf("\nClosing character information...");
        show_character_stats = false;
    }
}

