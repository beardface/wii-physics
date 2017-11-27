#include "PulleyJoint.h"

#include "GenericShape.h"

PulleyJoint::PulleyJoint(b2World *w, b2Body* b1, b2Vec2 b2, b2Body* b3, f32 width, GXColor color)
{
	
	_color = color;
	
	world = w;
	
	bod_1 = b1;
	bod_2 = b3;
	_b2 = b2;
	_width = width;
	
	b2Vec2 anchor1 = b1->GetWorldCenter();
	b2Vec2 anchor2 = b3->GetWorldCenter();
	b2Vec2 ta = b2;
	
	b2Vec2 groundAnchor1(ta.x-width, ta.y);
	b2Vec2 groundAnchor2(ta.x+width, ta.y);
	
	float32 ratio = 1.0f;
	b2PulleyJointDef jointDef;
	jointDef.Initialize(b1, b3, groundAnchor1, groundAnchor2, anchor1, anchor2, ratio);
	jointDef.maxLength1 = 18.0f;
	jointDef.maxLength2 = 20.0f;
	
	joint = (b2PulleyJoint*)world->CreateJoint(&jointDef);

	if(b1->GetUserData() == NULL)
	{
	   b1_id = 0;
	}
	else
	{
	   b1_id = ((GenericShape*)b1->GetUserData())->GetId();
	}
	
	if(b3->GetUserData() == NULL)
	{
	   b2_id = 0;
	}
	else
	{
	   b2_id = ((GenericShape*)b3->GetUserData())->GetId();
	}
}
		
PulleyJoint::~PulleyJoint()
{
    if(joint != NULL)
		world->DestroyJoint(joint);
}

void PulleyJoint::Save(mxml_node_t** world_node)
{
	
	//TODO Return save string
	mxml_node_t* pull_node; /*my new xml node*/
	pull_node = mxmlNewElement(*world_node, "pull");
	
    char buffer[50];
	
	sprintf(buffer, "%f", (float)_b2.x);
	mxmlElementSetAttr(pull_node, "b2.x", buffer);
	sprintf(buffer, "%f", (float)_b2.y);
	mxmlElementSetAttr(pull_node, "b2.y", buffer);
	
	sprintf(buffer, "%d", _color.r);
	mxmlElementSetAttr(pull_node, "color.r", buffer);
	sprintf(buffer, "%d", _color.g);
	mxmlElementSetAttr(pull_node, "color.g", buffer);
	sprintf(buffer, "%d", _color.b);
	mxmlElementSetAttr(pull_node, "color.b", buffer);
	sprintf(buffer, "%d", _color.a);
	mxmlElementSetAttr(pull_node, "color.a", buffer);
	
	sprintf(buffer, "%d", b1_id);
	mxmlElementSetAttr(pull_node, "b1_id", buffer);

	sprintf(buffer, "%d", b2_id);
	mxmlElementSetAttr(pull_node, "b2_id", buffer);
	
	sprintf(buffer, "%f", (float)_width);
	mxmlElementSetAttr(pull_node, "width", buffer);

}
void PulleyJoint::draw(float xoff, float yoff)
{
	if(joint != NULL)
	{
		b2Vec2 pos  = joint->GetBody1()->GetWorldCenter();
		b2Vec2 pos2 = joint->GetBody2()->GetWorldCenter();
		b2Vec2 ga = joint->GetGroundAnchor1();
		b2Vec2 ga2 = joint->GetGroundAnchor2();
		
		Mtx model;
		guMtxIdentity(model);
		GX_LoadPosMtxImm(model, GX_PNMTX0);

		GX_SetLineWidth(20,GX_TO_ONE);
		
				// Turn off texturing
		GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
		GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);

		// Draw a Quad
		GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 3);
		
		GX_Position2f32(PIXELS_PER_UNIT*(double)pos.x+xoff+25.0, PIXELS_PER_UNIT*(double)pos.y+yoff+20.0);
		GX_Color4u8(_color.r, _color.g, _color.b, _color.a);
		GX_Position2f32(PIXELS_PER_UNIT*(double)ga.x+xoff+25.0, PIXELS_PER_UNIT*(double)ga.y+yoff+20.0);
		GX_Color4u8(_color.r, _color.g, _color.b, _color.a);
		GX_Position2f32(PIXELS_PER_UNIT*(double)pos2.x+xoff+25.0, PIXELS_PER_UNIT*(double)pos2.y+yoff+20.0);
		GX_Color4u8(_color.r, _color.g, _color.b, _color.a);
		GX_End();
			
		// Turn texturing back on
		GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	}
}
