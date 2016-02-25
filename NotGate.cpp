/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Implementation of a NOT Logical Gate
 *
 */

#include "NotGate.h"

#ifndef DEBUG
//	#define DEBUG
#endif

NotGate::NotGate( const std::string& name, std::vector< Component* >& inputs ) :
	LogicalGate( name, inputs, "NOT" )
{	}

NotGate::~NotGate()
{
#ifdef DEBUG
	fprintf( stdout, "NotGate::~NotGate Destroying %s @ %p\n",
				_name.c_str(),
				this );
	fflush( stdout );
#endif
}

int NotGate::compute()
{
	int result;
	// Checking if this gate has some issues
	if( get_status() == GateStatus::correct )
		result = !( _inputs.at( 0 )->get_value() );
	else
		result = get_status_value();

	return result;
}


