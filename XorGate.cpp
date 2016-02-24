/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Implementation of a XOR Logical Gate
 *
 */

#include "XorGate.h"

#ifndef DEBUG
//	#define DEBUG
#endif

XorGate::XorGate( const std::string& name, std::vector< Component* >& inputs ) :
	LogicalGate( name, inputs, "XOR" )
{	}

XorGate::~XorGate()
{
#ifdef DEBUG
	fprintf( stdout, "XorGate::~XorGate Destroying %s @ %p\n",
				_name.c_str(),
				this );
	fflush( stdout );
#endif
}

int XorGate::compute()
{
	int result;
	// Checking if this gate has some issues
	if( get_status() == GateStatus::correct )
	{
		result = _inputs.at( 0 )->get_value();
		for( size_t i = 1; i < _inputs.size(); i++ )
			result ^= _inputs.at( i )->get_value();
	}
	else
		result = get_status_value();

	return result;
}

