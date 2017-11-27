
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <malloc.h>
#include <math.h>
#include <ogcsys.h>

#include <gccore.h>
#include <wiiuse/wpad.h>
#include "wiisprite.h"
#include "Box2D.h"
#include <fat.h>
#include "WiiStackTypes.h"

#include "OnScreenKeyboard.h"

#include "file.h"

#include "tiledtextlayer.h"

#include "Block.h"
#include "Ball.h"
#include "Line.h"
#include "Pen.h"

#include "mxml.h"

#include "GenericShape.h"

#include "box2d/b2Polygon.h"

#include "ToolBox.h"

#include "SettingsBox.h"

#include "MainMenuBox.h"

#include "MiniMap.h"

#include "Clouds.h"

#include <unistd.h>
#include <vector>

//Joints
#include "DistanceJoint.h"
#include "RevoluteJoint.h"
#include "PulleyJoint.h"
#include "PrismaticJoint.h"

#define DRIFT_DISTANCE 500

//Image Includes
#include "block_image.h"
#include "ball_image.h"
#include "select.h"
#include "rope.h"
#include "jointPointer.h"
#include "penPointer.h"
#include "revPointer.h"
#include "intro.h"
#include "penCursor.h"
#include "grass.h"
#include "weldPointer.h"

#include "deletePointer.h"
#include "cameraPointer.h"

#include "support.h"

#include "player1_point.h"
#include "player1_grab.h"
#include "player1_openhand.h"
#include "player2_point.h"
#include "player2_grab.h"
#include "player2_openhand.h"

#include "help_page_one.h"
#include "help_page_two.h"

#include "title.h"
#include "titlebg.h"

//Audio Includes
//#include "drawOgg.h"
#include "introOgg.h"
//#include "clearOgg.h"
//#include "hoverOgg.h"
//#include "undoOgg.h"
//#include "clickOgg.h"
#include "bgmOgg.h"

//Include OggPlayer
#include <fcntl.h>

#include "snd.h"
#include "oggplayer.h"

#define BLOCK 0
#define BALL  1
#define LINE  2
#define REV_JOINT 3
#define PUL_JOINT 4
#define DIST_JOINT 5
#define PRIS_JOINT 6
#define POLYPEN 7

#define SCROLL_EDGE_DIST 20
std::string save_string = "";

b2MouseJointDef mouseJointDef;
b2MouseJoint* mouseJoint = NULL;

b2MouseJointDef p2mouseJointDef;
b2MouseJoint* p2mouseJoint = NULL;

bool _loadDisplayed = false;
bool _saveDisplayed = false;

bool show_help = false;
bool show_support = false;
int help_page = 1;

int SelectedType = -1;
int p2SelectedType = -1;

std::vector<int> undo_list;

OnScreenKeyboard* osk;
	 
int drift_dist = 0;

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

using namespace wsp;
using namespace WiiStackTypes;

int screen_width, screen_height;

MiniMap* miniMap;

float MIN_SLIDE_Y = -595;
float MAX_SLIDE_Y = 750;

float MIN_SLIDE_X = -700;
float MAX_SLIDE_X = 700;

Clouds* myClouds;

f32 zoom = 1.0;

GameWindow gwd;
	
b2World *world = 0;
b2Body* groundBody ;

f32 sx;
f32 sy;

Image *blockimage;
Image *ballimage;

Image *lineimage;

Image *selectimage;
Image *grabimage;
Image *openimage;

Image *p2selectimage;
Image *p2grabimage;
Image *p2openimage;

Image *ropeimage;

Image *jointpointerimage;
Image *penimage;
Image *penCursorImage;
Image *revpointerimage;
Image *weldpointerimage;

Image *deletepointerimage;
Image *camerapointerimage;

//Main Menu Images
Image *titleimage;
Image *titlebgimage;
//

Image *grassimage;
Sprite grassSprite;

Image *helpimage1;
Image *helpimage2;
Image *supportimage;

Sprite titleSprite;
Sprite bgSprite;

Sprite pointersprite;
Sprite p2pointersprite;

bool hide_menu = false;

float m_init_x;
float m_init_y;
float m_init_a;
float m_init_pos_x;
float m_init_pos_y;
float m_init_pos_a;

float p2_init_x;
float p2_init_y;
float p2_init_a;
float p2_init_pos_x;
float p2_init_pos_y;
float p2_init_pos_a;

Quad boxQuad;
Rectangle boxRect;

Quad groundQuad;

Quad leftWallQuad;
Quad rightWallQuad;

Gravity::Type current_gravity = Gravity::EARTH;

b2Vec2 earth_gravity(0.0f, 10.0f);
b2Vec2 moon_gravity(0.0f, 1.7f);
b2Vec2 jupiter_gravity(0.0f, 23.6f);

bool drawingBox = false;

ToolBox *toolbox;
SettingsBox *settings;
MainMenuBox *main_menu;

std::vector<Block*> blocks; //[MAX_BLOCKS];
int n_blocks = 0;

std::vector<Ball *> balls;//[MAX_BALLS];
int n_balls = 0;

int m_next_id = 1;

std::vector<Line *> lines;//[MAX_LINES];
int n_lines = 0;

std::vector<Pen *> polyPen;//[MAX_POLYPENS];
int n_polypen = 0;

std::vector<DistanceJoint *> distJoints;//[MAX_DIST_JOINTS];
int n_dist_joints = 0;

std::vector<RevoluteJoint *> revJoints;//[MAX_REV_JOINTS];
int n_rev_joints = 0;

std::vector<PulleyJoint *> pulJoints;//[MAX_PUL_JOINTS];
int n_pul_joints = 0;

std::vector<PrismaticJoint *> prisJoints;//[MAX_PRIS_JOINTS];
int n_pris_joints = 0;

int draw_type = 0;

b2Body* selBod1 = NULL;
b2Body* selBod2 = NULL;
b2Body* selBod3 = NULL;
b2Body* mouseBod = NULL;
b2Body* p2mouseBod = NULL;

b2Vec2 click_point;
b2Vec2 click_point_2;
b2Vec2 click_point_3;

int num_picks_left = 0;

WPADData *wd;

bool camera_set = false;
b2Body* cameraBod = NULL;

b2Vec2 polyPoints[MAX_POLY_POINTS];
int num_points_current_poly = 0;
bool drawing_poly = false;

f32 cur_x;
f32 cur_y;

void* SelectedPointer = NULL;
void* p2SelectedPointer = NULL;

//Screen Zoom/Pan
float screen_x_offset = 0.0;
float screen_y_offset = 0.0;

f32 box_x;
f32 box_y;

typedef enum
{
	TYPE_BACK = 0,
	TYPE_FOLDER = 1,
	TYPE_PP = 2,
	TYPE_UNKNOWN = 3
} IconType;

char currentDir[MAXPATHLEN];
		
typedef struct
{
	Sprite *sprite;
	Sprite *icon;
	
	IconType whichIcon;
	bool played;
	
	char fileName[MAXPATHLEN];
	FileType fType;
} FileListType;

FileListType *fList = NULL;
int fListCount = 0;
		
/* my save callback */
const char *
whitespace_cb(mxml_node_t *node,
			  int where)
{
	const char *name;

	name = node->value.element.name;

	if (!strcmp(name, "ppsketch"))
	{
			return ("\n");
	}
	else if (!strcmp(name, "creator") ||
			 !strcmp(name, "author"))
	{
		if (where == MXML_WS_BEFORE_OPEN)
			return ("\t");
		else if (where == MXML_WS_AFTER_CLOSE)
			return ("\n");
	}	 
	else if (!strcmp(name, "world"))
	{
		if (where == MXML_WS_BEFORE_OPEN)
			return ("\t");
		else if (where == MXML_WS_AFTER_OPEN)
			return ("\n");
		else if (where == MXML_WS_BEFORE_CLOSE)
			return ("\t");
		else if (where == MXML_WS_AFTER_CLOSE)
			return ("\n");
	}
	else if (!strcmp(name, "world"))
	{
		if (where == MXML_WS_BEFORE_OPEN)
			return ("\t");
		else if (where == MXML_WS_AFTER_OPEN)
			return ("\n");
	}
	else if (!strcmp(name, "polygon") ||
			 !strcmp(name, "circle") ||
			 !strcmp(name, "line") ||
			 !strcmp(name, "block") ||
			 !strcmp(name, "dist") ||
			 !strcmp(name, "pris") ||
			 !strcmp(name, "pull") ||
			 !strcmp(name, "pin"))
	{
		if (where == MXML_WS_BEFORE_OPEN)
			return ("\t\t");
		else if (where == MXML_WS_AFTER_OPEN)
			return ("\n");
		if (where == MXML_WS_BEFORE_CLOSE)
			return ("\t\t");
		else if (where == MXML_WS_AFTER_CLOSE)
			return ("\n");
	}
	else if (!strcmp(name, "vertex") ||
			 !strcmp(name, "pinned_thing"))
	{
		if (where == MXML_WS_BEFORE_OPEN)
			return ("\t\t\t");
		else if (where == MXML_WS_AFTER_OPEN)
			return ("\n");
	}

	return (NULL);
}


//Box draw helper (EBOOL)
void resizeBox(f32 x,f32 y){
    if(x<0.0) x=0.0;
    if(y<0.0) y=0.0;
    s32 dw=(s32)(x-sx);
    s32 dh=(s32)(y-sy);
    u32 w;
    u32 h;
    u32 nx;
    u32 ny;
    
    if(dw<0){
        dw=-dw;
        nx=x;
    }else{
        nx=sx;
    }
    w=(u32)dw;
    if(w<10) w=10;
    
    if(dh<0){
        dh=-dh;
        ny=y;
    }else{
        ny=sy;
    }
    h=(u32)dh;
    if(h<10) h=10;
    
    boxQuad.SetX(nx);
    boxQuad.SetY(ny);
    boxQuad.SetWidth(w);
    boxQuad.SetHeight(h);
}

b2Body* GetSelectedBody(Sprite* ptr_sprite, int* selType, void** selPointer)
{
	float old_x = ptr_sprite->GetX();
	float old_y = ptr_sprite->GetY();
	
	ptr_sprite->SetPosition(ptr_sprite->GetX()-screen_x_offset, ptr_sprite->GetY()-screen_y_offset);
	
	for(int b=0; b<(int)blocks.size(); ++b)
	{
		 if(blocks[b]->IsSelected(ptr_sprite))
		 {
			if(blocks[b]->GetBody() != selBod1)
			{
				ptr_sprite->SetPosition(old_x, old_y);
				*selType = BLOCK;
				*selPointer = blocks[b];
				return blocks[b]->GetBody();
			}
	 	}
	}
	
	for(int b=0; b<(int)balls.size(); ++b)
	{
		 if(balls[b]->IsSelected(ptr_sprite))
		 {
			if(balls[b]->GetBody() != selBod1)
			{
				ptr_sprite->SetPosition(old_x, old_y);
				*selType = BALL;
				*selPointer = balls[b];
				return balls[b]->GetBody();
			}
	 	}
	}
	
	for(int b=0; b<(int)lines.size(); ++b)
	{
		 if(lines[b]->IsSelected(ptr_sprite))
		 {
			if(lines[b]->GetBody() != selBod1)
			{
				ptr_sprite->SetPosition(old_x, old_y);
				*selType = LINE;
				*selPointer = lines[b];
				return lines[b]->GetBody();
			}
	 	}
	}
	
	for(int b=0; b<(int)polyPen.size(); ++b)
	{
		 if(polyPen[b]->IsSelected(ptr_sprite))
		 {
			if(polyPen[b]->GetBody() != selBod1)
			{
				ptr_sprite->SetPosition(old_x, old_y);
				*selType = POLYPEN;
				*selPointer = polyPen[b];
				return polyPen[b]->GetBody();
			}
	 	}
	}
	
	ptr_sprite->SetPosition(old_x, old_y);
	
	*selType    = -1;
	*selPointer = NULL;
	return NULL;
}


