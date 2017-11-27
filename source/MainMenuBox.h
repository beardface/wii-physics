#ifndef _MainMenuBox_H_
#define _MainMenuBox_H_

#include "wiisprite.h"
#include "WiiStackTypes.h"
#include "Button.h"

using namespace wsp;
using namespace WiiStackTypes;

class MainMenuBox {
	
	public:
	
		MainMenuBox();
		~MainMenuBox();
		
		bool HoverButton(u32 x, u32 y);
		bool PressButton(u32 x, u32 y);
		
		void SetDisplayed(bool s){menu_state = s;}
		bool Displayed(){return menu_state;}
		
		
		void SetShowHelp(bool s){show_help = s;}
		bool ShowHelp(){return show_help;}
		
		
		void SetShowSupport(bool s){show_support = s;}
		bool ShowSupport(){return show_support;}
		
		void SetQuit(bool s){do_quit = s;}
		bool Quit(){return do_quit;}
		
		void ResetSinglePressButtons();
		
		void Draw(int drift = 0);
		
		bool IsFirstHover(){return firstHover;}
	private:
	
		bool menu_state;
		bool show_help;
		bool show_support;
		bool do_quit;
		
		bool firstHover;
		int lastHover;
		void ClearAllHover();
		void ResetSubs();
		
		Image* bigButtonImg;
		Image* bigButtonOverImg;
		Image* bigButtonDownImg;
	
		Image* playButtonImg;
		Image* helpButtonImg;
		Image* supportButtonImg;
		Image* quitButtonImg;
		
		Button* playMenuButton;
		Button* helpMenuButton;
		Button* quitMenuButton;
		Button* supportMenuButton;

};

#endif //_MainMenuBox_H_
