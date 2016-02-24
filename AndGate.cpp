/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Implementation of the AND Gate
 *
 */
#include "AndGate.h"

#ifndef DEBUG
//	#define DEBUG
#endif

AndGate::AndGate( const std::string& name, std::vector< Component* >& inputs ) :
	LogicalGate( name, inputs, "AND" )
{	}

AndGate::~AndGate()
{
#ifdef DEBUG
	fprintf( stdout, "AndGate::~AndGate Destroying %s @ %p\n",
				_name,
				this );
	fflush( stdout );
#endif
}

int AndGate::compute()
{
	int result;
	// Checking if this gate has some issues
	if( get_status() == GateStatus::correct )
	{
		result = _inputs.at( 0 )->get_value();
		for( size_t i = 1; i < _inputs.size(); i++ )
			result &= _inputs.at( i )->get_value();
	}
	else
		result = get_status_value();

	return result;
}


