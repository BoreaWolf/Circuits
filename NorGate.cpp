/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Class that represents a NOR Logical Gate
 *
 */

#include "NorGate.h"

#ifndef DEBUG
//	#define DEBUG
#endif

NorGate::NorGate( const std::string& name, std::vector< Component* >& inputs ) :
	LogicalGate( name, inputs, "NOR" )
{	}

NorGate::~NorGate()
{
#ifdef DEBUG
	fprintf( stdout, "NorGate::~NorGate Destroying %s @ %p\n",
				_name,
				this );
	fflush( stdout );
#endif
}

int NorGate::compute()
{
	int result;
	// Checking if this gate has some issues
	if( get_status() == GateStatus::correct )
	{
		result = _inputs.at( 0 )->get_value();
		for( size_t i = 1; i < _inputs.size(); i++ )
			result = ~( result | _inputs.at( i )->get_value() );
	}
	else
		result = get_status_value();

	return result;
}


