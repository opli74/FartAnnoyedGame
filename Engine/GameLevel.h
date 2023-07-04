#pragma once
#include "Rect.h"
#include "Colors.h"
#include "Graphics.h"
#include "Brick.h"
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

struct mapHeader
{
	int id = 0;
	int width = 0;
	int height = 0;
	std::vector< int > data;
};



class GameLevel
{
public:

	enum class Type
	{
		Game,
		Score,
		Menu,
	};

	GameLevel( );
	//set


	//get
	bool isCompleted( std::vector< Brick >& bricks ) const;
	std::vector< std::vector<int> > loadTiles( GameLevel::Type type , int level ) const;
	std::tuple<int , int> getDimensions( GameLevel::Type type , int level ) const;

private:
	std::vector< std::vector<int> > loadTo2Dvec( const mapHeader& level ) const;


private:

	float width = 1.0f;

	static constexpr float padding = 1.0f;

	static constexpr float brickWidth = 42.0f;
	static constexpr float brickHeight = 20.0f;

	const std::vector< std::string > fileNames = { "levels.txt" , "menuBricks.txt" , "scoreBricks.txt" };

	static constexpr int maxHeight = 17;
	static constexpr int maxWidth = 13;

	static constexpr int maxBrick = maxHeight * maxWidth;

	std::vector< mapHeader > gameLevelData;
	std::vector< mapHeader > scoreData;
	std::vector< mapHeader > menuData;

};

