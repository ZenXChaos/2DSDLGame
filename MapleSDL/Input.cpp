#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include "GameDebug.hpp"
#include "Global.h"

using namespace std;

#include "Input.hpp"

void Input::KeyDown(SDL_Scancode key) {
	this->keysDown[key] = true;
	this->keysUp[key] = false;
 
}

void Input::KeyUp(SDL_Scancode key) {
	this->keysDown[key] = false;
	this->keysUp[key] = true;
}

bool Input::IsKeyPressed(SDL_Scancode key) {
	return this->keysDown[key];
}