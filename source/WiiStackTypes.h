#ifndef _WiiStackTypes_H_
#define _WiiStackTypes_H_

#include "Box2D.h"

namespace WiiStackTypes {
	namespace ToolMode {
		enum Type{
			SELECT       = 0,
			DRAW_BOX     = 1,
			DRAW_CIRCLE  = 2,
			DRAW_LINE    = 3,
			DRAW_PEN     = 4,
			CREATE_JOINT = 5,
			CLEAR_SCREEN = 6,
			UNDO         = 7,
			DELETE       = 8,
			SET_CAMERA   = 9,
			NONE         = 10
		};
	};

	namespace Joint {
		enum Type{
			DISTANCE_JOINT   = 0,
			PRISMATIC_JOINT  = 1,
			REVOLUTE_JOINT   = 2,
			PULLEY_JOINT     = 3,
			GEAR_JOINT       = 4,
			WELD_JOINT       = 5,
			RUBBER_JOINT     = 6,
			NONE = 7
		};
	
	};

	namespace PenMode {
		 enum Type{
			CLOSED = 0,
			OPEN = 1
		};
	};
	
	namespace MotionMode {
		 enum Type{
			FREEZE = 0,
			MOBILE = 1,
			NONE   = 2
		};
	};

	namespace Gravity {
		 enum Type{
			MOON    = 0,
			EARTH   = 1,
			JUPITER = 2,
			NONE = 3
		};
	};
	
	namespace PlayMode {
		enum Type{
			PLAY   = 0,
			STOP   = 1,
			RECORD = 2,
			NONE   = 3
		};
	};

	namespace GenericPlusMinus {
		enum Type{
			MINUS   = 0,
			PLUS    = 1,
			NONE    = 2
		};
	};

	namespace Menu {
		enum Type{
			SHOW    = 0,
			HIDE    = 1,
			NONE    = 2
		};
	};
	
	const float PIXELS_PER_UNIT     = 80.0;
	const float DEFAULT_DENSITY     = 5.0f;
	const float DEFAULT_FRICTION    = 0.2f;
	const float DEFAULT_RESTITUTION = 0.4f;

	const int MAX_BLOCKS            = 1000;
	const int MAX_BALLS             = 1000;
	const int MAX_LINES             = 1000;
	const int MAX_POLYPENS            = 1000;
	const int MAX_FLOORS            = 1000;
	const int MAX_DIST_JOINTS       = 1000;
	const int MAX_REV_JOINTS       = 1000;
	const int MAX_PUL_JOINTS       = 1000;
	const int MAX_PRIS_JOINTS       = 1000;
	const int MAX_POLY_POINTS       = 100;
	const float32 timeStep          = 1.0f / 60.0f;
	const int32 iterations          = 10;

	const int BLOCK_TYPE = 0;
	const int BALL_TYPE  = 1;
	const int FLOOR_TYPE = 2;

	const int NUM_BUTTONS = 11;


	const int SHOW_HIDE_X = 302;
	const int SHOW_HIDE_Y = 450;

	const int CLEAR_BUTTON_X = 576;
	const int CLEAR_BUTTON_Y = 28;
	
	const int DELETE_BUTTON_X = 576;
	const int DELETE_BUTTON_Y = 64;
	
	const int UNDO_BUTTON_X = 576;
	const int UNDO_BUTTON_Y = 100;
	
	const int SELECT_BUTTON_X = 32;
	const int SELECT_BUTTON_Y = 28;

	const int PEN_BUTTON_X = 32;
	const int PEN_BUTTON_Y = 64;
	
	const int PEN_CLOSED_X = 66;
	const int PEN_CLOSED_Y = 64;
	
	const int PEN_OPEN_X = 102;
	const int PEN_OPEN_Y = 64;
	
	const int DRAW_BOX_BUTTON_X = 32;
	const int DRAW_BOX_BUTTON_Y = 100;

	const int DRAW_CIRCLE_BUTTON_X = 32;
	const int DRAW_CIRCLE_BUTTON_Y = 136;
	
