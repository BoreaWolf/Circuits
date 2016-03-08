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

Diagnostic::Diagnostic( const std::string& input_filename )
{
	_name = input_filename;
	_cones = cone_map();
	_values = value_map();
	_ok_gates = gate_list();
	_ko_gates = gate_list();

	_processing_ok = gate_list();
	_processing_ko = gate_list();
	_processing_okm = gate_list();
	_processing_kom = gate_list();

	_solution = DiagnosticSolution();

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

void Diagnostic::solve( DiagnosesType& diagnoses_type )
{
	fprintf( stdout, "Diagnostic::solve Solving '%s'\n",
				_name.c_str() );

	fprintf( stdout, "'%s' requested\n", to_string( diagnoses_type ) );

	all_diagnoses( diagnoses_type );
}

void Diagnostic::all_diagnoses( DiagnosesType& diagnoses_type )
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

		update_processing_vector( okm_configuration );

		// Stopping the procedure if the configuration created doesn't need to
		// be processed
		// NO_MASKING check
		if( diagnoses_type == DiagnosesType::NO_MASKING && 
			( _processing_okm.size() > 0 || _processing_kom.size() > 0 ) )
		{
#ifdef DEBUG
			fprintf( stdout, "Diagnostic::all_diagnoses %s requested, skipping the current configuration because it has a masking\n", to_string( diagnoses_type ) );
#endif
			continue;
		}

		// ALL, OKM and KOM MASKING check
		if( ( diagnoses_type == DiagnosesType::ALL_MASKING || 
			  diagnoses_type == DiagnosesType::OKM_MASKING || 
			  diagnoses_type == DiagnosesType::KOM_MASKING ) &&
			_processing_okm.size() == 0 )
		{
#ifdef DEBUG
			fprintf( stdout, "Diagnostic::all_diagnoses %s requested, skipping the current configuration because it doesn't have OKM masking\n", to_string( diagnoses_type ) );
#endif
			continue;
		}

		// Checking if the current subset needs to be processed:
		// if the cones of the OK values do intersecate with a cone of a KO
		// value then it needs to be processed
		if( check_cone_intersection( okm_configuration ) )
			diagnoses_one_config( diagnoses_type );
	}
}

void Diagnostic::diagnoses_one_config( DiagnosesType& diagnoses_type )
{
	GateCone ok_cones = GateCone();
	cone_map cone_collection = cone_map();
	choice_list* choices = new choice_list();
	
	// Creating the union of cones of the gates having OK as output value in the
	// current case
	for( size_t i = 0; i < _processing_ok.size(); i++ )
		ok_cones = ok_cones.join( _cones.find( _processing_ok.at( i ) )->second );

#ifdef DEBUG
	ok_cones.print( "All OK" );
	fprintf( stdout, "\n" );
#endif

	// Creating the cone collection from OKM and KO outputs
	// OKM
	for( size_t i = 0; i < _processing_okm.size(); i++ )
		cone_collection.insert( 
			std::pair< std::string, GateCone >
			(
				_processing_okm.at( i ),
				_cones.find( _processing_okm.at( i ) )->second
					.complement( ok_cones ) 
			) );

	// KO
	for( size_t i = 0; i < _processing_ko.size(); i++ )
		cone_collection.insert( 
			std::pair< std::string, GateCone >
			(
				_processing_ko.at( i ),
				_cones.find( _processing_ko.at( i ) )->second
					.complement( ok_cones )
			) );
	
#ifdef DEBUG
	fprintf( stdout, "Diagnostic::diagnoses_one_config Cone Collection A\n" );
	for( cone_map::iterator it = cone_collection.begin();
		 it != cone_collection.end();
		 it++ )
	{
		fprintf( stdout, "\t'%s': ", it->first.c_str() );
		it->second.print( it->first );
		fprintf( stdout, "\n" );
	}
#endif

	// KOM_MASKING check
	if( diagnoses_type == DiagnosesType::KOM_MASKING &&
		get_choice_combinations_number() == 0 )
	{
		fprintf( stdout, "Diagnostic::diagnoses_one_config %s requested, skipping the current configuration because it can't create any KOM gates\n", to_string( diagnoses_type ) );
		return;
	}

	// Skipping the no KOM solution when the diagnoses request KOM gates
	if( diagnoses_type != DiagnosesType::KOM_MASKING )
		// Processing the configuration without any KOM gates set
		diagnoses_one_choice( cone_collection, choices );

	// Skipping the combinations with KOM gates if the diagnoses requested is
	// only for OKM
	if( diagnoses_type != DiagnosesType::OKM_MASKING )
	{
		// Passing to the KOM combinations
		// Creating all the possible combinations between OKM and KO so, in the next
		// step, I can determine which are the KOM gates
		// I'll keep going with the diagnoses only if the number of KOM selected are
		// less or equal than the number of OKM gates (suggested improvement)
		for( int i = 0; i < get_choice_combinations_number(); i++ )
		{
			// Restoring KO and KOM vectors
			_processing_kom.clear();
			_processing_ko = _ko_gates;

			// Retrieving the ith combination of choices
			choices = get_ith_choice( i );

			// Updating the KO list accordingly with the set KOM gates
			for( size_t i = 0; i < _processing_kom.size(); i++ )
				_processing_ko.erase( std::find( _processing_ko.begin(),
												 _processing_ko.end(),
												 _processing_kom.at( i ) ) );
			
#ifdef DEBUG
			fprintf( stdout, "Diagnostic::diagnoses_one_config Choices: " );
			for( size_t i = 0; i < choices->size(); i++ )
				fprintf( stdout, "(%s, %s) ",
							choices->at( i ).first.c_str(),
							choices->at( i ).second.c_str() );
			fprintf( stdout, "\n" );

			print_processing_status();
#endif

			// Improvement suggested from the slide: processing only the choices
			// where there are less or equal KOM selected than OKM 
			// KOM.size() <= OKM.size()
			if( _processing_kom.size() <= _processing_okm.size() )
				diagnoses_one_choice( cone_collection, choices );
		}
	}
}

