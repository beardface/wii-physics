#include "SettingsBox.h"
#include <fat.h>
#include <unistd.h>

//Images
#include "Button_Image.h"
#include "Button_Over.h"
#include "Button_Down.h"

#include "earthIcon.h"
#include "jupiterIcon.h"
#include "moonIcon.h"
	
#include "plusIcon.h"
#include "minusIcon.h"
	
#include "fontMap.h"

#include "bigButton.h"
#include "bigButtonOver.h"
#include "bigButtonDown.h"
#include "backButton.h"

SettingsBox::SettingsBox()
{
	//Button Images
	btnImg     = new Image();
	btnOverImg = new Image();
	btnDownImg = new Image();
	
	bigButtonImg     = new Image();
	bigButtonOverImg = new Image();
	bigButtonDownImg = new Image();
	backButtonImg = new Image();
	
	earthIconImg   = new Image();
	moonIconImg    = new Image();
	jupiterIconImg = new Image();
	
	plusIconImg       = new Image();
	minusIconImg      = new Image();
	
	fontImg = new Image();
		
	if(bigButtonImg->LoadImage(bigButton, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(bigButtonOverImg->LoadImage(bigButtonOver, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(bigButtonDownImg->LoadImage(bigButtonDown, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(backButtonImg->LoadImage(backButton, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(fontImg->LoadImage(fontMap, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	//Load Button Images
	if(btnImg->LoadImage(Button_Image, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(btnOverImg->LoadImage(Button_Over, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(btnDownImg->LoadImage(Button_Down, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	//Icon Images
	
	if(earthIconImg->LoadImage(earthIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(moonIconImg->LoadImage(moonIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(jupiterIconImg->LoadImage(jupiterIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(plusIconImg->LoadImage(plusIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	if(minusIconImg->LoadImage(minusIcon, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	
	font = new Font(fontImg, 13, 24);
	textLayer = new Text(200,1);
	textLayer->SetFont(font);
	
	backMenuButton = new Button(BACK_X, BACK_Y, bigButtonImg, bigButtonOverImg, bigButtonDownImg, backButtonImg);
	menu_state = false;
	
	GravityButtons[Gravity::EARTH]    = new Button(EARTH_X, EARTH_Y, btnImg, btnOverImg, btnDownImg, earthIconImg);
	GravityButtons[Gravity::MOON]     = new Button(MOON_X, MOON_Y, btnImg, btnOverImg, btnDownImg, moonIconImg);
	GravityButtons[Gravity::JUPITER]  = new Button(JUPITER_X, JUPITER_Y, btnImg, btnOverImg, btnDownImg, jupiterIconImg);
	
	RestitutionButtons[GenericPlusMinus::MINUS] = new Button(RESTITUTION_MINUS_X, RESTITUTION_MINUS_Y, btnImg, btnOverImg, btnDownImg, minusIconImg);
	RestitutionButtons[GenericPlusMinus::PLUS]  = new Button(RESTITUTION_PLUS_X, RESTITUTION_PLUS_Y, btnImg, btnOverImg, btnDownImg, plusIconImg);

	FrictionButtons[GenericPlusMinus::MINUS]    = new Button(FRICTION_MINUS_X, FRICTION_MINUS_Y, btnImg, btnOverImg, btnDownImg, minusIconImg);
	FrictionButtons[GenericPlusMinus::PLUS]     = new Button(FRICTION_PLUS_X, FRICTION_PLUS_Y, btnImg, btnOverImg, btnDownImg, plusIconImg);

	DensityButtons[GenericPlusMinus::MINUS]     = new Button(DENSITY_MINUS_X, DENSITY_MINUS_Y, btnImg, btnOverImg, btnDownImg, minusIconImg);
	DensityButtons[GenericPlusMinus::PLUS]      = new Button(DENSITY_PLUS_X, DENSITY_PLUS_Y, btnImg, btnOverImg, btnDownImg, plusIconImg);


	RedButtons[GenericPlusMinus::MINUS]     = new Button(R_MINUS_X, R_MINUS_Y, btnImg, btnOverImg, btnDownImg, minusIconImg);
	RedButtons[GenericPlusMinus::PLUS]      = new Button(R_PLUS_X, R_PLUS_Y, btnImg, btnOverImg, btnDownImg, plusIconImg);

	GreenButtons[GenericPlusMinus::MINUS]     = new Button(G_MINUS_X, G_MINUS_Y, btnImg, btnOverImg, btnDownImg, minusIconImg);
	GreenButtons[GenericPlusMinus::PLUS]      = new Button(G_PLUS_X, G_PLUS_Y, btnImg, btnOverImg, btnDownImg, plusIconImg);

	BlueButtons[GenericPlusMinus::MINUS]     = new Button(B_MINUS_X, B_MINUS_Y, btnImg, btnOverImg, btnDownImg, minusIconImg);
	BlueButtons[GenericPlusMinus::PLUS]      = new Button(B_PLUS_X, B_PLUS_Y, btnImg, btnOverImg, btnDownImg, plusIconImg);

	AlphaButtons[GenericPlusMinus::MINUS]     = new Button(A_MINUS_X, A_MINUS_Y, btnImg, btnOverImg, btnDownImg, minusIconImg);
	AlphaButtons[GenericPlusMinus::PLUS]      = new Button(A_PLUS_X, A_PLUS_Y, btnImg, btnOverImg, btnDownImg, plusIconImg);


	RestitutionButtons[GenericPlusMinus::MINUS]->Deselect();
	RestitutionButtons[GenericPlusMinus::PLUS]->Deselect();
	
	FrictionButtons[GenericPlusMinus::MINUS]->Deselect();
	FrictionButtons[GenericPlusMinus::PLUS]->Deselect();
	
	DensityButtons[GenericPlusMinus::MINUS]->Deselect();
	DensityButtons[GenericPlusMinus::PLUS]->Deselect();
	
	RedButtons[GenericPlusMinus::MINUS]->Deselect();
	RedButtons[GenericPlusMinus::PLUS]->Deselect();

	GreenButtons[GenericPlusMinus::MINUS]->Deselect();
	GreenButtons[GenericPlusMinus::PLUS]->Deselect();

	BlueButtons[GenericPlusMinus::MINUS]->Deselect();
	BlueButtons[GenericPlusMinus::PLUS]->Deselect();

	AlphaButtons[GenericPlusMinus::MINUS]->Deselect();
	AlphaButtons[GenericPlusMinus::PLUS]->Deselect();
	
	ResetSubs();
	
	CurrentGravity     = Gravity::EARTH;
	CurrentRestitution = DEFAULT_RESTITUTION;
	CurrentFriction    = DEFAULT_FRICTION;
	CurrentDensity     = DEFAULT_DENSITY;
	
	CurrentColor.r = 0;
	CurrentColor.g = 0;
	CurrentColor.b = 0;
	CurrentColor.a = 255;
	
	SoundEnabled = true;
	lastHover = 0;
	firstHover = false;
}	

SettingsBox::~SettingsBox()
{

}
	
void SettingsBox::ClearAllHover()
{
	backMenuButton->ClearHover();

	GravityButtons[Gravity::EARTH]->ClearHover();
	GravityButtons[Gravity::MOON]->ClearHover();
	GravityButtons[Gravity::JUPITER]->ClearHover();
	
	FrictionButtons[GenericPlusMinus::MINUS]->ClearHover();
	FrictionButtons[GenericPlusMinus::PLUS]->ClearHover();
	
	RestitutionButtons[GenericPlusMinus::MINUS]->ClearHover();
	RestitutionButtons[GenericPlusMinus::PLUS]->ClearHover();
	
	DensityButtons[GenericPlusMinus::MINUS]->ClearHover();
	DensityButtons[GenericPlusMinus::PLUS]->ClearHover();
	
	RedButtons[GenericPlusMinus::MINUS]->ClearHover();
	RedButtons[GenericPlusMinus::PLUS]->ClearHover();
	
	GreenButtons[GenericPlusMinus::MINUS]->ClearHover();
	GreenButtons[GenericPlusMinus::PLUS]->ClearHover();

	BlueButtons[GenericPlusMinus::MINUS]->ClearHover();
	BlueButtons[GenericPlusMinus::PLUS]->ClearHover();

	AlphaButtons[GenericPlusMinus::MINUS]->ClearHover();
	AlphaButtons[GenericPlusMinus::PLUS]->ClearHover();
}

void SettingsBox::ResetSubs()
{

}

	
bool SettingsBox::HoverButton(u32 x, u32 y)
{
	ClearAllHover();
	firstHover = false;
	
	if(backMenuButton->IsPointerOver(x,y))
	{
		ResetSubs();
		
		if(lastHover != 1)
		{
			lastHover = 1;
			firstHover = true;
		}
		
		return true;
	}
	

	if(GravityButtons[Gravity::EARTH]->IsPointerOver(x,y))
	{
		if(lastHover != 2)
		{
			lastHover = 2;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(GravityButtons[Gravity::MOON]->IsPointerOver(x,y))
	{
		if(lastHover != 3)
		{
			lastHover = 3;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(GravityButtons[Gravity::JUPITER]->IsPointerOver(x,y))
	{
		if(lastHover != 4)
		{
			lastHover = 4;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	if(FrictionButtons[GenericPlusMinus::MINUS]->IsPointerOver(x,y))
	{
		if(lastHover != 5)
		{
			lastHover = 5;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(FrictionButtons[GenericPlusMinus::PLUS]->IsPointerOver(x,y))
	{
		if(lastHover != 6)
		{
			lastHover = 6;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	if(DensityButtons[GenericPlusMinus::MINUS]->IsPointerOver(x,y))
	{
		if(lastHover != 7)
		{
			lastHover = 7;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(DensityButtons[GenericPlusMinus::PLUS]->IsPointerOver(x,y))
	{
		if(lastHover != 8)
		{
			lastHover = 8;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	
	if(RestitutionButtons[GenericPlusMinus::MINUS]->IsPointerOver(x,y))
	{
		if(lastHover != 9)
		{
			lastHover = 9;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(RestitutionButtons[GenericPlusMinus::PLUS]->IsPointerOver(x,y))
	{
		if(lastHover != 10)
		{
			lastHover = 10;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	if(GreenButtons[GenericPlusMinus::MINUS]->IsPointerOver(x,y))
	{
		if(lastHover != 11)
		{
			lastHover = 11;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(GreenButtons[GenericPlusMinus::PLUS]->IsPointerOver(x,y))
	{
		if(lastHover != 12)
		{
			lastHover = 12;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	if(BlueButtons[GenericPlusMinus::MINUS]->IsPointerOver(x,y))
	{
		if(lastHover != 13)
		{
			lastHover = 13;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(BlueButtons[GenericPlusMinus::PLUS]->IsPointerOver(x,y))
	{
		if(lastHover != 14)
		{
			lastHover = 14;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	if(RedButtons[GenericPlusMinus::MINUS]->IsPointerOver(x,y))
	{
		if(lastHover != 15)
		{
			lastHover = 15;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(RedButtons[GenericPlusMinus::PLUS]->IsPointerOver(x,y))
	{
		if(lastHover != 16)
		{
			lastHover = 16;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	
	if(AlphaButtons[GenericPlusMinus::MINUS]->IsPointerOver(x,y))
	{
		if(lastHover != 17)
		{
			lastHover = 17;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	if(AlphaButtons[GenericPlusMinus::PLUS]->IsPointerOver(x,y))
	{
		if(lastHover != 18)
		{
			lastHover = 18;
			firstHover = true;
		}
		ResetSubs();
		return true;
	}
	lastHover = 0;
	ResetSubs();
	return false;
}

bool SettingsBox::PressButton(u32 x, u32 y)
{

   //Single Click tool buttons
   //----------------------------------------------------------------------------------------------------
   
	if(backMenuButton->Select(x,y))
	{
		menu_state = false;
		backMenuButton->Deselect();
		return true;
	}
	

	if(DensityButtons[GenericPlusMinus::MINUS]->Select(x,y))
	{
		CurrentDensity -= .25;
		if(CurrentDensity < 1) CurrentDensity = 1;
		
		DensityButtons[GenericPlusMinus::PLUS]->Deselect();
		return true;
	}

	if(DensityButtons[GenericPlusMinus::PLUS]->Select(x,y))
	{
		CurrentDensity += .25;
		if(CurrentDensity > 100) CurrentDensity = 100.0;
		
		DensityButtons[GenericPlusMinus::MINUS]->Deselect();
		return true;
	}
	
	if(FrictionButtons[GenericPlusMinus::MINUS]->Select(x,y))
	{
		CurrentFriction -= .005;
		if(CurrentFriction < 0) CurrentFriction = 0;
		
		FrictionButtons[GenericPlusMinus::PLUS]->Deselect();
		return true;
	}

	if(FrictionButtons[GenericPlusMinus::PLUS]->Select(x,y))
	{
		CurrentFriction += .005;
		if(CurrentFriction > 1) CurrentFriction = 1.0;
		
		FrictionButtons[GenericPlusMinus::MINUS]->Deselect();
		return true;
	}
	
	if(RestitutionButtons[GenericPlusMinus::MINUS]->Select(x,y))
	{
		CurrentRestitution -= .005;
		if(CurrentRestitution < 0) CurrentRestitution = 0;
		
		RestitutionButtons[GenericPlusMinus::PLUS]->Deselect();
		return true;
	}

	if(RestitutionButtons[GenericPlusMinus::PLUS]->Select(x,y))
	{
		CurrentRestitution += .005;
		if(CurrentRestitution > 1) CurrentRestitution = 1.0;
		
		RestitutionButtons[GenericPlusMinus::MINUS]->Deselect();
		return true;
	}

	
	if(RedButtons[GenericPlusMinus::MINUS]->Select(x,y))
	{
		if(CurrentColor.r > 0)
		{
			CurrentColor.r -= 1;
		}
		
		RedButtons[GenericPlusMinus::PLUS]->Deselect();
		return true;
	}

	if(RedButtons[GenericPlusMinus::PLUS]->Select(x,y))
	{
		if(CurrentColor.r < 255)
		{
			CurrentColor.r += 1;
		}
		
		RedButtons[GenericPlusMinus::MINUS]->Deselect();
		return true;
	}
	
	
	if(GreenButtons[GenericPlusMinus::MINUS]->Select(x,y))
	{
		if(CurrentColor.g > 0)
		{
			CurrentColor.g -= 1;
		}
		
		GreenButtons[GenericPlusMinus::PLUS]->Deselect();
		return true;
	}

	if(GreenButtons[GenericPlusMinus::PLUS]->Select(x,y))
	{
		if(CurrentColor.g < 255)
		{
			CurrentColor.g += 1;
		}
		
		GreenButtons[GenericPlusMinus::MINUS]->Deselect();
		return true;
	}
	
	
	if(BlueButtons[GenericPlusMinus::MINUS]->Select(x,y))
	{
		if(CurrentColor.b > 0)
		{
			CurrentColor.b -= 1;
		}
		
		BlueButtons[GenericPlusMinus::PLUS]->Deselect();
		return true;
	}

	if(BlueButtons[GenericPlusMinus::PLUS]->Select(x,y))
	{
		if(CurrentColor.b < 255)
		{
			CurrentColor.b += 1;
		}
		
		BlueButtons[GenericPlusMinus::MINUS]->Deselect();
		return true;
	}
	
	
	if(AlphaButtons[GenericPlusMinus::MINUS]->Select(x,y))
	{
		if(CurrentColor.a > 0)
		{
			CurrentColor.a -= 1;
		}
		
		AlphaButtons[GenericPlusMinus::PLUS]->Deselect();
		return true;
	}

	if(AlphaButtons[GenericPlusMinus::PLUS]->Select(x,y))
	{
		if(CurrentColor.a < 255)
		{
			CurrentColor.a += 1;
		}
		
		AlphaButtons[GenericPlusMinus::MINUS]->Deselect();
		return true;
	}

	//--------------------------------------------------------------------------------------------------
   //End Single Click tool buttons
   

	if(GravityButtons[Gravity::EARTH]->Select(x,y))
	{
		CurrentGravity = Gravity::EARTH;
		GravityButtons[Gravity::MOON]->Deselect();
		GravityButtons[Gravity::JUPITER]->Deselect();
		return true;
	}

	if(GravityButtons[Gravity::MOON]->Select(x,y))
	{
		CurrentGravity = Gravity::MOON;
		GravityButtons[Gravity::EARTH]->Deselect();
		GravityButtons[Gravity::JUPITER]->Deselect();
		return true;
	}
	
	if(GravityButtons[Gravity::JUPITER]->Select(x,y))
	{
		CurrentGravity = Gravity::JUPITER;
		GravityButtons[Gravity::EARTH]->Deselect();
		GravityButtons[Gravity::MOON]->Deselect();
		return true;
	}
	
	return false;
}
	
Gravity::Type SettingsBox::GetGravityMode()
{
	return CurrentGravity;
}

f32 SettingsBox::GetFriction()
{
	return CurrentFriction;
}

f32 SettingsBox::GetRestitution()
{
	return CurrentRestitution;
}

f32 SettingsBox::GetDensity()
{
	return CurrentDensity;
}

void SettingsBox::SetModes(Gravity::Type gravity_mode, f32 restitution, f32 friction, f32 density)
{
	GravityButtons[Gravity::JUPITER]->Deselect();
	GravityButtons[Gravity::EARTH]->Deselect();
	GravityButtons[Gravity::MOON]->Deselect();
	
	GravityButtons[gravity_mode]->SetDown();
	
	CurrentGravity = gravity_mode;
	CurrentRestitution = restitution;
	CurrentFriction = friction;
	CurrentDensity = density;
}

void SettingsBox::DrawText(char* txt, int x, int y)
{
	textLayer->SetText(txt);
	textLayer->SetPosition(x,y);
	textLayer->draw();
}

void SettingsBox::ResetSinglePressButtons()
{
	backMenuButton->Deselect();
	
	FrictionButtons[GenericPlusMinus::PLUS]->Deselect();
	FrictionButtons[GenericPlusMinus::MINUS]->Deselect();
	
	RestitutionButtons[GenericPlusMinus::PLUS]->Deselect();
	RestitutionButtons[GenericPlusMinus::MINUS]->Deselect();
	
	DensityButtons[GenericPlusMinus::PLUS]->Deselect();
	DensityButtons[GenericPlusMinus::MINUS]->Deselect();
	
	RedButtons[GenericPlusMinus::MINUS]->Deselect();
	RedButtons[GenericPlusMinus::PLUS]->Deselect();

	GreenButtons[GenericPlusMinus::MINUS]->Deselect();
	GreenButtons[GenericPlusMinus::PLUS]->Deselect();

	BlueButtons[GenericPlusMinus::MINUS]->Deselect();
	BlueButtons[GenericPlusMinus::PLUS]->Deselect();

	AlphaButtons[GenericPlusMinus::MINUS]->Deselect();
	AlphaButtons[GenericPlusMinus::PLUS]->Deselect();
}
		
void SettingsBox::Draw(int drift)
{
	char buf[120];
	
	textLayer->SetText("Settings:");
	textLayer->SetPosition(240,50);
	textLayer->draw();
	
	backMenuButton->Draw(0);
	
	textLayer->SetText("World Settings:");
	textLayer->SetPosition(150,80);
	
	textLayer->SetText("Gravity:");
	textLayer->SetPosition(100,105);
	textLayer->draw();
	
	GravityButtons[Gravity::EARTH]->Draw(drift);
	GravityButtons[Gravity::MOON]->Draw(drift);
	GravityButtons[Gravity::JUPITER]->Draw(drift);	
	
	textLayer->SetText("New Shape Settings:");
	textLayer->SetPosition(125,150);
	textLayer->draw();
	
	sprintf(buf, "Friction               [%1.3f]", CurrentFriction);
	textLayer->SetText(buf);
	textLayer->SetPosition(100,180);
	textLayer->draw();
	
	FrictionButtons[GenericPlusMinus::MINUS]->Draw(drift);
	FrictionButtons[GenericPlusMinus::PLUS]->Draw(drift);

	sprintf(buf, "Restitution (Bounce)   [%1.3f]", CurrentRestitution);
	textLayer->SetText(buf);
	textLayer->SetPosition(100,215);
	textLayer->draw();
	
	RestitutionButtons[GenericPlusMinus::MINUS]->Draw(drift);
	RestitutionButtons[GenericPlusMinus::PLUS]->Draw(drift);

	sprintf(buf, "Density                [%1.3f]", CurrentDensity);
	textLayer->SetText(buf);
	textLayer->SetPosition(100,250);
	textLayer->draw();
	
	DensityButtons[GenericPlusMinus::PLUS]->Draw(drift);
	DensityButtons[GenericPlusMinus::MINUS]->Draw(drift);
	
	//Draw Color chooser and buttons
	
	sprintf(buf, "Color    R[%3d]  G[%3d]  B[%3d]  A[%3d]", CurrentColor.r, CurrentColor.g, CurrentColor.b, CurrentColor.a);
	textLayer->SetText(buf);
	textLayer->SetPosition(30,300);
	textLayer->draw();

	
	RedButtons[GenericPlusMinus::PLUS]->Draw(drift);
	RedButtons[GenericPlusMinus::MINUS]->Draw(drift);
	
	GreenButtons[GenericPlusMinus::PLUS]->Draw(drift);
	GreenButtons[GenericPlusMinus::MINUS]->Draw(drift);
	
	BlueButtons[GenericPlusMinus::PLUS]->Draw(drift);
	BlueButtons[GenericPlusMinus::MINUS]->Draw(drift);
	
	AlphaButtons[GenericPlusMinus::PLUS]->Draw(drift);
	AlphaButtons[GenericPlusMinus::MINUS]->Draw(drift);
	
	rect.x = 550;
	rect.y = 300;
	rect.width = 50;
	rect.height = 50;
	
	quad.SetRectangle(&rect);
	quad.SetFillColor(CurrentColor);
	quad.Draw();
	
}



	