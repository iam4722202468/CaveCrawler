#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "drawMap.hpp"
#include "../gameClasses/object.hpp"

bool MapSprites::drawMap(GameController *game, std::vector<GameObject*> &gameObjects)
{
  window.draw(mapTiles, &mainSheet);
	
	for(int x = 0; x < gameObjects.size(); x++)
		gameObjects[x]->drawObject(game);
	
	window.draw(layerTiles, &mainSheet);
	
	return true;
}

//load map and layer in to object
bool MapSprites::loadMap(std::vector<std::vector<int>> &toLoadMapVector, bool isLayer)
{
	if(!isLayer)
		mapTiles.resize(toLoadMapVector[0].size() * toLoadMapVector.size() * 4);
	else
		layerTiles.resize(toLoadMapVector[0].size() * toLoadMapVector.size() * 4);
		
	int tileX = 32;
	int tileY = 32;
	
	int tileSizeX = 32;
	int tileSizeY = 32;
    
	int width = toLoadMapVector[0].size();
	int height = toLoadMapVector.size();
    
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = toLoadMapVector[j][i];
			
			if(tileNumber != 0)
			{
				// find its position in the tileset texture
				int tu = tileNumber % (mainSheet.getSize().x / tileX);
				int tv = tileNumber / (mainSheet.getSize().x / tileX);
				
				sf::Vertex* quad;
				
				// get a pointer to the current tile's quad
				if(!isLayer)
					quad = &mapTiles[(i + j * width) * 4];
				else
					quad = &layerTiles[(i + j * width) * 4];
				
				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSizeX, j * tileSizeY);
				quad[1].position = sf::Vector2f((i + 1) * tileSizeX, j * tileSizeY);
				quad[2].position = sf::Vector2f((i + 1) * tileSizeX, (j + 1) * tileSizeY);
				quad[3].position = sf::Vector2f(i * tileSizeX, (j + 1) * tileSizeY);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileX, tv * tileY);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileX, tv * tileY);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileX, (tv + 1) * tileY);
				quad[3].texCoords = sf::Vector2f(tu * tileX, (tv + 1) * tileY);
			}
		}
	
	return true;
}

//load spritemap
MapSprites::MapSprites(sf::RenderWindow &window) :
	window(window)
{
	if (!mainSheet.loadFromFile("resources/spritemap.png"))
		std::cout << "Error " << EXIT_FAILURE << " loading sprite";
	std::cout << "map created" << std::endl;
	
	mapTiles.setPrimitiveType(sf::Quads);
	layerTiles.setPrimitiveType(sf::Quads);
}
