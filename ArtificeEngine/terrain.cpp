#include "terrain.h"

terrain::terrain()
{
	chunkID = glm::ivec2(0, 0);
	if (map) delete map;
	map = new TileMap();
	map->setTexture(ResourceManager::GetTexture("tiles"));
	add_child(map);
	blocks = new block*[CHUNK_SIZE];
	std::vector<int>* vData = new std::vector<int>;
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		blocks[i] = new block[CHUNK_SIZE];

		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			blocks[i][j].x=i;
			blocks[i][j].y = j;

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

void terrain::render()
{
	map->render();
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