void Diagnostic::diagnoses_one_choice( cone_map& cone_collection,
									   choice_list* choices )
{
	cone_list result = cone_list();
	GateCone complement, intersection;

	for( size_t i = 0; i < choices->size(); i++ )
	{	
		// Temporary cones: using temp variables because are long and are needed
		// two times
		complement = 
			cone_collection.find( choices->at( i ).first )->second
				.complement( 
					cone_collection.find( choices->at( i ).second )->second );
		intersection = 
			cone_collection.find( choices->at( i ).first )->second
				.intersection(
					cone_collection.find( choices->at( i ).second )->second );

		// Checking if the difference between selected gate cones are empty: if
		// so I interrupt the procedure
		if( complement.empty() || intersection.empty() )
		{
#ifdef DEBUG
			fprintf( stdout, "Diagnostic::diagnoses_one_choice Stopping procedure: intersection or complement sets are empty\n" );
#endif
			return;
		}

#ifdef DEBUG
		fprintf( stdout, "Diagnostic::diagnoses_one_choice Choice (%s, %s):\n\t",
					choices->at( i ).first.c_str(),
					choices->at( i ).second.c_str() );
		complement.print( "Complement" );
		fprintf( stdout, "\n\t" );
		intersection.print( "Intersection" );
		fprintf( stdout, "\n" );
#endif

		// Composing the GateCone that is going to be processed at the end
		result.push_back( complement );
		result.push_back( intersection );
	}

	// Processing the cone collection now: I have to add to the result the cones
	// of the KO/KOM elements not present in the choices, so only the KO gates
	for( size_t i = 0; i < _processing_ko.size(); i++ )
		result.push_back( 
			cone_collection.find( _processing_ko.at( i ) )->second );

	// If no choices are given, so no KOM are set, I add also every okm to the
	// Collection B
	if( choices->size() == 0 )
	{
#ifdef DEBUG
		fprintf( stdout, "Diagnostic::diagnoses_one_chioce No choices, adding OKM to Collection B\n" );
#endif
		for( size_t i = 0; i < _processing_okm.size(); i++ )
			result.push_back(
				cone_collection.find( _processing_okm.at( i ) )->second );
	}
	
#ifdef DEBUG
	fprintf( stdout, "Diagnostic::diagnoses_one_choice Collection B\n" );
	for( size_t i = 0; i < result.size(); i++ )
	{
		fprintf( stdout, "\t" );
		result.at( i ).print( std::to_string( i ) );
		fprintf( stdout, "\n" );
	}
#endif

	// Calling the computation of the Minimal Hitting Set on the resulting gate
	// cones
	mhs( result );
}

