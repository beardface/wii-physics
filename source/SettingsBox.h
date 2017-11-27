#ifndef _SettingsBox_H_
#define _SettingsBox_H_

#include "wiisprite.h"
#include "WiiStackTypes.h"
#include "Button.h"
#include "tiledtextlayer.h"

using namespace wsp;
using namespace WiiStackTypes;

class SettingsBox {
	
	public:
	
		SettingsBox();
		~SettingsBox();
		
		bool HoverButton(u32 x, u32 y);
		bool PressButton(u32 x, u32 y);
		
		Gravity::Type GetGravityMode();
		f32 GetRestitution();
		f32 GetFriction();
		f32 GetDensity();
		
		void SetDisplayed(bool s){menu_state = s;}
		
		//return true if shown
		bool Displayed(){return menu_state;}
		
		void SetModes(Gravity::Type gravity_mode, f32 restitution, f32 friction, f32 density);
		void ResetSinglePressButtons();
		void Draw(int drift = 0);
		GXColor GetColor(){return CurrentColor;}
		void SetColor(GXColor c){CurrentColor = c;}
		bool IsSoundEnabled(){return SoundEnabled;}
		void SetSoundEnabled(bool b){SoundEnabled = b;}
		bool IsFirstHover(){return firstHover;}
		void DrawText(char* txt, int x, int y);
	private:
	
		f32 CurrentRestitution;
		f32 CurrentFriction;
		f32 CurrentDensity;
		Gravity::Type CurrentGravity;
		GXColor CurrentColor;
		bool SoundEnabled;
		
		bool firstHover;
		int lastHover;
		void ClearAllHover();
		void ResetSubs();
		
		bool menu_state;
		
		Image* btnImg;
		Image* btnOverImg;
		Image* btnDownImg;
		
		Image* bigButtonImg;
		Image* bigButtonOverImg;
		Image* bigButtonDownImg;
	
		Image* earthIconImg;
		Image* moonIconImg;
		Image* jupiterIconImg;
	
		Image* plusIconImg;
		Image* minusIconImg;
	
		Image* backButtonImg;
	
		
		Button* GravityButtons[3];
		
		Button* FrictionButtons[2];
		
		Button* RestitutionButtons[2];
		
		Button* DensityButtons[2];
		
		Button* backMenuButton;
		
		
		Button* RedButtons[2];
		Button* GreenButtons[2];
		Button* BlueButtons[2];
		Button* AlphaButtons[2];
		
		Image* fontImg;
		Font* font;
		Text* textLayer;
		
		Rectangle rect;
		Quad quad;

};

#endif //_SettingsBox_H_
