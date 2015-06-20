#ifndef MODEL
#define MODEL

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

//thanks, C!
#ifndef M_PI 
#define M_PI 3.14159265358979323846
#endif

//a 3d point
typedef struct
{
	float x, y, z;
} Vertex;

//a 2d point. Having a structure for this seems a little pointless (ha) as it isn't used very much. May remove later.
typedef struct
{
	float x, y;
} Point;

/*
This structure represents the loaded .obj file (or at least the parts we care about).
*/
typedef struct
{
	Vertex* verts;
	int numVerts;
 	int* faces;
	int numFaces;
} Mesh;


/*
This structure provides various information about the rendering environment (read:screen), include the camera position and rotation
*/
typedef struct
{
	SDL_Window* window;	//used by sdl
	SDL_Renderer* ren;	//" " " " " "
	float fov; 	//field of view
	Point dim;	//width and height in pixels of the screen
	Vertex camera;	//camer position
	float theta, az;	//theta describes rotation(in radians) about the y(up & down) axis. az is about the x (left & right) axis
} Context;

//loads a model from a wavefront file. Returns NULL on failure.
//note: only works for files that format face data as "f # # #", NOT "f #//# #//# #//#"
Mesh* loadModel(const char* file);
void freeModel(Mesh* mesh);

//renders the model.
void drawModel(Context* ctx, Mesh* mesh);


#endif
