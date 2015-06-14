#ifndef MODEL
#define MODEL

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
typedef struct
{
	float x, y, z;
} Vertex;

typedef struct
{
	float x, y;
} Point;

typedef struct 
{
	Vertex* verts;
	int numVerts;
 	int* faces;
	int numFaces;
} Mesh;



typedef struct
{
	SDL_Window* window;
	SDL_Renderer* ren;
	float fov;
	Point dim;
	Vertex camera;
	float theta, az; //
} Context;

Mesh* loadModel(const char* file);
void freeModel(Mesh* mesh);
void drawModel(Context* ctx, Mesh* mesh);


#endif
