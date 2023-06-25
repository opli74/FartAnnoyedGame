#pragma once
#include <vector>
#include "Graphics.h"
#include <string>

class Text
{
public:
	Text( ) = default;

	void drawText( Graphics& gfx , const std::string& text , const Vec2& pos, const Color& c , int size, bool center);
	void drawText( Graphics& gfx , const std::string& text , const Vec2& pos , const Color& c , int size );
	float getLength( const std::string& text , int size);

private:
	void drawLetter( int e , int size , Graphics& gfx , const Vec2& pos , const Color& c , int f );

private:

	std::vector< char > toDraw;

	static constexpr int width = 3;
	static constexpr int height = 3;

	static constexpr int textMap[ 38 ][ 2 ][ 35 ] =
	{
		//a
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 1, 1, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
			}
		},
		//b
		{ 
			{ 4, 7 },

			{
				1, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 1, 1, 0,
			}
		},
		//c
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		},
		//d
		{
			{ 4, 7 },

			{
				1, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 1, 1, 0,
			}
		},
		//e
		{
			{ 4, 7 },

			{
				1, 1, 1, 1,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 1, 1, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 1, 1, 1,
			}
		},
		//f
		{
			{ 4, 7 },

			{
				1, 1, 1, 1,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 1, 1, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
			}
		},
		//g
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 0, 1, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		},
		//h
		{
			{ 4, 7 },

			{
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 1, 1, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
			}
		} ,
		//i
		{
			{ 3, 7 },

			{
				1, 1, 1,
				0, 1, 0,
				0, 1, 0,
				0, 1, 0,
				0, 1, 0,
				0, 1, 0,
				1, 1, 1,
			}
		} ,
		//j
		{
			{ 4, 7 },

			{
				0, 0, 0, 1,
				0, 0, 0, 1,
				0, 0, 0, 1,
				0, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		} ,
		//k
		{
			{ 4, 7 },

			{
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 1, 0,
				1, 1, 0, 0,
				1, 0, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
			}
		} ,
		//l
		{
			{ 4, 7 },

			{
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 1, 1, 1,
			}
		} ,
		//m
		{
			{ 5, 7 },

			{
				1, 0, 0, 0, 1,
				1, 1, 0, 1, 1,
				1, 0, 1, 0, 1,
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
			}
		} ,
		//n
		{
			{ 4, 7 },

			{
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 1, 0, 1,
				1, 0, 1, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
			}
		} ,
		//o
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		} ,
		//p
		{
			{ 4, 7 },

			{
				1, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 1, 1, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
			}
		} ,
		//q
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 1, 0,
				0, 1, 0, 1,
			}
		} ,
		//r
		{
			{ 4, 7 },

			{
				1, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
			}
		} ,
		//s
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 0,
				0, 1, 1, 0,
				0, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		} ,
		//t
		{
			{ 5, 7 },

			{
				1, 1, 1, 1, 1,
				0, 0, 1, 0, 0,
				0, 0, 1, 0, 0,
				0, 0, 1, 0, 0,
				0, 0, 1, 0, 0,
				0, 0, 1, 0, 0,
				0, 0, 1, 0, 0,
			}
		} ,
		//u
		{
			{ 4, 7 },

			{
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		} ,
		//v
		{
			{ 5, 7 },

			{
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
				0, 1, 0, 1, 0,
				0, 0, 1, 0, 0,
			}
		} ,
		//w
		{
			{ 5, 7 },

			{
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
				1, 0, 1, 0, 1,
				1, 0, 1, 0, 1,
				0, 1, 0, 1, 0,
			}
		} ,
		//x
		{
			{ 5, 7 },

			{
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
				0, 1, 0, 1, 0,
				0, 0, 1, 0, 0,
				0, 1, 0, 1, 0,
				1, 0, 0, 0, 1,
				1, 0, 0, 0, 1,
			}
		} ,
		//y
		{
			{ 4, 7 },

			{
				1, 0, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 1,
				0, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		} ,
		//z
		{
			{ 4, 7 },

			{
				1, 1, 1, 1,
				0, 0, 0, 1,
				0, 0, 0, 1,
				0, 1, 1, 0,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 1, 1, 1,
			}
		} ,
		// 0
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 1, 1,
				1, 1, 0, 1,
				1, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		} ,
		//1
		{
			{ 3, 7 },

			{
				0, 1, 0,
				1, 1, 0,
				0, 1, 0,
				0, 1, 0,
				0, 1, 0,
				0, 1, 0,
				1, 1, 1,
			}
		} ,
		// 2
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				0, 0, 0, 1,
				0, 0, 1, 0,
				0, 1, 0, 0,
				1, 0, 0, 0,
				1, 1, 1, 1,
			}
		} ,
		// 3
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				0, 0, 0, 1,
				0, 1, 1, 0,
				0, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		} ,
		//4
		{
			{ 4, 7 },

			{
				0, 0, 1, 1,
				0, 1, 0, 1,
				1, 0, 0, 1,
				1, 1, 1, 1,
				0, 0, 0, 1,
				0, 0, 0, 1,
				0, 0, 0, 1,
			}
		} ,
		//5
		{
			{ 4, 7 },

			{
				1, 1, 1, 1,
				1, 0, 0, 0,
				1, 0, 0, 0,
				1, 1, 1, 0,
				0, 0, 0, 1,
				0, 0, 0, 1,
				1, 1, 1, 0,
			}
		} ,
		//6
		{
			{ 4, 7 },

			{
				0, 0, 1, 0,
				0, 1, 0, 0,
				1, 0, 0, 0,
				1, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		} ,
		//7
		{
			{ 4, 7 },

			{
				1, 1, 1, 1,
				0, 0, 0, 1,
				0, 0, 0, 1,
				0, 0, 1, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
			}
		} ,
		//8
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 0,
			}
		} ,
		//9
		{
			{ 4, 7 },

			{
				0, 1, 1, 0,
				1, 0, 0, 1,
				1, 0, 0, 1,
				0, 1, 1, 1,
				0, 0, 0, 1,
				0, 0, 1, 0,
				0, 1, 0, 0,
			}
		},
		//:
		{
			{
				3 , 7
			} ,

			{
				0, 0, 0,
				0, 1, 0,
				0, 0, 0,
				0, 0, 0,
				0, 0, 0,
				0, 1, 0,
				0, 0, 0,
			}
		},
		//.
		{
			{
				2 , 7
			} ,

			{
				0, 0,
				0, 0,
				0, 0, 
				0, 0,
				0, 0, 
				0, 0,
				0, 1,
			}
		}
	};
};