	const int DRAW_LINE_BUTTON_X = 32;
	const int DRAW_LINE_BUTTON_Y = 172;
	
	const int JOINT_BUTTON_X = 32;
	const int JOINT_BUTTON_Y = 208;
	//---
	const int DISTANCE_JOINT_X = 66;
	const int DISTANCE_JOINT_Y = 208;
	
	const int PRISMATIC_JOINT_X = 174;
	const int PRISMATIC_JOINT_Y = 208;
	
	const int WELD_JOINT_X = 210;
	const int WELD_JOINT_Y = 208;
	
	const int RUBBER_JOINT_X = 246;
	const int RUBBER_JOINT_Y = 208;
	
	const int REVOLUTE_JOINT_X = 138;
	const int REVOLUTE_JOINT_Y = 208;
	
	const int PULLEY_JOINT_X = 102;
	const int PULLEY_JOINT_Y = 208;
	//--
	const int MOBILE_BUTTON_X = 32;
	const int MOBILE_BUTTON_Y = 282;
	
	const int FREEZE_BUTTON_X = 32;
	const int FREEZE_BUTTON_Y = 318;

	const int PLAY_BUTTON_X = 576;
	const int PLAY_BUTTON_Y = 216;

	const int STOP_BUTTON_X = 576;
	const int STOP_BUTTON_Y = 254;
	
	const int CAMERA_BUTTON_X = 576;
	const int CAMERA_BUTTON_Y = 318;
	
	const int SAVE_X = 576;
	const int SAVE_Y = 354;
	
	const int LOAD_X = 576;
	const int LOAD_Y = 390;
	
	const int SETTINGS_X = 576;
	const int SETTINGS_Y = 426;
	
	const int RESET_X = 576;
	const int RESET_Y = 160;
	
	///SETTINGS BUTTON LAYOUT
	
	//-- Gravity Buttons	
	const int MOON_X = 420;
	const int MOON_Y = 100;
	
	const int EARTH_X = 460;
	const int EARTH_Y = 100;
	
	const int JUPITER_X = 496;
	const int JUPITER_Y = 100;
	//--End grav buttons
	
	//Friction Buttons
	const int FRICTION_MINUS_X = 510;
	const int FRICTION_MINUS_Y = 175;
	
	const int FRICTION_PLUS_X = 546;
	const int FRICTION_PLUS_Y = 175;
	//--End Fric Buttons
	
	//Restitution Buttons
	const int RESTITUTION_MINUS_X = 510;
	const int RESTITUTION_MINUS_Y = 210;
	
	const int RESTITUTION_PLUS_X = 546;
	const int RESTITUTION_PLUS_Y = 210;
	
	//--End Restitution Buttons
	
	//Density Buttons
	const int DENSITY_MINUS_X = 510;
	const int DENSITY_MINUS_Y = 245;
	
	const int DENSITY_PLUS_X = 546;
	const int DENSITY_PLUS_Y = 245;
	
	//--End Density Buttons
	
	const int BACK_X = 260;
	const int BACK_Y = 430;
	
	const int R_MINUS_X = 155;
	const int R_MINUS_Y = 330;
	const int R_PLUS_X = 191;
	const int R_PLUS_Y = 330;
	
	const int G_MINUS_X = 260;
	const int G_MINUS_Y = 330;
	const int G_PLUS_X = 296;
	const int G_PLUS_Y = 330;
	
	const int B_MINUS_X = 360;
	const int B_MINUS_Y = 330;
	const int B_PLUS_X = 396;
	const int B_PLUS_Y = 330;
	
	const int A_MINUS_X = 471;
	const int A_MINUS_Y = 330;
	const int A_PLUS_X = 508;
	const int A_PLUS_Y = 330;
	
	
	const int PLAY_X = 60;
	const int PLAY_Y = 320;
	
	const int HELP_X = 240;
	const int HELP_Y = 320;
	
	const int SUPPORT_X = 240;
	const int SUPPORT_Y = 420;
	
	const int QUIT_X = 424;
	const int QUIT_Y = 320;
}

#endif //_WiiStackTypes_H_
