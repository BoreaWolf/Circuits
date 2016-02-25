/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a single Circuit instance
 *
 */

#ifndef CIRCUIT
#define CIRCUIT

#include "./AndGate.h"
#include "./Component.h"
#include "./InputTerminal.h"
#include "./LogicalGate.h"
#include "./NandGate.h"
#include "./NorGate.h"
#include "./NotGate.h"
#include "./OrGate.h"
#include "./OutputTerminal.h"
#include "./XnorGate.h"
#include "./XorGate.h"

#include <fstream>
#include <map>
#include <regex>
#include <stdio.h>
#include <string>
#include <vector>

// Map to easily access every component of the circuit
typedef std::map< std::string, Component* > component_map;

class Circuit
{
	public:
		Circuit( const std::string& );
		~Circuit();

		const std::string& get_name(){ return _name; }

		//	std::vector< int >& solve();
		// TODO: Remove and remove the whole CircuitSet class
		void solve();
		void solve( const std::string&, const std::string& );
		void print_output_values( FILE* = stdout );
		void print_output_cones( FILE* = stdout );
		void print_cone( const std::string&, FILE* = stdout );
	
	private:
		// Methods
		void load( const std::string& );
		void load_initial_configuration( const std::string& );
		void load_failing_gates( const std::string& );
		
		// Attributes
		std::string _name;

		// Map of pointers to every item in the circuit
		component_map _components;

		// The real components of the circuit
		std::vector< InputTerminal* > _inputs;
		// The output is nothing else than a final logical gate
		std::vector< OutputTerminal* > _outputs;
		std::vector< LogicalGate* > _logical_gates;
};

#endif

