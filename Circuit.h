/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Class that represents a single Circuit instance
 *
 */

#ifndef CIRCUIT
#define CIRCUIT

#include "./Component.h"

#include <fstream>
#include <map>
#include <regex>
#include <vector>

// Map to easily access every component of the circuit
typedef std::map< int, Component* > component_map;

class Circuit
{
	public:
		Circuit( std::string );
		~Circuit();
	
	private:
		// Methods
		void load( std::string );
		
		// Attributes
		// Map of pointers to every item in the circuit
		component_map _components;

		// The real components of the circuit
		std::vector< InputTerminal > _input;
		std::vector< OutputTerminal > _output;
		std::vector< LogicalPorts > _logical_ports;
};

#endif

