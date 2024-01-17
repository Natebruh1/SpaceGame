#include "terrain.h"

terrain::terrain()
{
	chunkID = glm::ivec2(0, 0);
	genTerrain();
}

terrain::terrain(int x, int y)
{
	chunkID = glm::ivec2(x, y);
	genTerrain();
}

terrain::terrain(glm::ivec2 coords)
{
	chunkID = coords;
	genTerrain();
}

void terrain::genTerrain()
{
	if (map) delete map;
	map = new TileMap();
	map->setTexture(ResourceManager::GetTexture("tiles"));
	add_child(map);
	blocks = new block * [CHUNK_SIZE];
	std::vector<int>* vData = new std::vector<int>;
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		blocks[i] = new block[CHUNK_SIZE];
		int height = currentWorld->genHeight(i + (64 * chunkID.x));
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			blocks[i][j].x = i + (64 * chunkID.x);
			blocks[i][j].y = j + (64 * chunkID.y);

			if (j + (64 * chunkID.y) <= height - 8)
			{
				blocks[i][j].tile = 6; //Dirt
			}else if (j + (64 * chunkID.y) <= height)
			{
				blocks[i][j].tile = 5; //Dirt
			}
			else if (j + (64 * chunkID.y) <= height+1)
			{
				blocks[i][j].tile = 4; //Grass
			}

			for (int k : *(blocks[i][j].returnVertex()))
			{
				vData->push_back(k);
			}



		}
	}
	map->addVertex(vData);
	delete vData;
}

terrain::~terrain()
{
	for (int i = 0; i < 64; i++)
	{
		delete blocks[i];
	}
	delete blocks;
}



std::vector<std::vector<glm::vec2>*>* terrain::getCollisionVertices()
{

	std::vector<std::vector<glm::vec2>*>* ret = new std::vector<std::vector<glm::vec2>*>();
	std::vector<glm::vec2>* island = new std::vector<glm::vec2>();
	
	glm::vec2* startTile=nullptr;
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		startTile = nullptr;
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			if (blocks[i][j].tile != 0) // If we're not in air
			{
				if (!startTile) // If we haven't started
				{
					startTile = new glm::vec2((float)(i + (64 * chunkID.x)), (float)(j + (64 * chunkID.y)));
					island->push_back(*startTile - glm::vec2(0.5, 0.5)); //Add top-left corner
					island->push_back(*startTile + glm::vec2(0.5, -0.5)); //Add top-right corner
				}
				


			}
			else
			{
				//IF START TILE THEN WE HAVE REACHED THE END OF THIS STRIP
				if (startTile)
				{
					startTile = new glm::vec2((float)(i + (64 * chunkID.x)), (float)(j + (64 * chunkID.y)));
					island->push_back(*startTile - glm::vec2(0.5, -0.5)); //Add bottom-left corner
					island->push_back(*startTile + glm::vec2(0.5, 0.5)); //Add bottom-right corner
					delete startTile; //start with new strip
					ret->push_back(island); // Add it to the returns
				}
			}
			
		}
		if (island->size()>0) ret->push_back(island);
		
	}
	//Returns std::vector of std::vectors containing vertices from this terrain chunk -> These will be added to the collision map.
	return ret;
}

void terrain::chunkUpdate()
{
	std::vector<int>* vData = new std::vector<int>;
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		

		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			

			for (int k : *(blocks[i][j].returnVertex()))
			{
				vData->push_back(k);
			}



		}
	}
	map->addVertex(vData);
	delete vData;
}

void terrain::blockUpdate(glm::ivec2 coords, block b)
{
	b.x = coords.x;
	b.y = coords.y;
	blocks[coords.x][coords.y] = b;
	map->replaceVertex(b.returnVertex());
}
