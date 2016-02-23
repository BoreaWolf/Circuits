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

#include <vector>

class NorGate : public LogicalGate
{
	public:
		NorGate();
		~NorGate();

		int compute()
		{
			int result;
			// Checking if this gate has some issues
			if( _status == GateStatus::correct )
			{
				result = _inputs.at( 0 )->get_value();
				for( size_t i = 1; i < _inputs.size(); i++ )
					result = ~( result | _inputs.at( i )->get_value() );
			}
			else
				result = _status;

			return result;
		}
	
	private:
};

#endif


