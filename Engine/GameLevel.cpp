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

std::vector<std::vector<int>> GameLevel::loadTiles( GameLevel::Type type, int level , bool zeroes ) const
{
    switch ( type )
    {
        case Type::Create:
        case Type::Game:
        {
            for ( const mapHeader& e : gameLevelData )
            {
                if ( e.id == level )
                {
                    return loadTo2Dvec( e, zeroes );
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
                    return loadTo2Dvec( e , zeroes);
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
                    return loadTo2Dvec( e , zeroes );
                }
            }
            break;
        }
    }
}

std::tuple<int , int> GameLevel::getDimensions( GameLevel::Type type , int level, bool zeroes ) const
{
    switch ( type )
    {
        case Type::Create:
        case Type::Game:
        {
            if ( zeroes ) { return { maxWidth, maxHeight }; }

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

std::vector<std::vector<int>> GameLevel::loadTo2Dvec( const mapHeader& level , bool zeroes ) const
{
    std::vector< std::vector < int > > bricks;

    if ( zeroes )
    {
        int diffY = maxHeight - level.height , diffX = maxWidth - level.width , Xhalf = 0, Yhalf = 0;
        if ( maxHeight != level.height ) { Yhalf = diffY / 2; }
        if ( maxWidth != level.width ) { Xhalf = diffX / 2; }
        
        for ( int y = 0 - Yhalf; y < level.height + Yhalf; y++ )
        {
            std::vector <int> row;
            for ( int x = 0 - Xhalf; x < level.width + Xhalf; x++ )
            {
                if ( y < 0 || y >= level.height )
                {
                    row.push_back( 0 );
                }
                else if ( x < 0 || x >= level.width )
                {
                    row.push_back( 0 );
                }
                else
                {
                    row.push_back( level.data[ x + level.width * y ] );
                }
            }
            bricks.push_back( row );
        }
        return bricks;
    }

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
