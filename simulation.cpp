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
	//	std::vector< std::string > input_circuits;
	std::string input_circuit, input_configuration, input_failure;

	// Some input from the user
	if( argc > 1 )
	{
		/*
		 * Argv:
		 *  - argv[ 0 ]: program name
		 *  - argv[ 1 ]: circuit to solve name
		 *  - argv[ 2 ]: input configuration
		 *  - argv[ 3 ]: input failure gates
		 */
		//	input_circuits.push_back( argv[ 1 ] );
		input_circuit = argv[ 1 ];
		input_configuration = argv[ 2 ];
		input_failure = argv[ 3 ];
	}
	else
	{
		// If the user doesn't specifies any input file, I'll read all the
		// instances and solve them
		//	input_circuits.push_back( StringConstants::PATH_CIRCUITS + "C17.txt" );
		//	input_circuits.push_back( StringConstants::PATH_CIRCUITS + "C432.txt" );
		input_circuit = StringConstants::PATH_CIRCUITS + "C17.txt";
		input_configuration = StringConstants::FILE_INPUT_CONFIGURATION;
		input_failure = StringConstants::FILE_FAILING_GATES;
		//	input_circuit = StringConstants::PATH_CIRCUITS + "C432.txt";
	}

	// Creating the circuit and then passing to it the initial configuration and
	// the failing gates to it
	Circuit ckt( input_circuit );
	ckt.solve( input_configuration, input_failure ); 

	// Printing some results
	ckt.print_output_values();
	ckt.print_output_cones();
	ckt.print_solutions();

	

	// For every input file received I create one circuit instance
	//	CircuitSet ckts( input_circuits );
	//	ckts.solve();
	//	fprintf( stdout, "Yeah: solved %d circuits!\n", ckts.size() );

	fprintf( stdout, "Yeah! Solved circuit '%s'! (•̀ᴗ•́)൬༉\n", ckt.get_name().c_str() );
	
	return 0;
}

