/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a Logical Gate
 *
 */

#ifndef LOGICAL_GATE
#define LOGICAL_GATE

#include "Component.h"
#include "GateStatus.h"

#include <string>
#include <vector>

class LogicalGate : public Component
{
	public:
		LogicalGate();
		LogicalGate( const std::string&,
					 std::vector< Component* >&,
					 const std::string& = std::string() );
		~LogicalGate();

		void calculate_cone();
		// TODO: Fix this stuff
		virtual int compute() = 0;
		void calculate_value(){ compute(); }

	protected:
		// Inputs of the gate
		std::vector< Component* > _inputs;
};

#endif

