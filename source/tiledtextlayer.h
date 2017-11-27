#include "tiledlayer.h"
#include "wiisprite.h"
/*
	Graphical text object by _patch
	Uses libwiisprite by feesh! and Chaosteil
*/

/* HEADER CODE */

#ifndef _Font_H_
#define _Font_H_

class Font {
public:
	wsp::Image* image;
	const char *filename;
	float width, height;
	
	Font();
	Font(const char *fn, float nwidth, float nheight);
	Font(wsp::Image* i, float nwidth, float nheight);
};
#endif //_Font_H_

#ifndef _Text_H_
#define _Text_H_
class Text {
public:
	wsp::TiledLayer *graphic;
	Font *font;
	int numChars;
	float x, y;
	char *text;
	float width, height;
    s32 max_cols, max_rows;
	
	Text(s32 max_cols, s32 max_rows);
	~Text();
	void draw();
	void SetFont(Font *fnt);
	void SetText(char *tx);
	void SetPosition(float nx, float ny);
private:
	void updatePos();
};
#endif //_Text_H_


