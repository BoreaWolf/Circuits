/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents an Output Terminal of a Circuit
 *
 */

#ifndef OUTPUT_TERMINAL
#define OUTPUT_TERMINAL

#include "Component.h"

#include <string>

class OutputTerminal : public Component
{
	public:
		OutputTerminal( const std::string&, Component* );
		~OutputTerminal();

	private:
		// Pointer to the corresponding gate
		Component* _gate;
};

#endif


