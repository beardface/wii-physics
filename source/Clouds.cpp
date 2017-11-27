#include "Clouds.h"

#include "math.h"

#include "cloud.h"

Clouds::Clouds(int num_clouds, float min_x, float max_x, float min_y, float max_y)
{
	_min_x = min_x;
	_max_x = max_x;

	_min_y = min_y;
	_max_y = max_y;
	
	cloudImage = new Image();
	if(cloudImage->LoadImage(cloud, IMG_LOAD_TYPE_BUFFER) != IMG_LOAD_ERROR_NONE)
		exit(0);
	
	cloudSprite.SetImage(cloudImage);
	
	for(int i = 0; i < num_clouds; i++)
	{
		Cloud::Type newCloud;

		//random transparenecy (1-255)
		newCloud.trans = 1 + (rand() % 255);
		
		newCloud.zoom = 0.8 + (newCloud.trans/255.0);
		
		//random x and y
		newCloud.x = (rand() % (int)(_max_x - _min_x)) - _max_x;
		newCloud.y = (rand() % (int)(_max_y - _min_y)) - _max_y +100; //200 to bump clouds off ground
	
		cloudList.push_back(newCloud);
	}
}

Clouds::~Clouds()
{

}
		
void Clouds::Update()
{
	for(int i = 0; i < (int)cloudList.size(); i++)
	{
		cloudList.at(i).x = cloudList.at(i).x - ((cloudList.at(i).trans / 255)*(cloudList.at(i).trans / 255));
		
		//wrap clouds
		if(cloudList.at(i).x <= (_min_x - cloudSprite.GetWidth()))
		{
			cloudList.at(i).x = _max_x + 640;
		}
	}
}
		
void Clouds::Draw(float x_offset, float y_offset)
{
	for(int i = 0; i < (int)cloudList.size(); i++)
	{
		cloudSprite.SetPosition(cloudList.at(i).x , cloudList.at(i).y);
		cloudSprite.SetTransparency(cloudList.at(i).trans);
		cloudSprite.SetZoom(cloudList.at(i).zoom);
		
		cloudSprite.Draw(x_offset, y_offset);
	}
}
