#include "Text.h"


void Text::drawText( Graphics& gfx, const std::string& text , const Vec2& pos, const Color& c , int size, bool center)
{
	Vec2 pos_ = pos;

	if ( center )
	{
		float lenX = getLength( text , size );
		float lenY = float(size) * 7.0f;
		pos_.x -= lenX / 2;
		pos_.y -= lenY / 2;
	}

	for (char character : text) {
		int charCode = static_cast<int>(character);
		if (isalpha(charCode)) 
		{
			charCode = toupper(charCode);
			drawLetter(charCode, size, gfx, pos_, c, CharacterMapping::A);
			pos_.x += (size * characters[charCode - CharacterMapping::A].width + 2); 
		}
		else if (isdigit(charCode) || character == ':')
		{
			drawLetter(charCode, size, gfx, pos_, c, CharacterMapping::B);
			pos_.x += (size * characters[charCode - CharacterMapping::B].width + 2);
		}
		else if (character == '.')
		{
			drawLetter(charCode, size, gfx, pos_, c, CharacterMapping::DOT);
			pos_.x += (size * characters[charCode - CharacterMapping::DOT].width);
		}
		else 
		{
			pos_.x += (size * 5);
		}
	}
}

void Text::drawText(Graphics& gfx, const std::string& text, const Vec2& pos, const Color& c, int size)
{
	Vec2 pos_ = pos;
	for (char character : text) {
		int charCode = static_cast<int>(character);
		if (isalpha(charCode))
		{
			charCode = toupper(charCode);
			drawLetter(charCode, size, gfx, pos_, c, CharacterMapping::A);
			pos_.x += (size * characters[charCode - CharacterMapping::A].width + 2);
		}
		else if (isdigit(charCode) || character == ':' )
		{
			drawLetter(charCode, size, gfx, pos_, c, CharacterMapping::B);
			pos_.x += (size * characters[charCode - CharacterMapping::B].width + 2);
		}
		else if ( character == '.'  )
		{
			drawLetter(charCode, size, gfx, pos_, c, CharacterMapping::DOT);
			pos_.x += (size * characters[charCode - CharacterMapping::DOT].width);
		}
		else 
		{
			pos_.x += (size * 5);
		}
	}
}

float Text::getLength(const std::string& text, int size)
{
	float len = 0.0f;
	
	for ( char character : text )
	{
		int charCode = static_cast<int>(character);
		if (isalpha(charCode))
		{
			charCode = toupper(charCode);
			len += (size * characters[charCode - CharacterMapping::A].width + 2);
		}
		else if (isdigit(charCode) || character == ':')
		{
			len += (size * characters[charCode - CharacterMapping::B].width + 2);
		}
		else if (character == '.' )
		{
			len += ( size * characters[charCode - CharacterMapping::DOT].width);
		}
		else
		{
			len += ( size * 5 );
		}
	}
	return len;
}

void Text::drawLetter(int character, int size, Graphics& gfx, const Vec2& pos, const Color& c, int mapping)
{
	const CharacterData& charData = characters[character - mapping];
	int i = 0;
	for (int y = 0; y < charData.height; y++) {
		for (int x = 0; x < charData.width; x++) {
			if (charData.pixels[i] == 1) {
				gfx.DrawRect(Rect(pos + Vec2(float(x * size), float(y * size)), float(size), float(size)), c);
			}
			i++;
		}
	}
}


