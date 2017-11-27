#ifndef _ToolBox_H_
#define _ToolBox_H_

#include "wiisprite.h"
#include "WiiStackTypes.h"
#include "Button.h"
#include "tiledtextlayer.h"

using namespace wsp;
using namespace WiiStackTypes;

class ToolBox {
	
	public:
	
		ToolBox();
		~ToolBox();
		
		bool HoverButton(u32 x, u32 y);
		bool PressButton(u32 x, u32 y);
		
		ToolMode::Type GetToolMode();
		PlayMode::Type GetPlayMode();
		
		MotionMode::Type GetMotionMode();
		
		Joint::Type GetJointMode();
		
		PenMode::Type GetPenMode();
		
		Menu::Type GetSettingsMode();
		Menu::Type GetResetMode();
		Menu::Type GetSaveMode();
		Menu::Type GetLoadMode();
		
		void SetToolMode(ToolMode::Type tool_mode);
		
		void SetMenuState(bool s){menu_state = s;}
		bool GetMenuState(){return menu_state;}
		
		void SetModes(ToolMode::Type tool_mode, PlayMode::Type play_mode, MotionMode::Type motion_mode, Joint::Type joint_mode, PenMode::Type pen_mode);
		void ResetSinglePressButtons();
		void Draw(int drift = 0);
	
		bool IsFirstHover(){return firstHover;}
	private:
		bool firstHover;
		int lastHover;
		
		void ClearAllHover();
		void ResetSubs();
		
		bool menu_state;
		
		bool showSubJointBox;
		bool showRestitutionSubBox;
		bool showFrictionSubBox;
		bool showSubPenBox;
		
		Image* btnImg;
		Image* btnOverImg;
		Image* btnDownImg;
		
		Image* selectIconImg;
		Image* boxIconImg;
		Image* circleIconImg;
		Image* lineIconImg;
		Image* penIconImg;
		
		Image* penOpenIconImg;
		Image* penClosedIconImg;
		
		Image* playIconImg;
		Image* stopIconImg;
		
		Image* resetIconImg;
		
		Image* mobileIconImg;
		Image* frozenIconImg;
		
		Image* distJointIconImg;
		Image* revJointIconImg;
		Image* prisJointIconImg;
		Image* pulJointIconImg;
		Image* weldJointIconImg;
		Image* rubberJointIconImg;
	
		Image* clearScreenIconImg;
		Image* deleteIconImg;
		Image* undoIconImg;
	
		Image* setCameraIconImg;
		
		Image* showMenuIconImg;
		Image* hideMenuIconImg;
		
		Image* settingsIconImg;
	
		Image* saveIconImg;
		Image* loadIconImg;
		
		Button* ToolButtons[NUM_BUTTONS];
		int n_ToolButtons;
		
		Button* MotionButtons[NUM_BUTTONS];
		int n_MotionButtons;
		
		Button* PlayButtons[NUM_BUTTONS];
		int n_PlayButtons;
		
		Button* JointButtons[NUM_BUTTONS];
		int n_JointButtons;
		
		Button* PenButtons[2];
		int n_PenButtons;
		
		Button* hideMenuButton;
		Button* showSettingsButton;
		
		Button* loadButton;
		Button* saveButton;
		
		Button* resetButton;
		
};

#endif //_ToolBox_H_
