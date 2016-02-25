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
	_comparison = std::vector< std::pair< std::string, CircuitComparisonValues > >();
}


CircuitComparison::~CircuitComparison()
{	}

void CircuitComparison::compare( CircuitSolution& first,
								 CircuitSolution& second )
{
	// I assume that the two solutions are compatible:
	//  - same length
	//  - same gates in the same order
	
	CircuitComparisonValues temp_result;

	// TODO: Add some integrity checks, at least I should be sure to check the
	// value of the same gate
	for( int i = 0; i < first.size(); i++ )
	{
		if( first.get_gate_value_at( i ) == second.get_gate_value_at( i ) )
			temp_result = CircuitComparisonValues::OK;
		else
			temp_result = CircuitComparisonValues::KO;

		_comparison.push_back( 
			std::pair< std::string, CircuitComparisonValues >
				(
				    first.get_gate_name_at( i ),
				    temp_result
				)
			 );
	}
}
void CircuitComparison::print( FILE* file )
{
	for( size_t i = 0; i < _comparison.size(); i++ )
		fprintf( file, "\tGate %s = %s\n",
					_comparison.at( i ).first.c_str(),
					to_string( _comparison.at( i ).second ) );
}
 
