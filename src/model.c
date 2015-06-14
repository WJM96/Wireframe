#include "model.h"

///this needs a rewrite -- BAD
Mesh* loadModel(const char* file)
{

	Mesh* model = malloc(sizeof(Mesh));
	if(model == NULL)
	{
		printf("Could not allocate enough memory, abort!");
		return NULL;
	}
	
	printf("opening file...\n");
	FILE* fp = fopen(file, "r+");
	if(fp == NULL)
	{
		printf("Error! could not open file %s.\n", file);
		return NULL;
	}



	//the first time we scan through to see how much space we're gonna need
	model->numVerts = 0;
	model->numFaces = 0;
	char c = fgetc(fp);
	while(c!= EOF)
	{
		switch(c)
		{
		case 'v': model->numVerts++; break;
		case 'f': model->numFaces++; break;
		default: break;
		}
		c = fgetc(fp);
	}
	
	printf("Vertices found: %i\nFaces found:%i\n",
		       	model->numVerts, model->numFaces);

	model->verts = malloc(sizeof(Vertex) * model->numVerts);
	if(model->verts == NULL)
	{
		printf("Could not allocate enough memory, abort!");
		return NULL;
	}
	model->faces = malloc(sizeof(Vertex) * model->numFaces * 3);
	if(model->faces == NULL)
	{
		printf("Could not allocate enough memory, abort!");
		return NULL;
	}
	

	//now we actually read the data

	rewind(fp);
	c = fgetc(fp);
	int v = 0, f = 0;
	while(c!= EOF)
	{
		switch(c)
		{
		case 'v': fscanf(fp, " %f %f %f", &model->verts[v].x,
					  &model->verts[v].y, 
					  &model->verts[v].z); 
			  v++;
			  break;
		case 'f': fscanf(fp, " %i %i %i", &model->faces[f], 
					  &model->faces[f+1], 
					  &model->faces[f+2]);
			  f+=3; 
			  break;
		default: break;
		}
		c = fgetc(fp);
	}
	
	//and we're done!	
	fclose(fp);


	return model;
}


void freeModel(Mesh* model)
{
	free (model->faces);
	free (model->verts);
	free (model);
}


static Point getProjectedPoint(Context* ctx, Vertex v)
{
	//add rotation
	//doesn't work, just flattens. will fix later
/*
	float len = sqrt(v.x * v.x + v.z*v.z);
	float f = 1;
	
	v.x = cos(ctx->theta) * (len);
	v.z = sin(ctx->theta) * (len);
*/	
	//add camera
	v.x += ctx->camera.x;
	v.z += ctx->camera.z;
	v.y += ctx->camera.y;
	

	Point p = {0, 0};

	float distToScreen = abs((ctx->dim.x/2)/tan(ctx->fov/2));
	p.x = (ctx->dim.x/2) + v.x*distToScreen/v.z;
	p.y = (ctx->dim.y/2) + v.y*distToScreen/v.z;

	return p;
}

void drawModel(Context* ctx, Mesh* mesh)
{
	Point a, b, c;
	
	for(int i = 0; i < mesh->numFaces; i++)
	{
		a = getProjectedPoint(ctx, mesh->verts[mesh->faces[i*3]]);
		b = getProjectedPoint(ctx, mesh->verts[mesh->faces[i*3+1]]);
		c = getProjectedPoint(ctx, mesh->verts[mesh->faces[i*3+2]]);

		SDL_SetRenderDrawColor(ctx->ren, 255, 255, 255, 255);
		SDL_RenderDrawLine(ctx->ren, a.x, a.y, b.x, b.y);
		SDL_RenderDrawLine(ctx->ren, b.x, b.y, c.x, c.y);
		SDL_RenderDrawLine(ctx->ren, c.x, c.y, a.x, a.y);
		SDL_SetRenderDrawColor(ctx->ren, 0, 0, 0, 255);

	}
	SDL_RenderPresent(ctx->ren);
}

