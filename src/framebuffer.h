#pragma once
#include "color.h"
#include <glm/glm.hpp>
#include <vector>
#include <SDL.h>
#include "fragment.h"

void clear();

void point(const Fragment&);

void renderBuffer(SDL_Renderer*);