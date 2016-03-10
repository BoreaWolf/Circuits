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

		// Checking the integrity of the DiagnosesType
		if( ( *( argv[ 2 ] ) - '0' ) < 0 ||
			( *( argv[ 2 ] ) - '0' ) > 4 )
		{
			fprintf( stdout, "Diagnostic requested not valid!\n" );
			fprintf( stdout, "These are the possible options:\n" );
			for( int i = static_cast< int >( DiagnosesType::ALL_DIAGNOSES );
				 i <= static_cast< int >( DiagnosesType::KOM_MASKING );
				 i++ )
				fprintf( stdout, "\t%d) %s\n",
							i,
							to_string( static_cast< DiagnosesType >( i ) ) );

			exit( -1 );
		}

		input_diagnostic = static_cast< DiagnosesType >( *( argv[ 2 ] ) - '0' );
	}
	else
	{
		// If the user doesn't specifies any input file, I'll read all the
		// instances and solve them
		input_data = StringConstants::FILE_INPUT_DATA_DIAGNOSTIC;
		input_diagnostic = DiagnosesType::ALL_DIAGNOSES;
		//	input_diagnostic = DiagnosesType::NO_MASKING;
		//	input_diagnostic = DiagnosesType::ALL_MASKING;
		//	input_diagnostic = DiagnosesType::OKM_MASKING;
		//	input_diagnostic = DiagnosesType::KOM_MASKING;
		// Create an enum to define diagnostic types
	}
	
	// Creating the output file depending on the input files received
	// Retrieving the file name
	std::string solution_filename = 
		input_data.substr(
			input_data.find_last_of( "/" ) + 1 );

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
		StringConstants::PATH_DIA_SOLUTION +
		solution_filename + 
		StringConstants::EXT_DIA_SOLUTION;

	// Writing to file
	FILE* solution_file = fopen( solution_filename.c_str(), "w" );

	Diagnostic dia( input_data, solution_file );
	dia.solve( input_diagnostic );
	dia.print_solutions();

	dia.print_solutions( solution_file );
	fclose( solution_file );
	
	fprintf( stdout, "Yeah! Diagnostics done @ '%s'! (ฅ⁍̴̀◊⁍̴́)و ̑̑\n",
				solution_filename.c_str() );
	
	return 0;
}