void AddJoint(Joint::Type jointType, b2Body* b1, b2Body* b2, b2Body* b3)
{
   if(b1 == b2)
   {
		b2 = groundBody;
	}
	
	if(b1 == NULL) b1 = groundBody;
	if(b2 == NULL) b2 = groundBody;
	if(b3 == NULL) b3 = groundBody;
	
	switch(jointType)
	{
		case Joint::DISTANCE_JOINT:
			if((int)distJoints.size() < MAX_DIST_JOINTS-1)
			{
				
				distJoints.push_back(new DistanceJoint(world, b1, b2, click_point, click_point_2, true, settings->GetColor(), false));
				n_dist_joints++;
			}
			break;
		case Joint::RUBBER_JOINT:
			if((int)distJoints.size() < MAX_DIST_JOINTS-1)
			{
				distJoints.push_back(new DistanceJoint(world, b1, b2, click_point, click_point_2, true, settings->GetColor(), true));
				n_dist_joints++;
			}
			break;
		case Joint::PRISMATIC_JOINT:
			{
				//TODO find a better way to get this axis
				b2Vec2 worldAxis(1.0f, 0.0f);
			
				prisJoints.push_back(new PrismaticJoint(world, b1, b2, click_point, worldAxis, ropeimage, -2.5, 5.0));
				n_pris_joints++;
			}
			break;
		case Joint::PULLEY_JOINT:
			if((int)pulJoints.size() < MAX_PUL_JOINTS-1)
			{
				//get anchors
				pulJoints.push_back(new PulleyJoint(world, b1, b2->GetWorldCenter(), b3, .03, settings->GetColor()));
				n_pul_joints++;
			}
			break;
		case Joint::REVOLUTE_JOINT:
			if((int)revJoints.size() < MAX_REV_JOINTS-1)
			{
				revJoints.push_back(new RevoluteJoint(world, b1, b2, click_point, ropeimage));
				n_rev_joints++;
			}
			break;
		case Joint::WELD_JOINT:
			{
				//TODO find a better way to get this axis
				b2Vec2 worldAxis(1.0f, 0.0f);
			
				prisJoints.push_back(new PrismaticJoint(world, b1, b2, click_point, worldAxis, ropeimage, 0.0, 0.0));
				n_pris_joints++;
			}
			break;
		default:
			break;
		
	}
	
} 

void makeWorld(void)
{
	b2AABB worldAABB;
	// Visible area is 8x6 units
	worldAABB.lowerBound.Set(-100.0f, -100.0f);
	worldAABB.upperBound.Set(100.0f, 100.0f);
	
	bool doSleep = false;
	world = new b2World(worldAABB, earth_gravity, doSleep);
	
	// Get Screen Resolution
	GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);
	screen_width = (int)((float)rmode->viWidth * 2.2f); // <- works for me
	screen_height = (int)((float)rmode->viHeight * 2.2f);
	float32 width = ((float)screen_width / PIXELS_PER_UNIT)*2.0;
	float32 height = ((float)screen_height / PIXELS_PER_UNIT)*2.0;
	
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(-1*(width/2.0), -1*(height/2.0));
	groundBody = world->CreateBody(&groundBodyDef);
	
	groundQuad.SetWidth((float)width*PIXELS_PER_UNIT);
	groundQuad.SetHeight(300.0);
	groundQuad.SetX((float)((-1.0)*(width*PIXELS_PER_UNIT)/2.0));
	groundQuad.SetY((float)((-1.0)*(height*PIXELS_PER_UNIT)/2.0 + (height*PIXELS_PER_UNIT)+10.0));
	groundQuad.SetFillColor((GXColor){ 0, 255, 0, 255 });
	
	//Create MiniMap
	miniMap = new MiniMap((float)(640/10.0), (float)(480/10.0), (float).3, (float)50, (float)425);
	
	// Create a room
	b2PolygonDef groundShapeDef[4];
	groundShapeDef[0].SetAsBox(float32(width), float32(0.1f),   b2Vec2(width/2.0, -0.1),       0.0);
	groundShapeDef[1].SetAsBox(float32(width), float32(0.1f),   b2Vec2(width/2.0, height),     0.0);
	groundShapeDef[2].SetAsBox(float32(0.1f),  float32(height), b2Vec2(-0.1,      height/2.0), 0.0);
	groundShapeDef[3].SetAsBox(float32(0.1f),  float32(height), b2Vec2(width,     height/2.0), 0.0);
	
	for(int i=0;i<4;++i)
		groundBody->CreateShape(&groundShapeDef[i]);
}

void DrawScreen()
{
	if(main_menu->Displayed())
	{
		gwd.SetBackground((GXColor){ 255, 255, 255, 255 });
		bgSprite.SetPosition(0,0);
		bgSprite.Draw();
		
		titleSprite.SetPosition(100,58);
		titleSprite.Draw();
		main_menu->Draw(0);
		pointersprite.Draw();
		gwd.Flush();
	}
	else if(settings->Displayed())
	{
		gwd.SetBackground((GXColor){ 255, 255, 255, 255 });
		settings->Draw(0);
		pointersprite.Draw();
		gwd.Flush();
	}
	else
	{
	    //Set up pan window
		
		if(toolbox->GetPlayMode() == PlayMode::PLAY)
		{
			myClouds->Update();
		}
		
		gwd.SetBackground((GXColor){ 119, 205, 255, 255 });
		myClouds->Draw(screen_x_offset, screen_y_offset);
		
		//groundQuad.Draw(screen_x_offset, screen_y_offset);
		
		// Draw the balls
		for(int b=0; b<(int)lines.size(); ++b)
		{
			lines[b]->draw(screen_x_offset, screen_y_offset);
		}
		
		// Draw the balls
		for(int b=0; b<(int)blocks.size(); ++b)
		{
			blocks[b]->draw(screen_x_offset, screen_y_offset);
		}
		
		// Draw the balls
		for(int b=0; b<(int)balls.size(); ++b)
		{
			balls[b]->draw(screen_x_offset, screen_y_offset);
		}
		
		for(int b=0; b<(int)polyPen.size(); ++b)
		{
			polyPen[b]->draw(screen_x_offset, screen_y_offset);
		}
		
		for(int b=0; b<(int)distJoints.size(); ++b)
		{
			distJoints[b]->draw(screen_x_offset, screen_y_offset);
		}
		
		for(int b=0; b<(int)revJoints.size(); ++b)
		{
			revJoints[b]->draw(screen_x_offset, screen_y_offset);
		}
		
		for(int b=0; b<(int)pulJoints.size(); ++b)
		{
			pulJoints[b]->draw(screen_x_offset, screen_y_offset);
		}
		
		for(int b=0; b<(int)prisJoints.size(); ++b)
		{
			prisJoints[b]->draw(screen_x_offset, screen_y_offset);
		}
		
		
		if(drawingBox)
		{
			boxQuad.Draw(0, 0);
		}
		
		if(num_points_current_poly > 0)
		{
			Mtx model;
			guMtxIdentity(model);
			GX_LoadPosMtxImm(model, GX_PNMTX0);

			GX_SetLineWidth(50,GX_TO_ONE);
			
					// Turn off texturing
			GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
			GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);

			// Draw a Quad
			GX_Begin(GX_LINESTRIP, GX_VTXFMT0, num_points_current_poly+1);
			for(int i = 0; i < num_points_current_poly; i++)
			{
			// Use all the position data one can get
			
				GX_Position2f32(polyPoints[i].x+screen_x_offset, polyPoints[i].y+screen_y_offset);
				GX_Color4u8(settings->GetColor().r, settings->GetColor().g, settings->GetColor().b, settings->GetColor().a);

			}
			GX_Position2f32(cur_x, cur_y);
			GX_Color4u8(settings->GetColor().r, settings->GetColor().g, settings->GetColor().b, settings->GetColor().a);
			GX_End();
			
			
			// Turn texturing back on
			GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
			GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
		}
		
		
		//Draw Grass
		for(int i=MIN_SLIDE_X; i < MAX_SLIDE_X+600; i+=grassSprite.GetWidth())
		{
			grassSprite.SetPosition(i,groundQuad.GetY()-15);
			grassSprite.Draw(screen_x_offset, screen_y_offset);
		}
		
		
		// Draw the toolbox
		toolbox->Draw(drift_dist);
		
		miniMap->SetMiniMapWidthRatio((screen_x_offset-MIN_SLIDE_X)/(MAX_SLIDE_X - MIN_SLIDE_X));
		miniMap->SetMiniMapHeightRatio((screen_y_offset-MIN_SLIDE_Y)/(MAX_SLIDE_Y - MIN_SLIDE_Y));
		miniMap->Draw(0,0);
		
		pointersprite.Draw();
		
		p2pointersprite.Draw();
		
		gwd.Flush();
		
		//reset view box to be nice
		GX_SetScissor(0, 0, gwd.GetWidth(), gwd.GetHeight());
		
	}

}

void ResetShapes()
{
	for(int b=0; b<(int)lines.size(); ++b)
	{
		lines[b]->Reset();
	}
	
	// Draw the balls
	for(int b=0; b<(int)blocks.size(); ++b)
	{
		blocks[b]->Reset();
	}
	
	// Draw the balls
	for(int b=0; b<(int)balls.size(); ++b)
	{
		balls[b]->Reset();
	}
	
	for(int b=0; b<(int)polyPen.size(); ++b)
	{
		polyPen[b]->Reset();
	}
}

void init_console()
{
	// Initialise the video system
	VIDEO_Init();
	// Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL);

	// Allocate memory for the display in the uncached region
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	
	// Initialise the console, required for printf
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
	
	// Set up the video registers with the chosen mode
	VIDEO_Configure(rmode);
	
	// Tell the video hardware where our display memory is
	VIDEO_SetNextFramebuffer(xfb);
	
	// Make the display visible
	VIDEO_SetBlack(FALSE);

	// Flush the video register changes to the hardware
	VIDEO_Flush();

	// Wait for Video setup to complete
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

}

void RemoveObject(b2Body* body)
{
	if(body != NULL && body != groundBody)
	{
		if(body == mouseBod)
		{
			mouseBod = NULL;
			if(mouseJoint != NULL)
			{
				world->DestroyJoint(mouseJoint);
				mouseJoint = NULL;
			}
		}
		
		if(body == cameraBod)
		{
			cameraBod = NULL;
			camera_set = false;
		}
		
		if(body == p2mouseBod)
		{
			p2mouseBod = NULL;
			if(p2mouseJoint != NULL)
			{
				world->DestroyJoint(p2mouseJoint);
				p2mouseJoint = NULL;
			}
		}
		
		//clean up any joints
		for(int b=0; b<(int)distJoints.size(); ++b)
		{
			if(body == distJoints[b]->GetBody1() || body == distJoints[b]->GetBody2())
			{
				//delete this joint as well
				delete distJoints[b];
			    distJoints.erase(distJoints.begin()+b);
				b = 0;
				
				n_dist_joints--;
			}
		}
		
		for(int b=0; b<(int)revJoints.size(); ++b)
		{
			if(body == revJoints[b]->GetBody1() || body == revJoints[b]->GetBody2())
			{
				//delete this joint as well
				delete revJoints[b];
			    revJoints.erase(revJoints.begin()+b);
				b = 0;
				
				n_rev_joints--;
			}
		}
		
		for(int b=0; b<(int)pulJoints.size(); ++b)
		{
			if(body == pulJoints[b]->GetBody1() || body == pulJoints[b]->GetBody2())
			{
				//delete this joint as well
				delete pulJoints[b];
			    pulJoints.erase(pulJoints.begin()+b);
				b = 0;
				
				n_pul_joints--;
			}
		}
		
		for(int b=0; b<(int)prisJoints.size(); ++b)
		{
			if(body == prisJoints[b]->GetBody1() || body == prisJoints[b]->GetBody2())
			{
				//delete this joint as well
				delete prisJoints[b];
			    prisJoints.erase(prisJoints.begin()+b);
				b = 0;
				
				n_pris_joints--;
			}
		}
		
		switch(SelectedType)
		{
			case BALL:
				for(int b=0; b<(int)balls.size(); ++b)
				{
					if((Ball*)SelectedPointer == balls[b])
					{
						//delete this joint as well
						delete balls[b];
						balls.erase(balls.begin()+b);
						
						n_balls--;
						break;
					}
				}
				break;
			case BLOCK:
				for(int b=0; b<(int)blocks.size(); ++b)
				{
					if((Block*)SelectedPointer == blocks[b])
					{
						//delete this joint as well
						delete blocks[b];
						blocks.erase(blocks.begin()+b);
						
						n_blocks--;
						break;
					}
				}
				break;
			case POLYPEN:
				for(int b=0; b<(int)polyPen.size(); ++b)
				{
					if((Pen*)SelectedPointer == polyPen[b])
					{
						//delete this joint as well
						delete polyPen[b];
						polyPen.erase(polyPen.begin()+b);
						
						n_polypen--;
						break;
					}
				}
				break;
			case LINE:
				for(int b=0; b<(int)lines.size(); ++b)
				{
					if((Line*)SelectedPointer == lines[b])
					{
						//delete this joint as well
						delete lines[b];
						lines.erase(lines.begin()+b);
						
						n_lines--;
						break;
					}
				}
				break;
			default:
				break;
		}
	}
	
}

