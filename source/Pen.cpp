#include "Pen.h"
#include "box2d/b2Polygon.h"
#include "math.h"

Pen::Pen(b2World* tworld, b2Polygon* p, GXColor color, bool fixed, f32 restitution, f32 friction, f32 density, bool closed, int id):
	GenericShape(fixed)
{
	polygon = p;

	_color = color;
	
    SetId(id);
	
	world = tworld;
	b2BodyDef bodyDef;
	bodyDef.userData = (GenericShape*)this;
	
	_start_x = 0;
	_start_y = 0;
	_start_rot = 0;
	
	_density = density;
	_friction = friction;
	_restitution = restitution;
	
	_closed = closed;
	
	int n_points = polygon->nVertices;
	
	float32 *points_x = new float32[n_points];
	float32 *points_y = new float32[n_points];
	
	for(int i=0;i<n_points;++i)
	{
		points_x[i] = (polygon->x[i])/PIXELS_PER_UNIT;
		points_y[i] = (polygon->y[i])/PIXELS_PER_UNIT;
	}
	
	if(1) //_closed) /*Disabled open line drawing until it works better.*/
	{
		bodyDef.position.Set(0,0);
		bodyDef.angle = 0;
		
		body = world->CreateBody(&bodyDef);
		
		b2PolygonDef* polydef = new b2PolygonDef();
		polydef->vertexCount = n_points;

		polydef->density = density;
		
		polydef->friction = friction;
		polydef->restitution = restitution;
		
		b2Polygon *pgon = new b2Polygon(points_x, points_y, n_points);
		
		b2PolygonDef* deleteMe = DecomposeConvexAndAddTo(world, pgon, body, polydef);
		
		if(deleteMe)
		{
			delete[] deleteMe;
		}
		
		delete polydef;
		delete pgon;
	}
	else
	{

		bodyDef.position.Set(float32(polygon->x[0])/PIXELS_PER_UNIT, float32(polygon->y[0])/PIXELS_PER_UNIT);
		bodyDef.angle = 0;
		
		body = world->CreateBody(&bodyDef);
		
		for(int i=0; polygon->nVertices-1; ++i)
		{
			b2PolygonDef polyDef;
			
			polyDef.density = density;
				
			polyDef.friction = friction;
			polyDef.restitution = restitution;
			
			int x1, y1, x2, y2;
			
			x1 = polygon->x[i];
			y1 = polygon->y[i];			
			x2 = polygon->x[i+1];
			y2 = polygon->y[i+1];
			
			int odx = y1 - y2;
			int ody = x2 - x1;
			
			int len = sqrt(odx*odx + ody*ody);
			
			odx = (6 * (odx<<8) / len)>>8; // using 24.8 fixed point for normal calculation
			ody = (6 * (ody<<8) / len)>>8;
			polyDef.vertexCount = 4;
			polyDef.vertices[0].Set(float32(x1)/PIXELS_PER_UNIT, float32(y1)/PIXELS_PER_UNIT);
			polyDef.vertices[1].Set(float32(x2)/PIXELS_PER_UNIT, float32(y2)/PIXELS_PER_UNIT);
			polyDef.vertices[2].Set(float32(x2+odx)/PIXELS_PER_UNIT, float32(y2+ody)/PIXELS_PER_UNIT);
			polyDef.vertices[3].Set(float32(x1+odx)/PIXELS_PER_UNIT, float32(y1+ody)/PIXELS_PER_UNIT);
			
			body->CreateShape(&polyDef);
		}
	}
	
	delete points_x;
	delete points_y;
	
	if(!fixed)
	{
		body->SetMassFromShapes();
	}
	else
	{
		b2MassData massdata;
		massdata.mass = 0.0;
		body->SetMass(&massdata);
	}				
}

Pen::~Pen()
{
	if(body != NULL)
		world->DestroyBody(body);
}


void Pen::Save(mxml_node_t** world_node, int id)
{
	mxml_node_t* pen_node; /*my new xml node*/
	mxml_node_t* vertex_node;
	pen_node = mxmlNewElement(*world_node, "polygon");
	
    char buffer[50];
	
	if(body->GetMass() == 0.0)
	{
		mxmlElementSetAttr(pen_node, "type","solid");
	}
	else
	{
		mxmlElementSetAttr(pen_node, "type","dynamic");
	}
	
	sprintf(buffer, "%f", _density);
	mxmlElementSetAttr(pen_node, "density", buffer);
	sprintf(buffer, "%f", _friction);
	mxmlElementSetAttr(pen_node, "friction", buffer);
	sprintf(buffer, "%f", _restitution);
	mxmlElementSetAttr(pen_node, "restitution", buffer);
	
	sprintf(buffer, "%f", _start_x-_width/2.0);
	mxmlElementSetAttr(pen_node, "x", buffer);
	sprintf(buffer, "%f", _start_y-_height/2.0);
	mxmlElementSetAttr(pen_node, "y", buffer);
	
	sprintf(buffer, "%f", _start_rot*(180.0/M_PI));
	mxmlElementSetAttr(pen_node, "rotation", buffer);
	
	sprintf(buffer, "%d", _color.r);
	mxmlElementSetAttr(pen_node, "color.r", buffer);
	sprintf(buffer, "%d", _color.g);
	mxmlElementSetAttr(pen_node, "color.g", buffer);
	sprintf(buffer, "%d", _color.b);
	mxmlElementSetAttr(pen_node, "color.b", buffer);
	sprintf(buffer, "%d", _color.a);
	mxmlElementSetAttr(pen_node, "color.a", buffer);
	
	if(_closed)
	{
		mxmlElementSetAttr(pen_node, "closed", "1");
	}
	else
	{
		mxmlElementSetAttr(pen_node, "closed", "1");
	}
	
	sprintf(buffer, "%d", GetId());
	mxmlElementSetAttr(pen_node, "id", buffer);
	
	for(int i = 0; i < polygon->nVertices; i++)
	{
		vertex_node = mxmlNewElement(pen_node, "vertex");
		sprintf(buffer, "%f", (float)polygon->x[i]);
		mxmlElementSetAttr(vertex_node, "x", buffer);
		sprintf(buffer, "%f", (float)polygon->y[i]);
		mxmlElementSetAttr(vertex_node, "y", buffer);
	}
	
}

