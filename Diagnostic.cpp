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
	gate_list* current_subset;
	value_map okm_configuration = value_map();
	GateValue value_temp;

	for( int i = 0; i < get_ok_subset_number(); i++ )
	{
		// Resetting the OKM configuration so I can build a new one based on
		// the current subset
		okm_configuration = value_map();
		current_subset = get_ith_ok_subset( i );

		for( value_map::iterator it = _values.begin();
			 it != _values.end();
			 it++ )
		{
			// Checking if the element is present in the subset, if so I set it
			// to OKM exit value, otherwise I keep its configuration
			if( std::find( current_subset->begin(),
						   current_subset->end(),
						   it->first ) != current_subset->end() )
				value_temp = GateValue::OKM;
			else
				value_temp = it->second;

			// Adding the element to the configuration
			okm_configuration.insert( 
				std::pair< std::string, GateValue >
				(
					it->first,
					value_temp
				)
			);
		}

#ifdef DEBUG
		fprintf( stdout, "Diagnostic::all_diagnoses OKM configuration\n" );
		for( value_map::iterator it = okm_configuration.begin();
			 it != okm_configuration.end();
			 it++ )
			fprintf( stdout, "\t'%s' '%s'\n",
						it->first.c_str(),
						to_string( it->second ) );
#endif

		// Checking if the current subset needs to be processed:
		// if the cones of the OK values do intersecate with a cone of a KO
		// value then it needs to be processed
		if( check_cone_intersection( okm_configuration ) )
			diagnoses_one_config( okm_configuration );

		//	_solution.join( diagnoses_one_config( current_subset ) );

	}
}

void Diagnostic::diagnoses_one_config( value_map& current_values )
{
	// Creating the union of cones of the gates having OK as output value in the
	// current case, received as argument
	GateCone ok_cones = GateCone();
	GateCone cone_temp;
	std::vector< GateCone > cone_collection = std::vector< GateCone >();
	choice_list choices = choice_list();

	for( value_map::iterator it = current_values.begin();
		 it != current_values.end();
		 it++ )
		if( it->second == GateValue::OK )
			ok_cones.join( _cones.find( it->first )->second );

#ifdef DEBUG
	ok_cones.print( "All OK" );
	fprintf( stdout, "\n" );
#endif

	// Creating the cone collection from OKM and KO outputs
	for( value_map::iterator it = current_values.begin();
		 it != current_values.end();
		 it++ )
		if( it->second == GateValue::OKM ||
			it->second == GateValue::KO )
		{
			cone_temp = _cones.find( it->first )->second;
			cone_temp.complement( ok_cones );
			cone_collection.push_back( cone_temp );
		}
	
#ifdef DEBUG
	fprintf( stdout, "Diagnostic::diagnoses_one_config Cone Collection A\n" );
	for( size_t i = 0; i < cone_collection.size(); i++ )
	{
		fprintf( stdout, "\t" );
		cone_collection.at( i ).print( "Sbra" );
		fprintf( stdout, "\n" );
	}
#endif


	// Creating the choices: as I understood from the slides, I need to create a
	// choice for every OKM value associated with a random KO gate, so this is
	// what I'm going to do
	for( value_map::iterator it = current_values.begin();
		 it != current_values.end();
		 it++ )
		if( it->second == GateValue::OKM )
			choices.push_back(
				choice( it->first, _ko_gates.at( rand() % _ko_gates.size() ) ) );
	
#ifdef DEBUG
	fprintf( stdout, "Diagnostic::diagnoses_one_config Choices: " );
	for( size_t i = 0; i < choices.size(); i++ )
		fprintf( stdout, "(%s, %s) ",
					choices.at( i ).first.c_str(),
					choices.at( i ).second.c_str() );
	fprintf( stdout, "\n" );
#endif
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

gate_list* Diagnostic::get_ith_ok_subset( int subset_number )
{
	gate_list* result = new gate_list();

	// Creating a vector of elements that composes the ith subset of the ok
	// gates and returns it
	// The subset number is used to calculate which gates have to be part of the
	// current subset, translating that number into its corresponding binary
	// number and inserting it if the resulting binary value is 1.
	
#ifdef DEBUG
	fprintf( stdout, "Diagnostic::get_ith_ok_subset on %d: ", subset_number );
#endif

	for( size_t i = 0; i < _ok_gates.size(); i++ )
	{
		if( subset_number % 2 == 1 )
			result->push_back( _ok_gates.at( i ) );

#ifdef DEBUG
		fprintf( stdout, "%s(%d)[%lu] ",
					_ok_gates.at( i ).c_str(),
					subset_number % 2,
					result->size() );
#endif

		// Going for the next part of the binary number
		subset_number /= 2;
	}

#ifdef DEBUG
	fprintf( stdout, "\n" );
#endif

	return result;
}

int Diagnostic::get_ok_subset_number()
{
#ifdef DEBUG
	fprintf( stdout, "Diagnostic::get_ok_subset_number %d having %lu OK\n",
				( _ok_gates.size() == 0 ? 0 : (int) pow( 2, _ok_gates.size() ) ),
				_ok_gates.size() );
#endif

	return (int)( _ok_gates.size() == 0 ? 0 : ( pow( 2, _ok_gates.size() ) ) );
}

bool Diagnostic::check_cone_intersection( value_map& current_values )
{
#ifdef DEBUG
	fprintf( stdout, "Diagnostic::check_cone_intersection start\n" );
#endif
	// Checking only the OK values
	for( value_map::iterator value_it = current_values.begin();
		 value_it != current_values.end();
		 value_it++ )
	{
#ifdef DEBUG
		fprintf( stdout, "Diagnostic::check Checking gate '%s' '%s' ",
					value_it->first.c_str(),
					to_string( value_it->second ) );
#endif

		// I already created the OKM configuration, so i treat the OKM as an OK
		// output value and i'll check it
		if( value_it->second == GateValue::OK || 
			value_it->second == GateValue::OKM )
		{
#ifdef DEBUG
			fprintf( stdout, " continuing\n" );
#endif

			// Controlling through every KO exit
			for( size_t i = 0; i < _ko_gates.size(); i++ )
			{
#ifdef DEBUG
				fprintf( stdout, "\tComparing with '%s' '%s'\n",
							_ko_gates.at( i ).c_str(),
							to_string( _values.find( _ko_gates.at( i ) )->second ) );
#endif
				// If the two cones have an intersection then i stop the
				// procedure and return a true value: there is an intersection
				if( _cones.find( value_it->first )->second
						.intersection( _cones.find( _ko_gates.at( i ) )->second ) )
					return true;
			}
		}

#ifdef DEBUG
		fprintf( stdout, "\n" );
#endif
	}

#ifdef DEBUG
	fprintf( stdout, "Diagnostic::check_cone_intersection end, no intersection\n" );
#endif

	// No intersections have been found
	return false;
}
