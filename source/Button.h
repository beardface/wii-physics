#ifndef _Button_H_
#define _Button_H_

#include "WiiStackTypes.h"
#include "wiisprite.h"
#include <fat.h>

using namespace wsp;
using namespace WiiStackTypes;

class Button{
	public:
		Button(u32 x, u32 y, Image* img_up, Image* img_over, Image* img_down, Image* icon);
		~Button();
		
		void ChangeIcon(Image* new_icon);
		
		bool IsPointerOver(u32 x, u32 y);

		bool Select(u32 x, u32 y);
		
		void ClearHover(){hover = false;}
		void Deselect();
		void SetDown(){selected = true;}
		bool IsSelected(){return selected;}
		
		void Draw(int drift = 0);
	private:
		Image* upImage;
		Image* overImage;
		Image* downImage;
		Image* iconImage;
		
		Sprite* buttonSprite;
		Sprite* iconSprite;
		
		u32 sX;
		u32 sY;
		
		bool hover;
		bool selected;
		bool _fixed;
};

#endif //_Button_H_
