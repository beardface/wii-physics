#ifndef _OSK_TYPES_H_
#define _OSK_TYPES_H_

namespace OSK{
  typedef struct{
      bool valid;
      bool control;
      double x;
      double y;
      int w;
      int h;
      char* val;
      char* shift_val;
   }Key;
};
#endif //_OSK_TYPES_H_