void Undo()
{
	if(mouseJoint != NULL)
	{
		world->DestroyJoint(mouseJoint);
		mouseJoint = NULL;
	}
		
	if(p2mouseJoint != NULL)
	{
		world->DestroyJoint(p2mouseJoint);
		p2mouseJoint = NULL;
	}		
	
	mouseBod = NULL;
	p2mouseBod = NULL;
	
	if(undo_list.size() > 0)
	{
		if(undo_list.at(undo_list.size()-1) == BLOCK)
		{
			//remove last box
			if((int)blocks.size() > 0)
			{
			   delete blocks[(int)blocks.size() - 1];
			   //blocks.erase(blocks.end()-1);
			   n_blocks--;
			}
			undo_list.erase(undo_list.end()-1);	
		}
		else if(undo_list.at(undo_list.size()-1) == BALL)
		{
			//remove last square
			if((int)balls.size() > 0)
			{
			   delete balls[(int)balls.size() - 1];
			   balls.erase(balls.end()-1);
			   n_balls--;
			}
			undo_list.erase(undo_list.end()-1);	
		}
		else if(undo_list.at(undo_list.size()-1) == LINE)
		{
			//line
			if((int)lines.size() > 0)
			{
			   delete lines[(int)lines.size() - 1];
			   lines.erase(lines.end()-1);
			   n_lines--;
			}
			undo_list.erase(undo_list.end()-1);	
		}
		else if(undo_list.at(undo_list.size()-1) == DIST_JOINT)
		{
			//joint
			if((int)distJoints.size() > 0)
			{
			   delete distJoints[(int)distJoints.size() - 1];
			   distJoints.erase(distJoints.end()-1);
			   n_dist_joints--;
			}
			undo_list.erase(undo_list.end()-1);	
		}
		else if(undo_list.at(undo_list.size()-1) == REV_JOINT)
		{
			//joint
			if((int)revJoints.size() > 0)
			{
			   delete revJoints[(int)revJoints.size() - 1];
			   revJoints.erase(revJoints.end()-1);
			   n_rev_joints--;
			}
			undo_list.erase(undo_list.end()-1);	
		}
		else if(undo_list.at(undo_list.size()-1) == PUL_JOINT)
		{
			//joint
			if((int)pulJoints.size() > 0)
			{
			   delete pulJoints[(int)pulJoints.size() - 1];
			   pulJoints.erase(pulJoints.end()-1);
			   n_pul_joints--;
			}
			undo_list.erase(undo_list.end()-1);	
		}
		else if(undo_list.at(undo_list.size()-1) == PRIS_JOINT)
		{
			//joint
			if((int)prisJoints.size() > 0)
			{
			   delete prisJoints[(int)prisJoints.size() - 1];
			   prisJoints.erase(prisJoints.end()-1);
			   n_pris_joints--;
			}
			undo_list.erase(undo_list.end()-1);	
		}
		else if(undo_list.at(undo_list.size()-1) == POLYPEN)
		{
			if((int)polyPen.size() >0)
			{
			    delete polyPen[(int)polyPen.size() - 1];
				polyPen.erase(polyPen.end()-1);
				n_polypen--;
			}
			undo_list.erase(undo_list.end()-1);
		}
	}
}


void ClearAll()
{
	m_next_id = 1;
	camera_set = false;
	cameraBod  = NULL;
	
	if(mouseJoint != NULL)
	{
		world->DestroyJoint(mouseJoint);
		mouseJoint = NULL;
	}
		
	if(p2mouseJoint != NULL)
	{
		world->DestroyJoint(p2mouseJoint);
		p2mouseJoint = NULL;
	}			
	
	mouseBod = NULL;
	p2mouseBod = NULL;
	
	for(int b=0; b<(int)distJoints.size(); ++b)
	{
		delete distJoints[b];
	}
	n_dist_joints = 0;
	
	for(int b=0; b<(int)revJoints.size(); ++b)
	{
		delete revJoints[b];
	}
	n_rev_joints = 0;
	
	for(int b=0; b<(int)pulJoints.size(); ++b)
	{
		delete pulJoints[b];
	}
	n_pul_joints = 0;
	
	for(int b=0; b<(int)prisJoints.size(); ++b)
	{
		delete prisJoints[b];
	}
	n_pris_joints = 0;
	
	for(int b=0; b<(int)lines.size(); ++b)
	{
		delete lines[b];
	}
	n_lines = 0;
	
	for(int b=0; b<(int)blocks.size(); ++b)
	{
		delete blocks[b];
	}
	n_blocks = 0;
	
	for(int b=0; b<(int)balls.size(); ++b)
	{
		delete balls[b];
	}
	n_balls = 0;
	
	for(int b=0; b<(int)polyPen.size(); ++b)
	{
		delete polyPen[b];
	}
	n_polypen = 0;
	
	
	distJoints.clear();
	revJoints.clear();
	pulJoints.clear();
	prisJoints.clear();
	lines.clear();
	blocks.clear();
	balls.clear();
	polyPen.clear();
	undo_list.clear();
}

b2Body* GetBodyById(int id)
{

	if(id == 0)
		return groundBody;

	for(int b=0; b<(int)lines.size(); ++b)
	{
		if(lines[b]->GetId() == id) return lines[b]->GetBody();
		
	}

	for(int b=0; b<(int)blocks.size(); ++b)
	{
		if(blocks[b]->GetId() == id) return blocks[b]->GetBody();
	}

	for(int b=0; b<(int)balls.size(); ++b)
	{
		if(balls[b]->GetId() == id) return balls[b]->GetBody();
	}

	for(int b=0; b<(int)polyPen.size(); ++b)
	{
		if(polyPen[b]->GetId() == id) return polyPen[b]->GetBody();
	}
	
	return groundBody;
}


