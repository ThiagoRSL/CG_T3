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

#include "gl_canvas2d.h"
#include "Managers/FileManager.h"
#include "Managers/MouseManager.h"
#include "Managers/RenderManager.h"
#include "Managers/CollisionManager.h"
#include "Managers/FPSManager.h"
#include "Managers/PlayerManager.h"
#include "Builder/CharacterBuilder.h"
#include "Utils/Vec2.h"
#include "Entities/Poly.h"
#include "Entities/Entity.h"
#include "Entities/Character/Character.h"
#include "Entities/Character/PlayerCharacter.h"

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
    CameraManager::shared_instance().UpdateCameraOffset();
    FPSManager::shared_instance().UpdateFrames();
    PlayerManager::shared_instance().CheckInteraction();
    RenderManager::shared_instance().RenderAll();
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
        player_character->ReceiveDamage(200);
      break;
      case 120:
        //tecla X
        enemy_character->Shoot();
      break;
      case 122:
        //tecla Z
        player_character->Shoot();
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
      //tecla "I"
      case 105:
        // debugMode = !debugMode;
        break;
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
   //Sleep(1000);

    player_character = (PlayerCharacter*) CharacterBuilder::BuildShip(400, 400, RGB, 1);
    player_character->EquipWeapon(new Weapon(player_character));

    PlayerManager::shared_instance().SetPlayerCharacter(player_character);

    enemy_character = CharacterBuilder::BuildShip(800, 400, RGB, 1);

    enemy_character->EquipWeapon(new Weapon(enemy_character));
    enemy_character->SetAutonomous(true);

    /*
    ShipPart* body = new ShipPart(400, 400, RGB);
    body->AddVertex(-20,-25);
    body->AddVertex(-10,-40);
    body->AddVertex(10,-40);
    body->AddVertex(20,-25);
    body->AddVertex(20,25);
    body->AddVertex(-20,25);
    player_character->AppendPart(body);

    ShipPart* leftWing = new ShipPart(350, 400, RGB);
    leftWing->AddVertex(10, -25);
    leftWing->AddVertex(-10, -10);
    leftWing->AddVertex(-10, 30);
    leftWing->AddVertex(10, 30);
    leftWing->SetOffset(-30, 0);
    player_character->AppendPart(leftWing);

    ShipPart* rightWing = new ShipPart(350, 400, RGB);
    rightWing->AddVertex(10, -10);
    rightWing->AddVertex(-10, -25);
    rightWing->AddVertex(-10, 30);
    rightWing->AddVertex(10, 30);
    rightWing->SetOffset(30, 0);
    player_character->AppendPart(rightWing);

    enemy_character = new Character(800, 400, RGB2);

    Poly* bodye = new Poly(800, 400, RGB);
    bodye->AddVertex(-20,-25);
    bodye->AddVertex(-10,-40);
    bodye->AddVertex(10,-40);
    bodye->AddVertex(20,-25);
    bodye->AddVertex(20,25);
    bodye->AddVertex(-20,25);
    enemy_character->SetAutonomous(true);
    enemy_character->AppendPoly(bodye);
*/
    RenderManager::shared_instance().AddRenderableToList(player_character);
    RenderManager::shared_instance().AddRenderableToList(enemy_character);
    CollisionManager::shared_instance().SetPlayerCharacter(player_character);
    CollisionManager::shared_instance().AddNPC(player_character);
    CollisionManager::shared_instance().AddNPC(enemy_character);

    CV::init("Space Extinction");

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    CameraManager::shared_instance().SetCameraOffset(Pnt2((float) -screenWidth/2, (float) -screenHeight/2));
    CameraManager::shared_instance().SetCameraAnchor(player_character->GetAnchor());

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
