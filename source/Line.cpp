#include "Line.h"


Line::Line(b2World* tworld, float x, float y, float ang, GXColor color, int Width, int Height, bool fixed, f32 restitution, f32 friction, f32 density, int id)
	: GenericShape(fixed)
{
	if(Width <= 3) w = 10;
	else w = Width;
	
	if(Height <= 3) h = 10;
	else h = Height;

	rect.x = x;
	rect.y = y;
	rect.width = w;
	rect.height = h;
	quad.SetRectangle(&rect);
	quad.SetFillColor(color);
	
	_color = color;
	
	_density = density;
	_friction = friction;
	_restitution = restitution;
	
	_height = Height;
	_width  = Width;
	
    SetId(id);
	
	_start_x = (x+w/2.0);
	_start_y = (y+h/2.0);
	_start_rot = ang* ( M_PI / 180.0);
	
	world = tworld;
	b2BodyDef bodyDef;
	
	bodyDef.position.Set((x+w/2.0) / PIXELS_PER_UNIT, (y+h/2.0) / PIXELS_PER_UNIT);

	bodyDef.userData = (GenericShape*)this;
		
	bodyDef.angle = ang * ( M_PI / 180.0);
	body = world->CreateBody(&bodyDef);
	
	b2PolygonDef polydef;
	polydef.SetAsBox(((w/PIXELS_PER_UNIT)/2.0), ((h/PIXELS_PER_UNIT)/2.0));
	

  	polydef.density = density;
	
	polydef.friction = friction;
	polydef.restitution = restitution;
	
	body->CreateShape(&polydef);	
	if(!fixed)
		body->SetMassFromShapes();
}

Line::~Line()
{
	world->DestroyBody(body);
}

void Line::Reset()
{
	b2Vec2 v((_start_x)/ PIXELS_PER_UNIT, (_start_y)/PIXELS_PER_UNIT);
	body->SetXForm(v, (float)_start_rot);
	
	//Set Velocity
	b2Vec2 veloc( 0.0, 0.0); ///(wd->accel.x),(wd->accel.y));
	body->SetLinearVelocity(veloc);	

}

void Line::UpdateXform(float x, float y, float ang)
{
	_start_x = x;
	_start_y = y;
	_start_rot = ang;
}


void Line::Save(mxml_node_t** world_node, int id)
{
	//TODO Return save string
	mxml_node_t* line_node; /*my new xml node*/
	
	line_node = mxmlNewElement(*world_node, "line");
	
    char buffer[50];
	
    //SetId(id);
		
	if(body->GetMass() == 0.0)
	{
		mxmlElementSetAttr(line_node, "type","solid");
	}
	else
	{
		mxmlElementSetAttr(line_node, "type","dynamic");
	}
	
	sprintf(buffer, "%f", _density);
	mxmlElementSetAttr(line_node, "density", buffer);
	sprintf(buffer, "%f", _friction);
	mxmlElementSetAttr(line_node, "friction", buffer);
	sprintf(buffer, "%f", _restitution);
	mxmlElementSetAttr(line_node, "restitution", buffer);
	
	sprintf(buffer, "%f", _start_x-_width/2.0);
	mxmlElementSetAttr(line_node, "x", buffer);
	sprintf(buffer, "%f", _start_y-_height/2.0);
	mxmlElementSetAttr(line_node, "y", buffer);
	
	sprintf(buffer, "%f", _start_rot*(180.0/M_PI));
	mxmlElementSetAttr(line_node, "rotation", buffer);
	
	sprintf(buffer, "%f", _height);
	mxmlElementSetAttr(line_node, "height", buffer);
	sprintf(buffer, "%f", _width);
	mxmlElementSetAttr(line_node, "width", buffer);
	
	sprintf(buffer, "%d", _color.r);
	mxmlElementSetAttr(line_node, "color.r", buffer);
	sprintf(buffer, "%d", _color.g);
	mxmlElementSetAttr(line_node, "color.g", buffer);
	sprintf(buffer, "%d", _color.b);
	mxmlElementSetAttr(line_node, "color.b", buffer);
	sprintf(buffer, "%d", _color.a);
	mxmlElementSetAttr(line_node, "color.a", buffer);
	
	mxmlElementSetAttr(line_node, "closed", "1");
	
	sprintf(buffer, "%d", GetId());
	mxmlElementSetAttr(line_node, "id", buffer);
}

