#include "KeyCollection.h"
#include "mxml.h"
#include "fat.h"

#ifdef LINUX
#endif

KeyCollection::KeyCollection()
{
   shift = false;
   caps = false;
}

KeyCollection::~KeyCollection(){}

void KeyCollection::InitKeys(char* key_file)
{
  FILE *fp;
  mxml_node_t *tree;
  mxml_node_t *all_keys;
  mxml_node_t *key;
  mxml_node_t *val;
  mxml_node_t *sub;

  double x, y;
  int w, h;
  char* c;
  char* shift_c;
  int control;
  fp = fopen(key_file, "r");
  
  tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
  fclose(fp);
  all_keys = mxmlFindElement(tree, tree, "keys", NULL, NULL, MXML_DESCEND); 
  bg_file_name = (char*)mxmlElementGetAttr(all_keys,"kbd_bg_file"); 
  zoom_file_name = (char*)mxmlElementGetAttr(all_keys,"zoom_file"); 
  pointer_file_name = (char*)mxmlElementGetAttr(all_keys,"pointer_file"); 
  font_file_name = (char*)mxmlElementGetAttr(all_keys,"font_file"); 
  
  font_width = atoi(mxmlElementGetAttr(all_keys,"font_width"));
  font_height = atoi(mxmlElementGetAttr(all_keys,"font_height"));

  text_h = atoi(mxmlElementGetAttr(all_keys,"text_h"));
  text_w = atoi(mxmlElementGetAttr(all_keys,"text_w"));
  text_x = atoi(mxmlElementGetAttr(all_keys,"text_x"));
  text_y = atoi(mxmlElementGetAttr(all_keys,"text_y"));

  for(key = mxmlFindElement(all_keys, all_keys, "key", NULL, NULL, MXML_DESCEND); 
        key != NULL; 
        key = mxmlFindElement(key, all_keys, "key", NULL, NULL, MXML_DESCEND))
  {
     h = atoi(mxmlElementGetAttr(key,"h"));
     w = atoi(mxmlElementGetAttr(key,"w"));
     x = static_cast<double>(atoi(mxmlElementGetAttr(key,"x")));
     y = static_cast<double>(atoi(mxmlElementGetAttr(key,"y")));
     control = atoi(mxmlElementGetAttr(key,"control"));
     c = (char*) mxmlElementGetAttr(key,"char");
     shift_c = (char*) mxmlElementGetAttr(key,"shift_char");
     AddKey(h,w,x,y,c,shift_c,control);
  }
  printf("Done.\n");
}

OSK::Key KeyCollection::GetSelected(double x, double y)
{
   OSK::Key tkey;
   //printf("Get Selected (%f,%f):\n",x,y);
   for(int i = 0; i < keys.size(); i++)
   {
      tkey = keys.at(i);

      if((x > tkey.x && x < (tkey.x + tkey.w)) &&
         (y > tkey.y && y < (tkey.y + tkey.h)))
      {
       //  printf("Selected Found! (%s)\n",tkey.val);
         return tkey;
      }
   }
   //printf("NO SELECT!\n");
   tkey.valid = false;
   return tkey;
}

void KeyCollection::AddKey(int h, int w, double x, double y, char* val, char* shift_val, int control)
{
   OSK::Key tKey;
   if(control != 1)
      tKey.control = false;
   else
      tKey.control = true;

   tKey.valid = true;
   tKey.h = h;
   tKey.w = w;
   tKey.x = x;
   tKey.y = y;
   tKey.val = val;
   tKey.shift_val = shift_val;
   keys.push_back(tKey);
}

