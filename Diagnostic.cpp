/*
 * Author: Riccardo Orizio (R)
 * Date: 4 March 2016
 *
 * Description: Implementation of the Diagnostic class
 *
 */

#include "Diagnostic.h"

#ifndef DEBUG
	#define DEBUG
#endif

// TODO Is the diagnoses type really necessary here? Maybe i could pass it to
// the solve method, seems more reasonable
Diagnostic::Diagnostic( const std::string& input_filename )
{
	_name = input_filename;
	_cones = std::map< std::string, GateCone >();
	_values = std::map< std::string, GateValue >();

	load( _name );

#ifdef DEBUG
	fprintf( stdout, "Diagnostic::Diagnostic Created %p\n", this );
	fflush( stdout );
#endif
}

Diagnostic::~Diagnostic()
{
#ifdef DEBUG
	fprintf( stdout, "Diagnostic::~Diagnostic Destroying %p\n", this );
	fflush( stdout );
#endif
}

void Diagnostic::solve( DiagnosesType diagnoses_type )
{
	fprintf( stdout, "Diagnostic::solve Solving '%s'\n",
				_name.c_str() );

	fprintf( stdout, "'%s' requested\n", to_string( diagnoses_type ) );

	switch( diagnoses_type )
	{
		case DiagnosesType::ALL_DIAGNOSES:
			break;
		case DiagnosesType::NO_MASKING:
			break;
		case DiagnosesType::ALL_MASKING:
			break;
		case DiagnosesType::OK_MASKING:
			break;
		case DiagnosesType::KO_MASKING:
			break;
	}
}

// Private methods
void Diagnostic::load( const std::string& input_filename )
{

	// Opening the file and reading the cones
	std::ifstream input_file( input_filename, std::ifstream::in );
	if( input_file == NULL )
	{
		fprintf( stdout, "Circuit::load: error in opening file '%s'\n",
					input_filename.c_str() );
		exit( 1 );
	}

	// Reading the file using a regex
	//  - 0: the whole line that matched
	//  - 1: gate name
	//  - 2: list of gates composing the cone
	//  - 3: last element of the list, not used
	//  - 4: gate value
	std::regex regex_cones( "([A-Z][0-9]+):.*\\{(( [A-Z][0-9]+,?)*) \\}.*(OK|KO)" );
	std::smatch regex_results;
	std::string line;
	std::string cone_list;
	std::string cone_name_temp;
	GateCone cone_temp;
	
	// Reading lines one per time and applying the regex
	while( std::getline( input_file, line ) )
	{
		// Skipping empty lines
		if( line.length() > 1 )
		{
			// Terminals regex: Input and Output
			if( std::regex_search( line, regex_results, regex_cones ) )
			{
#ifdef DEBUG	
				fprintf( stdout, "Cone found %lu: ", regex_results.size() );
				for( size_t i = 0; i < regex_results.size(); i++ )
					fprintf( stdout, "'%s' ", regex_results.str( i ).c_str() );
				fprintf( stdout, "\n" );
#endif

				// Saving the cone
				// Processing all the gates in the list and adding them one by
				// one to the cone
				cone_temp = GateCone();
				cone_list = regex_results.str( 2 );

				// Checking if the gate really has a cone or not
				if( !cone_list.empty() )
				{
					size_t pos;
					// Deleting the first space
					cone_list.erase( 0, 1 );

					while( ( pos = cone_list.find( "," ) ) != std::string::npos )
					{
						cone_name_temp = cone_list.substr( 0, pos );
						cone_temp.insert( cone_name_temp );
						
						// Deleting the input name just processed, the comma and the
						// successive space
						cone_list.erase( 0, pos + 2 );
					}

					// Adding the last element
					cone_temp.insert( cone_list );
				}

				// Adding the cone to the map
				_cones.insert(
					std::pair< std::string, GateCone >
						(
							regex_results.str( 1 ),
							cone_temp
						)
				);

				GateValue value_temp;

				if( regex_results.str( 4 ).compare( "OK" ) == 0 )
					value_temp = GateValue::OK;
				else if( regex_results.str( 4 ).compare( "KO" ) == 0 )
					value_temp = GateValue::KO;

				// Adding the value
				_values.insert(
					std::pair< std::string, GateValue >
						(
							regex_results.str( 1 ),
							value_temp
						)
				);
			}
			// Something is not recognized correctly
			else
			{
				fprintf( stdout, "Diagnostic::load Error in reading the input file! %s line read not recognized.\n", line.c_str() );
				exit( 1 );
			}
		}
	}

#ifdef DEBUG
		fprintf( stdout, "Cones Map size: %lu\n", _cones.size() );
		for( std::map< std::string, GateCone >::iterator i = _cones.begin();
			 i != _cones.end();
			 i++ )
		{
			fprintf( stdout, "\t" );
			i->second.print( i->first );
			fprintf( stdout, "\n" );
		}
		fflush( stdout );

		fprintf( stdout, "Values Map size: %lu\n", _values.size() );
		for( std::map< std::string, GateValue >::iterator i = _values.begin();
			 i != _values.end();
			 i++ )
			fprintf( stdout, "\t%s(%s)\n",
						i->first.c_str(),
						to_string( i->second ) );
		fflush( stdout );
#endif

	// Closing the file
	input_file.close();
}
