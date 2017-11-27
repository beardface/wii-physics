#include "MiniMap.h"


MiniMap::MiniMap(float width, float height, float miniMapScale, float screen_x, float screen_y)
{
	_scale = 1.0;
	_miniScale = miniMapScale;
	
	_miniWidthRatio = 0;
	_miniHeightRatio = 0;

	_map.SetWidth(width);
	_map.SetHeight(height);
	
	_map.SetPosition(screen_x, screen_y);
	
	_map.SetBorderColor((GXColor){0,0,0,255});
	_map.SetFillColor((GXColor){0,0,0,100});
	
	_miniMap.SetWidth(width*miniMapScale);
	_miniMap.SetHeight(height*miniMapScale);
	
	_miniMap.SetPosition(screen_x + ((_miniScale*_map.GetWidth())) * _miniWidthRatio,
						 screen_y + ((_miniScale*_map.GetHeight())) * _miniHeightRatio);
	
	_miniMap.SetBorderColor((GXColor){255,0,0,255});
	_miniMap.SetFillColor((GXColor){0,0,0,100});
}

MiniMap::~MiniMap()
{

}
		
void MiniMap::SetMapColor(GXColor border, GXColor fill)
{
	_map.SetBorderColor(border);
	_map.SetFillColor(fill);
}

void MiniMap::SetMiniMapColor(GXColor border, GXColor fill)
{
	_miniMap.SetBorderColor(border);
	_miniMap.SetFillColor(fill);
}
		
void MiniMap::SetScreenLocation(float x, float y)
{
	_map.SetPosition(x,y);
}

float MiniMap::GetScreenX()
{
	return _map.GetX();
}

float MiniMap::GetScreenY()
{
	return _map.GetY();
}
		
void MiniMap::Draw(float xoffset, float yoffset)
{

	_miniMap.SetWidth(_map.GetWidth()*_miniScale);
	_miniMap.SetHeight(_map.GetHeight()*_miniScale);
	
	_miniMap.SetPosition(GetScreenX() + ((_map.GetWidth()-_miniScale*_map.GetWidth())) * (1.0-_miniWidthRatio),
						 GetScreenY() + ((_map.GetHeight()-_miniScale*_map.GetHeight())) * (1.0-_miniHeightRatio));
						 
	_map.Draw(xoffset, yoffset);
	_miniMap.Draw(xoffset, yoffset);
}
