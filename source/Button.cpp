#include "Button.h"

Button::Button(u32 x, u32 y, Image* img_up, Image* img_over, Image* img_down, Image* icon)
{
	sX = x;
	sY = y;

	buttonSprite = new Sprite();
	buttonSprite->SetPosition(x,y);
	
	upImage   = img_up;
	downImage = img_down;
	overImage = img_over;
	iconImage = icon;
	
	iconSprite = new Sprite();
	iconSprite->SetPosition(x,y);
	iconSprite->SetImage(iconImage);
}

Button::~Button()
{

}

void Button::ChangeIcon(Image* new_icon)
{
	iconImage = new_icon;
	iconSprite->SetImage(iconImage);
}
		
bool Button::IsPointerOver(u32 x, u32 y)
{
	hover = false;
	
	if(x >= buttonSprite->GetX() && x <= (buttonSprite->GetX() + buttonSprite->GetWidth()))
	{
		if(y >= buttonSprite->GetY() && y <= (buttonSprite->GetY() + buttonSprite->GetHeight()))
		{
			hover = true;
			return true;
		}
	}
	
	return false;
 
}

bool Button::Select(u32 x, u32 y)
{
	hover = false;

	if(x >= buttonSprite->GetX() && x <= (buttonSprite->GetX() + buttonSprite->GetWidth()))
	{
		if(y >= buttonSprite->GetY() && y <= (buttonSprite->GetY() + buttonSprite->GetHeight()))
		{
			selected = true;
			hover = false;
			return true;
		}
	}
	
	return false;
}

void Button::Deselect()
{
	hover = false;
	selected = false;
}
		
void Button::Draw(int drift)
{
	if(selected)
		buttonSprite->SetImage(downImage);
	else if(hover)
		buttonSprite->SetImage(overImage);
	else
		buttonSprite->SetImage(upImage);
	
	buttonSprite->SetPosition(sX, sY+drift);
	buttonSprite->Draw();
	iconSprite->SetPosition(sX, sY+drift);
	iconSprite->Draw();
};
