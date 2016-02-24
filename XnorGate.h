/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a XNOR Logical Gate
 *
 */

#ifndef XNOR_LOGICAL_GATE
#define XNOR_LOGICAL_GATE

#include "LogicalGate.h"

#include <string>
#include <vector>

class XnorGate : public LogicalGate
{
	public:
		XnorGate( const std::string&, std::vector< Component* >& );
		~XnorGate();

		int compute();
};

#endif


