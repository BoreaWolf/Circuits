/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a single Component of a Circuit
 * I'll use the inheritance and use this class as the father
 *
 */

#ifndef COMPONENT
#define COMPONENT

#include <string>

class Component
{
	public:
		//	No sense for this to be created
		//	Component( std::string );
		//	~Component();

		std::string get_name(){ return _name; }

		int get_value(){ return _value; }
		void set_value( int value ){ _value = value; }
	
	protected:
		std::string _name;
		int _value;
};

#endif

