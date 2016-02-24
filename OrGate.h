/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a OR Logical Gate
 *
 */

#ifndef OR_LOGICAL_GATE
#define OR_LOGICAL_GATE

#include "LogicalGate.h"

#include <string>
#include <vector>

class OrGate : public LogicalGate
{
	public:
		OrGate( const std::string&, std::vector< Component* >& );
		~OrGate();

		int compute();
};

#endif


