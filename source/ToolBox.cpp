#include "ToolBox.h"
#include <fat.h>
#include <unistd.h>

//Images
#include "Button_Image.h"
#include "Button_Over.h"
#include "Button_Down.h"
#include "selectIcon.h"
#include "boxIcon.h"
#include "circleIcon.h"
#include "lineIcon.h"
#include "playIcon.h"
#include "stopIcon.h"
#include "mobileIcon.h"
#include "frozenIcon.h"
#include "distJointIcon.h"
#include "revJointIcon.h"
#include "prisJointIcon.h"
#include "pulJointIcon.h"
#include "clearScreenIcon.h"
#include "undoIcon.h"
#include "penIcon.h"
#include "penOpenIcon.h"
#include "penClosedIcon.h"


#include "resetIcon.h"
#include "weldJointIcon.h"
#include "deleteIcon.h"
#include "cameraIcon.h"
#include "rubberIcon.h"

#include "showMenuIcon.h"
#include "hideMenuIcon.h"
#include "settingsIcon.h"

#include "saveIcon.h"
#include "loadIcon.h"

ToolBox::ToolBox()
{
	//Button Images
	btnImg     = new Image();
	btnOverImg = new Image();
	btnDownImg = new Image();
	
	selectIconImg = new Image();
	boxIconImg    = new Image();
	circleIconImg = new Image();
	lineIconImg = new Image();
	penIconImg = new Image();
	penOpenIconImg = new Image();
	penClosedIconImg = new Image();
	
	playIconImg = new Image();
	stopIconImg = new Image();
	
	resetIconImg = new Image();
	
	mobileIconImg = new Image();
	frozenIconImg = new Image();
	
	distJointIconImg = new Image();
	revJointIconImg  = new Image();
	pulJointIconImg  = new Image();
	prisJointIconImg = new Image();
	weldJointIconImg = new Image();
	rubberJointIconImg = new Image();
	
	deleteIconImg = new Image();
	setCameraIconImg = new Image();
	
	clearScreenIconImg = new Image();
	undoIconImg = new Image();
	
	showMenuIconImg = new Image();
	hideMenuIconImg = new Image();
	
	settingsIconImg = new Image();
	
	saveIconImg = new Image();
	loadIconImg = new Image();
	
	if(resetIconImg->LoadImage(resetIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(settingsIconImg->LoadImage(settingsIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(showMenuIconImg->LoadImage(showMenuIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(hideMenuIconImg->LoadImage(hideMenuIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);

	if(saveIconImg->LoadImage(saveIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(loadIconImg->LoadImage(loadIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	//Load Button Images
	if(btnImg->LoadImage(Button_Image, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(btnOverImg->LoadImage(Button_Over, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(btnDownImg->LoadImage(Button_Down, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	//Icon Images
	if(selectIconImg->LoadImage(selectIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(boxIconImg->LoadImage(boxIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(circleIconImg->LoadImage(circleIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(lineIconImg->LoadImage(lineIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(penIconImg->LoadImage(penIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(penOpenIconImg->LoadImage(penOpenIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(penClosedIconImg->LoadImage(penClosedIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(playIconImg->LoadImage(playIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(stopIconImg->LoadImage(stopIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(mobileIconImg->LoadImage(mobileIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(frozenIconImg->LoadImage(frozenIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(distJointIconImg->LoadImage(distJointIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(revJointIconImg->LoadImage(revJointIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(prisJointIconImg->LoadImage(prisJointIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(weldJointIconImg->LoadImage(weldJointIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(pulJointIconImg->LoadImage(pulJointIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(rubberJointIconImg->LoadImage(rubberIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(clearScreenIconImg->LoadImage(clearScreenIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(undoIconImg->LoadImage(undoIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(deleteIconImg->LoadImage(deleteIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(setCameraIconImg->LoadImage(cameraIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	
	hideMenuButton = new Button(SHOW_HIDE_X, SHOW_HIDE_Y, btnImg, btnOverImg, btnDownImg, hideMenuIconImg);
	menu_state = true;
	
	showSettingsButton = new Button(SETTINGS_X, SETTINGS_Y, btnImg, btnOverImg, btnDownImg, settingsIconImg);
	
	resetButton = new Button(RESET_X, RESET_Y, btnImg, btnOverImg, btnDownImg, resetIconImg);
	
	saveButton = new Button(SAVE_X, SAVE_Y, btnImg, btnOverImg, btnDownImg, saveIconImg);
	loadButton = new Button(LOAD_X, LOAD_Y, btnImg, btnOverImg, btnDownImg, loadIconImg);
	
	resetButton->Deselect();
	
	//Create ToolType Buttons
	ToolButtons[ToolMode::SELECT]      = new Button(SELECT_BUTTON_X, SELECT_BUTTON_Y, btnImg, btnOverImg, btnDownImg, selectIconImg);
	ToolButtons[ToolMode::DRAW_BOX]    = new Button(DRAW_BOX_BUTTON_X, DRAW_BOX_BUTTON_Y, btnImg, btnOverImg, btnDownImg, boxIconImg);
	ToolButtons[ToolMode::DRAW_CIRCLE] = new Button(DRAW_CIRCLE_BUTTON_X, DRAW_CIRCLE_BUTTON_Y, btnImg, btnOverImg, btnDownImg, circleIconImg);
	ToolButtons[ToolMode::CREATE_JOINT] = new Button(JOINT_BUTTON_X, JOINT_BUTTON_Y, btnImg, btnOverImg, btnDownImg, distJointIconImg);
	ToolButtons[ToolMode::CLEAR_SCREEN] = new Button(CLEAR_BUTTON_X, CLEAR_BUTTON_Y, btnImg, btnOverImg, btnDownImg, clearScreenIconImg);
	ToolButtons[ToolMode::DRAW_LINE]    = new Button(DRAW_LINE_BUTTON_X, DRAW_LINE_BUTTON_Y, btnImg, btnOverImg, btnDownImg, lineIconImg);
	ToolButtons[ToolMode::UNDO]         = new Button(UNDO_BUTTON_X, UNDO_BUTTON_Y, btnImg, btnOverImg, btnDownImg, undoIconImg);
	ToolButtons[ToolMode::DRAW_PEN]    = new Button(PEN_BUTTON_X, PEN_BUTTON_Y, btnImg, btnOverImg, btnDownImg, penIconImg);
	ToolButtons[ToolMode::DELETE]    = new Button(DELETE_BUTTON_X, DELETE_BUTTON_Y, btnImg, btnOverImg, btnDownImg, deleteIconImg);
	ToolButtons[ToolMode::SET_CAMERA]    = new Button(CAMERA_BUTTON_X, CAMERA_BUTTON_Y, btnImg, btnOverImg, btnDownImg, setCameraIconImg);
										
	//Create ToolType Buttons
	PlayButtons[PlayMode::PLAY]      = new Button(PLAY_BUTTON_X, PLAY_BUTTON_Y, btnImg, btnOverImg, btnDownImg, playIconImg);
	PlayButtons[PlayMode::STOP]      = new Button(STOP_BUTTON_X, STOP_BUTTON_Y, btnImg, btnOverImg, btnDownImg, stopIconImg);

	//Create ToolType Buttons
	MotionButtons[MotionMode::FREEZE]      = new Button(FREEZE_BUTTON_X, FREEZE_BUTTON_Y, btnImg, btnOverImg, btnDownImg, frozenIconImg);
	MotionButtons[MotionMode::MOBILE]      = new Button(MOBILE_BUTTON_X, MOBILE_BUTTON_Y, btnImg, btnOverImg, btnDownImg, mobileIconImg);

	JointButtons[Joint::DISTANCE_JOINT]  = new Button(DISTANCE_JOINT_X, DISTANCE_JOINT_Y, btnImg, btnOverImg, btnDownImg, distJointIconImg);
	JointButtons[Joint::PRISMATIC_JOINT] = new Button(PRISMATIC_JOINT_X, PRISMATIC_JOINT_Y, btnImg, btnOverImg, btnDownImg, prisJointIconImg);
	JointButtons[Joint::REVOLUTE_JOINT]  = new Button(REVOLUTE_JOINT_X, REVOLUTE_JOINT_Y, btnImg, btnOverImg, btnDownImg, revJointIconImg);
	JointButtons[Joint::PULLEY_JOINT]    = new Button(PULLEY_JOINT_X, PULLEY_JOINT_Y, btnImg, btnOverImg, btnDownImg, pulJointIconImg);
	JointButtons[Joint::WELD_JOINT]      = new Button(WELD_JOINT_X, WELD_JOINT_Y, btnImg, btnOverImg, btnDownImg, weldJointIconImg);
	JointButtons[Joint::RUBBER_JOINT]      = new Button(RUBBER_JOINT_X, RUBBER_JOINT_Y, btnImg, btnOverImg, btnDownImg, rubberJointIconImg);
		
	PenButtons[PenMode::CLOSED]      = new Button(PEN_CLOSED_X, PEN_CLOSED_Y, btnImg, btnOverImg, btnDownImg, penClosedIconImg);
	PenButtons[PenMode::OPEN]        = new Button(PEN_OPEN_X,   PEN_OPEN_Y, btnImg, btnOverImg, btnDownImg, penOpenIconImg);
		
	showSettingsButton->Deselect();
	ResetSubs();
	
	lastHover = 0;
	firstHover = false;
}	

ToolBox::~ToolBox()
{

}
	
void ToolBox::ClearAllHover()
{
	hideMenuButton->ClearHover();
	showSettingsButton->ClearHover();
	resetButton->ClearHover();
	saveButton->ClearHover();
	loadButton->ClearHover();

	ToolButtons[ToolMode::DRAW_BOX]->ClearHover();
	ToolButtons[ToolMode::DRAW_CIRCLE]->ClearHover();
	ToolButtons[ToolMode::DRAW_LINE]->ClearHover();
	ToolButtons[ToolMode::DRAW_PEN]->ClearHover();
	ToolButtons[ToolMode::CREATE_JOINT]->ClearHover();
	ToolButtons[ToolMode::SELECT]->ClearHover();
	ToolButtons[ToolMode::CLEAR_SCREEN]->ClearHover();
	ToolButtons[ToolMode::UNDO]->ClearHover();
	ToolButtons[ToolMode::DELETE]->ClearHover();
	ToolButtons[ToolMode::SET_CAMERA]->ClearHover();
	
	PlayButtons[PlayMode::STOP]->ClearHover();
	PlayButtons[PlayMode::PLAY]->ClearHover();
	
	MotionButtons[MotionMode::MOBILE]->ClearHover();
	MotionButtons[MotionMode::FREEZE]->ClearHover();
	
	PenButtons[PenMode::CLOSED]->ClearHover();
	PenButtons[PenMode::OPEN]->ClearHover();
	
	JointButtons[Joint::DISTANCE_JOINT]->ClearHover();
	JointButtons[Joint::REVOLUTE_JOINT]->ClearHover();
	JointButtons[Joint::PULLEY_JOINT]->ClearHover();
	JointButtons[Joint::PRISMATIC_JOINT]->ClearHover();
	JointButtons[Joint::WELD_JOINT]->ClearHover();
	JointButtons[Joint::RUBBER_JOINT]->ClearHover();
}

void ToolBox::ResetSubs()
{
	showSubJointBox       = false;
	showFrictionSubBox    = false;
	showRestitutionSubBox = false;
	showSubPenBox         = false;
}

	
bool ToolBox::HoverButton(u32 x, u32 y)
{
	ClearAllHover();
	firstHover = false;
	//offset text position to bottom right of pointer
	
	if(resetButton->IsPointerOver(x,y))
	{
		if(lastHover != 19)
		{
			lastHover = 19;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	if(showSettingsButton->IsPointerOver(x,y))
	{
		if(lastHover != 1)
		{
			lastHover = 1;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	if(saveButton->IsPointerOver(x,y))
	{
		ResetSubs();
		return true;
	}
	
	if(loadButton->IsPointerOver(x,y))
	{
		ResetSubs();
		return true;
	}
	
	if(hideMenuButton->IsPointerOver(x,y))
	{
		if(lastHover != 2)
		{
			lastHover = 2;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	if(ToolButtons[ToolMode::CLEAR_SCREEN]->IsPointerOver(x,y))
	{
		if(lastHover != 3)
		{
			lastHover = 3;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(ToolButtons[ToolMode::UNDO]->IsPointerOver(x,y))
	{
		if(lastHover != 4)
		{
			lastHover = 4;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(ToolButtons[ToolMode::SELECT]->IsPointerOver(x,y))
	{
		if(lastHover != 5)
		{
			lastHover = 5;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(ToolButtons[ToolMode::DRAW_BOX]->IsPointerOver(x,y))
	{
		if(lastHover != 6)
		{
			lastHover = 6;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(ToolButtons[ToolMode::DRAW_CIRCLE]->IsPointerOver(x,y))
	{
		if(lastHover != 7)
		{
			lastHover = 7;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(ToolButtons[ToolMode::DRAW_LINE]->IsPointerOver(x,y))
	{
		if(lastHover != 8)
		{
			lastHover = 8;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(ToolButtons[ToolMode::DRAW_PEN]->IsPointerOver(x,y))
	{
		if(lastHover != 18)
		{
			lastHover = 18;
			firstHover = true;
		}
		ResetSubs();
		showSubPenBox = true;
		return true;
	}
	if(ToolButtons[ToolMode::CREATE_JOINT]->IsPointerOver(x,y))
	{
		if(lastHover != 9)
		{
			lastHover = 9;
			firstHover = true;
		}
		ResetSubs();
		showSubJointBox = true;
		return true;
	}
	if(ToolButtons[ToolMode::SET_CAMERA]->IsPointerOver(x,y))
	{
		if(lastHover != 21)
		{
			lastHover = 21;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(ToolButtons[ToolMode::DELETE]->IsPointerOver(x,y))
	{
		if(lastHover != 20)
		{
			lastHover = 20;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(PlayButtons[PlayMode::PLAY]->IsPointerOver(x,y))
	{
		if(lastHover != 10)
		{
			lastHover = 10;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(PlayButtons[PlayMode::STOP]->IsPointerOver(x,y))
	{
		if(lastHover != 11)
		{
			lastHover = 11;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}

	if(MotionButtons[MotionMode::FREEZE]->IsPointerOver(x,y))
	{
		if(lastHover != 12)
		{
			lastHover = 12;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(MotionButtons[MotionMode::MOBILE]->IsPointerOver(x,y))
	{
		if(lastHover != 13)
		{
			lastHover = 13;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	
	if(showSubPenBox)
	{
		if(PenButtons[PenMode::CLOSED]->IsPointerOver(x,y))
		{
			ResetSubs();
			showSubPenBox = true;
			return true;
		}
		if(PenButtons[PenMode::OPEN]->IsPointerOver(x,y))
		{
			ResetSubs();
			showSubPenBox = true;
			return true;
		}
	}
	
	if(showSubJointBox)
	{
		if(JointButtons[Joint::DISTANCE_JOINT]->IsPointerOver(x,y))
		{
			if(lastHover != 14)
			{
				lastHover = 14;
				firstHover = true;
			}
			ResetSubs();
			showSubJointBox = true;
			return true;
		}
		if(JointButtons[Joint::REVOLUTE_JOINT]->IsPointerOver(x,y))
		{
			if(lastHover != 15)
			{
				lastHover = 15;
				firstHover = true;
			}
			ResetSubs();
			showSubJointBox = true;
			return true;
		}
		if(JointButtons[Joint::PULLEY_JOINT]->IsPointerOver(x,y))
		{			
			if(lastHover != 16)
			{
				lastHover = 16;
				firstHover = true;
			}

			ResetSubs();
			showSubJointBox = true;
			return true;
		}
		if(JointButtons[Joint::PRISMATIC_JOINT]->IsPointerOver(x,y))
		{
			if(lastHover != 17)
			{
				lastHover = 17;
				firstHover = true;
			}

			ResetSubs();
			showSubJointBox = true;
			return true;
		}
		if(JointButtons[Joint::WELD_JOINT]->IsPointerOver(x,y))
		{
			if(lastHover != 18)
			{
				lastHover = 18;
				firstHover = true;
			}

			ResetSubs();
			showSubJointBox = true;
			return true;
		}
		if(JointButtons[Joint::RUBBER_JOINT]->IsPointerOver(x,y))
		{
			if(lastHover != 22)
			{
				lastHover = 22;
				firstHover = true;
			}

			ResetSubs();
			showSubJointBox = true;
			return true;
		}
	}
	lastHover = 0;
	ResetSubs();
	return false;
}

bool ToolBox::PressButton(u32 x, u32 y)
{

   //Single Click tool buttons
   //----------------------------------------------------------------------------------------------------
   
	if(hideMenuButton->Select(x,y))
	{
		menu_state = !menu_state;
		hideMenuButton->Deselect();
		return true;
	}
	
	if(showSettingsButton->Select(x,y))
	{
		return true;
	}
	
	if(resetButton->Select(x,y))
	{
		return true;
	}
	
	if(saveButton->Select(x,y))
	{
		return true;
	}
	
	if(loadButton->Select(x,y))
	{
		return true;
	}
	
	if(ToolButtons[ToolMode::CLEAR_SCREEN]->Select(x,y))
	{
		return true;
	}

	if(ToolButtons[ToolMode::UNDO]->Select(x,y))
	{
		return true;
	}
	
	
	//--------------------------------------------------------------------------------------------------
   //End Single Click tool buttons
   
	if(ToolButtons[ToolMode::SELECT]->Select(x,y))
	{
		ToolButtons[ToolMode::DRAW_BOX]->Deselect();
		ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
		ToolButtons[ToolMode::DRAW_LINE]->Deselect();
		ToolButtons[ToolMode::CREATE_JOINT]->Deselect();
		ToolButtons[ToolMode::DRAW_PEN]->Deselect();
		ToolButtons[ToolMode::DELETE]->Deselect();
		ToolButtons[ToolMode::SET_CAMERA]->Deselect();
		return true;
	}
	
	if(ToolButtons[ToolMode::DRAW_BOX]->Select(x,y))
	{
		ToolButtons[ToolMode::SELECT]->Deselect();
		ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
		ToolButtons[ToolMode::DRAW_LINE]->Deselect();
		ToolButtons[ToolMode::CREATE_JOINT]->Deselect();
		ToolButtons[ToolMode::DELETE]->Deselect();
		ToolButtons[ToolMode::SET_CAMERA]->Deselect();
		return true;
	}
	
	if(ToolButtons[ToolMode::DRAW_CIRCLE]->Select(x,y))
	{
		ToolButtons[ToolMode::DRAW_BOX]->Deselect();
		ToolButtons[ToolMode::SELECT]->Deselect();
		ToolButtons[ToolMode::DRAW_LINE]->Deselect();
		ToolButtons[ToolMode::CREATE_JOINT]->Deselect();
		ToolButtons[ToolMode::DRAW_PEN]->Deselect();
		ToolButtons[ToolMode::DELETE]->Deselect();
		ToolButtons[ToolMode::SET_CAMERA]->Deselect();
		return true;
	}
	
	if(ToolButtons[ToolMode::CREATE_JOINT]->Select(x,y))
	{
		ToolButtons[ToolMode::DRAW_BOX]->Deselect();
		ToolButtons[ToolMode::SELECT]->Deselect();
		ToolButtons[ToolMode::DRAW_LINE]->Deselect();
		ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
		ToolButtons[ToolMode::DRAW_PEN]->Deselect();
		ToolButtons[ToolMode::DELETE]->Deselect();
		ToolButtons[ToolMode::SET_CAMERA]->Deselect();
		return true;
	}
	
	if(ToolButtons[ToolMode::DRAW_LINE]->Select(x,y))
	{
		ToolButtons[ToolMode::DRAW_BOX]->Deselect();
		ToolButtons[ToolMode::SELECT]->Deselect();
		ToolButtons[ToolMode::CREATE_JOINT]->Deselect();
		ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
		ToolButtons[ToolMode::DRAW_PEN]->Deselect();
		ToolButtons[ToolMode::DELETE]->Deselect();
		ToolButtons[ToolMode::SET_CAMERA]->Deselect();
		return true;
	}
	
	if(ToolButtons[ToolMode::DRAW_PEN]->Select(x,y))
	{
		ToolButtons[ToolMode::DRAW_BOX]->Deselect();
		ToolButtons[ToolMode::SELECT]->Deselect();
		ToolButtons[ToolMode::CREATE_JOINT]->Deselect();
		ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
		ToolButtons[ToolMode::DRAW_LINE]->Deselect();
		ToolButtons[ToolMode::DELETE]->Deselect();
		ToolButtons[ToolMode::SET_CAMERA]->Deselect();
		return true;
	}
	
	if(ToolButtons[ToolMode::DELETE]->Select(x,y))
	{
		ToolButtons[ToolMode::DRAW_BOX]->Deselect();
		ToolButtons[ToolMode::SELECT]->Deselect();
		ToolButtons[ToolMode::CREATE_JOINT]->Deselect();
		ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
		ToolButtons[ToolMode::DRAW_LINE]->Deselect();
		ToolButtons[ToolMode::DRAW_PEN]->Deselect();
		ToolButtons[ToolMode::SET_CAMERA]->Deselect();
		return true;
	}
	
	if(ToolButtons[ToolMode::SET_CAMERA]->Select(x,y))
	{
		ToolButtons[ToolMode::DRAW_BOX]->Deselect();
		ToolButtons[ToolMode::SELECT]->Deselect();
		ToolButtons[ToolMode::CREATE_JOINT]->Deselect();
		ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
		ToolButtons[ToolMode::DRAW_LINE]->Deselect();
		ToolButtons[ToolMode::DRAW_PEN]->Deselect();
		ToolButtons[ToolMode::DELETE]->Deselect();
		return true;
	}
	
	if(PlayButtons[PlayMode::PLAY]->Select(x,y))
	{
		PlayButtons[PlayMode::STOP]->Deselect();
		return true;
	}
	
	if(PlayButtons[PlayMode::STOP]->Select(x,y))
	{
		PlayButtons[PlayMode::PLAY]->Deselect();
		return true;
	}

	if(MotionButtons[MotionMode::FREEZE]->Select(x,y))
	{
		MotionButtons[MotionMode::MOBILE]->Deselect();
		return true;
	}
	
	if(MotionButtons[MotionMode::MOBILE]->Select(x,y))
	{
		MotionButtons[MotionMode::FREEZE]->Deselect();
		return true;
	}
	
	if(showSubPenBox)
	{
		if(PenButtons[PenMode::CLOSED]->Select(x,y))
		{
			ToolButtons[ToolMode::DRAW_BOX]->Deselect();
			ToolButtons[ToolMode::SELECT]->Deselect();
			ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
			ToolButtons[ToolMode::DRAW_LINE]->Deselect();
			ToolButtons[ToolMode::CREATE_JOINT]->Deselect();
			ToolButtons[ToolMode::DELETE]->Deselect();
			ToolButtons[ToolMode::SET_CAMERA]->Deselect();
			PenButtons[PenMode::OPEN]->Deselect();
			
			ToolButtons[ToolMode::DRAW_PEN]->SetDown();
			showSubPenBox = false;
			return true;
		}
		
		if(PenButtons[PenMode::OPEN]->Select(x,y))
		{
			ToolButtons[ToolMode::DRAW_BOX]->Deselect();
			ToolButtons[ToolMode::SELECT]->Deselect();
			ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
			ToolButtons[ToolMode::DRAW_LINE]->Deselect();
			ToolButtons[ToolMode::CREATE_JOINT]->Deselect();
			ToolButtons[ToolMode::DELETE]->Deselect();
			ToolButtons[ToolMode::SET_CAMERA]->Deselect();
			PenButtons[PenMode::CLOSED]->Deselect();
			
			ToolButtons[ToolMode::DRAW_PEN]->SetDown();
			showSubPenBox = false;
			return true;
		}
	}
	
	if(showSubJointBox)
	{
		if(JointButtons[Joint::DISTANCE_JOINT]->Select(x,y))
		{
			JointButtons[Joint::PRISMATIC_JOINT]->Deselect();
			JointButtons[Joint::REVOLUTE_JOINT]->Deselect();
			JointButtons[Joint::PULLEY_JOINT]->Deselect();
			JointButtons[Joint::WELD_JOINT]->Deselect();
			JointButtons[Joint::RUBBER_JOINT]->Deselect();
			
			ToolButtons[ToolMode::DRAW_BOX]->Deselect();
			ToolButtons[ToolMode::SELECT]->Deselect();
			ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
			ToolButtons[ToolMode::DRAW_LINE]->Deselect();
			ToolButtons[ToolMode::DRAW_PEN]->Deselect();
			ToolButtons[ToolMode::DELETE]->Deselect();
			ToolButtons[ToolMode::SET_CAMERA]->Deselect();
			
			ToolButtons[ToolMode::CREATE_JOINT]->SetDown();
			showSubJointBox = false;
			return true;
		}
		
		if(JointButtons[Joint::PRISMATIC_JOINT]->Select(x,y))
		{
			JointButtons[Joint::DISTANCE_JOINT]->Deselect();
			JointButtons[Joint::REVOLUTE_JOINT]->Deselect();
			JointButtons[Joint::PULLEY_JOINT]->Deselect();
			JointButtons[Joint::WELD_JOINT]->Deselect();
			JointButtons[Joint::RUBBER_JOINT]->Deselect();
			ToolButtons[ToolMode::DRAW_BOX]->Deselect();
			ToolButtons[ToolMode::SELECT]->Deselect();
			ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
			ToolButtons[ToolMode::CREATE_JOINT]->SetDown();
			ToolButtons[ToolMode::DRAW_LINE]->Deselect();
			ToolButtons[ToolMode::DRAW_PEN]->Deselect();
			ToolButtons[ToolMode::DELETE]->Deselect();
			ToolButtons[ToolMode::SET_CAMERA]->Deselect();
			showSubJointBox = false;
			return true;
		}
	
		if(JointButtons[Joint::REVOLUTE_JOINT]->Select(x,y))
		{
			JointButtons[Joint::DISTANCE_JOINT]->Deselect();
			JointButtons[Joint::PRISMATIC_JOINT]->Deselect();
			JointButtons[Joint::PULLEY_JOINT]->Deselect();
			JointButtons[Joint::WELD_JOINT]->Deselect();
			JointButtons[Joint::RUBBER_JOINT]->Deselect();
			ToolButtons[ToolMode::DRAW_BOX]->Deselect();
			ToolButtons[ToolMode::SELECT]->Deselect();
			ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
			ToolButtons[ToolMode::CREATE_JOINT]->SetDown();
			ToolButtons[ToolMode::DRAW_LINE]->Deselect();
			ToolButtons[ToolMode::DELETE]->Deselect();
			ToolButtons[ToolMode::SET_CAMERA]->Deselect();
			showSubJointBox = false;
			return true;
		}
		
		if(JointButtons[Joint::PULLEY_JOINT]->Select(x,y))
		{
			JointButtons[Joint::DISTANCE_JOINT]->Deselect();
			JointButtons[Joint::REVOLUTE_JOINT]->Deselect();
			JointButtons[Joint::PRISMATIC_JOINT]->Deselect();
			JointButtons[Joint::WELD_JOINT]->Deselect();
			JointButtons[Joint::RUBBER_JOINT]->Deselect();
			ToolButtons[ToolMode::DRAW_BOX]->Deselect();
			ToolButtons[ToolMode::SELECT]->Deselect();
			ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
			ToolButtons[ToolMode::CREATE_JOINT]->SetDown();
			ToolButtons[ToolMode::DRAW_PEN]->Deselect();
			ToolButtons[ToolMode::DRAW_LINE]->Deselect();
			ToolButtons[ToolMode::DELETE]->Deselect();
			ToolButtons[ToolMode::SET_CAMERA]->Deselect();
			showSubJointBox = false;
			return true;
		}
		if(JointButtons[Joint::WELD_JOINT]->Select(x,y))
		{
			JointButtons[Joint::DISTANCE_JOINT]->Deselect();
			JointButtons[Joint::REVOLUTE_JOINT]->Deselect();
			JointButtons[Joint::PRISMATIC_JOINT]->Deselect();
			JointButtons[Joint::PULLEY_JOINT]->Deselect();
			JointButtons[Joint::RUBBER_JOINT]->Deselect();
			ToolButtons[ToolMode::DRAW_BOX]->Deselect();
			ToolButtons[ToolMode::SELECT]->Deselect();
			ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
			ToolButtons[ToolMode::CREATE_JOINT]->SetDown();
			ToolButtons[ToolMode::DRAW_PEN]->Deselect();
			ToolButtons[ToolMode::DRAW_LINE]->Deselect();
			ToolButtons[ToolMode::DELETE]->Deselect();
			ToolButtons[ToolMode::SET_CAMERA]->Deselect();
			showSubJointBox = false;
			return true;
		}
		if(JointButtons[Joint::RUBBER_JOINT]->Select(x,y))
		{
			JointButtons[Joint::DISTANCE_JOINT]->Deselect();
			JointButtons[Joint::REVOLUTE_JOINT]->Deselect();
			JointButtons[Joint::PRISMATIC_JOINT]->Deselect();
			JointButtons[Joint::PULLEY_JOINT]->Deselect();
			JointButtons[Joint::WELD_JOINT]->Deselect();
			ToolButtons[ToolMode::DRAW_BOX]->Deselect();
			ToolButtons[ToolMode::SELECT]->Deselect();
			ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
			ToolButtons[ToolMode::CREATE_JOINT]->SetDown();
			ToolButtons[ToolMode::DRAW_PEN]->Deselect();
			ToolButtons[ToolMode::DRAW_LINE]->Deselect();
			ToolButtons[ToolMode::DELETE]->Deselect();
			ToolButtons[ToolMode::SET_CAMERA]->Deselect();
			showSubJointBox = false;
			return true;
		}
	}
	return false;
}
		
ToolMode::Type ToolBox::GetToolMode()
{
  //NOTE Put Single select buttons first!
	if(ToolButtons[ToolMode::CLEAR_SCREEN]->IsSelected()){return ToolMode::CLEAR_SCREEN;}
	else if(ToolButtons[ToolMode::UNDO]->IsSelected()){return ToolMode::UNDO;}
	else if(ToolButtons[ToolMode::SELECT]->IsSelected()){return ToolMode::SELECT;}
	else if(ToolButtons[ToolMode::DRAW_BOX]->IsSelected()){return ToolMode::DRAW_BOX;}
	else if(ToolButtons[ToolMode::DRAW_CIRCLE]->IsSelected()){return ToolMode::DRAW_CIRCLE;}
	else if(ToolButtons[ToolMode::DRAW_LINE]->IsSelected()){return ToolMode::DRAW_LINE;}
	else if(ToolButtons[ToolMode::CREATE_JOINT]->IsSelected()){return ToolMode::CREATE_JOINT;}
	else if(ToolButtons[ToolMode::DRAW_PEN]->IsSelected()){return ToolMode::DRAW_PEN;}
	else if(ToolButtons[ToolMode::DELETE]->IsSelected()){return ToolMode::DELETE;}
	else if(ToolButtons[ToolMode::SET_CAMERA]->IsSelected()){return ToolMode::SET_CAMERA;}
	else{return ToolMode::NONE;}
}

PlayMode::Type ToolBox::GetPlayMode()
{
	if(PlayButtons[PlayMode::PLAY]->IsSelected()){return PlayMode::PLAY;}
	else if(PlayButtons[PlayMode::STOP]->IsSelected()){return PlayMode::STOP;}
	else{return PlayMode::NONE;}
}

MotionMode::Type ToolBox::GetMotionMode()
{
	if(MotionButtons[MotionMode::FREEZE]->IsSelected()){return MotionMode::FREEZE;}
	else if(MotionButtons[MotionMode::MOBILE]->IsSelected()){return MotionMode::MOBILE;}
	else{return MotionMode::NONE;}
}

PenMode::Type ToolBox::GetPenMode()
{
	if(PenButtons[PenMode::OPEN]->IsSelected()){return PenMode::OPEN;}
	else {return PenMode::CLOSED;}
	
}

Menu::Type ToolBox::GetSettingsMode()
{
	if(showSettingsButton->IsSelected()){return Menu::SHOW;}
	else{return Menu::HIDE;}
}

Menu::Type ToolBox::GetResetMode()
{
	if(resetButton->IsSelected()){return Menu::SHOW;}
	else{return Menu::HIDE;}
}

Menu::Type ToolBox::GetSaveMode()
{
	if(saveButton->IsSelected()){return Menu::SHOW;}
	else{return Menu::HIDE;}
}

Menu::Type ToolBox::GetLoadMode()
{
	if(loadButton->IsSelected()){return Menu::SHOW;}
	else{return Menu::HIDE;}
}

Joint::Type ToolBox::GetJointMode()
{
	if(JointButtons[Joint::DISTANCE_JOINT]->IsSelected()){return Joint::DISTANCE_JOINT;}
	else if(JointButtons[Joint::REVOLUTE_JOINT]->IsSelected()){return Joint::REVOLUTE_JOINT;}
	else if(JointButtons[Joint::PULLEY_JOINT]->IsSelected()){return Joint::PULLEY_JOINT;}
	else if(JointButtons[Joint::PRISMATIC_JOINT]->IsSelected()){return Joint::PRISMATIC_JOINT;}
	else if(JointButtons[Joint::WELD_JOINT]->IsSelected()){return Joint::WELD_JOINT;}
	else if(JointButtons[Joint::RUBBER_JOINT]->IsSelected()){return Joint::RUBBER_JOINT;}
	else{return Joint::NONE;}
}

void ToolBox::SetToolMode(ToolMode::Type tool_mode)
{
	ToolButtons[ToolMode::SELECT]->Deselect();
	ToolButtons[ToolMode::DRAW_BOX]->Deselect();
	ToolButtons[ToolMode::DRAW_CIRCLE]->Deselect();
	ToolButtons[ToolMode::CREATE_JOINT]->Deselect();
	ToolButtons[ToolMode::CLEAR_SCREEN]->Deselect();
	ToolButtons[ToolMode::UNDO]->Deselect();
	ToolButtons[ToolMode::DRAW_LINE]->Deselect();
	ToolButtons[ToolMode::DRAW_PEN]->Deselect();
	ToolButtons[ToolMode::DELETE]->Deselect();
	ToolButtons[ToolMode::SET_CAMERA]->Deselect();
	
	ToolButtons[tool_mode]->SetDown();
}

void ToolBox::SetModes(ToolMode::Type tool_mode, PlayMode::Type play_mode, MotionMode::Type motion_mode, Joint::Type joint_mode, PenMode::Type pen_mode)
{
	
	SetToolMode(tool_mode);
	
	PlayButtons[PlayMode::PLAY]->Deselect();
	PlayButtons[PlayMode::STOP]->Deselect();

	MotionButtons[MotionMode::FREEZE]->Deselect();
	MotionButtons[MotionMode::MOBILE]->Deselect();
	
	PenButtons[PenMode::OPEN]->Deselect();
	PenButtons[PenMode::CLOSED]->Deselect();
	
	JointButtons[Joint::DISTANCE_JOINT]->Deselect();
	JointButtons[Joint::REVOLUTE_JOINT]->Deselect();
	JointButtons[Joint::PRISMATIC_JOINT]->Deselect();
	JointButtons[Joint::PULLEY_JOINT]->Deselect();
	JointButtons[Joint::WELD_JOINT]->Deselect();
	JointButtons[Joint::RUBBER_JOINT]->Deselect();
	
	PlayButtons[play_mode]->SetDown();
	MotionButtons[motion_mode]->SetDown();
	JointButtons[joint_mode]->SetDown();
	PenButtons[pen_mode]->SetDown();
}
		
void ToolBox::ResetSinglePressButtons()
{
	hideMenuButton->Deselect();
	showSettingsButton->Deselect();
	resetButton->Deselect();
	saveButton->Deselect();
	loadButton->Deselect();

	ToolButtons[ToolMode::CLEAR_SCREEN]->Deselect();
	ToolButtons[ToolMode::UNDO]->Deselect();
}
		
void ToolBox::Draw(int drift)
{
	if(menu_state)
	{
		hideMenuButton->ChangeIcon(hideMenuIconImg);
	}
	else
	{
		hideMenuButton->ChangeIcon(showMenuIconImg);
	}

	hideMenuButton->Draw(0);
	showSettingsButton->Draw(drift);
	resetButton->Draw(drift);
	saveButton->Draw(drift);
	loadButton->Draw(drift);
	
	ToolButtons[ToolMode::CLEAR_SCREEN]->Draw(drift);
	ToolButtons[ToolMode::UNDO]->Draw(drift);
	ToolButtons[ToolMode::SELECT]->Draw(drift);
	ToolButtons[ToolMode::DRAW_BOX]->Draw(drift);
	ToolButtons[ToolMode::DRAW_CIRCLE]->Draw(drift);
	ToolButtons[ToolMode::DRAW_LINE]->Draw(drift);
	switch(GetPenMode())
	{
		case PenMode::OPEN:
			ToolButtons[ToolMode::DRAW_PEN]->ChangeIcon(penOpenIconImg);
			break;
		default:
			ToolButtons[ToolMode::DRAW_PEN]->ChangeIcon(penClosedIconImg);
			break;
	}
	
	ToolButtons[ToolMode::DRAW_PEN]->Draw(drift);
	ToolButtons[ToolMode::DELETE]->Draw(drift);
	ToolButtons[ToolMode::SET_CAMERA]->Draw(drift);
	
	switch(GetJointMode())
	{
		case Joint::DISTANCE_JOINT:
			ToolButtons[ToolMode::CREATE_JOINT]->ChangeIcon(distJointIconImg);
			break;
		case Joint::REVOLUTE_JOINT:
			ToolButtons[ToolMode::CREATE_JOINT]->ChangeIcon(revJointIconImg);
			break;
		case Joint::PRISMATIC_JOINT:
			ToolButtons[ToolMode::CREATE_JOINT]->ChangeIcon(prisJointIconImg);
			break;
		case Joint::PULLEY_JOINT:
			ToolButtons[ToolMode::CREATE_JOINT]->ChangeIcon(pulJointIconImg);
			break;
		case Joint::WELD_JOINT:
			ToolButtons[ToolMode::CREATE_JOINT]->ChangeIcon(weldJointIconImg);
			break;
		case Joint::RUBBER_JOINT:
			ToolButtons[ToolMode::CREATE_JOINT]->ChangeIcon(rubberJointIconImg);
			break;
		default:
			break;
	}
	
	ToolButtons[ToolMode::CREATE_JOINT]->Draw(drift);
	
	PlayButtons[PlayMode::PLAY]->Draw(drift);
	PlayButtons[PlayMode::STOP]->Draw(drift);

	MotionButtons[MotionMode::FREEZE]->Draw(drift);
	MotionButtons[MotionMode::MOBILE]->Draw(drift);
	
	if(showSubJointBox)
	{
		JointButtons[Joint::DISTANCE_JOINT]->Draw(drift);
		JointButtons[Joint::REVOLUTE_JOINT]->Draw(drift);
		JointButtons[Joint::PULLEY_JOINT]->Draw(drift);
		JointButtons[Joint::PRISMATIC_JOINT]->Draw(drift);		
		JointButtons[Joint::WELD_JOINT]->Draw(drift);
		JointButtons[Joint::RUBBER_JOINT]->Draw(drift);				
	}
	
	if(showSubPenBox)
	{
		PenButtons[PenMode::CLOSED]->Draw(drift);	
		PenButtons[PenMode::OPEN]->Draw(drift);	
	}
	
}



	