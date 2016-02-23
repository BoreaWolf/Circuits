/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Main of the Circuits problem
 * A project of the class of Algorithms and Data Structures
 *
 */

#include "./CircuitSet.h"
#include "./constants.h"

#include <stdio.h>
#include <string>
#include <vector>

int main( int argc, char ** argv )
{
	// File names
	std::vector< std::string > input_circuits;

	// Some input from the user
	if( argc > 1 )
	{
		/*
		 * Argv:
		 *  - argv[ 0 ]: program name
		 *  - argv[ 1 ]: circuit to solve name
		 */
		input_circuits.push_back( argv[ 1 ] );
	}
	else
	{
		// If the user doesn't specifies any input file, I'll read all the
		// instances and solve them
		//	input_circuits.push_back( "./instances/C17.txt" );
		input_circuits.push_back( "./instances/C432.txt" );
	}

	// For every input file received I create one circuit instance
	CircuitSet ckts( input_circuits );
	//	ckts.solve();

	fprintf( stdout, "Yeah: solved %d circuits!\n", ckts.size() );
	
	return 0;
}

