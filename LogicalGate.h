/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a Logical Gate
 *
 */

#ifndef LOGICAL_GATE
#define LOGICAL_GATE

#include "Component.h"
#include "GateStatus.h"

#include <vector>

class LogicalGate : public Component
{
	public:
		LogicalGate();
		LogicalGate( const std::string&,
					 std::vector< Component* >&,
					 const std::string& = std::string() );
		~LogicalGate();

		virtual int compute() = 0;

		GateStatus get_status(){ return _status; }
		int get_status_value(){ return static_cast<int>( _status ); }
		void set_status( GateStatus status ){ _status = status; }
	
	protected:
		std::vector< Component* > _inputs;
		GateStatus _status;
};

#endif

