#include "RevoluteJoint.h"

#include "GenericShape.h"

RevoluteJoint::RevoluteJoint(b2World *w, b2Body* b1, b2Body* b2, b2Vec2 jointLoc, Image* jointImg)
{
	
	sprite.SetImage(jointImg);
	sprite.SetFrame(rand()%4);
	
	world = w;
	
	_x = jointLoc.x;
	_y = jointLoc.y;
	
	
	b2RevoluteJointDef jointDef;
	jointDef.Initialize(b1, b2, jointLoc);
	
	bod_1 = b1;
	bod_2 = b2;
	
	
	if(b1->GetUserData() == NULL)
	{
	   b1_id = 0;
	}
	else
	{
	   b1_id = ((GenericShape*)b1->GetUserData())->GetId();
	}
	
	if(b2->GetUserData() == NULL)
	{
	   b2_id = 0;
	}
	else
	{
	   b2_id = ((GenericShape*)b2->GetUserData())->GetId();
	}
	
	joint = world->CreateJoint(&jointDef);

}
		
RevoluteJoint::~RevoluteJoint()
{
	
    if(joint != NULL)
		world->DestroyJoint(joint);
}

void RevoluteJoint::Save(mxml_node_t** world_node)
{
	
	//TODO Return save string
	mxml_node_t* pin_node; /*my new xml node*/
	mxml_node_t* thing_node;
	pin_node = mxmlNewElement(*world_node, "pin");
	
    char buffer[50];
	
	sprintf(buffer, "%f", _x);
	mxmlElementSetAttr(pin_node, "x", buffer);
	sprintf(buffer, "%f", _y);
	mxmlElementSetAttr(pin_node, "y", buffer);

	thing_node = mxmlNewElement(pin_node, "pinned_thing");
	sprintf(buffer, "%d", b1_id);
	mxmlElementSetAttr(thing_node, "id", buffer);


	thing_node = mxmlNewElement(pin_node, "pinned_thing");
	sprintf(buffer, "%d", b2_id);
	mxmlElementSetAttr(thing_node, "id", buffer);

}

void RevoluteJoint::draw(float xoff, float yoff)
{
	if(joint != NULL)
	{
		b2Vec2 pos  = joint->GetAnchor1();
		
		sprite.SetPosition(PIXELS_PER_UNIT*(double)pos.x + xoff + 25, PIXELS_PER_UNIT*(double)pos.y + yoff + 20);
		sprite.Draw();
	}
}
