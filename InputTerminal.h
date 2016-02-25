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

		void calculate_cone();
		// This method is not needed here because it's useless, but I need it
		// anyway, so I'll just implement if empty
		void calculate_value();
};

#endif


