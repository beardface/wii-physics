#include "Ball.h"

Ball::Ball(b2World* w, float x, float y, Image* img, double radius, f32 zoom, bool fixed, f32 restitution, f32 friction, f32 density, int id):
	GenericShape(fixed)
{
	sprite = new Sprite();
	
    if(img != NULL)
	{
	   sprite->SetImage(img);
	}
	
    SetId(id);
	_density = density;
	_friction = friction;
	_restitution = restitution;
	
	_radius = radius;
	_zoom = zoom;
	
	//sprite.SetFrame(rand()%4);
	sprite->SetZoom(zoom);
	world = w;
	b2BodyDef bodyDef;
	
	bodyDef.position.Set(x / PIXELS_PER_UNIT, y / PIXELS_PER_UNIT);
		
	bodyDef.userData = (GenericShape*)this;
	body = world->CreateBody(&bodyDef);
	b2CircleDef circledef;
	circledef.radius = (radius / PIXELS_PER_UNIT)*zoom;
	
	_start_x = x;
	_start_y = y;
	_start_rot = 0;
	
	circledef.density = density;
		
	circledef.userData = this;

	circledef.friction = friction;
	circledef.restitution = restitution;
	
	body->CreateShape(&circledef);
	if(!fixed)
		body->SetMassFromShapes();
}

Ball::~Ball()
{
	world->DestroyBody(body);
}

void Ball::Reset()
{
	b2Vec2 v(_start_x/ PIXELS_PER_UNIT, _start_y/PIXELS_PER_UNIT);
		body->SetXForm(v, _start_rot);
	
	//Set Velocity
	b2Vec2 veloc( 0.0, 0.0); ///(wd->accel.x),(wd->accel.y));
	body->SetLinearVelocity(veloc);	

}

void Ball::UpdateXform(float x, float y, float ang)
{
	_start_x = x;
	_start_y = y;
	_start_rot = ang;
}

void Ball::Save(mxml_node_t** world_node, int id)
{
	//TODO Return save string
	mxml_node_t* ball_node; /*my new xml node*/
	
	ball_node = mxmlNewElement(*world_node, "circle");
	
    char buffer[50];
	
    //SetId(id);
	
	if(body->GetMass() == 0.0)
	{
		mxmlElementSetAttr(ball_node, "type","solid");
	}
	else
	{
		mxmlElementSetAttr(ball_node, "type","dynamic");
	}
	
	sprintf(buffer, "%f", _density);
	mxmlElementSetAttr(ball_node, "density", buffer);
	sprintf(buffer, "%f", _friction);
	mxmlElementSetAttr(ball_node, "friction", buffer);
	sprintf(buffer, "%f", _restitution);
	mxmlElementSetAttr(ball_node, "restitution", buffer);
	
	sprintf(buffer, "%f", _start_x);
	mxmlElementSetAttr(ball_node, "x", buffer);
	sprintf(buffer, "%f", _start_y);
	mxmlElementSetAttr(ball_node, "y", buffer);
	
	mxmlElementSetAttr(ball_node, "rotation", "0.0");
	
	sprintf(buffer, "%f", _radius);
	mxmlElementSetAttr(ball_node, "radius", buffer);
	sprintf(buffer, "%f", _zoom);
	mxmlElementSetAttr(ball_node, "zoom", buffer);
	
	sprintf(buffer, "%d", GetId());
	mxmlElementSetAttr(ball_node, "id", buffer);
}

bool Ball::IsSelected(Sprite* s)
{
	return sprite->CollidesWith(s,true);	
}

void Ball::draw(float xoff, float yoff)
{
	sprite->SetRotation((float)body->GetAngle() / M_PI * 180.0);
	b2Vec2 pos = body->GetPosition();
	
	if(this->GetFixed())
	{
		sprite->SetTransparency(125);
	}
	else
	{
		sprite->SetTransparency(255);
	}
	
	sprite->SetPosition(PIXELS_PER_UNIT*pos.x, PIXELS_PER_UNIT*pos.y);
	sprite->Draw(xoff, yoff);
}

