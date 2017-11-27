#include "PrismaticJoint.h"

#include "GenericShape.h"

PrismaticJoint::PrismaticJoint(b2World *w, b2Body* b1, b2Body* b2, b2Vec2 jointLoc,  b2Vec2 worldAxis, Image* jointImg, float upper, float lower)
{
	
	sprite.SetImage(jointImg);
	sprite.SetFrame(rand()%4);
	
	world = w;
	
	_v1 = jointLoc;
	_v2 = worldAxis;
	
	_upper = upper;
	_lower = lower;
	
	b2PrismaticJointDef jointDef;
	
	isWeld = false;
	
	if(lower == 0 && upper == 0)
		isWeld = true;
	
	jointDef.Initialize(b1, b2, jointLoc, worldAxis);
	jointDef.lowerTranslation = lower;
	jointDef.upperTranslation = upper;
	jointDef.enableLimit = true;
	jointDef.enableMotor = true;
	
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
		
PrismaticJoint::~PrismaticJoint()
{
	
    if(joint != NULL)
		world->DestroyJoint(joint);
}

void PrismaticJoint::Save(mxml_node_t** world_node)
{
	
	//TODO Return save string
	mxml_node_t* pris_node; /*my new xml node*/
	pris_node = mxmlNewElement(*world_node, "pris");
	
    char buffer[50];
	
	sprintf(buffer, "%f", (float)_v1.x);
	mxmlElementSetAttr(pris_node, "v1.x", buffer);
	sprintf(buffer, "%f", (float)_v1.y);
	mxmlElementSetAttr(pris_node, "v1.y", buffer);

	sprintf(buffer, "%f", (float)_v2.x);
	mxmlElementSetAttr(pris_node, "v2.x", buffer);
	sprintf(buffer, "%f", (float)_v2.y);
	mxmlElementSetAttr(pris_node, "v2.y", buffer);
	
	sprintf(buffer, "%d", b1_id);
	mxmlElementSetAttr(pris_node, "b1_id", buffer);

	sprintf(buffer, "%d", b2_id);
	mxmlElementSetAttr(pris_node, "b2_id", buffer);
	
	sprintf(buffer, "%f", (float)_upper);
	mxmlElementSetAttr(pris_node, "upper", buffer);
	
	sprintf(buffer, "%f", (float)_lower);
	mxmlElementSetAttr(pris_node, "lower", buffer);

}

void PrismaticJoint::draw(float xoff, float yoff)
{
	if(joint != NULL && !isWeld)
	{
		b2Vec2 pos  = joint->GetAnchor1();
		
		sprite.SetPosition(PIXELS_PER_UNIT*(double)pos.x + xoff, PIXELS_PER_UNIT*(double)pos.y + yoff);
		sprite.Draw();
	}
}
