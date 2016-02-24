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


