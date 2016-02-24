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

#include <vector>

class NotGate : public LogicalGate
{
	public:
		NotGate( std::string name, std::vector< std::string >& inputs ) :
			LogicalGate( name, inputs )
		{	}
		~NotGate()
		{	}
	
		int compute()
		{
			int result;
			// Checking if this gate has some issues
			if( get_status() == GateStatus::correct )
				result = ~_inputs.at( 0 )->get_value();
			else
				result = get_status_value();

			return result;
		}

	private:
};

#endif


