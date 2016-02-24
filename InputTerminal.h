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

#include <string>

class InputTerminal : public Component
{
	public:
		InputTerminal( const std::string& );
		~InputTerminal();
};

#endif


