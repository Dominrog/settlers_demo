#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "shader.h"

extern float tileVertices[21];
extern unsigned int tileIndices[18];


enum class TileType {
	Empty,
	Pasture,
	Field,
	Hill,
	Mountain,
	Desert,
	Ocean
};

struct Mesh {
  std::vector<glm::vec3> vertices;
  std::vector<unsigned int> indices;
};


class Tile 
{
private:
	float x, z;
	TileType type;
	unsigned int VAO, VBO, EBO;
	Mesh mesh;
public:
	Tile();
	Tile(float xpos, float zpos, TileType t);
	~Tile();

	void buildMesh();
	void upload();
	void render(Shader& shader);
};