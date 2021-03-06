/*
 * Author: Riccardo Orizio (R)
 * Date: 4 March 2016
 *
 * Description: Class that represents the Diagnostics
 *
 */

#ifndef DIAGNOSTIC
#define DIAGNOSTIC

#include "./constants.h"
#include "./DiagnosesType.h"
#include "./DiagnosticSolution.h"
#include "./GateCone.h"
#include "./GateValue.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <math.h>
#include <stdio.h>
#include <string>

enum class ProcessingStatus : int
{
	SOLUTION_FOUND = 0,
	OUT_OF_TIME = 1,
	COMPLEMENT_INTERSECTION_EMPTY = 2,
	SKIPPING_CONFIGURATION = 3,
	DONE = 4
};

// Type definitions
typedef std::map< std::string, GateCone > cone_map;
typedef std::map< std::string, GateValue > value_map;
typedef std::pair< std::string, std::string > choice;
typedef std::vector< choice > choice_list;
typedef std::vector< GateCone > cone_list;
typedef std::chrono::milliseconds time_um;

class Diagnostic
{
	public:
		Diagnostic( const std::string&, FILE* );
		~Diagnostic();

		void solve( DiagnosesType& );

		// Setting some output values to OKM
		ProcessingStatus all_diagnoses( DiagnosesType& );
		// Setting some other output values to KOM
		ProcessingStatus diagnoses_one_config( DiagnosesType& );
		// Calculating the final diagnoses solution
		ProcessingStatus diagnoses_one_choice( cone_map&, choice_list& );

		void print_solutions( FILE* = stdout );

	private:
		// Methods
		void load( const std::string& );

		void get_ith_ok_subset( double, gate_list& );
		double get_ok_subset_number();
		bool check_cone_intersection( value_map& );

		void update_processing_vector( value_map& );
		void print_processing_status();

		double get_choice_combinations_number();
		void get_ith_choice( double, choice_list& );

		bool check_end_of_time();

		void mhs( cone_list& );
		
		// Attributes
		std::string _name;

		// Map of cones and of output values with lists to easily locate ok and
		// ko gates
		cone_map _cones;
		value_map _values;
		gate_list _ok_gates;
		gate_list _ko_gates;

		// Lists of gates that are going to be kept updated while the processing
		// goes on
		gate_list _processing_ok;
		gate_list _processing_ko;
		gate_list _processing_okm;
		gate_list _processing_kom;

		DiagnosticSolution _solution;

		// Times
		double _execution_time;
		double _mhs_processing_time;
		std::chrono::high_resolution_clock::time_point _starting_time;

		FILE* _output_file;
};

#endif

