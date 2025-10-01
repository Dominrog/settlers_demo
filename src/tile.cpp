#include "tile.h"

float tileVertices[21] = {
	// positions - x/y/z
	0.0f,	0.0f,	0.0f, 	// middle

	0.0f,	0.0f,	1.0f,	// top

	0.75f,	0.0f,	0.5f,	// top right

	0.75f,	0.0f,	-0.5f,	// bottom right

	0.0f,	0.0f,	-1.0f,	// bottom

	-0.75f,	0.0f,	0.5f,	// top left

	-0.75f,	0.0f,	-0.5f,	// bottom left
};

unsigned int tileIndices[18] = {
	0, 2, 1, // top right
	0, 3, 2, // right
	0, 4, 3, // bottom right
	0, 5, 4, // bottom left
	0, 6, 5, // left
	0, 1, 6  // top left
};

Tile::Tile()
{

}

Tile::Tile(float xpos, float zpos, TileType t)
	:	x(xpos),
		z(zpos),
		type(t)
{

}

Tile::~Tile()
{

}

void Tile::buildMesh()
{

}

void Tile::upload()
{

}

void Tile::render(Shader& shader)
{
	
}