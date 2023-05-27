/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <set>
#include <iterator>
#include <cstdlib>
#include <iostream>

#include "gl_canvas2d.h"
#include "Managers/FileManager.h"
#include "Managers/MouseManager.h"
#include "Managers/RenderManager.h"
#include "Managers/CollisionManager.h"
#include "Managers/FPSManager.h"
#include "Managers/PlayerManager.h"
#include "Managers/UIManager.h"
#include "Builder/CharacterBuilder.h"
#include "Utils/Vec2.h"
#include "Entities/Poly.h"
#include "Entities/Entity.h"
#include "Entities/Character/Character.h"
#include "Entities/Character/PlayerCharacter.h"
#include "Utils/Curves.h"

Character* player_character;
Character* enemy_character;

std::set<int> PressedKeys;

float moving;
int rotating;

bool control_rotating_right;
bool control_rotating_left;
bool control_moving;

void render()
{
    CV::clear(0,0,0);
    FPSManager::shared_instance().UpdateFrames();
    CameraManager::shared_instance().UpdateCameraOffset();
    PlayerManager::shared_instance().CheckInteraction();
    RenderManager::shared_instance().RenderAll();
    UIManager::shared_instance().RenderAll();
}


void keyboard(int key)
{
    //printf("\nTecla: %d" , key);

    if(PressedKeys.find(key) != PressedKeys.end())
    {
        return;
    }
    PressedKeys.insert(key);

    switch(key)
    {
      //seta para a esquerda
      case 99:
        //tecla C
        //player_character->ReceiveDamage(200);
      break;
      case 120:
        //tecla X
        enemy_character->Shoot();
      break;
      case 122:
        //tecla Z
        player_character->ActivateSpecial();
      break;
      case 97:
        player_character->SetRotating(-1);
      break;
      case 100:
        player_character->SetRotating(1);
      break;
      case 115:
        player_character->SetMoving(-0.5);
      break;
      case 119:
        player_character->SetMoving(1);
      break;
    }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
    //printf("\nLiberou: %d" , key);
    if(PressedKeys.find(key) != PressedKeys.end())
        PressedKeys.erase(PressedKeys.find(key));
    switch(key)
    {
      case 27:
         //exit(0);
      break;
        //InventoryManager::shared_instance().OpenMenu();
      case 107:
        //ClearAllFigures();
        break;
      case 108:
        //LoadSave();
        break;
      case 109:
        //FileManager::shared_instance().SaveData(SavedFilePath, FigureManager::shared_instance().GetFiguresAsString(), FigureManager::shared_instance().CountFigures());
        break;
      //seta para a esquerda
      case 98:
        printf("\nB pressionado, loja abertas.");
        break;
      case 99:
        UIManager::shared_instance().OpenCharacterStats();
        break;
      case 105:
        UIManager::shared_instance().OpenInventory();
        break;
      case 97:
        if(PressedKeys.find(100) != PressedKeys.end())
            player_character->SetRotating(1);
        else
            player_character->SetRotating(0);
      break;
      case 100:
        if(PressedKeys.find(97) != PressedKeys.end())
            player_character->SetRotating(-1);
        else
            player_character->SetRotating(0);
      break;
      case 115:
        if(PressedKeys.find(119) != PressedKeys.end())
            player_character->SetMoving(-0.5);
        else
            player_character->SetMoving(0);
      break;
      case 119:
        if(PressedKeys.find(115) != PressedKeys.end())
            player_character->SetMoving(1);
        else
            player_character->SetMoving(0);
      break;
    }
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    MouseManager::shared_instance().PosX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    MouseManager::shared_instance().PosY = y;

    //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

    if(UIManager::shared_instance().CheckInteraction(x, y))
    {
        return;
    }
    if(button == 0 && state == 0)
    {
        player_character->Shoot();
    }

}

