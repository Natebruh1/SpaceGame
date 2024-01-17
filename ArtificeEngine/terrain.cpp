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



std::vector<std::vector<glm::vec2>>* terrain::getCollisionVertices()
{
	
	std::vector<std::vector<glm::vec2>>* ret = new std::vector<std::vector<glm::vec2>>();
	std::vector<glm::vec2>* island = new std::vector<glm::vec2>();
	
	glm::vec2* startTile=nullptr;
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		startTile = nullptr;
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			block indexedBlock = blocks[i][j];
			if (indexedBlock.tile != 0) // If we're not in air
			{
				if (!startTile) // If we haven't started
				{
					startTile = new glm::vec2((float)(i + (64 * chunkID.x))*16.f, (float)(j + (64 * chunkID.y))*16.f);
					island->push_back(*startTile - glm::vec2(8, 8)); //Add top-left corner
					//(*island)[0] = glm::vec2((*island)[0].x * projection[0][0], (*island)[0].y*projection[1][1]);
					
					//std::cout << (*island)[0].x << "|" << (*island)[0].y << " // ";


					island->push_back(*startTile + glm::vec2(8, -8)); //Add top-right corner
					//(*island)[1] = (*island)[1] * glm::vec2(projection[0][0], projection[1][1]);

					//std::cout << (*island)[1].x << "|" << (*island)[1].y << std::endl;


				}
				


			}
			else
			{
				//IF START TILE THEN WE HAVE REACHED THE END OF THIS STRIP
				if (startTile!=nullptr)
				{
					startTile = new glm::vec2((float)(i + (64 * chunkID.x)) * 16.f, (float)(j + (64 * chunkID.y)) * 16.f);
					island->push_back(*startTile - glm::vec2(8, -8)); //Add bottom-left corner
					island->push_back(*startTile + glm::vec2(8, 8)); //Add bottom-right corner
					
					delete startTile; //start with new strip
					startTile = nullptr;
					ret->push_back(*island); // Add it to the returns
					delete island;
					island = new std::vector<glm::vec2>();
				}
			}
			
		}
		if (island->size() > 0)
		{
			startTile = new glm::vec2((float)(i + (64 * chunkID.x)), (float)(63 + (64 * chunkID.y)));
			island->push_back(*startTile - glm::vec2(8, -8)); //Add bottom-left corner
			island->push_back(*startTile + glm::vec2(8, 8)); //Add bottom-right corner
			ret->push_back(*island);
			delete island;
			island = new std::vector<glm::vec2>();
		}
	}
	//Returns std::vector of std::vectors containing vertices from this terrain chunk -> These will be added to the collision map.
	std::cout << ret->size() << std::endl;
	return ret;
}

glm::vec2 terrain::getPosition()
{
	return glm::vec2(CHUNK_SIZE*(float)chunkID.x*16.f, CHUNK_SIZE * (float)chunkID.y*16.f);
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
