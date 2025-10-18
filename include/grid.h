#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <cmath>

#include "shader.h"
#include "tile.h"
#include "node.h"
#include "road.h"
#include "settings.h"
#include "camera.h"

class Grid
{
private:
  unsigned int radius;
  int grid_size;
  glm::vec3 grid[10][10];

  std::vector<std::unique_ptr<Tile>> tiles;
  std::vector<std::shared_ptr<Road>> roads;
  std::vector<std::shared_ptr<Node>> nodes;
public:
  Grid();
  Grid(unsigned int r, int size);
  ~Grid() = default;

  void initializeGrid();
  void CreateTiles();

  void render(Shader& shader, Camera& camera);
  void destroy();
};