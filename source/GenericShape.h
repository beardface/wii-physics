#ifndef _GenericShape_H_
#define _GenericShape_H_


class GenericShape
{
	public:
		GenericShape(bool fixed){_fixed = fixed; _id = 0;}
		virtual ~GenericShape(){};
		
		void SetFixed(bool b){_fixed = b;}
		bool GetFixed(){return _fixed;}
		
		void SetId(int i){_id = i;}
		int GetId(){return _id;}
		
	private:
		bool _fixed;
		int _id;
		
};

#endif //_GenericShape_H_

	
