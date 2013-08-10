/*
 *  This file is part of Banana-ade.
 *  Copyright (C) 2013 Kieran Hancock & Alex Kerr
 *
 *  Banana-ade is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Banana-ade is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Banana-ade.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "level.h"
#include <fstream>
#include <iostream>

Level::Level(std::string filename)
{
	//Creates an input file stream to read the level:
	std::ifstream reader(filename.c_str());

	//Checks the filestream was created successfully:
	if(! reader)
		throw "Error reading file";

	std::string line = "";

	//Gives the metadata a default value:
	_name = "";
	_author = "";

	//The first part of the file is the meta-data:
	while(line != ";;")
	{
		//Reads the entire line:
		getline(reader, line);

		//Checks if it contains relevant info, and
		//adds it to the object's members if so:
		if(line.substr(0, 5) == "name=")
			_name = line.substr(5);
		else if(line.substr(0, 7) == "author=")
			_author = line.substr(7);
	}

	//Some other stuff for enemies:
	//lel

	//The code for the tile that has been read:
	int tileCode = -1;

	//The pointer that will be added to the vector:
	Tile* tilePtr = NULL;

	//Variables for the loop:
	int i = 0, j = 0;

	//The next part is the tile layout:
	while(reader.peek() != -1)
	{
		//All the tiles on the same line have the
		//same Y co-ordinate, so it reads in lines:
		while(char(reader.peek()) != '\n')
		{
			//The X and Y co-ordinates of the tile:
			float x = TILE_WIDTH * j;
			float y = TILE_HEIGHT * i;

			//Reads the tile code:
			reader >> tileCode;

			//Creates a new tile based on the code:
			switch(tileCode)
			{
				case 0: tilePtr = new EmptyTile(x, y); break;
				case 1: tilePtr = new SolidTile(x, y); break;
				default: throw "Invalid Tile"; break;
			}

			//Adds the new tile to the array:
			_tiles.push_back(tilePtr);

			j++;
		}
		j = 0;
		i++;
		reader.ignore(1, '\n');
	}
	reader.close();
}

Level::~Level()
{
	//Deletes the tiles, enemies and projectiles:
	for(unsigned int i = 0; i < _tiles.size(); i++)
		delete _tiles[i];

	/*for(unsigned int i = 0; i < _enemies.size(); i++)
		delete _enemies[i];

	for(unsigned int i = 0; i < _projectiles.size(); i++)
		delete _projectiles[i];*/
}

std::string& Level::getName()
{
	return _name;
}

std::string& Level::getAuthor()
{
	return _author;
}

std::vector <Tile*>& Level::getTiles()
{
	return _tiles;
}
