/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Main of the Circuits problem
 * A project of the class of Algorithms and Data Structures
 *
 */

#include "Circuit.h"
#include "./constants.h"

#include <stdio.h>
#include <string>
#include <vector>

int main( int argc, char ** argv )
{
	// File names
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
		input_circuit = argv[ 1 ];
		input_configuration = argv[ 2 ];
		input_failure = argv[ 3 ];
	}
	else
	{
		// If the user doesn't specifies any input file, I'll read all the
		// instances and solve them
		input_circuit = StringConstants::PATH_CIRCUITS + "C17.txt";
		//	input_circuit = StringConstants::PATH_CIRCUITS + "C432.txt";
		input_configuration = StringConstants::FILE_INPUT_CONFIGURATION;
		input_failure = StringConstants::FILE_FAILING_GATES;
	}

	// Creating the circuit and then passing to it the initial configuration and
	// the failing gates to it
	Circuit ckt( input_circuit );
	ckt.solve( input_configuration, input_failure ); 

	// Printing some results
	//	ckt.print_output_values();
	//	ckt.print_output_cones();
	//	ckt.print_solutions();
	//	ckt.print_solutions_for_diagnostic();

	// Creating the output file depending on the input files received
	// Retrieving the file name
	std::string solution_filename = 
		input_configuration.substr(
			input_configuration.find_last_of( "/" ) + 1 );

	// Removing the current file extension
	solution_filename = 
		solution_filename.substr( 
			0,
			(
				solution_filename.size() -
				solution_filename.substr(
					solution_filename.find_last_of( "." ) ).size()
			) );

	// Composing the final file name
	solution_filename = 
		StringConstants::PATH_SIM_SOLUTION +
		solution_filename + 
		StringConstants::EXT_SIM_SOLUTION;

	// Writing to file
	FILE* solution_file = fopen( solution_filename.c_str(), "w" );
	ckt.print_solutions_for_diagnostic( solution_file );
	fclose( solution_file );

	fprintf( stdout, "Yeah! Solved circuit '%s'! Results on '%s'! (•̀ᴗ•́)൬༉\n",
				ckt.get_name().c_str(),
				solution_filename.c_str() );
	
	return 0;
}

