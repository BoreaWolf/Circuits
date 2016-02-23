/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class for handling a set of Circuits objects
 *
 */

#ifndef CIRCUIT_SET
#define CIRCUIT_SET

#include "Circuit.h"

#include <string>
#include <vector>

class CircuitSet
{
	public:
		CircuitSet( std::vector< std::string > );
		~CircuitSet();

		int size();
	
	private:
		std::vector< Circuit > _ckts;
};

#endif

