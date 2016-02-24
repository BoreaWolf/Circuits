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