void Diagnostic::print_solutions( FILE* file )
{
	_solution.print( file );
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
		exit( -1 );
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
	fprintf( stdout, "\nDiagnostic::get_ok_subset_number %d having %lu OK\n",
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
				fprintf( stdout, "\tComparing with '%s' '%s' ",
							_ko_gates.at( i ).c_str(),
							to_string( _values.find( _ko_gates.at( i ) )->second ) );
#endif
				// If the two cones have an intersection then i stop the
				// procedure and return a true value: there is an intersection
				if( _cones.find( value_it->first )->second
						.intersecate( _cones.find( _ko_gates.at( i ) )->second ) )
				{
#ifdef DEBUG
					fprintf( stdout, "found\n" );
#endif
					return true;
				}

#ifdef DEBUG
				fprintf( stdout, "\n" );
#endif
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

void Diagnostic::update_processing_vector( value_map& current_status )
{
	_processing_ok.clear();
	_processing_ko.clear();
	_processing_okm.clear();
	_processing_kom.clear();

	for( value_map::iterator it = current_status.begin();
		 it != current_status.end();
		 it++ )
	{
		switch( it->second )
		{
			case GateValue::OK:
				_processing_ok.push_back( it->first );
				break;

			case GateValue::KO:
				_processing_ko.push_back( it->first );
				break;
				
			case GateValue::OKM:
				_processing_okm.push_back( it->first );
				break;

			case GateValue::KOM:
				_processing_kom.push_back( it->first );
				break;

			default:
				fprintf( stdout, "Diagnotic::update_processing_vector Error\n" );
				return;
		}
	}

#ifdef DEBUG
	print_processing_status();
#endif
}

void Diagnostic::print_processing_status()
{
	fprintf( stdout, "Diagnostic::print_processing_vector current status\n\t" );
	print_gatelist( _processing_ok, "OK", stdout );
	fprintf( stdout, "\n\t" );
	print_gatelist( _processing_ko, "KO", stdout );
	fprintf( stdout, "\n\t" );
	print_gatelist( _processing_okm, "OKM", stdout );
	fprintf( stdout, "\n\t" );
	print_gatelist( _processing_kom, "KOM", stdout );
	fprintf( stdout, "\n" );
}

int Diagnostic::get_choice_combinations_number()
{
#ifdef DEBUG
	fprintf( stdout, "\nDiagnostic::get_choice_combinations_number %d having %lu OKM and %lu KO\n",
				( _processing_okm.size() == 0 ? 
					0 : 
					(int) pow( _ko_gates.size(), _processing_okm.size() ) ),
				_processing_okm.size(),
				_ko_gates.size() );
#endif

	return (int)( _processing_okm.size() == 0 ? 
					0 : 
					pow( _ko_gates.size(), _processing_okm.size() ) );
}

// Composing the ith combination of the possible choices, starting from the OKM
// and KO lists
// The combination number will get transformed in a different base number
// according to the current KO list size
choice_list* Diagnostic::get_ith_choice( int combination_number )
{
#ifdef DEBUG
	fprintf( stdout, "Diagnostic::get_ith_choice %d\n", combination_number );
#endif

	choice_list* result = new choice_list();
	
	// Clearing the kom vector
	_processing_kom.clear();

	for( size_t i = 0; i < _processing_okm.size(); i++ )
	{
		result->push_back( 
			choice( 
				_processing_okm.at( i ),
				_ko_gates.at( combination_number % _ko_gates.size() ) ) );

		// Adding the current element to the kom gates, if not already in it
		if( std::find( _processing_kom.begin(),
					   _processing_kom.end(),
					   _ko_gates.at( combination_number % _ko_gates.size() ) )
			== _processing_kom.end() )
			_processing_kom.push_back( 
				_ko_gates.at( combination_number % _ko_gates.size() ) );

		// Going forward to the next okm element
		combination_number /= _ko_gates.size();
	}

#ifdef DEBUG
	for( size_t i = 0; i < result->size(); i++ )
		fprintf( stdout, "\t(%s, %s)\n",
					result->at( i ).first.c_str(),
					result->at( i ).second.c_str() );
#endif

	return result;
}

void Diagnostic::mhs( cone_list& cone_collection )
{
	std::vector< gate_list > result = std::vector< gate_list >();

	// Printing the collection to a file as requested for the mhs solver
	// Retrieving all the gates present in the collection
	GateCone final_gates = GateCone();

	for( size_t i = 0; i < cone_collection.size(); i++ )
		final_gates = final_gates.join( cone_collection.at( i ) );

#ifdef DEBUG
	fprintf( stdout, "Diagnostic::mhs Final Gates\n\t" );
	final_gates.print( "Final Gates" );
	fprintf( stdout, "\n" );
#endif

	// Creating the file for the mhs solver
	FILE* file_output = fopen( 
		StringConstants::FILE_OUTPUT_FOR_STACCATO.c_str(), "w" );
	if( file_output == NULL )
	{
		fprintf( stdout, "Diagnostic::mhs Error creating '%s' file\n",
					StringConstants::FILE_OUTPUT_FOR_STACCATO.c_str() );
		exit( -1 );
	}

#ifdef DEBUG
	fprintf( stdout, "Diagnostic::mhs Staccato input file\n" );
#endif

	// Cycling on the collection and final gates to create the matrix
	for( cone_list::iterator cone_it = cone_collection.begin();
		 cone_it != cone_collection.end();
		 cone_it++ )
	{
#ifdef DEBUG
		fprintf( stdout, "\t" );
#endif

		for( GateConeIterator gate_it = final_gates.begin();
			 gate_it != final_gates.end();
			 gate_it++ )
		{
#ifdef DEBUG
			fprintf( stdout, "%d ", cone_it->has_element( *gate_it ) );
#endif
			fprintf( file_output, "%d ", cone_it->has_element( *gate_it ) );
		}

#ifdef DEBUG
		fprintf( stdout, "-\n" );
#endif
		fprintf( file_output, "-\n" );
	}

	// Closing the file
	fclose( file_output );

	// Launching the staccato program
	// Creating the command
	char mhs_command[ 250 ];
	sprintf( mhs_command, "%s -o %lu %s > %s",
				StringConstants::EXEC_STACCATO.c_str(),
				final_gates.size(),
				StringConstants::FILE_OUTPUT_FOR_STACCATO.c_str(),
				StringConstants::FILE_OUTPUT_OF_STACCATO.c_str() );
#ifdef DEBUG
	fprintf( stdout, "Diagnostic::mhs Launching '%s': %s\n",
				StringConstants::EXEC_STACCATO.c_str(),
				mhs_command );
#endif

	// Executing staccato
	std::system( mhs_command );	

	// Reading the output file created
	std::ifstream input_file( StringConstants::FILE_OUTPUT_OF_STACCATO,
							  std::ifstream::in );
	if( input_file == NULL )
	{
		fprintf( stdout, "Diagnostic::mhs Error in opening file '%s'\n",
					StringConstants::FILE_OUTPUT_OF_STACCATO.c_str() );
		exit( -1 );
	}

	std::string line;
	gate_list current_result = gate_list();

	// Cycling on every line of the file and reading the result
	while( std::getline( input_file, line ) )
	{
		// Clearing the temporary value
		current_result.clear();

#ifdef DEBUG
		fprintf( stdout, "Diagnostic::mhs Processing '%s': ", line.c_str() );
#endif

		while( line.find( "," ) != std::string::npos )
		{
#ifdef DEBUG
			fprintf( stdout, "'%s' ",
					 line.substr( 1, line.find( "," ) - 1 ).c_str() );
#endif
			// Adding the corresponding final gate to the current result
			current_result.push_back( 
				final_gates.element_at( 
					std::stoi( line.substr( 1, line.find( "," ) - 1 ) ) - 1 ) );

			// Going to the successive element of the line
			line = line.substr( line.find( "," ) + 1 );
		}

#ifdef DEBUG
		fprintf( stdout, "'%s'\n", line.substr( 1 ).c_str() );
#endif

		// Processing the last element
		current_result.push_back( 
			final_gates.element_at( 
				std::stoi( line.substr( 1 ) ) - 1 ) );

		// Saving the current result
		result.push_back( current_result );
	}

	// Closing the file
	input_file.close();

	// Saving the result in the solution
	_solution.save( result, 
					_processing_ok, 
					_processing_ko, 
					_processing_okm,
					_processing_kom );

#ifdef DEBUG
	fprintf( stdout, "Diagnostic::mhs Result\n" );
	for( size_t i = 0; i < result.size(); i++ )
	{
		fprintf( stdout, "\t{" );
		for( size_t j = 0; j < result.at( i ).size(); j++ )
		{
			if( j != 0 )
				fprintf( stdout, "," );
			fprintf( stdout, " %s", result.at( i ).at( j ).c_str() );
		}
		fprintf( stdout, " }\n" );
	}
#endif
	
}
