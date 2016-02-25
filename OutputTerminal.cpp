/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Implementation of an Output Terminal of a Circuit
 *
 */

#include "OutputTerminal.h"

#ifndef DEBUG
//	#define DEBUG
#endif

OutputTerminal::OutputTerminal( const std::string& name, Component* gate )
{
	_name = name;
	_gate = gate;
	_value = GATE_UNKNOWN_VALUE;

	calculate_cone();

#ifdef DEBUG
	fprintf( stdout, "OutputTerminal::OutputTerminal Created %s @ %p ref to %s(%p)\n",
				_name.c_str(),
				this,
				_gate->get_name().c_str(),
				_gate );
	fflush( stdout );
#endif
}

OutputTerminal::~OutputTerminal()
{
#ifdef DEBUG
	fprintf( stdout, "OutputTerminal::~OutputTerminal Destroying %s @ %p\n",
				_name.c_str(),
				this );
	fflush( stdout );
#endif
}

void OutputTerminal::calculate_cone()
{
	// TODO: Not really sure about this
	_cone = _gate->get_cone();
}

void OutputTerminal::calculate_value()
{
	if( get_value() == GATE_UNKNOWN_VALUE )
		set_value( _gate->get_value() );
}

int OutputTerminal::get_value()
{
	return _gate->get_value();
}

void OutputTerminal::print_value( FILE* file )
{
	fprintf( file, "'%s' = %d\n",
				get_name().c_str(),
				get_value() );
}
