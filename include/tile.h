#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

enum class TileType {
	Empty,
	Pasture,
	Field,
	Hill,
	Mountain,
	Desert,
	Ocean
};

extern float tileVertices[21];
extern unsigned int tileIndices[18];


class Tile 
{
private:
	float x, z;
	TileType type;
	unsigned int VAO, VBO, EBO;
public:
	Tile();
	Tile(float xpos, float zpos, TileType t);
	~Tile();

	void buildMesh();
	void upload();
	void render(Shader& shader);
};