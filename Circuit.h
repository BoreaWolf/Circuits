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
#include <vector>

// Map to easily access every component of the circuit
typedef std::map< std::string, Component* > component_map;

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
		// The output is nothing else than a final logical gate
		std::vector< LogicalGate* > _output;
		std::vector< LogicalGate* > _logical_gates;
};

#endif

