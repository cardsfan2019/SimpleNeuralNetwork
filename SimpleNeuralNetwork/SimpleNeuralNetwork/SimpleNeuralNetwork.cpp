#include <iostream>
#include <array>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "NeuralNetwork.h"

#define WIDTH 1000
#define HEIGHT 1000
#define SDL2_GFXPRIMITIVES_SCOPE extern

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
} App;

App app;
NeuralNetwork brain(2, 4, 1, .0001);

float input[4][2] = {
	{0, 0},
	{0, 1},
	{1, 0},
	{1, 1}
};

float answer[4][1] = {
	{0},
	{1},
	{1},
	{0}
};

void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		default:
			break;
		}
	}
}

void prepareScene()
{
	SDL_SetRenderDrawColor(app.renderer, 100, 255, 255, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene()
{
	float cols = 100;
	float rows = cols;

	float res = WIDTH / cols;

	for (int x = 0; x < cols; x++) {
		for (int y = 0; y < rows; y++) {
			float x1 = x / cols;
			float y1 = y / rows;
			float inputs[] = { x1, y1 };

			float* c = brain.feedforward(inputs, 2);

			int k = rand() % 4;
			brain.train(input[k], answer[k], 2);

			SDL_SetRenderDrawColor(app.renderer, 255 * *c, 255 * *c, 255 * *c, 255);

			const SDL_Rect rec = { x*res, y*res, res, res };

			int result = SDL_RenderFillRect(app.renderer, &rec);
		}
	}

	SDL_RenderPresent(app.renderer);
}

void initSDL()
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, windowFlags);

	if (!app.window)
	{
		printf("Failed to open %d x %d window: %s\n", WIDTH, HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	if (!app.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

int main(int argc, char* argv[])
{
	memset(&app, 0, sizeof(App));

	initSDL();

	while (1)
	{
		prepareScene();
		doInput();
		presentScene();
		SDL_Delay(16);
	}
	return 0;
}