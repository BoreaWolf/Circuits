/*
 * Author: Riccardo Orizio (R)
 * Date: 25 February 2016
 *
 * Description: Implementation of a Circuit Solution
 *
 */

#include "CircuitSolution.h"

CircuitSolution::CircuitSolution()
{
	_solution = std::map< std::string, int >();
}

CircuitSolution::~CircuitSolution()
{	}

void CircuitSolution::save( std::map< std::string, Component* >& result )
{
	// Saving the result
	for( std::map< std::string, Component* >::iterator i = result.begin();
		 i != result.end();
		 i++ )
		_solution.insert( std::pair< std::string, int >
						  (
						      i->first,
						      i->second->get_value()
						  )
						);
}

int CircuitSolution::size()
{
	return _solution.size();
}

std::map< std::string, int >::iterator CircuitSolution::begin()
{
	return _solution.begin();
}

std::map< std::string, int >::iterator CircuitSolution::end()
{
	return _solution.end();
}

int CircuitSolution::get_gate_value_of( const std::string& gate_name )
{
	return _solution.find( gate_name )->second;
}

void CircuitSolution::print( FILE* file )
{
	for( std::map< std::string, int >::iterator i = _solution.begin();
		 i != _solution.end();
		 i++ )
		fprintf( file, "\tGate %s = %d\n",
					i->first.c_str(),
					i->second );
}

