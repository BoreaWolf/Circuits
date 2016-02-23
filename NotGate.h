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
		NotGate();
		~NotGate();
	
		int compute()
		{
			int result;
			// Checking if this gate has some issues
			if( _status == GateStatus::correct )
				result = ~_inputs.at( 0 )->get_value();
			else
				result = _status;

			return result;
		}

	private:
};

#endif


