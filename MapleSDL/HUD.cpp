#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <tinyxml2.h>
#include <Box2D/Box2D.h>
#include "GameDebug.h"
#include "Global.h"

#pragma comment(lib, "tinyxml2.lib")

using namespace std;

#include "Input.h"
#include "MessageDispatch.h"
#include "GameUtils.h"
#include "RelativeSpace.h"
#include "AnimatedSprite.h"
#include "MISC\ItemDrop.hpp"
#include "Entity.hpp"
#include "SpawnManager.h"
#include "Box.h"
#include "Game.h"
#include "HUD.h"

HUD::HUD()
{
}


HUD::~HUD()
{
}

void HUD_GridPanel::AddObject(std::string elem_name, HUDObject obj)
{
	this->elements[elem_name] = obj;
}

void HUD_GridPanel::DrawPanel(int x, int y)
{
	int posx = 0, posy = 0;
	std::map<std::string, HUDObject>::iterator collection;

	for (collection = this->elements.begin(); collection != this->elements.end(); collection++) {
		SDL_Rect pos = { 0,0,0,0 };
		pos.x = x + (collection->second.column > 0 ? (this->width / this->columns)*collection->second.column : 0);
		pos.y = y + (collection->second.row > 0 ? (this->height / this->rows)*collection->second.row : 0);
		pos.w = collection->second.sprites->animclips[0].w;
		pos.h = collection->second.sprites->animclips[0].h;

		collection->second.sprites->Animate(pos, 0, NULL, SDL_FLIP_NONE, NULL);
	}
}

void HUD_FlowPanel::AddObject(std::string elem_name, HUDObject obj)
{

	this->elements[elem_name] = obj;
}

void HUD_FlowPanel::DrawPanel(int x, int y)
{
	int posx = 0, posy = 0;
	std::map<std::string, HUDObject>::iterator collection;

	int tallestObject = 0;
	int indexX = 0;
	int indexY = 0;
	for (collection = this->elements.begin(); collection != this->elements.end(); collection++) {
		SDL_Rect pos = { 0,0,0,0 };
		if (indexX + this->spacingX + collection->second.sprites->animclips[0].w > this->width) {
			indexY += tallestObject+spacingY;
			indexX = x;
			pos.x = x+spacingX;
		}else{

			pos.x = x+indexX+spacingX;
			indexX += x+collection->second.sprites->animclips[0].w + spacingX;
		}
		if (tallestObject < collection->second.sprites->animclips[0].h) {
			tallestObject = collection->second.sprites->animclips[0].h;
		}
		pos.y = y+indexY;
		pos.w = collection->second.sprites->animclips[0].w;
		pos.h = collection->second.sprites->animclips[0].h;

		collection->second.sprites->Animate(pos, 0, NULL, SDL_FLIP_NONE, NULL);
	}
}
