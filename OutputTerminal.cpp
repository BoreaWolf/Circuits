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

