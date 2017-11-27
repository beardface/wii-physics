#include "tiledtextlayer.h"
#include <string>

/* Returns the tile index for an ASCII char
   (Replace this according to your image) */
int fontIndexForASCII(char c)
{
	return c+0x01;// - 0x1F;	// This is what I have in mine
}

/* Only used if you initialize later */
Font::Font() {
	filename = NULL;
	width = height = 0;
}

/* Init font */
Font::Font(const char *fn, float nwidth, float nheight) {
	filename = fn;	
	image->LoadImage(filename);
	width = nwidth;
	height = nheight;
}

/* Init font */
Font::Font(wsp::Image* i, float nwidth, float nheight) {
	image = i;	
	width = nwidth;
	height = nheight;
}

/* Init text */
Text::Text(s32 max_cols, s32 max_rows) {
	graphic = NULL;
	font = NULL;
	numChars = 0;
	text = NULL;
	x = y = width = height = 0;
	this->max_cols = max_cols;
	this->max_rows = max_rows;
}

/* Delete text */
Text::~Text() {
	if (graphic)
		delete graphic;
	
	if (text)
		delete text;
}

/* Draw text */
void Text::draw() {
	if (text && font && numChars)
		graphic->Draw();
};

/* Set font for text */
void Text::SetFont(Font *fnt) {
	Font *oldFont = font;
	if (fnt == oldFont)
		return;
	
	font = fnt;
	
	// Check if we can display
	if (text && font && numChars)
	{
		if (!graphic)
		{
			graphic = new wsp::TiledLayer(numChars, 1, 0);
			
			for (int i = 0; i < numChars; i++)
				graphic->SetCell(i, 0, fontIndexForASCII(text[i]));
		}
		
		graphic->SetStaticTileset(font->image, font->width, font->height);
		updatePos();
	}
};

/* Set text value */
void Text::SetText(char *tx) {
	if (text)
	{
		delete text;
		text = NULL;
	}

	int oldLength = numChars;
	numChars = strlen(tx);
	text = new char[numChars+1];
	strcpy(text, tx);
	
	// Check if we can display
	if (text && font && numChars)
	{
		if (graphic && oldLength != numChars)
		{
			delete graphic;
			graphic = NULL;
		}
		
		if (!graphic)
		{
			graphic = new wsp::TiledLayer(max_cols, max_rows, 0);
			graphic->SetStaticTileset(font->image, font->width, font->height);
		}

		s32 cur_row = 0;
		s32 cur_col = 0;
		bool new_line = false;
		
		for (int i = 0; i < numChars; i++)
		{
			new_line = false;
			
		    if(cur_col > max_cols)
			{
				cur_col = 0;
				cur_row++;
			}
		
			if(text[i] == '\n')
			{
				new_line = true;
				cur_col = 0;
				cur_row++;
			}
			
			if(cur_row >= max_rows) cur_row = max_rows - 1;
			
			
			if(!new_line)
			{
				graphic->SetCell(cur_col, cur_row, fontIndexForASCII(text[i]));
				cur_col++;
			}
		}
		updatePos();
	}
};

/* Updates visual screen position */
void Text::updatePos() {
	width = numChars * font->width;
	height = font->height;
	float nx = x;// - width / 2;
	float ny = y;// - height / 2;
	graphic->SetPosition(nx, ny);
}

/* Sets screen position */
void Text::SetPosition(float nx, float ny) {
	x = nx;
	y = ny;
	
	if (text && font && numChars)
		updatePos();
}
