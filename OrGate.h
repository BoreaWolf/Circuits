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

#include <vector>

class OrGate : public LogicalGate
{
	public:
		OrGate();
		OrGate( std::string name, std::vector< Component* >& inputs ) :
			LogicalGate( name, inputs )
		{	}
		~OrGate()
		{	}

		int compute()
		{
			int result;
			// Checking if this gate has some issues
			if( get_status() == GateStatus::correct )
			{
				result = _inputs.at( 0 )->get_value();
				for( size_t i = 1; i < _inputs.size(); i++ )
					result |= _inputs.at( i )->get_value();
			}
			else
				result = get_status_value();

			return result;
		}
	
	private:
};

#endif


