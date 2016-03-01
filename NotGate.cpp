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
#ifdef DEBUG
	fprintf( stdout, "NotGate::compute computing %lu: ", _inputs.size() );
#endif

	// Checking if this gate has some issues
	if( get_status() == GateStatus::correct )
	{
		_value = !( _inputs.at( 0 )->get_value() );

#ifdef DEBUG
		fprintf( stdout, "%d(%d) ", _inputs.at( 0 )->get_value(), _value );
#endif
	}
	else
	{
		_value = get_status_value();

#ifdef DEBUG
		fprintf( stdout, "stuck to %d ", _value );
#endif
	}

#ifdef DEBUG
	fprintf( stdout, "= computed %d\n", _value );
#endif

	return _value;
}


