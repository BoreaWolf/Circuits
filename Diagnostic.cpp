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
	_cones = cone_map();
	_values = value_map();
	_ok_gates = std::vector< std::string >();
	_ko_gates = std::vector< std::string >();

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
			all_diagnoses();
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

void Diagnostic::all_diagnoses()
{
	value_map* current_subset;
	for( int i = 0; i < get_ok_subset_number(); i++ )
	{
		current_subset = get_ith_ok_subset( i );

		// Checking if the current subset needs to be processed:
		// if the cone of the OK values does intersecate with a cone of a KO
		// value then it needs to be processed
		if( check_cone_interesection( current_subset ) )
		{
			for( value_map::iterator it = current_subset->begin();
				 it != current_subset->end();
				 it++ )
			{
#ifdef DEBUG
				fprintf( stdout, "%s: %s %s => ",
							it->first.c_str(),
							to_string( _values.find( it->first )->second ),
							to_string( it->second ) );
#endif
				// Checking if the value associated to the current subset of every
				// gate matches with the input data, if so I'll set it to OKM,
				// otherwise I'll keep it as it is in the input
				if( it->second == _values.find( it->first )->second )
					it->second = GateValue::OKM;
				else
					it->second = _values.find( it->first )->second;

#ifdef DEBUG
				fprintf( stdout, "%s\n", to_string( it->second ) );
#endif
			}

			// Joining the solution with the current calculated
			//	_solution.join( diagnoses_one_config( current_subset ) );
		}

	}
	fprintf( stdout, "\n" );
	
}

void Diagnostic::diagnoses_one_config( value_map* current_values )
{
}

void Diagnostic::diagnoses_one_choice()
{
}

// Private methods
void Diagnostic::load( const std::string& input_filename )
{
	// Opening the file and reading the cones
	std::ifstream input_file( input_filename, std::ifstream::in );
	if( input_file == NULL )
	{
		fprintf( stdout, "Diagnostic::load: error in opening file '%s'\n",
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

				// Saving information about the value in both a map and in two
				// vectors
				// TODO Really needed?
				GateValue value_temp;

				if( regex_results.str( 4 ).compare( "OK" ) == 0 )
				{
					value_temp = GateValue::OK;
					_ok_gates.push_back( regex_results.str( 1 ) );
				}
				else if( regex_results.str( 4 ).compare( "KO" ) == 0 )
				{
					value_temp = GateValue::KO;
					_ko_gates.push_back( regex_results.str( 1 ) );
				}

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
		for( cone_map::iterator i = _cones.begin();
			 i != _cones.end();
			 i++ )
		{
			fprintf( stdout, "\t" );
			i->second.print( i->first );
			fprintf( stdout, "\n" );
		}
		fflush( stdout );

		fprintf( stdout, "Values Map size: %lu\n", _values.size() );
		for( value_map::iterator i = _values.begin();
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

value_map* Diagnostic::get_ith_ok_subset( int i )
{
	value_map* result = new std::map< std::string, GateValue >();

	// Creating the map having the gate name as key and OK/KO as value,
	// translating the int parameter in its corresonding binary value and
	// creating the subset with that information:
	//  - 0 => OK
	//  - 1 => KO
	// It doesn't change much if OK = 0 | 1, at the end every set is going to be
	// checked
	
	fprintf( stdout, "Diagnostic::get_ith_ok_subset on %d: ", i );

	for( value_map::iterator it = _values.begin();
		 it != _values.end();
		 it++ )
	{
		result->insert(
			std::pair< std::string, GateValue >
			(
				it->first,
				static_cast<GateValue>( i%2 )
			)
		);

		fprintf( stdout, "%d(%s) ", i%2, to_string( static_cast< GateValue >( i%2 ) ) );
		// Going for the next part of the binary number
		i /= 2;
	}

	fprintf( stdout, "\n" );

	return result;
}

int Diagnostic::get_ok_subset_number()
{
	fprintf( stdout, "Diagnostic::get_ok_subset_number %d having %lu OK\n",
				( _ok_gates.size() == 0 ? 0 : (int) pow( 2, _ok_gates.size() ) ),
				_ok_gates.size() );

	return (int)( _ok_gates.size() == 0 ? 0 : ( pow( 2, _ok_gates.size() ) ) );
}

bool Diagnostic::check_cone_interesection( value_map* current_values )
{
	fprintf( stdout, "Diagnostic::check_cone_intersection start\n" );
	// Checking only the OK values
	for( value_map::iterator value_it = current_values->begin();
		 value_it != current_values->end();
		 value_it++ )
	{
		fprintf( stdout, "Diagnostic::check Checking gate '%s' '%s' ",
					value_it->first.c_str(),
					to_string( value_it->second ) );

		if( value_it->second == GateValue::OK )
		{
			fprintf( stdout, " continuing\n" );

			// Controlling through every KO exit
			for( size_t i = 0; i < _ko_gates.size(); i++ )
			{
				fprintf( stdout, "\tComparing with '%s' '%s'\n",
							_ko_gates.at( i ).c_str(),
							to_string( _values.find( _ko_gates.at( i ) )->second ) );
				// If the two cones have an intersection then i stop the
				// procedure and return a true value: there is an intersection
				if( _cones.find( value_it->first )->second
						.intersection( _cones.find( _ko_gates.at( i ) )->second ) )
					return true;
			}
		}

		fprintf( stdout, "\n" );
	}

	fprintf( stdout, "Diagnostic::check_cone_intersection end, no intersection\n" );
	// No intersections have been found
	return false;
}