bool LoadWorld(const char* world_file)
{
  FILE *fp;
  mxml_node_t *xml;
  mxml_node_t *ppsketch;
  mxml_node_t *world_n;
  mxml_node_t *ball_n;
  mxml_node_t *block_n;
  mxml_node_t *line_n;
  mxml_node_t *pen_n;
  mxml_node_t *vertex_n;
  mxml_node_t *pin_n;
  mxml_node_t *thing_n;
  mxml_node_t *dist_n;
  mxml_node_t *pull_n;
  mxml_node_t *pris_n;

  ClearAll();
  
  int tid;
  
  std::string filename;
  filename = "sd://apps/wiiphysics/";
  filename += world_file;
  
  fp = fopen(filename.c_str(), "r");
  if(fp == NULL) return false;

  xml = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
  fclose(fp);

  ppsketch = mxmlFindElement(xml, xml, "ppsketch", NULL, NULL, MXML_DESCEND); 
  if(ppsketch == NULL) return false;
  
  world_n =  mxmlFindElement(ppsketch, ppsketch, "world", NULL, NULL, MXML_DESCEND); 
  if(world_n == NULL) return false;
  
  //Add balls
  for(ball_n = mxmlFindElement(world_n, world_n, "circle", NULL, NULL, MXML_DESCEND); 
        ball_n != NULL; 
        ball_n = mxmlFindElement(ball_n, world_n, "circle", NULL, NULL, MXML_DESCEND))
  {
     bool fixed_n = false;
	 if(strcmp(mxmlElementGetAttr(ball_n,"type"),"solid")==0)
	 {
	    fixed_n = true;
	 }
  
     tid = atoi(mxmlElementGetAttr(ball_n,"id"));
	 
	 if(tid > m_next_id) m_next_id = tid;
  
     balls.push_back(new Ball(world, atof(mxmlElementGetAttr(ball_n,"x")),
									atof(mxmlElementGetAttr(ball_n,"y")), ballimage, 
									atof(mxmlElementGetAttr(ball_n,"radius")),
									atof(mxmlElementGetAttr(ball_n,"zoom")),
									fixed_n, 
									atof(mxmlElementGetAttr(ball_n,"restitution")), 
									atof(mxmlElementGetAttr(ball_n,"friction")), 
									atof(mxmlElementGetAttr(ball_n,"density")),
									tid));
									
	// balls[balls.size()-1]->SetId(atoi(mxmlElementGetAttr(ball_n,"id")));
  }
  
  //Add blocks
  for(block_n = mxmlFindElement(world_n, world_n, "block", NULL, NULL, MXML_DESCEND); 
        block_n != NULL; 
        block_n = mxmlFindElement(block_n, world_n, "block", NULL, NULL, MXML_DESCEND))
  {
     bool fixed_n = false;
	 if(strcmp(mxmlElementGetAttr(block_n,"type"),"solid")==0)
	 {
	    fixed_n = true;
	 }
  
     tid = atoi(mxmlElementGetAttr(block_n,"id"));
	 
	 if(tid > m_next_id) m_next_id = tid;
	 
     blocks.push_back(new Block(world, atof(mxmlElementGetAttr(block_n,"x")),
									atof(mxmlElementGetAttr(block_n,"y")), 
									atof(mxmlElementGetAttr(block_n,"rotation")), blockimage, 
									atof(mxmlElementGetAttr(block_n,"width")),
									atof(mxmlElementGetAttr(block_n,"height")),
									atof(mxmlElementGetAttr(block_n,"zoom")),
									fixed_n, 
									atof(mxmlElementGetAttr(block_n,"restitution")), 
									atof(mxmlElementGetAttr(block_n,"friction")), 
									atof(mxmlElementGetAttr(block_n,"density")),
									tid));
									
	// blocks[blocks.size()-1]->SetId();
  }
  
  //Add lines
  for(line_n = mxmlFindElement(world_n, world_n, "line", NULL, NULL, MXML_DESCEND); 
        line_n != NULL; 
        line_n = mxmlFindElement(line_n, world_n, "line", NULL, NULL, MXML_DESCEND))
  {
     bool fixed_n = false;
	 if(strcmp(mxmlElementGetAttr(line_n,"type"),"solid")==0)
	 {
	    fixed_n = true;
	 }
  
     tid = atoi(mxmlElementGetAttr(line_n,"id"));
	 
	 if(tid > m_next_id) m_next_id = tid;
	 
	 GXColor t_color;
	 t_color.r = atoi(mxmlElementGetAttr(line_n,"color.r"));
	 t_color.g = atoi(mxmlElementGetAttr(line_n,"color.g"));
	 t_color.b = atoi(mxmlElementGetAttr(line_n,"color.b"));
	 t_color.a = atoi(mxmlElementGetAttr(line_n,"color.a"));
  
     lines.push_back(new Line(world, atof(mxmlElementGetAttr(line_n,"x")),
									atof(mxmlElementGetAttr(line_n,"y")), 
									atof(mxmlElementGetAttr(line_n,"rotation")), 
									t_color,
									atof(mxmlElementGetAttr(line_n,"width")),
									atof(mxmlElementGetAttr(line_n,"height")),
									fixed_n, 
									atof(mxmlElementGetAttr(line_n,"restitution")), 
									atof(mxmlElementGetAttr(line_n,"friction")), 
									atof(mxmlElementGetAttr(line_n,"density")),
									tid));
									
	 //lines[lines.size()-1]->SetId(atoi(mxmlElementGetAttr(line_n,"id")));
  }
  
  //Add pen
  for(pen_n = mxmlFindElement(world_n, world_n, "polygon", NULL, NULL, MXML_DESCEND); 
        pen_n != NULL; 
        pen_n = mxmlFindElement(pen_n, world_n, "polygon", NULL, NULL, MXML_DESCEND))
  {
     bool fixed_n = false;
	 if(strcmp(mxmlElementGetAttr(pen_n,"type"),"solid")==0)
	 {
	    fixed_n = true;
	 }
  
     tid = atoi(mxmlElementGetAttr(pen_n,"id"));
	 
	 if(tid > m_next_id) m_next_id = tid;
	 
	 GXColor t_color;
	 t_color.r = atoi(mxmlElementGetAttr(pen_n,"color.r"));
	 t_color.g = atoi(mxmlElementGetAttr(pen_n,"color.g"));
	 t_color.b = atoi(mxmlElementGetAttr(pen_n,"color.b"));
	 t_color.a = atoi(mxmlElementGetAttr(pen_n,"color.a"));
	 
	 float r = atof(mxmlElementGetAttr(pen_n,"restitution")); 
	 float f = atof(mxmlElementGetAttr(pen_n,"friction")); 
	 float d = atof(mxmlElementGetAttr(pen_n,"density"));
	 
	 bool _closed = true;
	 
	if(strcmp(mxmlElementGetAttr(pen_n,"closed"),"0")==0)
		_closed = false;
  
	 num_points_current_poly = 0;
	 
	  for(vertex_n = mxmlFindElement(pen_n, pen_n, "vertex", NULL, NULL, MXML_DESCEND); 
			vertex_n != NULL; 
			vertex_n = mxmlFindElement(vertex_n, pen_n, "vertex", NULL, NULL, MXML_DESCEND))
	  {
	     polyPoints[num_points_current_poly].x = atof(mxmlElementGetAttr(vertex_n,"x"));
	     polyPoints[num_points_current_poly].y = atof(mxmlElementGetAttr(vertex_n,"y"));
		 num_points_current_poly++;
	  }
	  
      polyPen.push_back(new Pen(world, new b2Polygon(polyPoints, num_points_current_poly),
									t_color,
									fixed_n, 
									r, f, d, _closed,
									tid));
									
	 //polyPen[polyPen.size()-1]->SetId(atoi(mxmlElementGetAttr(pen_n,"id")));
  }
  
  m_next_id++;
  
  num_points_current_poly = 0;
  int id_1, id_2;
  
  //Add pin
  for(pin_n = mxmlFindElement(world_n, world_n, "pin", NULL, NULL, MXML_DESCEND);
        pin_n != NULL; 
        pin_n = mxmlFindElement(pin_n, world_n, "pin", NULL, NULL, MXML_DESCEND))
  {
	 
	 float x = atof(mxmlElementGetAttr(pin_n,"x")); 
	 float y = atof(mxmlElementGetAttr(pin_n,"y")); 

	 thing_n = mxmlFindElement(pin_n, pin_n, "pinned_thing", NULL, NULL, MXML_DESCEND);
	 id_1 = atoi(mxmlElementGetAttr(thing_n,"id"));
	 
	 thing_n = mxmlFindElement(thing_n, pin_n, "pinned_thing", NULL, NULL, MXML_DESCEND);
	 id_2 = atoi(mxmlElementGetAttr(thing_n,"id"));
	 
	 b2Body* b1 = NULL;
	 b2Body* b2 = NULL;
	 
	 b1 = GetBodyById(id_1);
	 b2 = GetBodyById(id_2);
	 
	click_point.x = x;
	click_point.y = y;
	
    revJoints.push_back(new RevoluteJoint(world, b1, b2, click_point, ropeimage));
	n_rev_joints++;
		
  }
  
  //Add dist
  for(dist_n = mxmlFindElement(world_n, world_n, "dist", NULL, NULL, MXML_DESCEND);
      dist_n != NULL; 
      dist_n = mxmlFindElement(dist_n, world_n, "dist", NULL, NULL, MXML_DESCEND))
  {
	 
	 b2Vec2 v1;
	 b2Vec2 v2;
	 bool flex = false;
	 
	 v1.x = atof(mxmlElementGetAttr(dist_n,"v1.x")); 
	 v1.y = atof(mxmlElementGetAttr(dist_n,"v1.y")); 

	 v2.x = atof(mxmlElementGetAttr(dist_n,"v2.x")); 
	 v2.y = atof(mxmlElementGetAttr(dist_n,"v2.y")); 
	 
	 id_1 = atoi(mxmlElementGetAttr(dist_n,"b1_id"));
	 
	 id_2 = atoi(mxmlElementGetAttr(dist_n,"b2_id"));
	 
	 GXColor t_color;
	 t_color.r = atoi(mxmlElementGetAttr(dist_n,"color.r"));
	 t_color.g = atoi(mxmlElementGetAttr(dist_n,"color.g"));
	 t_color.b = atoi(mxmlElementGetAttr(dist_n,"color.b"));
	 t_color.a = atoi(mxmlElementGetAttr(dist_n,"color.a"));
	 
	 if(strcmp(mxmlElementGetAttr(dist_n,"flex"), "true") == 0)
	 {
		flex = true;
	 }
	 
	 b2Body* b1 = NULL;
	 b2Body* b2 = NULL;
	 
	 b1 = GetBodyById(id_1);
	 b2 = GetBodyById(id_2);
	
	distJoints.push_back(new DistanceJoint(world, b1, b2, v1, v2, true, t_color, flex));
	n_dist_joints++;
		
  }
  
  //Add pris
  for(pris_n = mxmlFindElement(world_n, world_n, "pris", NULL, NULL, MXML_DESCEND);
      pris_n != NULL; 
      pris_n = mxmlFindElement(pris_n, world_n, "pris", NULL, NULL, MXML_DESCEND))
  {
	 
	 b2Vec2 v1;
	 b2Vec2 v2;
	 
	 v1.x = atof(mxmlElementGetAttr(pris_n,"v1.x")); 
	 v1.y = atof(mxmlElementGetAttr(pris_n,"v1.y")); 

	 v2.x = atof(mxmlElementGetAttr(pris_n,"v2.x")); 
	 v2.y = atof(mxmlElementGetAttr(pris_n,"v2.y")); 
	 
	 id_1 = atoi(mxmlElementGetAttr(pris_n,"b1_id"));
	 
	 id_2 = atoi(mxmlElementGetAttr(pris_n,"b2_id"));
	 
	 
	 float t_upper = atof(mxmlElementGetAttr(pris_n,"upper")); 
	 float t_lower = atof(mxmlElementGetAttr(pris_n,"lower")); 
	 
	 b2Body* b1 = NULL;
	 b2Body* b2 = NULL;
	 
	 b1 = GetBodyById(id_1);
	 b2 = GetBodyById(id_2);
	
	prisJoints.push_back(new PrismaticJoint(world, b1, b2, v1, v2, ropeimage, t_upper, t_lower));
	n_pris_joints++;
		
  }
  
  //Add pull
  for(pull_n = mxmlFindElement(world_n, world_n, "pull", NULL, NULL, MXML_DESCEND);
      pull_n != NULL; 
      pull_n = mxmlFindElement(pull_n, world_n, "pull", NULL, NULL, MXML_DESCEND))
  {
	 
	 b2Vec2 v1;
	 
	 v1.x = atof(mxmlElementGetAttr(pull_n,"b2.x")); 
	 v1.y = atof(mxmlElementGetAttr(pull_n,"b2.y")); 
	 
	 id_1 = atoi(mxmlElementGetAttr(pull_n,"b1_id"));
	 
	 id_2 = atoi(mxmlElementGetAttr(pull_n,"b2_id"));
	 
	 GXColor t_color;
	 t_color.r = atoi(mxmlElementGetAttr(pull_n,"color.r"));
	 t_color.g = atoi(mxmlElementGetAttr(pull_n,"color.g"));
	 t_color.b = atoi(mxmlElementGetAttr(pull_n,"color.b"));
	 t_color.a = atoi(mxmlElementGetAttr(pull_n,"color.a"));
	 
	 float t_width = atof(mxmlElementGetAttr(pull_n,"width")); 
	 
	 b2Body* b1 = NULL;
	 b2Body* b2 = NULL;
	 
	 b1 = GetBodyById(id_1);
	 b2 = GetBodyById(id_2);
	
	pulJoints.push_back(new PulleyJoint(world, b1, v1, b2, t_width, t_color));
	n_pul_joints++;
		
  }
  
  
  //TODO Delete memory to clean up leak
  //mxmlDelete(xml);
  
  return true;
}

void SaveWorld(char* save_file)
{
    mxml_node_t *xml;
	mxml_node_t *ppsketch;
	mxml_node_t *node;
	mxml_node_t *world;
	
	xml = mxmlNewXML("1.0");
	
	ppsketch = mxmlNewElement(xml, "ppsketch");
	
	node = mxmlNewElement(ppsketch, "creator");
    mxmlNewText(node, 0, "WiiPhysics 2.x");
	
	node = mxmlNewElement(ppsketch, "author");
    mxmlNewText(node, 0, "beardface");
	
	world = mxmlNewElement(ppsketch, "world");
	
	mxmlElementSetAttr(world, "gravity_x", "0.0");
	mxmlElementSetAttr(world, "gravity_y", "10.0");
	
	int next_id = 1;
	//Save Shapes
	for(int b=0; b<(int)balls.size(); ++b)
	{
		balls[b]->Save(&world, next_id);
		next_id++;
	}
	
	for(int b=0; b<(int)blocks.size(); ++b)
	{
		blocks[b]->Save(&world, next_id);
		next_id++;
	}
	
	for(int b=0; b<(int)lines.size(); ++b)
	{
		lines[b]->Save(&world, next_id);
		next_id++;
	}
	
	for(int b=0; b<(int)polyPen.size(); ++b)
	{
		polyPen[b]->Save(&world, next_id);
		next_id++;
	}
	
	for(int b=0; b<(int)revJoints.size(); ++b)
	{
		revJoints[b]->Save(&world);
	}
	
	for(int b=0; b<(int)distJoints.size(); ++b)
	{
		distJoints[b]->Save(&world);
	}
	
	for(int b=0; b<(int)prisJoints.size(); ++b)
	{
		prisJoints[b]->Save(&world);
	}
	
	for(int b=0; b<(int)pulJoints.size(); ++b)
	{
		pulJoints[b]->Save(&world);
	}
	FILE *fp;
	
    std::string filename;
    filename = "sd://apps/wiiphysics/";
    filename += save_file;
	fp = fopen(filename.c_str(), "w");
	mxmlSaveFile(xml, fp, whitespace_cb);
	fclose(fp);
	
}

