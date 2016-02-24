/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents an Input Terminal of a Circuit
 *
 */

#ifndef INPUT_TERMINAL
#define INPUT_TERMINAL

#include "Component.h"

class InputTerminal : public Component
{
	public:
		InputTerminal( std::string name )
		{
			_name = name;

			fprintf( stdout, "InputTerminal::InputTerminal Created %s @ %p\n",
						_name.c_str(),
						this );
			fflush( stdout );
		}

		~InputTerminal()
		{
			fprintf( stdout, "InputTerminal::~InputTerminal Destroying %s @ %p\n",
						_name.c_str(),
						this );
		}
};

#endif