void Pen::Reset()
{
	b2Vec2 v(_start_x/ PIXELS_PER_UNIT, _start_y/PIXELS_PER_UNIT);
	body->SetXForm(v, _start_rot);
	
	//Set Velocity
	b2Vec2 veloc( 0.0, 0.0); ///(wd->accel.x),(wd->accel.y));
	body->SetLinearVelocity(veloc);	

}

void Pen::UpdateXform(float x, float y, float ang)
{
	_start_x = (x);// - polygon->x[0];
	_start_y = (y);// - polygon->y[0];
	_start_rot = ang;
}

bool Pen::IsSelected(Sprite* s)
{/* The points creating the polygon. */

  float x = s->GetX();
  float y = s->GetY();
  
  int i, j, c = 0;

  b2Vec2 pos = body->GetPosition();

	for (i = 0, j = polygon->nVertices-1; i < polygon->nVertices; j = i++) {
	
		b2Vec2 pos2;
		pos2.x = float32(polygon->x[i]);
		pos2.y = float32(polygon->y[i]);
		
		b2Mat22 rot;
		rot.Set(float32(body->GetAngle()));
		pos2 = b2Mul(rot, pos2);
		
		float pyi = (int)pos2.y + (PIXELS_PER_UNIT*pos.y) + 20.0;
		float pxi = (int)pos2.x + (PIXELS_PER_UNIT*pos.x) + 25.0; 
		
		pos2.x = float32(polygon->x[j]);
		pos2.y = float32(polygon->y[j]);
		
		pos2 = b2Mul(rot, pos2);
		
		float pyj = (int)pos2.y + (PIXELS_PER_UNIT*pos.y) + 20.0;
		float pxj = (int)pos2.x + (PIXELS_PER_UNIT*pos.x) + 25.0; 
		
	
		if ((((pyi <= y) && (y < pyj)) ||
			 ((pyj<= y) && (y < pyi))) &&
			(x < (pxj - pxi) * (y - pyi) / (pyj - pyi) + pxi))
		  c = !c;
	}
	
	if(c == 1) return true;
	
	return false;

} 


void Pen::draw(float xoff, float yoff)
{
	
	int vx, vy, vxs, vys;
	b2Vec2 pos = body->GetPosition();
	
	vxs = 0;
	vys = 0;
	

	// Use all the position data one can get
	Mtx model;
	guMtxIdentity(model);
	GX_LoadPosMtxImm(model, GX_PNMTX0);

	GX_SetLineWidth(50,GX_TO_ONE);
	
			// Turn off texturing
	GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);

	// Draw a Quad
	if(_closed)
	{
		GX_Begin(GX_LINESTRIP, GX_VTXFMT0, polygon->nVertices+1);
	}
	else
	{
		GX_Begin(GX_LINESTRIP, GX_VTXFMT0, polygon->nVertices);
	}
	double alpha = _color.a;
	
	if(this->GetFixed())
	{
		alpha = _color.a/2.0;
	}
	
	for(int i=0;i<polygon->nVertices;++i)
	{
		b2Vec2 pos2;
		pos2.x = float32(polygon->x[i]);
		pos2.y = float32(polygon->y[i]);
		
		b2Mat22 rot;
		rot.Set(float32(body->GetAngle()));
		pos2 = b2Mul(rot, pos2);
		
		vx = (int)pos2.x + (PIXELS_PER_UNIT*pos.x) + 25.0+xoff;
		vy = (int)pos2.y + (PIXELS_PER_UNIT*pos.y) + 20.0+yoff;
	
		if(i == 0)
		{
			vxs = vx;
			vys = vy;
		}
	
		GX_Position2f32(vx, vy);
		GX_Color4u8(_color.r, _color.g, _color.b, alpha);

	}
	
	if(_closed)
	{
		GX_Position2f32(vxs, vys);
		GX_Color4u8(_color.r, _color.g, _color.b, alpha);
	}
	
	GX_End();
		
	// Turn texturing back on
	GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
}
