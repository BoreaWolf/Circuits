/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a NOR Logical Gate
 *
 */

#ifndef NOR_LOGICAL_GATE
#define NOR_LOGICAL_GATE

#include "LogicalGate.h"

#include <string>
#include <vector>

class NorGate : public LogicalGate
{
	public:
		NorGate( const std::string&, std::vector< Component* >& );
		~NorGate();

		int compute();
};

#endif


