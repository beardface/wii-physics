#ifndef _PrismaticJoint_H_
#define _PrismaticJoint_H_

#include "Box2D.h"
#include "wiisprite.h"
#include "WiiStackTypes.h"

#include "mxml.h"

using namespace wsp;
using namespace WiiStackTypes;

class PrismaticJoint {

	public:
		Sprite sprite;
		b2Joint *joint;
		
		PrismaticJoint(b2World *w, b2Body* b1, b2Body* b2,  b2Vec2 jointLoc, b2Vec2 worldAxis, Image* jointImg, float upper = 5.0, float lower = -2.50);
		~PrismaticJoint();
		void draw(float xoff, float yoff);
		b2Joint* GetJoint(){return joint;}
		b2Body* GetBody1(){return bod_1;}
		b2Body* GetBody2(){return bod_2;}
		
		void Save(mxml_node_t** world_node);
	private:
		b2World *world;
		bool isWeld;
		b2Body* bod_1;
		b2Body* bod_2;
		
		float _upper;
		float _lower;
		b2Vec2 _v1;
		b2Vec2 _v2;
		int b1_id;
		int b2_id;

};

#endif //PrismaticJoint
