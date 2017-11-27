#include "Block.h"

Block::Block(b2World* w, float x, float y, float ang, Image* img, int Width, int Height, f32 zoom, bool fixed, f32 restitution, f32 friction, f32 density, int id):
	GenericShape(fixed)
{
	if(img != NULL)
	{
		sprite.SetImage(img);
	}
	
	_density = density;
	_friction = friction;
	_restitution = restitution;
	
	_height = (float)Height;
	_width  = (float)Width;
	_zoom = zoom;
	
    SetId(id);
	//sprite.SetFrame(rand()%4);
	sprite.SetZoom(zoom);
	
	world = w;
	b2BodyDef bodyDef;
	
	bodyDef.position.Set(x / PIXELS_PER_UNIT, y / PIXELS_PER_UNIT);
	
	bodyDef.angle = ang * ( M_PI / 180.0);
	
	bodyDef.userData = (GenericShape*)this;
	
	body = world->CreateBody(&bodyDef);
	
	_start_x = x;
	_start_y = y;
	_start_rot = ang* ( M_PI / 180.0);
	
	b2PolygonDef polydef;
	polydef.SetAsBox(((Width/PIXELS_PER_UNIT)/2)*zoom, ((Height/PIXELS_PER_UNIT)/2)*zoom);
	
  	polydef.density = density;
		
	polydef.friction = friction;
	polydef.restitution = restitution;
	
	body->CreateShape(&polydef);	
	if(!fixed)
		body->SetMassFromShapes();
}

Block::~Block()
{
	world->DestroyBody(body);
}

void Block::Reset()
{
	b2Vec2 v(_start_x/ PIXELS_PER_UNIT, _start_y/PIXELS_PER_UNIT);
	body->SetXForm(v, (float)_start_rot);
	
	//Set Velocity
	b2Vec2 veloc( 0.0, 0.0); ///(wd->accel.x),(wd->accel.y));
	body->SetLinearVelocity(veloc);	

}

void Block::Save(mxml_node_t** world_node, int id)
{
	mxml_node_t* block_node; /*my new xml node*/
	
    char buffer[50];
   
    //SetId(id);
   
	block_node = mxmlNewElement(*world_node, "block");
	
	if(body->GetMass() == 0.0)
	{
		mxmlElementSetAttr(block_node, "type","solid");
	}
	else
	{
		mxmlElementSetAttr(block_node, "type","dynamic");
	}
	
	sprintf(buffer, "%f", _density);
	mxmlElementSetAttr(block_node, "density", buffer);
	sprintf(buffer, "%f", _friction);
	mxmlElementSetAttr(block_node, "friction", buffer);
	sprintf(buffer, "%f", _restitution);
	mxmlElementSetAttr(block_node, "restitution", buffer);
	
	sprintf(buffer, "%f", _start_x);
	mxmlElementSetAttr(block_node, "x", buffer);
	sprintf(buffer, "%f", _start_y);
	mxmlElementSetAttr(block_node, "y", buffer);
	
	sprintf(buffer, "%f", _start_rot*(180.0/M_PI));
	mxmlElementSetAttr(block_node, "rotation", buffer);
	sprintf(buffer, "%f", _height);
	mxmlElementSetAttr(block_node, "height", buffer);
	sprintf(buffer, "%f", _width);
	mxmlElementSetAttr(block_node, "width", buffer);
	sprintf(buffer, "%f", _zoom);
	mxmlElementSetAttr(block_node, "zoom", buffer);
	
	sprintf(buffer, "%d", GetId());
	mxmlElementSetAttr(block_node, "id", buffer);
	
	
}

void Block::UpdateXform(float x, float y, float ang)
{
	_start_x = x;
	_start_y = y;
	_start_rot = ang;
}

bool Block::IsSelected(Sprite* s)
{
	return sprite.CollidesWith(s,true);	
}

void Block::draw(float xoff, float yoff)
{
	sprite.SetRotation(((float)body->GetAngle() * (180 / M_PI))/2.0);
	b2Vec2 pos = body->GetPosition();
	
	if(this->GetFixed())
	{
		sprite.SetTransparency(125);
	}
	else
	{
		sprite.SetTransparency(255);
	}
	
	sprite.SetPosition(PIXELS_PER_UNIT*pos.x, PIXELS_PER_UNIT*pos.y);
	sprite.Draw(xoff, yoff);
}


