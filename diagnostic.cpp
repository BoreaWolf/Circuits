/*
 * Author: Riccardo Orizio (R)
 * Date: 4 March 2016
 *
 * Description: Main of the Diagnostic Circuits problem
 * A project of the class of Algorithms and Data Structures
 *
 */

#include "./constants.h"

#include <stdio.h>
#include <string>

int main( int argc, char ** argv )
{
	// File names
	std::string input_data, input_diagnostic;

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
		input_diagnostic = argv[ 2 ];
	}
	else
	{
		// If the user doesn't specifies any input file, I'll read all the
		// instances and solve them
		input_data = StringConstants::PATH_CIRCUITS + "C17.txt";
		input_diagnostic = StringConstants::FILE_INPUT_CONFIGURATION;
	}

	fprintf( stdout, "Yeah! Diagnostics done! (ฅ⁍̴̀◊⁍̴́)و ̑̑\n" );
	
	return 0;
}

