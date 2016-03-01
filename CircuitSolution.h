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
#include <vector>

class CircuitSolution
{
	public:
		CircuitSolution();
		~CircuitSolution();

		void save( std::map< std::string, Component* >& );
	
		int size();

		std::string& get_gate_name_at( int );
		int get_gate_value_at( int );
		int get_gate_value( std::string& );

		void print( FILE* = stdout );
		
	private:
		std::vector< std::pair< std::string, int > > _solution;
};

#endif

