/*
 * Author: Riccardo Orizio (R)
 * Date: 25 February 2016
 *
 * Description: Class that represents a Circuit Solution
 *
 */

#ifndef CIRCUIT_SOLUTION
#define CIRCUIT_SOLUTION

#include "./LogicalGate.h"
#include "./OutputTerminal.h"

#include <map>
#include <string>

class CircuitSolution
{
	public:
		CircuitSolution();
		~CircuitSolution();

		void save( std::map< std::string, Component* >& );
	
		int size();
		std::map< std::string, int >::iterator begin();
		std::map< std::string, int >::iterator end();

		int get_gate_value_of( const std::string& );

		void print( FILE* = stdout );
		
	private:
		std::map< std::string, int > _solution;
};

#endif

