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
		void print( FILE* = stdout );

	private:
		std::vector< std::pair< std::string, CircuitComparisonValues > > _comparison;
};

#endif

