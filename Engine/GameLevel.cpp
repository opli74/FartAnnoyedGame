#include "GameLevel.h"

GameLevel::GameLevel( )
{
    loadLevelData("levels.txt", gameLevelData);
    loadLevelData("menuBricks.txt", menuLevelData);
    loadLevelData("scoreBricks.txt", scoreLevelData);
}

void GameLevel::loadLevelData(const std::string& fileName, std::vector<mapHeader>& levelData)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        // Handle file opening error
        return;
    }

    while (file)
    {
        mapHeader data{};
        file >> data.id >> data.width >> data.height;

        for (int y = 0; y < data.height; ++y)
        {
            for (int x = 0; x < data.width; ++x)
            {
                int value;
                file >> value;
                data.data.push_back(value);
            }
        }

        if (fileName == "levels.txt") gameLevelData.push_back(data);
        else if (fileName == "menuBricks.txt") menuLevelData.push_back(data);
        else if (fileName == "scoreBricks.txt") scoreLevelData.push_back(data);
    }

    file.close();
}

bool GameLevel::isCompleted( std::vector< Brick >& bricks ) const
{
    return std::all_of(bricks.begin(), bricks.end(), [](Brick& brick) {
        return brick.getDestroyed();
        });
}

std::vector<int> GameLevel::loadTiles( GameLevel::Type type, int level , bool zeroes ) const
{

    const auto& levelData = getLevelData(type);

    auto it = std::find_if(levelData.begin(), levelData.end(), [level](const mapHeader& e) {
        return e.id == level;
        });

    if (it != levelData.end())
    {
        return loadToVector(*it, zeroes);
    }

    // Handle level not found
    return {};
}

std::tuple<int , int> GameLevel::getDimensions( GameLevel::Type type , int level, bool zeroes ) const
{
    const auto& levelData = getLevelData(type);

    auto it = std::find_if(levelData.begin(), levelData.end(), [level](const mapHeader& e) {
        return e.id == level;
        });

    if (it != levelData.end())
    {
        return zeroes ? std::make_tuple(maxWidth, maxHeight) : std::make_tuple(it->width, it->height);
    }

    // Handle level not found
    return {};
}

std::vector<int> GameLevel::loadToVector( const mapHeader& level , bool zeroes ) const
{
    std::vector< int > bricks;

    if ( zeroes )
    {
        int diffY = maxHeight - level.height , diffX = maxWidth - level.width , Xhalf = 0, Yhalf = 0;
        if ( maxHeight != level.height ) { Yhalf = diffY / 2; }
        if ( maxWidth != level.width ) { Xhalf = diffX / 2; }
        
        for ( int y = 0 - Yhalf; y < level.height + Yhalf; y++ )
        {
            for ( int x = 0 - Xhalf; x < level.width + Xhalf; x++ )
            {
                if ( (y < 0 || y >= level.height ) || (x < 0 || x >= level.width) )
                {
                    bricks.push_back( 0 );
                }
                else
                {
                    bricks.push_back( level.data[ x + level.width * y ] );
                }
            }
        }
        return bricks;
    }

    for ( int y = 0; y < level.height; y++ )
    {
        for ( int x = 0; x < level.width; x++ )
        {
            bricks.push_back( level.data[ x + level.width * y ] );
        }
    }
    return bricks;
}

const std::vector<mapHeader>& GameLevel::getLevelData(Type type) const
{
    switch (type)
    {
    case Type::Create:
    case Type::Game:
        return gameLevelData;
    case Type::Score:
        return scoreLevelData;
    case Type::Menu:
        return menuLevelData;
    }

    // Handle invalid type
    static const std::vector<mapHeader> empty;
    return empty;
}