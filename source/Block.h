#ifndef _Block_H_
#define _Block_H_

#include "wiisprite.h"
#include "Box2D.h"
#include "WiiStackTypes.h"

#include "mxml.h"

#include "GenericShape.h"

using namespace wsp;
using namespace WiiStackTypes;

class Block : public GenericShape
{
	public:
		
		
		Block(b2World *w, float x, float y,  float ang, Image* img, int Width, int Height, f32 zoom, bool fixed, f32 restitution, f32 friction, f32 densitys, int id = 0);
		~Block();
		void draw(float xoff, float yoff);
		bool IsSelected(Sprite* s);
		b2Body* GetBody(){return body;}
		f32 GetWidth(){return sprite.GetWidth()*sprite.GetZoom();}
		void Reset();
		void UpdateXform(float x, float y, float ang);
		
		void Save(mxml_node_t** world_node, int id);
		
	private:
		Sprite sprite;
		b2Body *body;
		b2World *world;
		float _start_x;
		float _start_y;
		float _start_rot;
		
		float _density;
		float _restitution;
		float _friction;
		float _height;
		float _width;
		float _zoom;
};

#endif //_Block_H_

