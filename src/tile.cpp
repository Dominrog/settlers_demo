#include "tile.h"

float tileVertices[21] = {
	// positions - x/y/z
	0.0f,	0.0f,	0.0f, 	// middle

	0.0f,	0.0f,	1.0f,	// top

	0.866f,	0.0f,	0.5f,	// top right

	0.866f,	0.0f,	-0.5f,	// bottom right

	0.0f,	0.0f,	-1.0f,	// bottom

	-0.866f,0.0f,	0.5f,	// top left

	-0.866f,0.0f,	-0.5f,	// bottom left
};

unsigned int tileIndices[18] = {
	0, 1, 2, // top right
	0, 2, 3, // right
	0, 3, 4, // bottom right
	0, 1, 5, // bottom left
	0, 5, 6, // left
	0, 6, 4  // top left
};

Tile::Tile()
{
	VAO = 0;
	VBO = 0;
	EBO = 0;
}

Tile::Tile(float xpos, float zpos, TileType t)
	:	x(xpos),
		z(zpos),
		type(t)
{
	VAO = 0;
	VBO = 0;
	EBO = 0;
}

Tile::~Tile()
{
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
    }

    if (VBO != 0)
    {
    	glDeleteBuffers(1, &VBO);
    }

    if (EBO != 0)
    {
    	glDeleteBuffers(1, &EBO);
    }
}

void Tile::buildMesh()
{
	mesh.vertices.clear();
	mesh.indices.clear();

	int vertexCount = sizeof(tileVertices) / sizeof(float);
	for (int i = 0; i < vertexCount; i+= 3)
	{
		mesh.vertices.push_back(glm::vec3(tileVertices[i], tileVertices[i+1], tileVertices[i+2]));
	}

	int indexCount = sizeof(tileIndices) / sizeof(unsigned int);
	for (int i = 0; i < indexCount; i++)
	{
		mesh.indices.push_back(tileIndices[i]);
	}
}

void Tile::upload()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(glm::vec3), mesh.vertices.data(), GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    if (!glIsVertexArray(VAO)) {
        std::cout << "[upload] Warning: VAO is invalid!" << std::endl;
        return;
    }
}

void Tile::render(Shader& shader)
{
	if (glIsVertexArray(VAO) == GL_FALSE) {
		std::cout << "[render] Warning: VAO is invalid!" << std::endl;
		return;
	}

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, 0, z));
	shader.setMat4("model", model);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}