/***************************************************************
|	File:		BitmapFont.cpp
|	Author:		Jason Bloomfield
|	Course:		N/A
|	Purpose:	BitmapFont class draws text using an image
|				of fixed-size character glyphs
***************************************************************/

#include "BitmapFont.h"
#include "../TinyXML/tinyxml.h"

#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <ctype.h>
#include <cassert>


/**************************************************************/
// Initialize
//	- configure the font for "SGD_Font_Glow.png"
////	- probably should have parameters / config file
//void BitmapFont::Initialize( void )
//{
//	// Load the image
//	m_hImage = SGD::GraphicsManager::GetInstance().LoadTexture(
//				L"resource/graphics/SGD_Font_Glow.png" );
//
//	m_fCharWidth		= 32.0F;
//	m_fCharHeight		= 32.0F;
//	m_nNumRows			= 6;
//	m_nNumCols			= 10;
//	
//	m_cFirstChar		= ' ';		// space
//	m_bOnlyUppercase	= true;
//}


/**************************************************************/
// Initialize
//	- configure the font for any bitmap font
//	- has parameters
void BitmapFont::Initialize( const char* path, char firstchar, bool onlyuppercase )
{
	TiXmlDocument doc;
	if (doc.LoadFile(path) == false)
	{
		return;
	}

	TiXmlElement * root = doc.RootElement();
	if (root == nullptr)
	{
		return;
	}

	TiXmlElement * imageData = root->FirstChildElement("image_info");
	
	m_hImage = SGD::GraphicsManager::GetInstance()->LoadTexture(imageData->GetText(), { 0, 0, 0 });


	TiXmlElement * letter = root->FirstChildElement("letter_info");

	while (letter != nullptr)
	{
		int sRectL, sRectT, width, height, xOffset, yOffset, xAdvance, symbol;
		letter->Attribute("symbol", &symbol);

	

		letter->Attribute("sRectL", &sRectL);
		letter->Attribute("sRectT", &sRectT);
		letter->Attribute("width", &width);
		letter->Attribute("height", &height);
		letter->Attribute("xoffet", &xOffset);
		letter->Attribute("yoffset", &yOffset);
		letter->Attribute("xadvance", &xAdvance);
		

		
		letters[symbol].renderRect.left = (float)sRectL;
		letters[symbol].renderRect.top = (float)sRectT;
		letters[symbol].renderRect.right = letters[symbol].renderRect.left + (float)width;
		letters[symbol].renderRect.bottom = letters[symbol].renderRect.top + (float)height;
		letters[symbol].yOffset = yOffset;
		letters[symbol].xOffset = xOffset;
		letters[symbol].xAdvance = xAdvance;
		letters[symbol].symbol = (char)symbol;

		 
		letter = letter->NextSiblingElement("letter_info");

	}

	SpaceWidth = (int)(letters['A'].renderRect.right - letters['A'].renderRect.left);
	SpaceHeight = (int)(letters['A'].renderRect.bottom - letters['A'].renderRect.top);

	// Load the image

	
	
	m_cFirstChar		= firstchar;		// ' ' . space
	m_bOnlyUppercase	= onlyuppercase;
}


/**************************************************************/
// Terminate
//	- clean up resources
void BitmapFont::Terminate( void )
{
	// Unload the image
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hImage );
}


/**************************************************************/
// Draw
//	- draw the text one character at a time,
//	  using the Cell Algorithm to calculate the source rect
void BitmapFont::Draw( const char* output, SGD::Point position, float scale, SGD::Color color ) const
{
	// Validate the image
	assert( m_hImage != SGD::INVALID_HANDLE && "BitmapFont::Draw - image was not loaded" );

	// Validate the parameter
	assert( output != nullptr && "BitmapFont::Draw - string cannot be null" );
	
	
	// Is this string invisible?
	if( output[ 0 ] == '\0'			// string is empty?
		|| scale == 0.0f			// scale is invisible?
		|| color.alpha == 0 )		// color is invisible?
		return;
	
	
	// Store the starting X position for newlines
	float colStart = position.x;

	// Iterate through the characters in the string
	for (int i = 0; output[i]; i++)
	{
		// Get the current character
		char ch = output[i];


		// Check for whitespace
		if (ch == ' ')
		{
			// Move to the next position
			position.x += SpaceWidth * scale;
			continue;
		}
		else if (ch == '\n')
		{
			// Move to the next row
			position.y += SpaceHeight * scale;
			position.x = colStart;
			continue;
		}
		else if (ch == '\t')
		{
			// Calculate the number of pixels from the start
			float pixels = position.x - colStart;

			// Calculate the number of characters from the start
			int chars = int(pixels / (SpaceWidth * scale));

			// Calculate the number of characters to add
			// to get a 4-space alignment
			int spaces = 4 - (chars % 4);


			// Move to the next position
			position.x += spaces * (SpaceWidth * scale);
			continue;
		}


		// Convert to uppercase?
		if (m_bOnlyUppercase == true)
			ch = toupper(ch);


		// Calculate the tile ID for this character
		//int id = ch - m_cFirstChar;

		// Calculate the source rect for that glyph


		// Draw the character
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(
			m_hImage, {position.x + letters[ch].xOffset, position.y + letters[ch].yOffset},
			letters[ch].renderRect, 0.0f, {}, 
			color, {scale, scale} );

		
		// Move to the next position
		position.x += (int)(letters[ch].xAdvance  * scale);
	}
}

	
/**************************************************************/
// Draw
//	- draw the text one character at a time,
//	  using the Cell Algorithm to calculate the source rect
void BitmapFont::Draw( const wchar_t* output, SGD::Point position, float scale, SGD::Color color ) const
{
		// Validate the image
	assert( m_hImage != SGD::INVALID_HANDLE 
			&& "BitmapFont::Draw - image was not loaded" );

	// Validate the parameter
	assert( output != nullptr 
			&& "BitmapFont::Draw - string cannot be null" );
	
	
	// Is this string invisible?
	if( output[ 0 ] == L'\0'		// string is empty?
		|| scale == 0.0f			// scale is invisible?
		|| color.alpha == 0 )		// color is invisible?
		return;


	// Store the starting X position for newlines
	float colStart = position.x;

	// Iterate through the characters in the string
	for( int i = 0; output[ i ]; i++ )
	{
		// Get the current character (narrowed to ASCII)
		char ch = (char)output[ i ];


		// Check for whitespace
		if( ch == ' ' )
		{
			// Move to the next position
			position.x += SpaceWidth * scale;
			continue;
		}
		else if( ch == '\n' )
		{
			// Move to the next row
			position.y += SpaceHeight * scale;
			position.x =  colStart;
			continue;
		}
		else if( ch == '\t' )
		{
			// Calculate the number of pixels from the start
			float pixels = position.x - colStart;

			// Calculate the number of characters from the start
			int chars = int(pixels / (SpaceWidth * scale));

			// Calculate the number of characters to add
			// to get a 4-space alignment
			int spaces = 4 - (chars%4);

			
			// Move to the next position
			position.x += spaces * (SpaceWidth * scale);
			continue;
		}


		// Convert to uppercase?
		if( m_bOnlyUppercase == true )
			ch = toupper( ch );


		

		SGD::GraphicsManager::GetInstance()->DrawTextureSection(
			m_hImage, { position.x + letters[ch].xOffset, position.y + letters[ch].yOffset },
			letters[ch].renderRect, 0.0f, {},
			color, { scale, scale });


		
		// Move to the next position
		position.x += (int)(letters[ch].xAdvance * scale);
	}
}
