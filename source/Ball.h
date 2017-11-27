#ifndef _Ball_H_
#define _Ball_H_

#include "wiisprite.h"
#include "Box2D.h"
#include "WiiStackTypes.h"

#include "GenericShape.h"

#include "mxml.h"

using namespace wsp;
using namespace WiiStackTypes;

class Ball : public GenericShape
{
	public:
		
		b2Body *body;
		
		Ball(b2World *w, float x, float y, Image* img, double radius, f32 zoom, bool fixed, f32 restitution, f32 friction, f32 density, int id = 0);;
		~Ball();
		void draw(float xoff, float yoff);
		bool IsSelected(Sprite* s);
		b2Body* GetBody(){return body;}
		f32 GetWidth(){return sprite->GetWidth()*sprite->GetZoom();}
		void Reset();
		void UpdateXform(float x, float y, float ang);
		
		void Save(mxml_node_t** world_node, int id);
		
	private:
		Sprite* sprite;
		b2World *world;
		float _start_x;
		float _start_y;
		float _start_rot;
		
		float _density;
		float _restitution;
		float _friction;
		float _radius;
		float _zoom;
};

#endif //_Ball_H_