bool Line::IsSelected(Sprite* sprite)
{
   f32 angle1 = (f32)quad.GetRotation()*M_PI/90,
		angle2 = (f32)sprite->GetRotation()*M_PI/90;

	Rectangle rect[4]; // Points which help calculate this stuff.

	f32 cosa, sina, // For sin/cos calculations
		temp, x, a, // Temp vars for various useage.
		deltaX, // For linear equations
		vertical1, vertical2; // Min/max vertical values

	// Init data
	rect[0].x = (f32)(sprite->GetX()+(f32)(sprite->GetWidth()/2));
	rect[0].y = (f32)(sprite->GetY()+(f32)(sprite->GetHeight()/2));
	rect[1].x = (f32)(quad.GetX()+(f32)((quad.GetWidth()/2)));
	rect[1].y = (f32)(quad.GetY()+(f32)((quad.GetHeight()/2)));
	rect[0].width = (f32)(quad.GetWidth()/2);
	rect[0].height = (f32)(quad.GetHeight()/2);
	rect[1].width = (f32)(sprite->GetWidth()/2)*sprite->GetStretchWidth();
	rect[1].height = (f32)(sprite->GetHeight()/2)*sprite->GetStretchHeight();

	// Move the sprite by the other sprites values
	rect[0].x -= rect[1].x; rect[0].y -= rect[1].y;

	// Rotate the other sprite clockwise by its angle to make it axis-aligned
	cosa = cos(angle2),
	sina = sin(angle2);
	temp = rect[0].x; rect[0].x = temp*cosa + rect[0].y*sina; rect[0].y = -temp*sina + rect[0].y*cosa;

	// Calculate the points of the other sprite. 
	rect[2].width = rect[2].x = rect[0].x;
	rect[2].height = rect[2].y = rect[0].y;
	rect[2].width -= rect[1].width; rect[2].height -= rect[1].height;
	rect[2].x += rect[1].width; rect[2].y += rect[1].height;

	cosa = cos(angle1-angle2);
	sina = sin(angle1-angle2);
	// Calculate the points of this sprite
	rect[3].x = -rect[0].height*sina; rect[3].width = rect[3].x; temp = rect[0].width*cosa; rect[3].x += temp; rect[3].width -= temp;
	rect[3].y =  rect[0].height*cosa; rect[3].height = rect[3].y; temp = rect[0].width*sina; rect[3].y += temp; rect[3].height -= temp;

	temp = sina*cosa;

	// Check for the right A and B values, swap them if they're not
	if(temp < 0){
		temp = rect[3].x; rect[3].x = rect[3].width; rect[3].width = temp;
		temp = rect[3].y; rect[3].y = rect[3].height; rect[3].height = temp;
	}

	// Verify that B is the vertex closest to the left
	if(sina < 0){
		rect[3].width = -rect[3].width; rect[3].height = -rect[3].height;
	}

	// Check B if it is in the range that needs to be checked
	if(rect[3].width > rect[2].x || rect[3].width > -rect[2].width)return false;

	// Check if they are aligned to the axis, checking is easier then
	if(temp == 0){
		vertical1 = rect[3].y; vertical2 = -vertical1;
	}else{
		// Check for the vertical range

		x = rect[2].width-rect[3].x; a = rect[2].x-rect[3].x;
		vertical1 = rect[3].y;
		
		// If the first vertical range is not between the given values,
		// check on the value itself
		if(a*x > 0){
			deltaX = rect[3].x;
			if(x < 0){
				deltaX -= rect[3].width; vertical1 -= rect[3].height; x = a;
			}else{
				deltaX += rect[3].width; vertical1 += rect[3].height;
			}
			vertical1 *= x; vertical1 /= deltaX; vertical1 += rect[3].y;
		}

		x = rect[2].width+rect[3].x; a = rect[2].x+rect[3].x;
		vertical2 = -rect[3].y;
		
		//If the second vertical range is not between the given values,
		//check on the value itself
		if(a*x > 0){
			deltaX = -rect[3].x;
			if(x < 0){
				deltaX -= rect[3].width; vertical2 -= rect[3].height; x = a;
			}else{
				deltaX += rect[3].width; vertical2 += rect[3].height;
			}
			vertical2 *= x; vertical2 /= deltaX; vertical2 -= rect[3].y;
		}
	}

	//Check if this sprite is in the vertical range of the other. Returns either true or false.
	return !((vertical1 < rect[2].height && vertical2 < rect[2].height) ||
		(vertical1 > rect[2].y && vertical2 > rect[2].y));

	//return s->CollidesWith(&rect);
}

void Line::draw(float xoff, float yoff)
{
	b2Vec2 pos = body->GetPosition();
	
	quad.SetRotation(((float)body->GetAngle() * (180 / M_PI))/2.0);
	rect.x = ((PIXELS_PER_UNIT*pos.x)) - rect.width/2.0 + 25.0;
	rect.y = ((PIXELS_PER_UNIT*pos.y)) - rect.height/2.0 + 20.0;
	
	if(this->GetFixed())
	{
		GXColor tcolor = _color;
		tcolor.a = _color.a/2.0;
			
		quad.SetFillColor(tcolor);
	
	}
	else
	{
		quad.SetFillColor(_color);
	}
	
	quad.SetRectangle(&rect);
	quad.Draw(xoff, yoff);

}
