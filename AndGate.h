/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a AND Logical Gate
 *
 */

#ifndef AND_LOGICAL_GATE
#define AND_LOGICAL_GATE

#include "LogicalGate.h"

#include <string>
#include <vector>

class AndGate : public LogicalGate
{
	public:
		AndGate( const std::string&, std::vector< Component* >& );
		~AndGate();

		int compute();
};

#endif


