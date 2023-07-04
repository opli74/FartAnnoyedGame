#include "GameLevel.h"

GameLevel::GameLevel( )
{
    for ( const std::string& e : fileNames )
    {
        std::ifstream file( e );

        while ( !file.eof( ) )
        {
            mapHeader data {};

            file >> data.id >> data.width >> data.height;

            int count = 0;
            std::string line;

            while ( count <= data.height )
            {
                std::getline( file , line );
                std::stringstream iss( line );

                for ( std::string value; std::getline( iss , value , ' ' ); )
                {
                    data.data.push_back( std::stoi( value ) );
                }

                count++;
            }
            if ( e == "levels.txt" ) { gameLevelData.push_back( data ); }
            else if ( e == "menuBricks.txt" ) { menuData.push_back( data ); }
            else if ( e == "scoreBricks.txt" ) { scoreData.push_back( data ); }
        }
        file.close( );
    }
    
}

bool GameLevel::isCompleted( std::vector< Brick >& bricks ) const
{
    for ( Brick& brick : bricks )
    {
        if ( brick.getDestroyed( ) ) { return false; }
    }
    return true;
}

std::vector<std::vector<int>> GameLevel::loadTiles( GameLevel::Type type, int level ) const
{
    switch ( type )
    {
        case Type::Game:
        {
            for ( const mapHeader& e : gameLevelData )
            {
                if ( e.id == level )
                {
                    return loadTo2Dvec( e );
                }
            }
            break;
        }
        case Type::Score:
        {
            for ( const mapHeader& e : scoreData )
            {
                if ( e.id == level )
                {
                    return loadTo2Dvec( e );
                }
            }
            break;
        }
        case Type::Menu:
        {
            for ( const mapHeader& e : menuData )
            {
                if ( e.id == level )
                {
                    return loadTo2Dvec( e );
                }
            }
            break;
        }
    }
}

std::tuple<int , int> GameLevel::getDimensions( GameLevel::Type type , int level ) const
{
    switch ( type )
    {
        case Type::Game:
        {
            for ( const mapHeader& e : gameLevelData )
            {
                if ( e.id == level )
                {
                    return { e.width, e.height };
                }
            }
            break;
        }
        case Type::Score:
        {
            for ( const mapHeader& e : scoreData )
            {
                if ( e.id == level )
                {
                    return { e.width, e.height };
                }
            }
            break;
        }
        case Type::Menu:
        {
            for ( const mapHeader& e : menuData )
            {
                if ( e.id == level )
                {
                    return { e.width, e.height };
                }
            }
            break;
        }
    }
}

std::vector<std::vector<int>> GameLevel::loadTo2Dvec( const mapHeader& level ) const
{
    std::vector< std::vector < int > > bricks;
    for ( int y = 0; y < level.height; y++ )
    {
        std::vector <int> row;
        for ( int x = 0; x < level.width; x++ )
        {
            row.push_back( level.data[ x + level.width * y ] );
        }
        bricks.push_back( row );
    }
    return bricks;
}
