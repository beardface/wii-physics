#ifndef _Line_H_
#define _Line_H_

#include "wiisprite.h"
#include "Box2D.h"
#include "WiiStackTypes.h"

#include "GenericShape.h"

#include "mxml.h"

using namespace wsp;
using namespace WiiStackTypes;

class Line : public GenericShape
{
	public:
		
		Rectangle rect;
		Quad quad;
		b2Body *body;
		
		Line(b2World *tworld, float x, float y,  float ang, GXColor color, int Width, int Height, bool fixed, f32 restitution, f32 friction, f32 density, int id = 0);
		~Line();
		void draw(float xoff, float yoff);
		bool IsSelected(Sprite* sprite);
		b2Body* GetBody(){return body;}
		f32 GetWidth(){return rect.width;}
		void Reset();
		void UpdateXform(float x, float y, float ang);
		void SetFixed(bool b){_fixed = b;}
		
		void Save(mxml_node_t** world_node, int id);
		
	private:
		b2World *world;
		float _start_x;
		float _start_y;
		float _start_rot;
		float w, h;
		bool _fixed;
		GXColor _color;
		
		float _density;
		float _restitution;
		float _friction;
		float _height;
		float _width;
		
};

#endif //_Line_H_
