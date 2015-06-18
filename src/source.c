#include <stdio.h>
#include <SDL2/SDL.h>
#include "model.h"

Context* createContext(int w, int h, float fov)
{
	Context* ctx = malloc(sizeof(Context));
	if(ctx == NULL)
	{
		printf("Couldn't allocate enough space, abort!\n");
		return NULL;
	}
	
	ctx->window = SDL_CreateWindow("model viewer", 0, 0, w, h, SDL_WINDOW_SHOWN);
	if(ctx->window == NULL)
	{	
		printf("Couldn't initialize the window!\n");
		return NULL;
	}
	ctx->ren = SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_ACCELERATED);
	if(ctx->ren == NULL)
	{
		printf("couldn't initialize the renderer!\n");
		return NULL;
	}
	ctx->dim.x = w;
	ctx->dim.y = h;	
	ctx->fov = fov;
	ctx->camera.z = 0;
	ctx->camera.x = 0;
	ctx->camera.y = 0;
	ctx->theta = 0;
	ctx->az = 0;	
	return ctx;
}

void freeContext(Context* ctx)
{
	SDL_DestroyRenderer(ctx->ren);
	SDL_DestroyWindow(ctx->window);
	free (ctx);
}

int main(int argc, char* argv[])
{

	SDL_Init(SDL_INIT_EVERYTHING);
	Context* ctx = createContext(640, 640, 65.0f);
	if(ctx == NULL)
		return 1;
	if(argc < 2)
	{
		printf("Please specify a model to load!");
	}
	Mesh* m = loadModel(argv[1]);
	if(m == NULL)
	{
		return 1;
	}
	
	SDL_Event e;
	int playing = 1;
	while(playing)
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
				playing = 0;
			else if(e.type ==SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
				case SDLK_UP:
					ctx->camera.z -= .05; break;
				case SDLK_DOWN:
					ctx->camera.z += .05; break;
				case SDLK_LEFT: 
					ctx->theta -=.05; break;
				case SDLK_RIGHT:
					ctx->theta +=.05; break;
				case SDLK_z: 
					ctx->az -=.05; break;
				case SDLK_x:
					ctx->az +=.05; break;
				default: break;
				}
			}
		}

		SDL_RenderClear(ctx->ren);
		drawModel(ctx, m);
		SDL_Delay(16);
	}
	freeModel(m);
	freeContext(ctx);
	SDL_Quit();
	return 0;
};


