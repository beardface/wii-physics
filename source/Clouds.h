#ifndef _Clouds_H_
#define _Clouds_H_

#include "wiisprite.h"
#include <vector>

using namespace wsp;

namespace Cloud {
	typedef struct {
		float x;
		float y;
		
		float zoom;
		
		float trans;
		
	} Type;
}

class Clouds  {
	public:
		Clouds(int num_clouds, float min_x, float max_x, float min_y, float max_y);
		~Clouds();
		
		void Update();
		
		void Draw(float x_offset, float y_offset);
	
	private:
		std::vector<Cloud::Type> cloudList;
		float _min_x;
		float _max_x;
		float _min_y;
		float _max_y;
		
		Image* cloudImage;
		Sprite cloudSprite;
};

#endif //_Clouds_H_
