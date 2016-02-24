/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Implementation of CircuitSet class
 *
 */

#include "CircuitSet.h"

CircuitSet::CircuitSet( std::vector< std::string > input_ckts )
{
	for( size_t i = 0; i < input_ckts.size(); i++ )
		_ckts.push_back( Circuit( input_ckts.at( i ) ) );

	fprintf( stdout, "CircuitSet::CircuitSet Created %p\n", this );
}

CircuitSet::~CircuitSet()
{
	fprintf( stdout, "CircuitSet::~CircuitSet Destroying %p\n", this );
}

int CircuitSet::size()
{
	return _ckts.size();
}
