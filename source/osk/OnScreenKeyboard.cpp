#include "OnScreenKeyboard.h"

#include "fontMap.h"

extern u8 blank_kbd_png[];
extern u8 key_zoom_png[];
extern u8 pointer_png[];

OnScreenKeyboard::OnScreenKeyboard(GameWindow* gw, char* key_config_file):
manager(3)
{

   pos_x = 0;
   pos_y = 0;
   gwd = gw;
   keys = new KeyCollection();
   keys->InitKeys(key_config_file);

   if(kbd_surface.LoadImage(blank_kbd_png, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)exit(0);
   if(zoom_key_surface.LoadImage(key_zoom_png, IMG_LOAD_TYPE_BUFFER)!= IMG_LOAD_ERROR_NONE)exit(0);
   if(pointer_surface.LoadImage(pointer_png, IMG_LOAD_TYPE_BUFFER)!= IMG_LOAD_ERROR_NONE)exit(0);
   
    Image* fontImg = new Image();
	fontImg->LoadImage(fontMap, IMG_LOAD_TYPE_BUFFER);
	font = new Font(fontImg, 13, 24);

   s32 cols;
   s32 rows;
   
   cols = keys->text_w / keys->font_width;
   rows = keys->text_h / keys->font_height;

   text = new Text(200,1);
   text->SetFont(font);
   
   kbd.SetImage(&kbd_surface);
   zoom_key.SetImage(&zoom_key_surface);
   pointer.SetImage(&pointer_surface);

   zoom_key.SetTransparency(0);
   zoom_key.SetPosition(0,0);

}

OnScreenKeyboard::~OnScreenKeyboard()
{

}

int OnScreenKeyboard::RenderText(char* Text, int x, int y)
{
   text->SetText(Text);
   text->SetPosition(x, y);
   text->draw();
   return 0;
}

void OnScreenKeyboard::DrawKeyboard()
{
   OSK::Key key;

   kbd.SetPosition(0,0);
   kbd.Draw();
   
   if(return_string.size() > 0)
      RenderText((char*)(return_string.c_str()), keys->text_x, keys->text_y);

   for(int i=0; i < keys->GetKeyCount(); i++)
   {
      key = keys->GetKey(i);
      if((keys->shift || keys->caps) && !(key.control))
      {
         RenderText(key.shift_val,key.x,key.y);
      }
      else if(!(key.control))
      {
         RenderText(key.val,key.x,key.y);
      }
   }

   //Draw Zoom Key
   key = keys->GetSelected(pos_x, pos_y);
   zoom_key.SetTransparency(0);
   if(key.valid)
   {
        selected_text = key.val;

        if((keys->shift || keys->caps) && !(key.control))
        {
           zoom_key.SetPosition(key.x-zoom_key_surface.GetWidth()/4, key.y-zoom_key_surface.GetHeight()/4);
           zoom_key.SetTransparency(255);
		   zoom_key.Draw();
           RenderText(key.shift_val,key.x,key.y);
           selected_text = key.shift_val;
        }
        else if(!(key.control))
        {
           zoom_key.SetPosition(key.x-zoom_key_surface.GetWidth()/4, key.y-zoom_key_surface.GetHeight()/4);
           zoom_key.SetTransparency(255);
		   zoom_key.Draw();
           RenderText(key.val,key.x,key.y);
        }
   }
   else
   {
      selected_text = "";
   }
   
   pointer.Draw();
   if(gwd->IsInitialized())
   {
     gwd->Flush();
   } else {
      gwd->InitVideo();
   }

}


char* OnScreenKeyboard::GetString()
{
   while(1)
   {
      WPAD_ScanPads();
      u32 pressed = WPAD_ButtonsDown(WPAD_CHAN_0);

      if(pressed & WPAD_BUTTON_HOME) return NULL;

      ir_t ir;
      WPAD_IR(WPAD_CHAN_0, &ir);
      pointer.SetPosition(ir.sx-200, ir.sy-250);
	  
      pointer.SetRotation(ir.angle/2);
      pos_x = ir.sx-200;
      pos_y = ir.sy-250;

      if(pressed & WPAD_BUTTON_A)
      {
            if(strcmp(selected_text,"BACKSPACE")==0)
            {
               if(return_string.size()>0)
                  return_string.erase(return_string.size()-1);
            }
            else if(strcmp(selected_text,"RETURN")==0)
            {
               return_string.append("\n");
            }
            else if(strcmp(selected_text,"CAPS")==0)
            {
               keys->caps = !(keys->caps);
            }
            else if(strcmp(selected_text,"SHIFT")==0)
            {
               keys->shift = !(keys->shift);
            }
            else if(strcmp(selected_text,"LANG")==0)
            {
               //TODO Change Lang
            }
            else if(strcmp(selected_text,"OK")==0)
            {
               return (char*)(return_string.c_str());
            }
            else if(strcmp(selected_text,"QUIT")==0)
            {
               return NULL;
            }
            else
            {
               keys->shift = false;
               return_string.append(selected_text);
            }
      }
      
      DrawKeyboard();
   }   

   return NULL;
}

char* OnScreenKeyboard::EditString(char* str)
{
   char* ret = NULL;
   return_string.clear();
   if(str != NULL)
      return_string.append(str);
   ret = GetString();
   if(ret == NULL) return str;
   return ret;
}
