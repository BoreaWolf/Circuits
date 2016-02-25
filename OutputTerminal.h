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

		void calculate_cone();
		void calculate_value();

		int get_value();
		void print_value( FILE* = stdout );

	private:
		// Pointer to the corresponding gate
		Component* _gate;
};

#endif


