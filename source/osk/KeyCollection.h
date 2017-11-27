#ifndef _KeyCollection_H_
#define _KeyCollection_H_

#include <vector>
#include "osk_types.h"

class KeyCollection{

   public:

      KeyCollection();
      ~KeyCollection();

      void InitKeys(char* key_file);
      OSK::Key GetSelected(double x, double y);

      int GetKeyCount(){return keys.size();}
      OSK::Key GetKey(int i){return keys.at(i);}

      bool shift;
      bool caps;
      char* bg_file_name;
      char* zoom_file_name;
      char* pointer_file_name;
      char* font_file_name;
      int font_width;
	  int font_height;
      int text_w;
      int text_h;
      int text_x;
      int text_y;
   private:
      void AddKey(int h, int w, double x, double y, char* val, char* shift_val, int control);

      std::vector<OSK::Key> keys;
      int depth;
      
};

#endif //_KeyCollection_H_
