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
		Component( std::string );
		~Component();

		int get_value(){ return _value; }

		std::string get_name(){ return _name; }
	
	protected:
		std::string _name;
		int _value;
};

#endif

