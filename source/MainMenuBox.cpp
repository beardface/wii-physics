#include "MainMenuBox.h"
#include <fat.h>
#include <unistd.h>

//Images
#include "bigButton.h"
#include "bigButtonOver.h"
#include "bigButtonDown.h"
#include "playButton.h"
#include "helpButton.h"
#include "quitButton.h"
#include "supportButton.h"

MainMenuBox::MainMenuBox()
{
	//Button Images
	bigButtonImg     = new Image();
	bigButtonOverImg = new Image();
	bigButtonDownImg = new Image();
	playButtonImg = new Image();
	helpButtonImg = new Image();
	quitButtonImg = new Image();
	supportButtonImg = new Image();
	
	if(bigButtonImg->LoadImage(bigButton, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(bigButtonOverImg->LoadImage(bigButtonOver, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(bigButtonDownImg->LoadImage(bigButtonDown, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(playButtonImg->LoadImage(playButton, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	
	if(helpButtonImg->LoadImage(helpButton, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(quitButtonImg->LoadImage(quitButton, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	if(supportButtonImg->LoadImage(supportButton, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
		
	playMenuButton = new Button(PLAY_X, PLAY_Y, bigButtonImg, bigButtonOverImg, bigButtonDownImg, playButtonImg);
	menu_state = false;
	show_help  = false;
	show_support  = false;
	do_quit    = false;
	
	helpMenuButton = new Button(HELP_X, HELP_Y, bigButtonImg, bigButtonOverImg, bigButtonDownImg, helpButtonImg);
	
	quitMenuButton = new Button(QUIT_X, QUIT_Y, bigButtonImg, bigButtonOverImg, bigButtonDownImg, quitButtonImg);

	supportMenuButton = new Button(SUPPORT_X, SUPPORT_Y, bigButtonImg, bigButtonOverImg, bigButtonDownImg, supportButtonImg);
	
	ResetSubs();
	ResetSinglePressButtons();
	lastHover = 0;
	firstHover = false;
}	

MainMenuBox::~MainMenuBox()
{

}
	
void MainMenuBox::ClearAllHover()
{
	playMenuButton->ClearHover();
	helpMenuButton->ClearHover();
	quitMenuButton->ClearHover();
	supportMenuButton->ClearHover();
}

void MainMenuBox::ResetSubs()
{

}

	
bool MainMenuBox::HoverButton(u32 x, u32 y)
{
	ClearAllHover();
	firstHover = false;
	
	if(playMenuButton->IsPointerOver(x,y))
	{
		ResetSubs();
		
		if(lastHover != 1)
		{
			lastHover = 1;
			firstHover = true;
		}
		
		return true;
	}
	
	if(helpMenuButton->IsPointerOver(x,y))
	{
		ResetSubs();
		
		if(lastHover != 2)
		{
			lastHover = 2;
			firstHover = true;
		}
		
		return true;
	}
	
	if(quitMenuButton->IsPointerOver(x,y))
	{
		ResetSubs();
		
		if(lastHover != 3)
		{
			lastHover = 3;
			firstHover = true;
		}
		
		return true;
	}
	
	if(supportMenuButton->IsPointerOver(x,y))
	{
		ResetSubs();
		
		if(lastHover != 4)
		{
			lastHover = 4;
			firstHover = true;
		}
		
		return true;
	}
	lastHover = 0;
	ResetSubs();
	return false;
}

bool MainMenuBox::PressButton(u32 x, u32 y)
{
	show_help = false;
	show_support = false;
	do_quit   = false;
	
	if(playMenuButton->Select(x,y))
	{
		menu_state = false;
		ResetSinglePressButtons();
		return true;
	}
	
	if(helpMenuButton->Select(x,y))
	{
		show_help = true;
		ResetSinglePressButtons();
		return true;
	}
	
	if(quitMenuButton->Select(x,y))
	{
		do_quit = true;
		ResetSinglePressButtons();
		return true;
	}
	
	if(supportMenuButton->Select(x,y))
	{
		show_support = true;
		ResetSinglePressButtons();
		return true;
	}
	return false;
}

void MainMenuBox::ResetSinglePressButtons()
{
	playMenuButton->Deselect();
	helpMenuButton->Deselect();
	quitMenuButton->Deselect();
	supportMenuButton->Deselect();
}

void MainMenuBox::Draw(int drift)
{
	playMenuButton->Draw(0);
	helpMenuButton->Draw(0);
	quitMenuButton->Draw(0);
	supportMenuButton->Draw(0);
	
}



	