int main(void)
{
    control_rotating_right = false;
    control_rotating_left = false;
    control_moving = false;

    float RGB[3] = {0.0,0.75,0.75};
    float RGB2[3] = {0.75,0.0,0.75};
    float RGB3[3] = {0.75, 0.75, 0.0};
    float RGB4[3] = {0.75, 0.35, 0.35};
   //Sleep(1000);


    //Wall Close
    Bezier* closeBottom = new Bezier();
    closeBottom->SetColor(RGB3);
    closeBottom->SetShowWithLines(true);
    closeBottom->SetCurveResolution(100);

    //LeftWall
    BSpline* left = new BSpline();
    left->SetColor(RGB3);
    left->SetShowWithLines(true);
    //left->SetShowControlGraph(true);
    //left->SetCurveResolution(1);

    //RightWall
    BSpline* right = new BSpline();
    right->SetColor(RGB3);
    right->SetShowWithLines(true);
    //right->SetShowControlGraph(true);
    //right->SetCurveResolution(1);x

    Pnt2* p = new Pnt2(100,100);
    Pnt2* pn;
    Pnt2* pnx;
    int controlPoints = 150;
    int i;
    for (i = 0; i < controlPoints; i++)
    {
        pn = new Pnt2((std::rand() % 100), p->y - (std::rand() % 125) - 175);
        left->AddControlPoint(pn);
        pnx = new Pnt2(pn->x + 1000 + (std::rand() % 200), pn->y - (std::rand() % 50));
        right->AddControlPoint(pnx);
        p = pn;
    }

    left->GenerateCurvePoints();
    right->GenerateCurvePoints();

    Pnt2* firstRightPoint = right->GetFirstCurvePoint();
    Pnt2* firstLeftPoint = left->GetFirstCurvePoint();
    closeBottom->AddControlPoint(firstRightPoint);
    closeBottom->AddControlPoint(new Pnt2((firstRightPoint->x + firstLeftPoint->x)/2, firstLeftPoint->y + 500));

    closeBottom->AddControlPoint(firstLeftPoint);
    closeBottom->GenerateCurvePoints();
    CollisionManager::shared_instance().addWall(left);
    RenderManager::shared_instance().AddRenderableToList(left);
    CollisionManager::shared_instance().addWall(right);
    RenderManager::shared_instance().AddRenderableToList(right);
    CollisionManager::shared_instance().addWall(closeBottom);
    RenderManager::shared_instance().AddRenderableToList(closeBottom);

    Poly* base = new Poly(0,0,RGB4);
    base->AddVertex(300,0);
    base->AddVertex(150,300);
    RenderManager::shared_instance().AddRenderableToList(base);

    player_character = (PlayerCharacter*) CharacterBuilder::BuildShip(200, 700, RGB, 2);
    Weapon* w1 = new Weapon();
    w1->SetBackgroundColor(RGB3);
    Weapon* w2 = new Weapon();
    w2->SetBackgroundColor(RGB2);
    Weapon* w3 = new Weapon();
    w3->SetBackgroundColor(RGB2);
    player_character->EquipWeapon(w1);
    player_character->EquipWeapon(w2);
    player_character->EquipWeapon(w3);
    PlayerManager::shared_instance().SetPlayerCharacter(player_character);
    RenderManager::shared_instance().AddRenderableToList(player_character);
    CollisionManager::shared_instance().SetPlayerCharacter(player_character);
    CollisionManager::shared_instance().AddNPC(player_character);
    UIManager::shared_instance().AddCharacterStatsToRenderer(player_character);
    player_character->TeleportTo((firstRightPoint->x + firstLeftPoint->x)/2, firstLeftPoint->y);

    enemy_character = CharacterBuilder::BuildShip(800, 400, RGB2, 1);
    enemy_character->Rotate(180);
    w1 = new Weapon();
    w1->SetBackgroundColor(RGB4);
    w2 = new Weapon();
    w2->SetBackgroundColor(RGB4);
    enemy_character->EquipWeapon(w1);
    enemy_character->EquipWeapon(w2);
    enemy_character->SetAutonomous(true);
    RenderManager::shared_instance().AddRenderableToList(enemy_character);
    CollisionManager::shared_instance().AddNPC(enemy_character);
    enemy_character->TeleportTo((firstRightPoint->x + firstLeftPoint->x)/2, firstLeftPoint->y-1000);


    CV::init("Space Extinction");

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    CameraManager::shared_instance().SetCameraOffset(Pnt2((float) -screenWidth/2, (float) -screenHeight/2));
    CameraManager::shared_instance().SetCameraAnchor(player_character->GetAnchor());

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
