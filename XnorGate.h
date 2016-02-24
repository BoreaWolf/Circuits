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

#include <vector>

class XnorGate : public LogicalGate
{
	public:
		XnorGate();
		XnorGate( std::string name, std::vector< Component* >& inputs ) :
			LogicalGate( name, inputs )
		{	}
		~XnorGate()
		{	}

		int compute()
		{
			int result;
			// Checking if this gate has some issues
			if( get_status() == GateStatus::correct )
			{
				result = _inputs.at( 0 )->get_value();
				for( size_t i = 1; i < _inputs.size(); i++ )
					result = ~( result ^ _inputs.at( i )->get_value() );
			}
			else
				result = get_status_value();

			return result;
		}
	
	private:
};

#endif


