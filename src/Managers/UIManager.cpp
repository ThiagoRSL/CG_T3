#include "UIManager.h"

UIManager::UIManager()
{
    float RGB[3] = {0.4, 0.4, 0.4};
    InventoryBackground = new Entity(50, 50);
    InventoryBackground->SetBackgroundColor(RGB);
    Poly* background = new Poly(0, 0);
    background->AddVertex(500,0);
    background->AddVertex(500,500);
    background->AddVertex(0,500);
    InventoryBackground->AppendPoly(background);
}

void UIManager::OpenInventory()
{
    if(!show_inventory)
    {
        // Main Background
        InventoryBackground->SetStatic(true);
        InventoryBackground->SetStaticOffset(50,50);
        UIManager::shared_instance().AddRenderableToList(InventoryBackground);

        // CharacterProjection
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
        UIManager::shared_instance().RemoveRenderableFromList(InventoryBackground);
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

bool UIManager::CheckInteraction(float x, float y)
{
    if(show_inventory)
    {
        Poly* part = CharacterProjection->CollideAt(x, y);
        Select(part);
        return true;
    }
    return false;
}

void UIManager::Select(Poly* selectedPoly)
{
    if(SelectedPoly != nullptr)
        SelectedPoly->SetShowBorder(false);

    this->SelectedPoly = selectedPoly;

    if(SelectedPoly != nullptr)
    {
        CharacterProjection->SetFirstPosition(SelectedPoly);
        SelectedPoly->SetShowBorder(true);
    }
}



void UIManager::AddCharacterStatsToRenderer(Character* character)
{
    CharacterStatsFrameUI* charStatsFrame = new CharacterStatsFrameUI(character);
    CharacterStatsFrames.push_back(charStatsFrame);
}
void UIManager::RemoveCharacterStatsToRenderer(Character* character)
{
    return;
}

void UIManager::RenderAll()
{
    RenderManager::RenderAll();
    int i;
    for(i = 0; i < CharacterStatsFrames.size();i++)
    {
        CharacterStatsFrames.at(i)->Render();
    }
}
