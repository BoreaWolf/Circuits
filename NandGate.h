/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a NAND Logical Gate
 *
 */

#ifndef NAND_LOGICAL_GATE
#define NAND_LOGICAL_GATE

#include "LogicalGate.h"

#include <string>
#include <vector>

class NandGate : public LogicalGate
{
	public:
		NandGate( const std::string&, std::vector< Component* >& );
		~NandGate();
	
		int compute();
};

#endif


