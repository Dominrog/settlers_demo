#include "grid.h"

Grid::Grid()
{

}

Grid::Grid(unsigned int r, int size)
	:	radius(r),
		grid_size(size)
{
  initializeGrid();
}

void Grid::initializeGrid()
{
	for (int x = 0; x < grid_size; x++)
	{
		for (int z = 0; z < grid_size; z++)
		{
			if (z % 2 != 0)
			{
				grid[x][z] = glm::vec3(x * std::sqrt(3.0f) * 1.1f + (std::sqrt(3.0f) / 2) * 1.1f, 0, z * 1.5f * 1.1f);
			}
			else
			{
				grid[x][z] = glm::vec3(x * std::sqrt(3.0f) * 1.1f, 0, z * 1.5f * 1.1f);
			}
		}
	}
}

void Grid::CreateTiles()
{
	for (int x = 0; x < grid_size; x++)
	{
		for (int z = 0; z < grid_size; z++)
		{
			auto tile = std::make_unique<Tile>(grid[x][z].x, grid[x][z].z, TileType::Field);
		  tile->buildMesh();
		  tile->upload();

		  tiles.push_back(std::move(tile));
		}
	}
}

void Grid::render(Shader& shader, Camera& camera)
{
	shader.use();
	glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = camera.GetViewMatrix();
  glm::mat4 projection = glm::perspective(glm::radians(45.0f),
      (float)SCR_WIDTH / (float)SCR_HEIGHT, 
      0.1f, 
      10000.0f);

	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	shader.setVec3("baseColor", 1.0f, 1.0f, 1.0f);

	for (const auto& tile : tiles)
	{
		model = glm::translate(glm::mat4(1.0f), glm::vec3(tile->GetX(), 0.0f, tile->GetZ()));
	  shader.setMat4("model", model);

	  tile->render(shader);
	} 
}


void Grid::destroy()
{
	
}