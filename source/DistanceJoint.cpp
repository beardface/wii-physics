#include "DistanceJoint.h"

#include "GenericShape.h"

#include <stdio.h>
#include <stdlib.h>

DistanceJoint::DistanceJoint(b2World *w, b2Body* b1, b2Body* b2, b2Vec2 v1, b2Vec2 v2, bool collide, GXColor color, bool flex)
{
	
	_color = color;
	
	world = w;
	
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
	
	_flex = flex;
	_v1 = v1;
	_v2 = v2;
	
	b2DistanceJointDef jointDef;
	//jointDef.Initialize(b1, b2, v1, v2);
	jointDef.collideConnected = false; //collide;
	
	//rubberize
	if(flex)
	{
		jointDef.dampingRatio = 0.5;
		jointDef.frequencyHz = 1.2;
	}
	
	bod_1 = b1;
	bod_2 = b2;
	
	b2Body* prevBody = b1;
	
	float dist = sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
	
	float dx = v2.x-v1.x;
	float dy = v2.y-v1.y;
	
	int links = (int)(dist/0.5);
		
	b2Vec2 prevAnchor = v1;	
	
	   bodies.push_back(b1);

   b2PolygonDef sd;
   sd.SetAsBox(0.6f, 0.125f);
   sd.density  = 20.0f;
   sd.friction = 0.2f;
   //sd.filter.maskBits=0x0000;

	for(int i = 0; i < links-1; i++)
	{
	   b2BodyDef bd;
	   bd.position.Set((v1.x+(dx/links)*i),(v1.y+(dy/links)*i));
	   
	   b2Body* body = world->CreateBody(&bd);
	   
	   body->CreateShape(&sd);
	   body->SetMassFromShapes();
	   
	   b2Vec2 anchor(body->GetWorldCenter().x, body->GetWorldCenter().y);
	   jointDef.Initialize(prevBody,body,prevAnchor,anchor);
	   
	   prevAnchor = anchor;
	   
	   joints.push_back(world->CreateJoint(&jointDef));
	   bodies.push_back(body);
    }
	
	jointDef.Initialize(prevBody, b2, prevAnchor, v2);
	
	joints.push_back(world->CreateJoint(&jointDef));
	bodies.push_back(b2);

	mathHelper = new MathHelper();
	
}
		
DistanceJoint::~DistanceJoint()
{
	
    for(int i = 0; i < joints.size(); i++)
		world->DestroyJoint(joints[i]);

    for(int i = 1; i < joints.size()-1; i++)
		world->DestroyBody(bodies[i]);
		
	delete mathHelper;
}

void DistanceJoint::Save(mxml_node_t** world_node)
{
	
	//TODO Return save string
	mxml_node_t* dist_node; /*my new xml node*/
	dist_node = mxmlNewElement(*world_node, "dist");
	
    char buffer[50];
	
	sprintf(buffer, "%f", (float)_v1.x);
	mxmlElementSetAttr(dist_node, "v1.x", buffer);
	sprintf(buffer, "%f", (float)_v1.y);
	mxmlElementSetAttr(dist_node, "v1.y", buffer);

	sprintf(buffer, "%f", (float)_v2.x);
	mxmlElementSetAttr(dist_node, "v2.x", buffer);
	sprintf(buffer, "%f", (float)_v2.y);
	mxmlElementSetAttr(dist_node, "v2.y", buffer);
	
	sprintf(buffer, "%d", b1_id);
	mxmlElementSetAttr(dist_node, "b1_id", buffer);

	sprintf(buffer, "%d", b2_id);
	mxmlElementSetAttr(dist_node, "b2_id", buffer);
	
	sprintf(buffer, "%d", _color.r);
	mxmlElementSetAttr(dist_node, "color.r", buffer);
	sprintf(buffer, "%d", _color.g);
	mxmlElementSetAttr(dist_node, "color.g", buffer);
	sprintf(buffer, "%d", _color.b);
	mxmlElementSetAttr(dist_node, "color.b", buffer);
	sprintf(buffer, "%d", _color.a);
	mxmlElementSetAttr(dist_node, "color.a", buffer);
	
	if(_flex)
	{
		mxmlElementSetAttr(dist_node, "flex", "true");
	}
	else
	{
		mxmlElementSetAttr(dist_node, "flex", "false");
	}
}

void DistanceJoint::draw(float xoff, float yoff)
{
	int l = bodies.size();
	double *x;
	double *y;
	
	//Change this to increase/decrease smoothing
	int m = 3;
	
	int n = (l - 1) * m + 1;
	
	double *u_x;
	double *v_y;
	
	x = (double*)malloc(sizeof(double)*bodies.size());
	y = (double*)malloc(sizeof(double)*bodies.size());
	
	u_x = (double*)malloc(sizeof(double)*n);
	v_y = (double*)malloc(sizeof(double)*n);
	
    for(int i = 0; i < bodies.size(); i++)
	{
		b2Vec2 pos  = bodies[i]->GetWorldCenter();
		
		x[i] = pos.x;
		y[i] = pos.y;
	}
	
	if(mathHelper->splakima(2, bodies.size(), x, y, m, n, u_x, v_y) == 0)
	{
		//
		for(int i = 0; i < n - 1; i++)
		{
			//b2Vec2 pos  = bodies[i]->GetWorldCenter();
			//b2Vec2 pos2 = bodies[i+1]->GetWorldCenter(); //GetBody2()->GetWorldCenter();
			
			Mtx model;
			guMtxIdentity(model);
			GX_LoadPosMtxImm(model, GX_PNMTX0);

			GX_SetLineWidth(20,GX_TO_ONE);
			
			// Turn off texturing
			GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
			GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);

			// Draw a Quad
			GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 2);
			
			GX_Position2f32(PIXELS_PER_UNIT*(double)u_x[i]+xoff, PIXELS_PER_UNIT*(double)v_y[i]+yoff);
			GX_Color4u8(_color.r, _color.g, _color.b, _color.a);
			GX_Position2f32(PIXELS_PER_UNIT*(double)u_x[i+1]+xoff, PIXELS_PER_UNIT*(double)v_y[i+1]+yoff);
			GX_Color4u8(_color.r, _color.g, _color.b, _color.a);
			GX_End();
				
			// Turn texturing back on
			GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
			GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
		}
	}
	
	free (x);
	free (y);
	free (u_x);
	free (v_y);
}
