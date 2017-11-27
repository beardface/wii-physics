#ifndef _RevoluteJoint_H_
#define _RevoluteJoint_H_

#include "Box2D.h"
#include "wiisprite.h"
#include "WiiStackTypes.h"
#include "mxml.h"

using namespace wsp;
using namespace WiiStackTypes;

class RevoluteJoint {

	public:
		Sprite sprite;
		b2Joint *joint;
		
		RevoluteJoint(b2World *w, b2Body* b1, b2Body* b2,  b2Vec2 jointLoc, Image* jointImg);
		~RevoluteJoint();
		void draw(float xoff, float yoff);
		b2Joint* GetJoint(){return joint;}
		b2Body* GetBody1(){return bod_1;}
		b2Body* GetBody2(){return bod_2;}
		
		void Save(mxml_node_t** world_node);
		
	private:
		b2World *world;
		b2Body* bod_1;
		b2Body* bod_2;
		
		int b1_id;
		int b2_id;
		
		float _x;
		float _y;

};

#endif //DistanceJoint