void RunWiiPhysics()
{

	WPAD_ScanPads();
	
	u16 btnsdown = WPAD_ButtonsDown(0);
	u16 btnsheld = WPAD_ButtonsHeld(0);

	// Infrared calculation
	ir_t ir; // The struct for infrared
	gforce_t gforce;
	
	WPAD_IR(WPAD_CHAN_0, &ir); // Let's get our infrared data
	WPAD_GForce(WPAD_CHAN_0, &gforce);
	wd = WPAD_Data(WPAD_CHAN_0);

	pointersprite.SetPosition(ir.sx-200, ir.sy-250);
	pointersprite.SetRotation(ir.angle/2); // Set angle/2 to translate correctly
	
	// Infrared calculation
	ir_t p2ir; // The struct for infrared
	u16 p2btnsdown = WPAD_ButtonsDown(1);
	u16 p2btnsheld = WPAD_ButtonsHeld(1);
	
	WPAD_IR(WPAD_CHAN_1, &p2ir); // Let's get our infrared data
	
	p2pointersprite.SetPosition(p2ir.sx-200, p2ir.sy-250);
	p2pointersprite.SetRotation(p2ir.angle/2); // Set angle/2 to translate correctly
	
	cur_x = ir.sx-200;
	cur_y = ir.sy-250;
	
	if(btnsheld & WPAD_BUTTON_PLUS)
	{
		zoom += 0.01;
	}
	
	if(btnsheld & WPAD_BUTTON_MINUS)
	{
		if(zoom > 0.2)
		{
			zoom -= 0.01;
		}
	}
	
	hide_menu = !(toolbox->GetMenuState());
	
	if(hide_menu && drift_dist < DRIFT_DISTANCE)
	{
		drift_dist+=20;
	}
	else if(!hide_menu && drift_dist > 0)
	{
		drift_dist-=20;
	}
	
	
	if(btnsdown & WPAD_BUTTON_HOME)
	{
		main_menu->SetDisplayed(true);
	}
		
		
	
	if(!camera_set || cameraBod == NULL)
	{
		if(btnsheld & WPAD_BUTTON_UP)
		{
			if(screen_y_offset < (MAX_SLIDE_Y - 5))
				screen_y_offset+=5;
		}
		
		if(btnsheld & WPAD_BUTTON_DOWN)
		{
			if(screen_y_offset > (MIN_SLIDE_Y + 5.0))
				screen_y_offset-=5;
		}
		
		if(btnsheld & WPAD_BUTTON_RIGHT)
		{
			if(screen_x_offset > (MIN_SLIDE_X + 5))
				screen_x_offset-=5;
		}
		
		if(btnsheld & WPAD_BUTTON_LEFT)
		{
			if(screen_x_offset < (MAX_SLIDE_X - 5))
				screen_x_offset+=5;
		}
		
		if(((btnsheld & WPAD_BUTTON_B) && ir.sy-250 <= SCROLL_EDGE_DIST))
		{
			float dist = (SCROLL_EDGE_DIST - (ir.sy-250));
			
			if(dist > SCROLL_EDGE_DIST)
				dist = SCROLL_EDGE_DIST;
		
			if(screen_y_offset < (MAX_SLIDE_Y - dist))
				screen_y_offset+=dist;
		}
		
		if(((btnsheld & WPAD_BUTTON_B) && ir.sy-250 >= 480 - SCROLL_EDGE_DIST))
		{
			float dist = -1*(480 - SCROLL_EDGE_DIST -(ir.sy-250));
			
			if(dist > SCROLL_EDGE_DIST)
				dist = SCROLL_EDGE_DIST;
				
			if(screen_y_offset > (MIN_SLIDE_Y + dist))
				screen_y_offset-=dist;
		}
		
		if(((btnsheld & WPAD_BUTTON_B) && ir.sx-200 >= 640 - SCROLL_EDGE_DIST))
		{
			float dist = -1*(640 - SCROLL_EDGE_DIST -(ir.sx-200));
			
			if(dist > SCROLL_EDGE_DIST)
				dist = SCROLL_EDGE_DIST;
				
			if(screen_x_offset > (MIN_SLIDE_X + dist))
				screen_x_offset-=dist;
		}
		
		if(((btnsheld & WPAD_BUTTON_B) && ir.sx-200 <= SCROLL_EDGE_DIST))
		{
				
			float dist = (SCROLL_EDGE_DIST - (ir.sx-200));
			
			if(dist > SCROLL_EDGE_DIST)
				dist = SCROLL_EDGE_DIST;
				
			if(screen_x_offset < (MAX_SLIDE_X - dist))
				screen_x_offset+=dist;
		}
	}
	else
	{
		if(cameraBod != NULL)
		{
			b2Vec2 v = cameraBod->GetPosition();
		
			screen_x_offset = -1*v.x*PIXELS_PER_UNIT + 320.0;
			
			if(screen_x_offset > MAX_SLIDE_X)
				screen_x_offset = MAX_SLIDE_X;
			else if(screen_x_offset < MIN_SLIDE_X)
				screen_x_offset = MIN_SLIDE_X;
			
			screen_y_offset = -1*v.y*PIXELS_PER_UNIT + 240.0;
			
			if(screen_y_offset > MAX_SLIDE_Y)
				screen_y_offset = MAX_SLIDE_Y;
			else if(screen_y_offset < MIN_SLIDE_Y)
				screen_y_offset = MIN_SLIDE_Y;
				
		}
	}
	//------------------------------------------------
	
	
	if((btnsheld & WPAD_BUTTON_A) && (btnsdown & WPAD_BUTTON_B))
	{
		if(mouseBod != NULL && toolbox->GetToolMode() == ToolMode::SELECT)
		{
			bool can_freeze = true;
			
			for(int b=0; b<n_pul_joints; ++b)
			{
				if(pulJoints[b]->GetBody1() == mouseBod ||
				   pulJoints[b]->GetBody2() == mouseBod)
				{
					can_freeze = false;
				}
			}
			
			if(can_freeze)
			{
				if(mouseBod->GetMass() == 0.0)
				{
					mouseBod->SetMassFromShapes();
					if(mouseBod->GetUserData() != NULL)
						((GenericShape*)(mouseBod->GetUserData()))->SetFixed(false);
				}
				else
				{
					b2MassData massdata;
					massdata.mass = 0.0;
					
					if(mouseJoint != NULL)
					{
						world->DestroyJoint(mouseJoint);
						mouseJoint = NULL;
					}
					
					b2Vec2 v(0,0);
						
					mouseBod->SetMass(&massdata);
					mouseBod->SetAngularVelocity(0.0);
					mouseBod->SetLinearVelocity(v);
					mouseBod->SetMass(&massdata);
					if(mouseBod->GetUserData() != NULL)
						((GenericShape*)(mouseBod->GetUserData()))->SetFixed(true);
				}
			}
	
		}
	}
	
	/* Player 2 handlers */
	p2pointersprite.SetImage(p2openimage);
				
	if(p2btnsdown & WPAD_BUTTON_A)
	{
		p2mouseBod = GetSelectedBody(&p2pointersprite, &p2SelectedType, &p2SelectedPointer);
		
		p2_init_x = p2ir.sx-screen_x_offset-200;
		p2_init_y = p2ir.sy-screen_y_offset-250;
		
		p2_init_a = p2ir.angle/2;
		
		if(p2mouseBod != NULL)
		{
			if(p2mouseBod->GetMass() > 0.0)
			{
				p2mouseJointDef.body2 = p2mouseBod;
				p2mouseJointDef.body1 = groundBody;
				p2mouseJointDef.target.Set((p2ir.sx-screen_x_offset-200)/PIXELS_PER_UNIT, (p2ir.sy-screen_y_offset-250)/PIXELS_PER_UNIT);
				p2mouseJointDef.maxForce = 1000; //*mouseBod->GetMass();
				//mouseJointDef.timeStep = timeStep;
				
				if(p2mouseJoint != NULL)
				{
					world->DestroyJoint(p2mouseJoint);
					p2mouseJoint = NULL;
				}
				
				p2mouseJoint = (b2MouseJoint*)world->CreateJoint(&p2mouseJointDef);
			}
			
			b2Vec2 v = p2mouseBod->GetPosition();
			
			p2_init_pos_x = v.x;
			p2_init_pos_y = v.y;
			p2_init_pos_a = p2mouseBod->GetAngle();
		}
	}
		
	if((p2btnsheld & WPAD_BUTTON_A) && (p2btnsdown & WPAD_BUTTON_B))
	{
		if(p2mouseBod != NULL)
		{
			bool can_freeze = true;
			
			for(int b=0; b<n_pul_joints; ++b)
			{
				if(pulJoints[b]->GetBody1() == p2mouseBod ||
				   pulJoints[b]->GetBody2() == p2mouseBod)
				{
					can_freeze = false;
				}
			}
			
			if(can_freeze)
			{
				if(p2mouseBod->GetMass() == 0.0)
				{
					p2mouseBod->SetMassFromShapes();
					if(p2mouseBod->GetUserData() != NULL)
						((GenericShape*)(p2mouseBod->GetUserData()))->SetFixed(false);
				}
				else
				{
					b2MassData massdata;
					massdata.mass = 0.0;
					
					if(p2mouseJoint != NULL)
					{
						world->DestroyJoint(p2mouseJoint);
						p2mouseJoint = NULL;
					}
					
					b2Vec2 v(0,0);
						
					p2mouseBod->SetMass(&massdata);
					p2mouseBod->SetAngularVelocity(0.0);
					p2mouseBod->SetLinearVelocity(v);
					p2mouseBod->SetMass(&massdata);
					if(p2mouseBod->GetUserData() != NULL)
						((GenericShape*)(p2mouseBod->GetUserData()))->SetFixed(true);
				}
			}
		}
	}
	
	if(p2btnsheld & WPAD_BUTTON_A)
	{
		if(p2mouseBod != NULL)
		{
			
			if(p2SelectedPointer != NULL)
			{
				p2pointersprite.SetImage(p2grabimage);
				
				//Moving Static shapes
				if(p2mouseBod->GetMass() == 0.0  || toolbox->GetPlayMode() == PlayMode::STOP)
				{
					float tx = (p2ir.sx-screen_x_offset-200)-p2_init_x;
					float ty = (p2ir.sy-screen_y_offset-250)-p2_init_y;
					float rtx = (tx) + p2_init_pos_x*PIXELS_PER_UNIT;
					float rty = (ty) + p2_init_pos_y*PIXELS_PER_UNIT;
					b2Vec2 v((tx)/ PIXELS_PER_UNIT + p2_init_pos_x, (ty)/PIXELS_PER_UNIT + p2_init_pos_y);
					float angle = (p2ir.angle/2- p2_init_a) * ( M_PI / 180.0) + p2_init_pos_a;
					
					b2Vec2 veloc( 0.0, 0.0); ///(wd->accel.x),(wd->accel.y));
					
					switch(p2SelectedType)
					{
						case BLOCK:
							{
								p2mouseBod->SetXForm(v, angle);
								
								//Set Velocity
								p2mouseBod->SetLinearVelocity(veloc);	
							}
							((Block*)p2SelectedPointer)->UpdateXform(rtx, rty, angle);
							break;
						case BALL:
							{
								p2mouseBod->SetXForm(v, angle);
								
								//Set Velocity
								p2mouseBod->SetLinearVelocity(veloc);	
							}
							((Ball*)p2SelectedPointer)->UpdateXform(rtx, rty, angle);
							break;
						case LINE:
							{
								p2mouseBod->SetXForm(v, angle);
								
								//Set Velocity
								p2mouseBod->SetLinearVelocity(veloc);	
							}
							((Line*)p2SelectedPointer)->UpdateXform(rtx, rty, angle);
							break;
						case POLYPEN:
							((Pen*)p2SelectedPointer)->UpdateXform(rtx, rty, angle);
							((Pen*)p2SelectedPointer)->Reset();
							break;
						default:
							break;
					}
				}
				else
				{
					if(p2mouseJoint != NULL)
					{
						b2Vec2 mouse_v((p2ir.sx-screen_x_offset-200)/ PIXELS_PER_UNIT, (p2ir.sy-screen_y_offset-250)/PIXELS_PER_UNIT);
						p2mouseJoint->SetTarget(mouse_v);	
					}
					else
					{
						//better create the mouseJoint!
						p2mouseJointDef.body2 = p2mouseBod;
						p2mouseJointDef.body1 = groundBody;
						p2mouseJointDef.target.Set((p2ir.sx-screen_x_offset-200)/PIXELS_PER_UNIT, (p2ir.sy-screen_y_offset-250)/PIXELS_PER_UNIT);
						p2mouseJointDef.maxForce = 1000; //*mouseBod->GetMass();
						//mouseJointDef.timeStep = timeStep;
						
						p2mouseJoint = (b2MouseJoint*)world->CreateJoint(&p2mouseJointDef);
					}
				}
			}
		}
	}
	else
	{
		//A was released
		if(p2mouseJoint != NULL)
		{
			world->DestroyJoint(p2mouseJoint);
			p2mouseJoint = NULL;
		}

		p2mouseBod = NULL;
	}
	/* End player 2 */
	
	// The A button spawns a ball
	if(btnsdown & WPAD_BUTTON_A)
	{
		if(!(toolbox->PressButton(ir.sx-200, ir.sy-250)))
		{
			switch(toolbox->GetToolMode())
			{
				case ToolMode::SELECT:
					//TODO Select block or balls
					mouseBod = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
					if(mouseBod != NULL)
					{
						if(mouseBod->GetMass() > 0.0)
						{
							mouseJointDef.body2 = mouseBod;
							mouseJointDef.body1 = groundBody;
							mouseJointDef.target.Set((ir.sx-screen_x_offset-200)/PIXELS_PER_UNIT, (ir.sy-screen_y_offset-250)/PIXELS_PER_UNIT);
							mouseJointDef.maxForce = 1000; //*mouseBod->GetMass();
							//mouseJointDef.timeStep = timeStep;
							
							if(mouseJoint != NULL)
							{
								world->DestroyJoint(mouseJoint);
								mouseJoint = NULL;
							}
							
							mouseJoint = (b2MouseJoint*)world->CreateJoint(&mouseJointDef);
						}
					}
					
					m_init_x = ir.sx-screen_x_offset-200;
					m_init_y = ir.sy-screen_y_offset-250;
					
					m_init_a = ir.angle/2;
					
					if(mouseBod != NULL)
					{
						b2Vec2 v = mouseBod->GetPosition();
					
						m_init_pos_x = v.x;
						m_init_pos_y = v.y;
						m_init_pos_a = mouseBod->GetAngle();
					}
					
					break;
				case ToolMode::DELETE:
					RemoveObject(GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer));
					break;
				case ToolMode::SET_CAMERA:
					cameraBod = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
					
					if(cameraBod != NULL)
					{
						camera_set = true;
					}
					else
					{
						camera_set = false;
					}
					toolbox->SetToolMode(ToolMode::SELECT);
					break;
				case ToolMode::DRAW_BOX:
					if((int)blocks.size() < MAX_BLOCKS - 1)
					{
						if(settings->IsSoundEnabled())
						{
						//	PlayOgg(mem_open((char*)drawOgg, drawOgg_size), 0, OGG_ONE_TIME);
						}
						switch(toolbox->GetMotionMode())
						{
							case MotionMode::FREEZE:
								blocks.push_back(new Block(world, ir.sx-screen_x_offset-200, ir.sy-screen_y_offset-250, ir.angle/2, blockimage, blockimage->GetWidth(), blockimage->GetHeight(),zoom,true, settings->GetRestitution(), settings->GetFriction(), settings->GetDensity(),m_next_id));
								break;
							case MotionMode::MOBILE:
								blocks.push_back(new Block(world, ir.sx-screen_x_offset-200, ir.sy-screen_y_offset-250, ir.angle/2, blockimage, blockimage->GetWidth(), blockimage->GetHeight(),zoom,false, settings->GetRestitution(), settings->GetFriction(), settings->GetDensity(),m_next_id));
								break;
							default:
								break;
						}
						m_next_id++;
						undo_list.push_back(BLOCK);
						n_blocks++;
					}
					break;
				case ToolMode::DRAW_PEN:
					if((int)polyPen.size() < MAX_POLYPENS - 1)
					{
						if(!drawing_poly)
						{
							drawing_poly = true;
							b2Vec2 tv(ir.sx-screen_x_offset-200, ir.sy-screen_y_offset-250);
							polyPoints[num_points_current_poly] = tv;
							num_points_current_poly=1;
						}
					}
					break;
				case ToolMode::DRAW_LINE:
					if((int)lines.size() < MAX_LINES - 1)
					{
						if(!drawingBox)
						{
							drawingBox = true;
							boxRect.x = ir.sx-200;
							boxRect.y = ir.sy-250;
							boxRect.width = 1;
							boxRect.height = 1;
							boxQuad.SetWidth(boxRect.width);
							boxQuad.SetHeight(boxRect.height);
							boxQuad.SetRotation(0);//(ir.angle/2));
							if(boxRect.x<0) boxRect.x=0;
							if(boxRect.y<0) boxRect.y=0;
							boxQuad.SetFillColor(settings->GetColor());
							boxQuad.SetWidth(20);
							boxQuad.SetHeight(20);
							boxQuad.SetPosition(boxRect.x,boxRect.y);
							sx=boxRect.x;
							sy=boxRect.y;
						}
					}
					break;
				case ToolMode::DRAW_CIRCLE:
					if((int)balls.size() < MAX_BALLS - 1)
					{
						if(settings->IsSoundEnabled())
						{
						//	PlayOgg(mem_open((char*)drawOgg, drawOgg_size), 0, OGG_ONE_TIME);
						}
						switch(toolbox->GetMotionMode())
						{
							case MotionMode::FREEZE:
								balls.push_back(new Ball(world, ir.sx-screen_x_offset-200, ir.sy-screen_y_offset-250, ballimage, ballimage->GetWidth()/2,zoom,true, settings->GetRestitution(), settings->GetFriction(), settings->GetDensity(),m_next_id));
								break;
							case MotionMode::MOBILE:
								balls.push_back(new Ball(world, ir.sx-screen_x_offset-200, ir.sy-screen_y_offset-250, ballimage, ballimage->GetWidth()/2,zoom,false, settings->GetRestitution(), settings->GetFriction(), settings->GetDensity(),m_next_id));
								break;
							default:
								break;
						}
						m_next_id++;
						undo_list.push_back(BALL);
						n_balls++;
					}
					break;
				case ToolMode::CREATE_JOINT:
					switch(toolbox->GetJointMode())
					{
						case Joint::PULLEY_JOINT:
							if(selBod1 == NULL)
							{
								selBod1 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
							}
							else if(selBod2 == NULL)
							{
								selBod2 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
							}
							else
							{
								selBod3 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
								AddJoint(Joint::PULLEY_JOINT, selBod1, selBod2, selBod3);
								undo_list.push_back(PUL_JOINT);
								selBod1 = NULL;
								selBod2 = NULL;
								selBod3 = NULL;
							}
							break;
						case Joint::DISTANCE_JOINT:
							if(selBod1 == NULL)
							{
								selBod1 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
								click_point.x = (ir.sx-screen_x_offset-200)/ PIXELS_PER_UNIT;
								click_point.y = (ir.sy-screen_y_offset-250)/ PIXELS_PER_UNIT;
							}
							else
							{
								click_point_2.x = (ir.sx-screen_x_offset-200)/ PIXELS_PER_UNIT;
								click_point_2.y = (ir.sy-screen_y_offset-250)/ PIXELS_PER_UNIT;
								selBod2 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
								AddJoint(Joint::DISTANCE_JOINT, selBod1, selBod2, NULL);
								undo_list.push_back(DIST_JOINT);
								selBod1 = NULL;
								selBod2 = NULL;
								selBod3 = NULL;
							}
							break;
						case Joint::RUBBER_JOINT:
							if(selBod1 == NULL)
							{
								selBod1 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
								click_point.x = (ir.sx-screen_x_offset-200)/ PIXELS_PER_UNIT;
								click_point.y = (ir.sy-screen_y_offset-250)/ PIXELS_PER_UNIT;
							}
							else
							{
								click_point_2.x = (ir.sx-screen_x_offset-200)/ PIXELS_PER_UNIT;
								click_point_2.y = (ir.sy-screen_y_offset-250)/ PIXELS_PER_UNIT;
								selBod2 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
								AddJoint(Joint::RUBBER_JOINT, selBod1, selBod2, NULL);
								undo_list.push_back(DIST_JOINT);
								selBod1 = NULL;
								selBod2 = NULL;
								selBod3 = NULL;
							}
							break;
						case Joint::REVOLUTE_JOINT:
							selBod1 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
							selBod2 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
							click_point.x = (ir.sx-screen_x_offset-200-25)/ PIXELS_PER_UNIT;
							click_point.y = (ir.sy-screen_y_offset-250-20)/ PIXELS_PER_UNIT;
							AddJoint(Joint::REVOLUTE_JOINT, selBod1, selBod2, NULL);
							undo_list.push_back(REV_JOINT);
							selBod1 = NULL;
							selBod2 = NULL;
							selBod3 = NULL;
							break;
						case Joint::PRISMATIC_JOINT:
							if(selBod1 == NULL)
							{
								selBod1 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
								click_point.x = (ir.sx-screen_x_offset-200)/ PIXELS_PER_UNIT;
								click_point.y = (ir.sy-screen_y_offset-250)/ PIXELS_PER_UNIT;
							}
							else
							{
								click_point_2.x = (ir.sx-screen_x_offset-200)/ PIXELS_PER_UNIT;
								click_point_2.y = (ir.sy-screen_y_offset-250)/ PIXELS_PER_UNIT;
								selBod2 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
								AddJoint(Joint::PRISMATIC_JOINT, selBod1, selBod2, NULL);
								undo_list.push_back(PRIS_JOINT);
								selBod1 = NULL;
								selBod2 = NULL;
								selBod3 = NULL;
							}
							break;
						case Joint::WELD_JOINT:
							if(selBod1 == NULL)
							{
								selBod1 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
								click_point.x = (ir.sx-screen_x_offset-200)/ PIXELS_PER_UNIT;
								click_point.y = (ir.sy-screen_y_offset-250)/ PIXELS_PER_UNIT;
							}
							else
							{
								click_point_2.x = (ir.sx-screen_x_offset-200)/ PIXELS_PER_UNIT;
								click_point_2.y = (ir.sy-screen_y_offset-250)/ PIXELS_PER_UNIT;
								selBod2 = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
								AddJoint(Joint::WELD_JOINT, selBod1, selBod2, NULL);
								undo_list.push_back(PRIS_JOINT);
								selBod1 = NULL;
								selBod2 = NULL;
								selBod3 = NULL;
							}
							break;
						default:
							break;
					}
					break;
							
				default:
					break;
			}
			
		}
		else
		{
			//if(settings->IsSoundEnabled())
			//{
			//	PlayOgg(mem_open((char*)clickOgg, clickOgg_size), 0, OGG_ONE_TIME);
			//}
			
			//Handle Single Click Actions
			switch(toolbox->GetToolMode())
			{
				case ToolMode::CLEAR_SCREEN:
					if(settings->IsSoundEnabled())
					{
						//PlayOgg(mem_open((char*)clearOgg, clearOgg_size), 0, OGG_ONE_TIME);
					}
					ClearAll();
					toolbox->ResetSinglePressButtons();
					break;
				case ToolMode::UNDO:
					if(settings->IsSoundEnabled())
					{
						//PlayOgg(mem_open((char*)hoverOgg, hoverOgg_size), 0, OGG_ONE_TIME);
					}
					Undo();
					toolbox->ResetSinglePressButtons();
					break;
				default:
					break;
			}
			
			switch(toolbox->GetSettingsMode())
			{
				case Menu::SHOW:
					settings->SetDisplayed(true);
					toolbox->ResetSinglePressButtons();
				default:
					break;
			}
			
			switch(toolbox->GetSaveMode())
			{
				case Menu::SHOW:
					_saveDisplayed = true;
					toolbox->ResetSinglePressButtons();
				default:
					break;
			}
			
			switch(toolbox->GetLoadMode())
			{
				case Menu::SHOW:
					_loadDisplayed = true;
					toolbox->ResetSinglePressButtons();
				default:
					break;
			}
			
			switch(toolbox->GetResetMode())
			{
				case Menu::SHOW:
					ResetShapes();
					toolbox->ResetSinglePressButtons();
				default:
					break;
			}
		}

	}
	
	
	
	if(btnsheld & WPAD_BUTTON_A)
	{
		if(mouseBod != NULL && toolbox->GetToolMode() == ToolMode::SELECT)
		{
			
			if(SelectedPointer != NULL)
			{
				pointersprite.SetImage(grabimage);
				
				//Moving Static shapes
				if(mouseBod->GetMass() == 0.0  || toolbox->GetPlayMode() == PlayMode::STOP)
				{
					float tx = (ir.sx-screen_x_offset-200)-m_init_x;
					float ty = (ir.sy-screen_y_offset-250)-m_init_y;
					float rtx = (tx) + m_init_pos_x*PIXELS_PER_UNIT;
					float rty = (ty) + m_init_pos_y*PIXELS_PER_UNIT;
					b2Vec2 v((tx)/ PIXELS_PER_UNIT + m_init_pos_x, (ty)/PIXELS_PER_UNIT + m_init_pos_y);
					float angle = (ir.angle/2- m_init_a) * ( M_PI / 180.0) + m_init_pos_a;
					
					b2Vec2 veloc( 0.0, 0.0); ///(wd->accel.x),(wd->accel.y));
					
					switch(SelectedType)
					{
						case BLOCK:
							{
								mouseBod->SetXForm(v, angle);
								
								//Set Velocity
								mouseBod->SetLinearVelocity(veloc);	
							}
							((Block*)SelectedPointer)->UpdateXform(rtx, rty, angle);
							break;
						case BALL:
							{
								mouseBod->SetXForm(v, angle);
								
								//Set Velocity
								mouseBod->SetLinearVelocity(veloc);	
							}
							((Ball*)SelectedPointer)->UpdateXform(rtx, rty, angle);
							break;
						case LINE:
							{
								mouseBod->SetXForm(v, angle);
								
								//Set Velocity
								mouseBod->SetLinearVelocity(veloc);	
							}
							((Line*)SelectedPointer)->UpdateXform(rtx, rty, angle);
							break;
						case POLYPEN:
							((Pen*)SelectedPointer)->UpdateXform(rtx, rty, angle);
							((Pen*)SelectedPointer)->Reset();
							break;
						default:
							break;
					}
				}
				else
				{
					if(mouseJoint != NULL)
					{
						b2Vec2 mouse_v((ir.sx-screen_x_offset-200)/ PIXELS_PER_UNIT, (ir.sy-screen_y_offset-250)/PIXELS_PER_UNIT);
						mouseJoint->SetTarget(mouse_v);	
					}
					else
					{
						//better create the mouseJoint!
						mouseJointDef.body2 = mouseBod;
						mouseJointDef.body1 = groundBody;
						mouseJointDef.target.Set((ir.sx-screen_x_offset-200)/PIXELS_PER_UNIT, (ir.sy-screen_y_offset-250)/PIXELS_PER_UNIT);
						mouseJointDef.maxForce = 1000; //*mouseBod->GetMass();
						//mouseJointDef.timeStep = timeStep;
						
						mouseJoint = (b2MouseJoint*)world->CreateJoint(&mouseJointDef);
					}
				}
			}
		}
		else if(drawing_poly)
		{
			if(num_points_current_poly < MAX_POLY_POINTS-2)
			{
				//Check to see if point passes threshhold for addition to list
				if(abs(polyPoints[num_points_current_poly-1].x - (ir.sx-screen_x_offset-200)) > 20 ||
					abs(polyPoints[num_points_current_poly-1].y - (ir.sy-screen_y_offset-250)) > 20)
				{
					b2Vec2 tv(ir.sx-screen_x_offset-200, ir.sy-screen_y_offset-250);
					polyPoints[num_points_current_poly] = tv;
					num_points_current_poly++;
				}
			}
		}
		else if(drawingBox)
		{
			resizeBox(ir.sx-200,ir.sy-250);
		}
	}
	else
	{
		//A was released
		if(drawingBox)
		{
			
			switch(toolbox->GetMotionMode())
			{
				case MotionMode::FREEZE:
					if(boxRect.width > 0 && boxRect.height > 0)
					{
						if(settings->IsSoundEnabled())
						{
							//PlayOgg(mem_open((char*)drawOgg, drawOgg_size), 0, OGG_ONE_TIME);
						}
						lines.push_back(new Line(world, boxQuad.GetX()-screen_x_offset-25, boxQuad.GetY()-screen_y_offset-20, boxQuad.GetRotation(), settings->GetColor(), boxQuad.GetWidth(), boxQuad.GetHeight(),true, settings->GetRestitution(), settings->GetFriction(), settings->GetDensity(),m_next_id));
						undo_list.push_back(LINE);
						n_lines++;
					}
					break;
				case MotionMode::MOBILE:
					if(boxRect.width > 0 && boxRect.height > 0)
					{
						if(settings->IsSoundEnabled())
						{
							//PlayOgg(mem_open((char*)drawOgg, drawOgg_size), 0, OGG_ONE_TIME);
						}
						lines.push_back(new Line(world, boxQuad.GetX()-screen_x_offset-25, boxQuad.GetY()-screen_y_offset-20, boxQuad.GetRotation(), settings->GetColor(), boxQuad.GetWidth(), boxQuad.GetHeight(),false, settings->GetRestitution(), settings->GetFriction(), settings->GetDensity(),m_next_id));
						undo_list.push_back(LINE);
						n_lines++;
					}
					break;
				default:
					break;
			}
			m_next_id++;
			
			drawingBox = false;
		}
		else if(drawing_poly)
		{
			b2Vec2 tv(ir.sx-screen_x_offset-200, ir.sy-screen_y_offset-250);
			polyPoints[num_points_current_poly] = tv;
			num_points_current_poly++;
			
			for(int i = 0; i < num_points_current_poly; i++)
			{
				polyPoints[i].x -= 25;
				polyPoints[i].y -= 20;
			}
			
			drawing_poly = false;
			bool closed = true;
			
			
			switch(toolbox->GetPenMode())
			{
				case PenMode::OPEN:
					closed = false;
					break;
				case PenMode::CLOSED:
					closed = true;
					break;
				default:
					break;
			}
			
			switch(toolbox->GetMotionMode())
			{
				case MotionMode::FREEZE:
					polyPen.push_back(new Pen(world, new b2Polygon(polyPoints, num_points_current_poly), settings->GetColor(), true, settings->GetRestitution(), settings->GetFriction(), settings->GetDensity(),closed, m_next_id));
					n_polypen++;
					break;
				case MotionMode::MOBILE:
					polyPen.push_back(new Pen(world, new b2Polygon(polyPoints, num_points_current_poly), settings->GetColor(), false, settings->GetRestitution(), settings->GetFriction(), settings->GetDensity(),closed, m_next_id));
					n_polypen++;
					break;
				default:
					break;
			}
			m_next_id++;
			undo_list.push_back(POLYPEN);
			num_points_current_poly = 0;
		}
		
		if(mouseJoint != NULL)
		{
			world->DestroyJoint(mouseJoint);
			mouseJoint = NULL;
		}

		mouseBod = NULL;
		
	}
	
	//Set Pointer
	if(toolbox->HoverButton(ir.sx-200, ir.sy-250))
	{
		if(toolbox->IsFirstHover())
		{
			//if(settings->IsSoundEnabled())
			//{
			//	PlayOgg(mem_open((char*)hoverOgg, hoverOgg_size), 0, OGG_ONE_TIME);
			//}
		}
		pointersprite.SetRotation(0);
		pointersprite.SetImage(selectimage);
		pointersprite.SetZoom(1);
	}
	else
	{
		switch(toolbox->GetToolMode())
		{
			case ToolMode::DRAW_BOX:
				pointersprite.SetImage(blockimage);
				pointersprite.SetZoom(zoom);
				break;
			case ToolMode::DRAW_CIRCLE:
				pointersprite.SetImage(ballimage);
				pointersprite.SetZoom(zoom);
				break;
			case ToolMode::DRAW_LINE:
				pointersprite.SetImage(penimage);
				pointersprite.SetZoom(1);
				break;
			case ToolMode::DRAW_PEN:
				pointersprite.SetImage(penCursorImage);
				pointersprite.SetZoom(1);
				break;
			case ToolMode::CREATE_JOINT:
				switch(toolbox->GetJointMode())
				{
					case Joint::REVOLUTE_JOINT:				
						pointersprite.SetImage(revpointerimage);
						pointersprite.SetZoom(1);
						break;
					case Joint::WELD_JOINT:				
						pointersprite.SetImage(weldpointerimage);
						pointersprite.SetZoom(1);
						break;
					case Joint::RUBBER_JOINT:				
						pointersprite.SetImage(jointpointerimage);
						pointersprite.SetZoom(1);
						break;
					default:
						pointersprite.SetImage(jointpointerimage);
						pointersprite.SetZoom(1);
						break;
				}
				break;
			case ToolMode::DELETE:
				pointersprite.SetImage(deletepointerimage);
				pointersprite.SetZoom(1);
				break;
			case ToolMode::SET_CAMERA:
				pointersprite.SetImage(camerapointerimage);
				pointersprite.SetZoom(1);
				break;
			default:
				if(mouseBod != NULL)
				{
					pointersprite.SetImage(grabimage);
					pointersprite.SetZoom(1);
				}
				else
				{
					pointersprite.SetImage(openimage);
					pointersprite.SetZoom(1);
				}
				break;
		}
	}
	
		
	if(btnsdown & WPAD_BUTTON_1)
	{
		cameraBod = GetSelectedBody(&pointersprite, &SelectedType, &SelectedPointer);
		
		if(cameraBod != NULL)
		{
			camera_set = true;
		}
		else
		{
			camera_set = false;
		}
		
	}
	
	if(btnsdown & WPAD_BUTTON_2)
	{
		settings->SetDisplayed(true);
	}
	
	//--------------------
	
	DrawScreen();
	
	//Get Gravity Mode
	switch(settings->GetGravityMode())
	{
		case Gravity::EARTH:
			if(current_gravity != Gravity::EARTH)
			{
				current_gravity = Gravity::EARTH;
				world->SetGravity(earth_gravity);
			}
			break;
		case Gravity::MOON:
			if(current_gravity != Gravity::MOON)
			{
				current_gravity = Gravity::MOON;
				world->SetGravity(moon_gravity);
			}
			break;
		case Gravity::JUPITER:
			if(current_gravity != Gravity::JUPITER)
			{
				current_gravity = Gravity::JUPITER;
				world->SetGravity(jupiter_gravity);
			}
			break;
		default:
			break;
	}
	
	//Get Sim State Mode
	switch(toolbox->GetPlayMode())
	{
		case PlayMode::PLAY:
			// Advance the physics simulation
			world->Step(timeStep, iterations, iterations);
			break;
		case PlayMode::STOP:
			break;
		default:
			break;
	}
}

