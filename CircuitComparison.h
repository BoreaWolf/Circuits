/*
 * Author: Riccardo Orizio (R)
 * Date: 25 February 2016
 *
 * Description: Solution comparison results
 *
 */

#ifndef CIRCUIT_COMPARISON
#define CIRCUIT_COMPARISON

#include "./CircuitSolution.h"

#include <map>
#include <string>
#include <vector>

enum class CircuitComparisonValues : int
{
	OK = 0,
	KO = 1
};

inline const char* to_string( CircuitComparisonValues v )
{
    switch( v )
    {
		case CircuitComparisonValues::OK:	return "OK";
		case CircuitComparisonValues::KO:	return "KO";
    }
}

class CircuitComparison
{
	public:
		CircuitComparison();
		~CircuitComparison();

		void compare( CircuitSolution&, CircuitSolution& );
		const char* get_comparison_value_of( const std::string& );

		void print( FILE* = stdout );

	private:
		std::map< std::string, CircuitComparisonValues > _comparison;
};

#endif

