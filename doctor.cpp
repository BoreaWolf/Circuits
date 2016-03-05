/*
 * Author: Riccardo Orizio (R)
 * Date: 4 March 2016
 *
 * Description: Main of the Diagnostic Circuits problem
 * A project of the class of Algorithms and Data Structures
 *
 */

#include "./constants.h"
#include "./Diagnostic.h"

#include <stdio.h>
#include <string>

int main( int argc, char ** argv )
{
	// File names
	std::string input_data;
	DiagnosesType input_diagnostic;

	// Some input from the user
	if( argc > 1 )
	{
		/*
		 * Argv:
		 *  - argv[ 0 ]: program name
		 *  - argv[ 1 ]: input data
		 *  - argv[ 2 ]: input diagnostic
		 */
		input_data = argv[ 1 ];
		input_diagnostic = static_cast< DiagnosesType >( *( argv[ 2 ] ) - '0' );
	}
	else
	{
		// If the user doesn't specifies any input file, I'll read all the
		// instances and solve them
		input_data = StringConstants::FILE_INPUT_DATA_DIAGNOSTIC;
		input_diagnostic = DiagnosesType::ALL_DIAGNOSES;
		// Create an enum to define diagnostic types
	}

	Diagnostic dia( input_data );
	dia.solve( input_diagnostic );

	fprintf( stdout, "Yeah! Diagnostics done! (ฅ⁍̴̀◊⁍̴́)و ̑̑\n" );
	
	return 0;
}

