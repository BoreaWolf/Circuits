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
	_solution = std::vector< std::pair< std::string, int > >();
}

CircuitSolution::~CircuitSolution()
{	}

void CircuitSolution::save( std::map< std::string, Component* >& result )
{
	// Saving the result
	for( std::map< std::string, Component* >::iterator i = result.begin();
		 i != result.end();
		 i++ )
		_solution.push_back( std::pair< std::string, int >
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

std::string& CircuitSolution::get_gate_name_at( int position )
{
	return _solution.at( position ).first;
}

int CircuitSolution::get_gate_value_at( int position )
{
	return _solution.at( position ).second;
}

int CircuitSolution::get_gate_value( std::string& gate_name )
{
	for( size_t i = 0; i < _solution.size(); i++ )
		if( _solution.at( i ).first.compare( gate_name ) == 0 )
			return _solution.at( i ).second;

	return -1;
}

void CircuitSolution::print( FILE* file )
{
	for( size_t i = 0; i < _solution.size(); i++ )
		fprintf( file, "\tGate %s = %d\n",
					_solution.at( i ).first.c_str(),
					_solution.at( i ).second );
}

