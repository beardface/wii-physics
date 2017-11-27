#ifndef _Pen_H_
#define _Pen_H_

#include "wiisprite.h"
#include "Box2D.h"
#include "WiiStackTypes.h"
#include "box2d/b2Polygon.h"

#include "GenericShape.h"

#include "mxml.h"
using namespace wsp;
using namespace WiiStackTypes;

class Pen : public GenericShape
{
	public:
		b2BodyDef *bodyDef;
		b2Body *body;
		
		Pen(b2World *tworld, b2Polygon* p, GXColor color, bool fixed, f32 restitution, f32 friction, f32 density, bool closed, int id = 0);
		~Pen();
		void draw(float xoff, float yoff);
		
		bool IsSelected(Sprite* s);
		b2Body* GetBody(){return body;}
		
		void Reset();
		void UpdateXform(float x, float y, float ang);
		
		void Save(mxml_node_t** world_node, int id);
		
	private:
		void  DrawRope(int x0, int x1, int y0, int y1);
		b2World *world;
		b2Polygon* polygon;
		GXColor _color;
		
		float _start_x;
		float _start_y;
		float _start_rot;
		
		bool _closed;
		
		float _density;
		float _restitution;
		float _friction;
		float _height;
		float _width;
		
		
};

#endif //_Pen_H_
