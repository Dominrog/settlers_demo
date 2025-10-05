#pragma once

#include <vector>
#include <memory>

#include "tile.h"
#include "node.h"
#include "road.h"

class Grid
{
private:
	unsigned int radius;
	std::vector<std::unique_ptr<Tile>> tiles;
	std::vector<std::shared_ptr<Road>> roads;
	std::vector<std::shared_ptr<Node>> nodes;
public:
	Grid();
	Grid(unsigned int r);
	~Grid() = default;

	void initializeGrid();

	void render();
	void destroy();
};