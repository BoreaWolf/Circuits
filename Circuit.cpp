/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Implementation of the Circuit class
 *
 */

#include "Circuit.h"

Circuit::Circuit( std::string input_filename )
{
	load( input_filename );
	fprintf( stdout, "Circuit::Circuit Created %p\n", this );
}

Circuit::~Circuit()
{
	fprintf( stdout, "Circuit::~Circuit Destroying %p\n", this );
}

void Circuit::load( std::string input_filename )
{
	// Opening the file and reading all the components of the circuit
	std::ifstream input_file( input_filename, std::ifstream::in );
	if( input_file == NULL )
	{
		fprintf( stdout, "Circuit::load: Error in opening file '%s'\n",
					input_filename.c_str() );
		exit( 1 );
	}
	
	// Reading the file using some regex
	std::regex regex_terminals( "(IN|OUT)PUT\\(([A-Z][0-9]+)\\)" );
	std::regex regex_logic_ports( "([A-Z][0-9]+) = ([A-Z]+)\\(([A-Z][0-9]+)((,([A-Z][0-9]+))*)\\)" );
	std::smatch regex_results;

	std::string line;

	// Reading lines one per time and applying the regex
	while( std::getline( input_file, line ) )
	{
		// Skipping empty lines
		if( line.length() > 1 )
		{
			// Terminals regex: Input and Output
			if( std::regex_search( line, regex_results, regex_terminals ) )
			{
				fprintf( stdout, "IN/OUT found %lu: ", regex_results.size() );
				for( size_t i = 0; i < regex_results.size(); i++ )
					fprintf( stdout, "'%s' ", regex_results.str( i ).c_str() );
				fprintf( stdout, "\n" );

				
			}
			else
			{
				// Logical ports regex
				if( std::regex_search( line, regex_results, regex_logic_ports ) )
				{
					fprintf( stdout, "Logic port found %lu: ", regex_results.size() );
					for( size_t i = 0; i < regex_results.size(); i++ )
						fprintf( stdout, "'%s' ", regex_results.str( i ).c_str() );
					fprintf( stdout, "\n" );
				}
				// Something is not recognized correctly
				else
				{
					fprintf( stdout, "Circuit::load Error in reading the input file!\n" );
					exit( 1 );
				}
			}
		}
	}

	// Closing the file
	input_file.close();
}
