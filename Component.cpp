/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Implementation of the Component class
 *
 */

#include "Component.h"

#ifndef DEBUG
//	#define DEBUG
#endif

//	Component::Component( std::string name )
//	{
//		_name = name;
//		_value = 0;
//		fprintf( stdout, "Component::Component %s Created %p\n",
//					_name.c_str(),
//					this );
//	}
//	
//	Component::~Component()
//	{
//		fprintf( stdout, "Component::~Component %s Destroying %p\n",
//					_name.c_str(),
//					this );
//	}
//	

void Component::set_status( const std::string& status )
{
#ifdef DEBUG
	fprintf( stdout, "Component::set_status '%s' %d",
				status.c_str(),
				get_status_value() );
#endif

	if( status.compare( "s0" ) == 0 )
		_status = GateStatus::stuck_to_zero;
	else if( status.compare( "s1" ) == 0 )
			_status = GateStatus::stuck_to_one;

#ifdef DEBUG
	fprintf( stdout, " => %d\n", get_status_value() );
#endif
}

void Component::print_value( FILE* file )
{
	fprintf( file, "'%s' = %d\n", _name.c_str(), _value );
}
