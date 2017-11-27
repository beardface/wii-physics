#ifndef _DistanceJoint_H_
#define _DistanceJoint_H_

#include "Box2D.h"
#include "wiisprite.h"
#include "WiiStackTypes.h"

#include "mxml.h"

#include <vector>

#include "MathHelper.h"

using namespace wsp;
using namespace WiiStackTypes;

class DistanceJoint {

	public:
	
		std::vector<b2Body*> bodies;
		std::vector<b2Joint*> joints;
				
		DistanceJoint(b2World *w, b2Body* b1, b2Body* b2,  b2Vec2 v1, b2Vec2 v2, bool collide, GXColor color, bool flex = false);
		~DistanceJoint();
		void draw(float xoff, float yoff);

		b2Body* GetBody1(){return bod_1;}
		b2Body* GetBody2(){return bod_2;}
		
		void Save(mxml_node_t** world_node);
	private:
		
		b2World *world;
		GXColor _color;
		b2Body* bod_1;
		b2Body* bod_2;
		bool _flex;
		b2Vec2 _v1;
		b2Vec2 _v2;
		int b1_id;
		int b2_id;
		MathHelper* mathHelper;
};

#endif //DistanceJoint
