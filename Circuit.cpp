/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Implementation of the Circuit class
 *
 */

#include "Circuit.h"

#ifndef DEBUG
//	#define DEBUG
#endif

Circuit::Circuit( const std::string& input_filename )
{
	_name = input_filename;
	load( _name );

#ifdef DEBUG
	fprintf( stdout, "Circuit::Circuit Created %p\n", this );
	fflush( stdout );
#endif
}

// TODO: Delete every object in the vectors
Circuit::~Circuit()
{
#ifdef DEBUG
	fprintf( stdout, "Circuit::~Circuit Destroying %p\n", this );
	fflush( stdout );
#endif
}

void Circuit::load( const std::string& input_filename )
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

	std::vector< std::string > outputs;
	std::vector< Component* > gate_inputs;

	// Reading lines one per time and applying the regex
	while( std::getline( input_file, line ) )
	{
		// Skipping empty lines
		if( line.length() > 1 )
		{
			// Terminals regex: Input and Output
			if( std::regex_search( line, regex_results, regex_terminals ) )
			{
#ifdef DEBUG	
				fprintf( stdout, "IN/OUT found %lu: ", regex_results.size() );
				for( size_t i = 0; i < regex_results.size(); i++ )
					fprintf( stdout, "'%s' ", regex_results.str( i ).c_str() );
				fprintf( stdout, "\n" );
#endif

				// Creating the input terminal
				if( regex_results.str( 1 ).compare( "IN" ) == 0 )
				{
					// Creating a new Input Terminal
					_input.push_back( 
						new InputTerminal( regex_results.str( 2 ) ) );
				}
				else
					// Saving the name of the output terminal, I'll use it later
					if( regex_results.str( 1 ).compare( "OUT" ) == 0 )
						outputs.push_back( regex_results.str( 2 ) );
			}
			else
			{
				// Logical ports regex
				if( std::regex_search( line, regex_results, regex_logic_ports ) )
				{
					
#ifdef DEBUG
					fprintf( stdout, "Logic port found %lu: ", regex_results.size() );
					for( size_t i = 0; i < regex_results.size(); i++ )
						fprintf( stdout, "'%s' ", regex_results.str( i ).c_str() );
					fprintf( stdout, "\n" );
#endif
					

					// Getting the inputs name
					gate_inputs.clear();
					// The input elements are in the third and fourth
					// regex_results, always having one element in the third one
					// despite the fourth that could have one, a list or no
					// elements
					gate_inputs.push_back(
						_components.find( regex_results.str( 3 ) )->second );

					if( !regex_results.str( 4 ).empty() )
					{
						std::string input_list = regex_results.str( 4 );

						size_t pos;
						// Deleting the first comma
						input_list.erase( 0, 1 );

						while( ( pos = input_list.find( "," ) ) != std::string::npos )
						{
							gate_inputs.push_back(
								_components.find( input_list.substr( 0, pos ) )->second );
							
							// Deleting the input name just processed
							input_list.erase( 0, pos + 1 );
						}

						// Adding the last element
						gate_inputs.push_back(
							_components.find( input_list )->second );
					}

#ifdef DEBUG
					fprintf( stdout, "%lu Gates: ", gate_inputs.size() );
					fflush( stdout );
					for( size_t i = 0; i < gate_inputs.size(); i++ )
					 fprintf( stdout, "%s ", gate_inputs.at( i )->get_name().c_str() );
					fprintf( stdout, "\n" );
					fflush( stdout );
#endif

					// Creating different logical gates depending on the type
					// read
					if( regex_results.str( 2 ).compare( "AND" ) == 0 )
						_logical_gates.push_back(
							new AndGate( regex_results.str( 1 ),
										 gate_inputs ) );

					else if( regex_results.str( 2 ).compare( "NAND" ) == 0 )
								_logical_gates.push_back(
									new NandGate( regex_results.str( 1 ),
												  gate_inputs ) );

					else if( regex_results.str( 2 ).compare( "NOR" ) == 0 )
								_logical_gates.push_back(
									new NorGate( regex_results.str( 1 ),
												 gate_inputs ) );

					else if( regex_results.str( 2 ).compare( "NOT" ) == 0 )
								_logical_gates.push_back(
									new NotGate( regex_results.str( 1 ),
												 gate_inputs ) );
					
					else if( regex_results.str( 2 ).compare( "OR" ) == 0 )
								_logical_gates.push_back(
									new OrGate( regex_results.str( 1 ),
												gate_inputs ) );

					else if( regex_results.str( 2 ).compare( "XNOR" ) == 0 )
								_logical_gates.push_back(
									new XnorGate( regex_results.str( 1 ),
												  gate_inputs ) );

					else if( regex_results.str( 2 ).compare( "XOR" ) == 0 )
								_logical_gates.push_back(
									new XorGate( regex_results.str( 1 ),
												 gate_inputs ) );

				}
				// Something is not recognized correctly
				else
				{
					fprintf( stdout, "Circuit::load Error in reading the input file! %s line read not recognized.\n", line.c_str() );
					exit( 1 );
				}
			}

			// Adding the component to the map, checking if it was a terminal
			// input or a logical gate
			if( regex_results.str( 1 ).compare( "IN" ) == 0 )
			{
				_components.insert(
					std::pair< std::string, Component* >
						(
						    _input.at( _input.size() - 1 )->get_name(),
						    _input.at( _input.size() - 1 )
						)
					);
			}
			else if( regex_results.str( 1 ).compare( "OUT" ) != 0 )
			{
				_components.insert( 
					std::pair< std::string, Component* >
						(
						    _logical_gates.at( _logical_gates.size() - 1 )->get_name(),
						    _logical_gates.at( _logical_gates.size() - 1 )
						)
				 );
			}
		}

#ifdef DEBUG
		fprintf( stdout, "Map size: %lu => ", _components.size() );
		for( component_map::iterator i = _components.begin(); i != _components.end(); i++ )
			fprintf( stdout, "%s(%p) ",
						i->first.c_str(),
						i->second );
		fprintf( stdout, "\n" );
		fflush( stdout );
#endif
	}

	// Adding the output terminals
	for( size_t i = 0; i < outputs.size(); i++ )
		_output.push_back(
			new OutputTerminal( outputs.at( i ),
								_components.find( outputs.at( i ) )->second ) );

	// Closing the file
	input_file.close();
}
