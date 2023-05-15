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
#include "FileManager.h"
#include "MouseManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "Vec2.h"
#include "Poly.h"
#include "FPSManager.h"
#include "Character.h"
#include "PlayerCharacter.h"

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
        if(PressedKeys.find(202) != PressedKeys.end())
            player_character->SetRotating(1);
        else
            player_character->SetRotating(0);
      break;
      case 115:
        if(PressedKeys.find(203) != PressedKeys.end())
            player_character->SetMoving(-0.5);
        else
            player_character->SetMoving(0);
      break;
      case 100:
        if(PressedKeys.find(200) != PressedKeys.end())
            player_character->SetRotating(-1);
        else
            player_character->SetRotating(0);
      break;
      case 119:
        if(PressedKeys.find(201) != PressedKeys.end())
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
    player_character->AddVertex(-20,-25);
    player_character->AddVertex(-10,-40);
    player_character->AddVertex(10,-40);
    player_character->AddVertex(20,-25);
    player_character->AddVertex(20,25);
    player_character->AddVertex(-20,25);


    enemy_character = new Character(800, 400, RGB2);
    enemy_character->AddVertex(-20,-25);
    enemy_character->AddVertex(-10,-40);
    enemy_character->AddVertex(10,-40);
    enemy_character->AddVertex(20,-25);
    enemy_character->AddVertex(20,25);
    enemy_character->AddVertex(-20,25);
    enemy_character->SetAutonomous(true);

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
