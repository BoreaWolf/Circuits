/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Implementation of a XNOR Logical Gate
 *
 */

#include "XnorGate.h"

#ifndef DEBUG
//	#define DEBUG
#endif

XnorGate::XnorGate( const std::string& name, std::vector< Component* >& inputs ) :
	LogicalGate( name, inputs, "XNOR" )
{	}

XnorGate::~XnorGate()
{
#ifdef DEBUG
	fprintf( stdout, "XnorGate::~XnorGate Destroying %s @ %p\n",
				_name.c_str(),
				this );
	fflush( stdout );
#endif
}

int XnorGate::compute()
{
#ifdef DEBUG
	fprintf( stdout, "XnorGate::compute computing %lu: ", _inputs.size() );
#endif

	// Checking if this gate has some issues
	if( get_status() == GateStatus::correct )
	{
		_value = _inputs.at( 0 )->get_value();

#ifdef DEBUG
		fprintf( stdout, "%d ", _value );
#endif

		for( size_t i = 1; i < _inputs.size(); i++ )
		{
			_value = !( _value ^ _inputs.at( i )->get_value() );

#ifdef DEBUG
			fprintf( stdout, "%d(%d) ", _inputs.at( i )->get_value(), _value );
#endif
		}
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

