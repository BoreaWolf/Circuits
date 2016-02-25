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

#include "GateCone.h"
#include "GateStatus.h"

#include <string>

class Component
{
	public:
		//	No sense for this to be created
		//	Component( std::string );
		//	~Component();
		
		virtual void calculate_cone() = 0;
		virtual void calculate_value() = 0;

		std::string& get_name(){ return _name; }

		int get_value(){ return _value; }
		void set_value( int value ){ _value = value; }

		GateCone& get_cone(){ return _cone; }

		GateStatus& get_status(){ return _status; }
		int get_status_value(){ return static_cast<int>( _status ); }
		void set_status( const std::string& );

		void print_value( FILE* = stdout );
	
	protected:
		std::string _name;
		int _value;
		// Cone: dependencies of the current gate
		GateCone _cone;
		// Status: if it is working correctly or not
		GateStatus _status;
};

#endif

