#ifndef _PulleyJoint_H_
#define _PulleyJoint_H_

#include "Box2D.h"
#include "wiisprite.h"
#include "WiiStackTypes.h"

#include "mxml.h"

using namespace wsp;
using namespace WiiStackTypes;

class PulleyJoint {

	public:
		Sprite sprite;
		b2PulleyJoint *joint;
		
		PulleyJoint(b2World *w, b2Body* b1, b2Vec2 b2,  b2Body *b3, f32 width, GXColor color);
		~PulleyJoint();
		void draw(float xoff, float yoff);
		
		b2Body* GetBody1(){return bod_1;}
		b2Body* GetBody2(){return bod_2;}
		
		void Save(mxml_node_t** world_node);
	private:
		b2World *world;
		GXColor _color;
		b2Body* bod_1;
		b2Body* bod_2;
		
		b2Vec2 _b2;
		int b1_id;
		int b2_id;
		float _width;
		
};

#endif //_PulleyJoint_H_
