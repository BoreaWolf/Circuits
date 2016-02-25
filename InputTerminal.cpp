/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Implementation of an Input Terminal of a Circuit
 *
 */

#include "InputTerminal.h"

#ifndef DEBUG
//	#define DEBUG
#endif

InputTerminal::InputTerminal( const std::string& name )
{
	_name = name;
	_value = GATE_UNKNOWN_VALUE;
	calculate_cone();

#ifdef DEBUG
	fprintf( stdout, "InputTerminal::InputTerminal Created %s @ %p\n",
				_name.c_str(),
				this );
	fflush( stdout );
#endif
}

InputTerminal::~InputTerminal()
{
#ifdef DEBUG
	fprintf( stdout, "InputTerminal::~InputTerminal Destroying %s @ %p\n",
				_name.c_str(),
				this );
	fflush( stdout );
#endif
}

void InputTerminal::calculate_cone()
{
	// For the Input Terminal, the Cone is nothing else than an empty cone
	_cone = GateCone();
}

void InputTerminal::calculate_value()
{	}