void init_system()
{
	fatInitDefault();
	// Create the game window and initalise the VIDEO subsystem
	gwd.InitVideo();

	gwd.SetBackground((GXColor){ 255, 255, 255, 255 });
	// Initialise Wiimote
	WPAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetDataFormat(WPAD_CHAN_1, WPAD_FMT_BTNS_ACC_IR);
	
	init_console();
	
	SND_Init(INIT_RATE_48000); // Initialize the Sound Lib


    SND_Pause(0); // the sound loop is running now
   
}

void init_wii_physics()
{
	toolbox = new ToolBox();
	toolbox->SetModes(ToolMode::SELECT, PlayMode::PLAY, MotionMode::MOBILE, Joint::DISTANCE_JOINT, PenMode::CLOSED);

	settings = new SettingsBox();
	settings->SetModes(Gravity::EARTH, DEFAULT_RESTITUTION, DEFAULT_FRICTION, DEFAULT_DENSITY);

	main_menu = new MainMenuBox();
	
	main_menu->SetDisplayed(true);

	boxQuad.SetRectangle(&boxRect);

	makeWorld();
	
	blockimage  = new Image();
	ballimage   = new Image();

	selectimage = new Image();
	p2selectimage = new Image();
	grabimage = new Image();
	p2grabimage = new Image();
	openimage = new Image();
	p2openimage = new Image();
	
	ropeimage = new Image();
	jointpointerimage = new Image();
	revpointerimage = new Image();
	weldpointerimage = new Image();
	
	lineimage = new Image();
	penimage = new Image();
	titleimage = new Image();
	titlebgimage = new Image();
	penCursorImage = new Image();
	
	helpimage1 = new Image();
	helpimage2 = new Image();
	
	grassimage = new Image();
	supportimage = new Image();
	
	deletepointerimage = new Image();
	camerapointerimage = new Image();
	
	
	if(grassimage->LoadImage(grass, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	
	grassSprite.SetImage(grassimage);
	
	myClouds = new Clouds(70,MIN_SLIDE_X, MAX_SLIDE_X, MIN_SLIDE_Y+100, MAX_SLIDE_Y+100);
	
	if(supportimage->LoadImage(support, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(helpimage1->LoadImage(help_page_one, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(helpimage2->LoadImage(help_page_two, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	
	if(titleimage->LoadImage(title, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(titlebgimage->LoadImage(titlebg, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(blockimage->LoadImage(block_image, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(ballimage->LoadImage(ball_image, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(selectimage->LoadImage(player1_point, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(p2selectimage->LoadImage(player2_point, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(grabimage->LoadImage(player1_grab, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(p2grabimage->LoadImage(player2_grab, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(p2openimage->LoadImage(player2_openhand, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(openimage->LoadImage(player1_openhand, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
		
	if(ropeimage->LoadImage(rope, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(jointpointerimage->LoadImage(jointPointer, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(penimage->LoadImage(penPointer, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(penCursorImage->LoadImage(penCursor, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(revpointerimage->LoadImage(revPointer, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(weldpointerimage->LoadImage(weldPointer, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(deletepointerimage->LoadImage(deletePointer, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(camerapointerimage->LoadImage(cameraPointer, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	titleSprite.SetImage(titleimage);
	titleSprite.SetFrame(2);
		
	bgSprite.SetImage(titlebgimage);
	bgSprite.SetFrame(2);
		
	p2pointersprite.SetImage(p2selectimage);
	p2pointersprite.SetFrame(2);
	
	pointersprite.SetImage(selectimage);
	pointersprite.SetFrame(2);

     //Init onscreenkeyboard
     osk = new OnScreenKeyboard(&gwd, "/config/key_config.xml");
	 

}

void HandleSettings()
{
	WPAD_ScanPads();
	
	u16 btnsdown = WPAD_ButtonsDown(0);
	u16 btnsheld = WPAD_ButtonsHeld(0);

	// Infrared calculation
	ir_t ir; // The struct for infrared
	
	WPAD_IR(WPAD_CHAN_0, &ir); // Let's get our infrared data
	wd = WPAD_Data(WPAD_CHAN_0);

	pointersprite.SetPosition(ir.sx-200, ir.sy-250);
	pointersprite.SetRotation(ir.angle/2); // Set angle/2 to translate correctly
	pointersprite.SetImage(openimage);
	
	//Set Pointer
	if(settings->HoverButton(ir.sx-200, ir.sy-250))
	{
		//if(settings->IsSoundEnabled())
		//{
		//	PlayOgg(mem_open((char*)hoverOgg, hoverOgg_size), 0, OGG_ONE_TIME);
		//}
		pointersprite.SetImage(selectimage);
	}
	
	if(btnsheld & WPAD_BUTTON_A)
	{
		if(settings->PressButton(ir.sx-200, ir.sy-250))
		{
			pointersprite.SetImage(grabimage);
			//if(settings->IsSoundEnabled())
			//{
			//	PlayOgg(mem_open((char*)clickOgg, clickOgg_size), 0, OGG_ONE_TIME);
			//}
		}
		settings->ResetSinglePressButtons();
	}
	
	pointersprite.SetZoom(1);
		
	if(btnsdown & WPAD_BUTTON_1)
	{
		settings->SetDisplayed(false);
	}
	DrawScreen();

}

void GameIntro()
{
	//TODO Show Main Image
	//"Fade in"
	Sprite introSprite;
	Image* introImg = new Image();
	if(introImg->LoadImage(intro, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	
	introSprite.SetImage(introImg);
	introSprite.SetPosition(192,120);
	
	introSprite.SetTransparency(0);
	gwd.Flush();
	
    PlayOgg(mem_open((char*)introOgg, introOgg_size), 0, OGG_ONE_TIME);
	
	for(int i = 0; i < 255; i++) //255 *2
	{
		introSprite.SetTransparency(i);
		introSprite.Draw();
		gwd.Flush();
	}
	
	//Init Game!
	init_wii_physics();
	
	//Fade Out
}

void HandleMainMenu()
{
	WPAD_ScanPads();
	
	u16 btnsdown = WPAD_ButtonsDown(0);

	// Infrared calculation
	ir_t ir; // The struct for infrared
	
	WPAD_IR(WPAD_CHAN_0, &ir); // Let's get our infrared data
	wd = WPAD_Data(WPAD_CHAN_0);

	pointersprite.SetPosition(ir.sx-200, ir.sy-250);
	pointersprite.SetRotation(ir.angle/2); // Set angle/2 to translate correctly
	
	pointersprite.SetImage(openimage);
	
	//Set Pointer
	if(main_menu->HoverButton(ir.sx-200, ir.sy-250))
	{
		//if(settings->IsSoundEnabled())
		//{
		//	PlayOgg(mem_open((char*)hoverOgg, hoverOgg_size), 0, OGG_ONE_TIME);
		//}
		pointersprite.SetImage(selectimage);
	}
	
	
	if(btnsdown & WPAD_BUTTON_HOME)
	{
		show_help = false;
		show_support = false;
	}
	
	if(btnsdown & WPAD_BUTTON_PLUS)
	{
		help_page = (help_page + 1);
		if(help_page > 2) help_page = 1;
	}
	
	
	if(btnsdown & WPAD_BUTTON_A)
	{
		if(main_menu->PressButton(ir.sx-200, ir.sy-250))
		{
			//if(settings->IsSoundEnabled())
			//{
			//	PlayOgg(mem_open((char*)clickOgg, clickOgg_size), 0, OGG_ONE_TIME);
			//}
			pointersprite.SetImage(selectimage);
			
			if(main_menu->Quit())
			{
				//Quit!
				Quad fadeQuad;
				GXColor fill_color;
				fill_color.r = 0;
				fill_color.g = 0;
				fill_color.b = 0;
				fill_color.a = 0;
				fadeQuad.SetFillColor(fill_color);
				fadeQuad.SetWidth(700);
				fadeQuad.SetHeight(700);
				fadeQuad.SetPosition(-30,-30);
				int i = 0;
				
				while(i < 255)
				{
					main_menu->Draw();
					fill_color.a = i;
					fadeQuad.SetFillColor(fill_color);
					fadeQuad.Draw();
					i+=15;
					gwd.Flush();
				}
				
				exit(0);
			}
			else if(main_menu->ShowHelp())
			{
				show_help = true;
				show_support = false;
				help_page = 1;
				
			}
			else if(main_menu->ShowSupport())
			{
				show_support = true;
				show_help = false;
				
			}
		}
		main_menu->ResetSinglePressButtons();
	}
	
	pointersprite.SetZoom(1);
		
	if(!show_help && !show_support)
	{
		DrawScreen();
	}
	else if(show_help)
	{
		Sprite helpSprite;
		if(help_page == 1)
			helpSprite.SetImage(helpimage1);
		else
			helpSprite.SetImage(helpimage2);
			
		helpSprite.SetPosition(0,0);
		
		helpSprite.Draw();
		gwd.Flush();
	}
	else if(show_support)
	{
		Sprite supportSprite;
		supportSprite.SetImage(supportimage);
			
		supportSprite.SetPosition(0,0);
		
		supportSprite.Draw();
		gwd.Flush();
	}
	
}

void HandleSave()
{
   char* tmp = osk->EditString((char*)(save_string.c_str()));

   if(tmp != NULL)
      save_string = tmp;
   else
      save_string = "";	  


   if(strcmp(save_string.c_str(),"") != 0)
   {
	// Figure out if it's supported or not
	if(strlen(save_string.c_str())>4)
	{
		if(save_string[strlen(save_string.c_str()) - 3] != '.' ||
			save_string[strlen(save_string.c_str()) - 2] != 'p' ||
			save_string[strlen(save_string.c_str()) - 1] != 'p')
		{
		   save_string += ".pp";
		}
    }
	else
	{
	   save_string += ".pp";
	}
    SaveWorld((char*)save_string.c_str());
   }
   
   _saveDisplayed = false;
}

void destroyList()
{
	if(!fList)
	{
		// Nothing to destroy
		return;
	}
	
	// Delete all sprites
	for(int i = 0; i < fListCount; i++)
	{
		if(fList[i].sprite) { delete fList[i].sprite; }
		if(fList[i].icon) { delete fList[i].icon; }
	}
	
	// Delete item
	free(fList);
}

void populateList(const char *url, bool reset_scroll)
{
	// Clear old run
	destroyList();	
	
	// Ensure settings back to defaults
	fList = NULL;
	fListCount = 0;
	
	// Temporary data for directory list
	char fileName[MAXPATHLEN];
	FileType fileType;
	
	if(url[strlen(url) - 1] == '/')
	{
		// Open directory
		File dir;
		dir.open(url, "d");
		
		// Loop through and add all
		while(dir.findNextFile(fileName, fileType))
		{
			if(strcmp(fileName, ".") == 0) { continue; }
			
			if(fListCount > 0)
			{
				// Make more room
				fListCount++;
				fList = (FileListType *)realloc(fList, sizeof(FileListType) * fListCount);
			}
			else
			{
				// Make initial room
				fList = (FileListType *)malloc(sizeof(FileListType) * 1);
				fListCount = 1;
			}
			
			// Copy file details
			strcpy(fList[fListCount - 1].fileName, fileName);
			fList[fListCount - 1].fType = fileType;
			
			if(fileType == FILE_DIRECTORY)
			{
				if(strcmp(fileName, "..") == 0)
				{
					// Back icon
					fList[fListCount - 1].whichIcon = TYPE_BACK;
				}
				else
				{
					// Generic folder icon
					fList[fListCount - 1].whichIcon = TYPE_FOLDER;
				}
			}
			else
			{
				// Figure out if it's supported or not
				if(strlen(fileName)>4)
				{
					if(fileName[strlen(fileName) - 3] == '.' &&
						fileName[strlen(fileName) - 2] == 'p' &&
						fileName[strlen(fileName) - 1] == 'p')
					{
						fList[fListCount - 1].whichIcon = TYPE_PP;
					}
					else
					{
						// No, set to unknown icon
						fList[fListCount - 1].whichIcon = TYPE_UNKNOWN;
					}
					
				}
				else
				{
					// No, set to unknown icon
					fList[fListCount - 1].whichIcon = TYPE_UNKNOWN;
				}
			}
			
			// Ensure null
			fList[fListCount - 1].sprite = NULL;
			fList[fListCount - 1].icon = NULL;
			
		}
		
		// No leaked handles please
		dir.close();
	}
}

void HandleLoad()
{ 
   populateList("sd://apps/wiiphysics/",true);
   
   bool do_load = true;
   int selected_index = 0;
   int scroll = 0;
   int start_scroll = 11;
   IconType cType = TYPE_UNKNOWN;
   Quad selQuad;
   
	gwd.SetBackground((GXColor){ 255, 255, 255, 255 });
		
   selQuad.SetWidth(400);
   selQuad.SetHeight(30);
   selQuad.SetPosition(35,50);
   
   selQuad.SetFillColor((GXColor){ 112, 203, 255, 200 });
   
   while(do_load)
   {
		WPAD_ScanPads();
		
		u16 btnsdown = WPAD_ButtonsDown(0);
		
		ir_t ir; // The struct for infrared
		
		WPAD_IR(WPAD_CHAN_0, &ir); // Let's get our infrared data
		wd = WPAD_Data(WPAD_CHAN_0);

		pointersprite.SetPosition(ir.sx-200, ir.sy-250);
		pointersprite.SetRotation(ir.angle/2); // Set angle/2 to translate correctly
	
		if(btnsdown & WPAD_BUTTON_A)
		{
			if(fList != NULL)
			{
				if(cType == TYPE_PP)
				{
					LoadWorld(fList[selected_index].fileName);
					save_string = fList[selected_index].fileName;
					do_load = false;
				}
				if(cType == TYPE_BACK)
				{
					
				}
				if(cType == TYPE_FOLDER)
				{
					populateList(fList[selected_index].fileName,true);
				}
			}
		}
		
		if(btnsdown & WPAD_BUTTON_DOWN)
		{
			if(selected_index < fListCount-1)
			{
				selected_index++;
			}
			
			if(selected_index > start_scroll)
				scroll++;
		}
		
		if(btnsdown & WPAD_BUTTON_UP)
		{
			if(selected_index > 0)
			{
				selected_index--;
			}
			
			if(selected_index < start_scroll && scroll > 0)
				scroll--;
		}
		
		if(btnsdown & WPAD_BUTTON_B)
		{
			do_load = false;
		}
		
		if(fList != NULL)
		{
			int num_drawn = 0;
			
			//Draw list
			for(int i = scroll; i < (fListCount-scroll) && i < scroll + start_scroll +1; i++)
			{
				if(fList[i].whichIcon == TYPE_PP)
				{
					if(selected_index == i)
					{
						cType = TYPE_PP;
						settings->DrawText("@", 25, 50+num_drawn*30);
						selQuad.SetPosition(25, 50+num_drawn*30);
						selQuad.Draw();
					}
					
					settings->DrawText(fList[i].fileName, 40, 50+num_drawn*30);
					num_drawn++;
				}
				if(fList[i].whichIcon == TYPE_BACK)
				{
					if(selected_index == i)
					{
						cType = TYPE_BACK;
						//settings->DrawText(">", 25, 50+num_drawn*30);
						selQuad.SetPosition(25, 50+num_drawn*30);
						selQuad.Draw();
					}
					
					settings->DrawText("..",40, 50+num_drawn*30);
					num_drawn++;
				}
				if(fList[i].whichIcon == TYPE_FOLDER)
				{
				    //TODO Draw folder Icon
					if(selected_index == i)
					{
						cType = TYPE_FOLDER;
						//settings->DrawText(">", 25, 50+num_drawn*30);
						selQuad.SetPosition(25, 50+num_drawn*30);
						selQuad.Draw();
					}
	
					settings->DrawText(fList[i].fileName, 40, 50+num_drawn*30);
					num_drawn++;
				}
				if(fList[i].whichIcon == TYPE_UNKNOWN)
				{
					if(selected_index == i)
					{
						cType = TYPE_BACK;
						//settings->DrawText("?", 25, 50+num_drawn*30);
						selQuad.SetPosition(25, 50+num_drawn*30);
						selQuad.Draw();
					}
					
					settings->DrawText(fList[i].fileName,40, 50+num_drawn*30);
					num_drawn++;
				}
				
				
			}
		}
		else
		{
			do_load = false;
		}
		
		if(fList != NULL)
		{
			char buf[120];
			sprintf(buf, "Select a wiiphysics file... (%s)", fList[selected_index].fileName);

			settings->DrawText(buf, 50,20);
		}
		else
		{
			char buf[120];
			sprintf(buf, "Select a wiiphysics file...");

			settings->DrawText(buf, 50,20);
		}
		pointersprite.Draw();
		gwd.Flush();
   }
   
	_loadDisplayed = false;
}

int main(int argc, char **argv)
{
	init_system();
	
	GameIntro();
	
	if(settings->IsSoundEnabled())
	{
		PlayOgg(mem_open((char*)bgmOgg, bgmOgg_size), 0, OGG_INFINITE_TIME);
	}
	main_menu->SetDisplayed(true);
	
	for(;;)
	{
		if(_saveDisplayed)
		{
			HandleSave();
		}
		else if(_loadDisplayed)
		{
			HandleLoad();
		}
		else if(main_menu->Displayed())
		{
			HandleMainMenu();
		}
		else if(settings->Displayed())
		{
			HandleSettings();
		}
		else
		{
			RunWiiPhysics();
		}
	}
	return 0;
}
