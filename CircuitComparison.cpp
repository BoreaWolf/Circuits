/*
 * Author: Riccardo Orizio (R)
 * Date: 25 February 2016
 *
 * Description: Implementation of a Solution comparison
 *
 */

#include "./CircuitComparison.h"

CircuitComparison::CircuitComparison()
{
	_comparison = std::map< std::string, CircuitComparisonValues >();
}


CircuitComparison::~CircuitComparison()
{	}

void CircuitComparison::compare( CircuitSolution& sol_one,
								 CircuitSolution& sol_two )
{
	// I assume that the two solutions are compatible:
	//  - same length
	//  - same gates in the same order
	
	CircuitComparisonValues temp_result;

	for( std::map< std::string, int >::iterator i = sol_one.begin();
		 i != sol_one.end();
		 i++ )
	{
		if( sol_one.get_gate_value_of( i->first ) == 
			sol_two.get_gate_value_of( i->first ) )
			temp_result = CircuitComparisonValues::OK;
		else
			temp_result = CircuitComparisonValues::KO;

		// Inserting the result in the map
		_comparison.insert( 
			std::pair< std::string, CircuitComparisonValues >
				(
					i->first,
				    temp_result
				)
			 );
	}
}

const char* CircuitComparison::get_comparison_value_of( const std::string& gate )
{
	return to_string( _comparison.find( gate )->second );
}

void CircuitComparison::print( FILE* file )
{
	for( size_t i = 0; i < _comparison.size(); i++ )
	for( std::map< std::string, CircuitComparisonValues >::iterator i = _comparison.begin();
		 i != _comparison.end();
		 i++ )
		fprintf( file, "\tGate %s = %s\n",
					i->first.c_str(),
					to_string( i->second ) );
}
