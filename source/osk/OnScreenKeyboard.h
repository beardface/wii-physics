#ifndef _OnScreenKeyboard_H_
#define _OnScreenKeyboard_H_

#include <wiiuse/wpad.h>

#include <ogcsys.h>
#include <gccore.h>
#include <ogc/ipc.h>

#include "fat.h"
#include "wiisprite.h"
#include "tiledtextlayer.h"

#include "KeyCollection.h"
#include "osk_types.h"
#include <string>

using namespace wsp;

class OnScreenKeyboard {

   public:
 
      OnScreenKeyboard(GameWindow* gw, char* key_config_file);
      ~OnScreenKeyboard();

      char* GetString();
      char* EditString(char* str);
      
   private:
      void DrawKeyboard();
      void DrawZoomKey();

      void* screen_ptr;
      void* mouse_ptr; 
      int RenderText(char* Text, int x, int y);
      double pos_x;
      double pos_y;

      Font* font;
	  Text*  text;

      GameWindow* gwd;
	  
      Image kbd_surface;
      LayerManager manager;
      Image zoom_key_surface;
      Image pointer_surface;
      Sprite kbd;
      Sprite zoom_key;
      Sprite pointer;
      
      std::string return_string;
      char* selected_text;
      KeyCollection* keys;
      int language;
};

#endif //_OnScreenKeyboard_H_
