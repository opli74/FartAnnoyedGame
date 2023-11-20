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
	int left = -1;
	int top = -1;
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
		Create
	};

	GameLevel( );
	//set

	//get
	bool isCompleted( std::vector< Brick >& bricks ) const;
	std::vector< int > loadTiles( GameLevel::Type type , int level , bool zeroes = false ) const;
	std::tuple<int , int> getDimensions( GameLevel::Type type , int level , bool zeroes = false ) const;

private:
	std::vector< int > loadToVector( const mapHeader& level, bool zeroes ) const;
	void loadLevelData(const std::string& fileName, std::vector<mapHeader>& levelData);
	const std::vector<mapHeader>& getLevelData(Type type) const;


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
	std::vector< mapHeader > scoreLevelData;
	std::vector< mapHeader > menuLevelData;

};

