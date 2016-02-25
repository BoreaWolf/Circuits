/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Implementation of the Logical Gate class
 *
 */

#include "LogicalGate.h"

#ifndef DEBUG
//	#define DEBUG
#endif

LogicalGate::LogicalGate()
{	}

LogicalGate::LogicalGate( const std::string& name,
						  std::vector< Component* >& inputs,
						  const std::string& subclass_name )
{
	_name = name;
	_inputs = inputs;
	_status = GateStatus::correct;
	_value = GATE_UNKNOWN_VALUE;
	
	// Initializing and calculating the cone
	calculate_cone();
	
#ifdef DEBUG
	fprintf( stdout, "LogicalGate::LogicalGate '%s' Created %s @ %p: ",
				subclass_name.c_str(),
				_name.c_str(),
				this );
	for( size_t i = 0; i < _inputs.size(); i++ )
		fprintf( stdout, "%s(%p) ",
					_inputs.at( i )->get_name().c_str(),
					_inputs.at( i ) );
	fflush( stdout );
#endif
}

LogicalGate::~LogicalGate()
{
#ifdef DEBUG
	fprintf( stdout, "LogicalGate::~LogicalGate Destroying %s @ %p\n",
				_name.c_str(),
				this );
	fflush( stdout );

#endif
}

void LogicalGate::calculate_cone()
{
	// Calculating the cone of the current gate, since I already know every
	// Component before this one
	//	_cone = std::vector< std::string >();
	_cone = GateCone();
	
	// The cone is made by the name of the current gate followed by the names of
	// all the others gate before him, so I'm adding the current gate in the
	// first position and then I'll add all the others, checking that they are
	// Gates and not InputTerminals
	
	// Current Gate
	_cone.insert( _name );
	// Cycling on the inputs and adding them only if they are Gates
	for( size_t i = 0; i < _inputs.size(); i++ )
		_cone.join( _inputs.at( i )->get_cone() );
}
