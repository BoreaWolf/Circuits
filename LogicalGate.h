/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents an Input Terminal of a Circuit
 *
 */

#ifndef LOGICAL_GATE
#define LOGICAL_GATE

#include "Component.h"
#include "GateStatus.h"

#include <vector>

class LogicalGate : public Component
{
	public:
		LogicalGate();
		~LogicalGate();

		virtual int compute() = 0;
	
	protected:
		std::vector< Component* > _inputs;
		GateStatus _status;
};

#endif


