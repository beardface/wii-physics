#ifndef _MiniMap_H_
#define _MiniMap_H_

#include "wiisprite.h"

using namespace wsp;

class MiniMap {
   public:
	    MiniMap(float width, float height, float miniMapScale, float screen_x, float screen_y);
		~MiniMap();
		
		void SetMapColor(GXColor border, GXColor fill);
		void SetMiniMapColor(GXColor border, GXColor fill);
		
		void SetScreenLocation(float x, float y);
		float GetScreenX();
		float GetScreenY();
		
		void SetMapScale(float scale){_scale = scale;}
		float GetMapScale(){return _scale;}
		
		void SetMiniMapScale(float s){_miniScale = s;}
		float GetMiniMapScale(){return _miniScale;}
		
		//0 is all the way left, 1 is all the way right
		void SetMiniMapWidthRatio(float ratio){_miniWidthRatio = ratio;}
		
		//0 is all the way to the top, 1 is all the way to the bottom
		void SetMiniMapHeightRatio(float ratio){_miniHeightRatio = ratio;}

		void Draw(float xoffset, float yoffset);
		
	private:
		float _miniScale;
		float _scale;
		
		float _miniWidthRatio;
		float _miniHeightRatio;

		Quad _map;
		Quad _miniMap;

};

#endif //_MiniMap_H_
