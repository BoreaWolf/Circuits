/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a XOR Logical Gate
 *
 */

#ifndef XOR_LOGICAL_GATE
#define XOR_LOGICAL_GATE

#include "LogicalGate.h"

#include <string>
#include <vector>

class XorGate : public LogicalGate
{
	public:
		XorGate( const std::string&, std::vector< Component* >& );
		~XorGate();

		int compute();
};

#endif


