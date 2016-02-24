/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents an Input Terminal of a Circuit
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
		LogicalGate( std::string name, std::vector< std::string > inputs )
		{
			_name = name;
			_inputs = inputs;
			_status = GateStatus::correct;

			fprintf( stdout, "LogicalGate::LogicalGate Created %s @ %p\n",
						_name.c_str(),
						this );
			fflush( stdout );
		}

		~LogicalGate()
		{	}

		virtual int compute() = 0;

		GateStatus get_status(){ return _status; }
		int get_status_value(){ return static_cast<int>( _status ); }
		void set_status( GateStatus status ){ _status = status; }
	
	protected:
		// TODO: Component* or string?
		// I decided for a vector of strings because the code will be easier to
		// maintain
		std::vector< std::string > _inputs;
		GateStatus _status;
};

#endif


