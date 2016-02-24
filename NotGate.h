/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a NOT Logical Gate
 *
 */

#ifndef NOT_LOGICAL_GATE
#define NOT_LOGICAL_GATE

#include "LogicalGate.h"

#include <string>
#include <vector>

class NotGate : public LogicalGate
{
	public:
		NotGate( const std::string&, std::vector< Component* >& );
		~NotGate();
	
		int compute();
};

#endif


