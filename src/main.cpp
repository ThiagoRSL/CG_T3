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
    FPSManager::shared_instance().UpdateFrames();
    RenderManager::shared_instance().RenderAll();
}


void keyboard(int key)
{
    printf("\nTecla: %d" , key);

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
    printf("\nLiberou: %d" , key);
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

    printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

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
    player_character = new PlayerCharacter(400, 400, RGB);

    Poly* body = new Poly(400, 400, RGB);
    body->AddVertex(-20,-25);
    body->AddVertex(-10,-40);
    body->AddVertex(10,-40);
    body->AddVertex(20,-25);
    body->AddVertex(20,25);
    body->AddVertex(-20,25);
    player_character->AppendPoly(body);

    Poly* leftWing = new Poly(350, 400, RGB);
    leftWing->AddVertex(15, -25);
    leftWing->AddVertex(-15, -10);
    leftWing->AddVertex(-15, 20);
    leftWing->AddVertex(15, 20);
    player_character::Entity->AppendPoly(leftWing);

    enemy_character = new Character(800, 400, RGB2);

    Poly* bodye = new Poly(800, 400, RGB);
    bodye->AddVertex(-20,-25);
    bodye->AddVertex(-10,-40);
    bodye->AddVertex(10,-40);
    bodye->AddVertex(20,-25);
    bodye->AddVertex(20,25);
    bodye->AddVertex(-20,25);
    enemy_character->SetAutonomous(true);
    enemy_character::Entity->AppendPoly(bodye);

    RenderManager::shared_instance().AddRenderableToList(player_character);
    RenderManager::shared_instance().AddRenderableToList(enemy_character);
    CollisionManager::shared_instance().SetPlayerCharacter(player_character);
    CollisionManager::shared_instance().AddNPC(player_character);
    CollisionManager::shared_instance().AddNPC(enemy_character);

    int screenWidth = 1600;
    int screenHeight = 800;
    CV::init(&screenWidth, &screenHeight, "Space Extinction");
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
