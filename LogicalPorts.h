/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents an Input Terminal of a Circuit
 *
 */

#ifndef LOGICAL_PORT
#define LOGICAL_PORT

#include "Component.h"
#include "FailureStatus.h"

#include <vector>

class LogicalPort : public Component
{
	public:
		LogicalPort();
		~LogicalPort();
	
	private:
		std::vector< Component* > _inputs;
		FailureStatus status;
};

#endif


