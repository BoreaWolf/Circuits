/*
 * Author: Riccardo Orizio (R)
 * Date: 4 March 2016
 *
 * Description: Class that represents the Diagnostics
 *
 */

#ifndef DIAGNOSTIC
#define DIAGNOSTIC

#include "DiagnosticSolution.h"
#include "GateCone.h"
#include "GateValue.h"

#include <algorithm>
#include <fstream>
#include <regex>
#include <map>
#include <math.h>
#include <stdio.h>
#include <string>

// Type definitions
typedef std::map< std::string, GateCone > cone_map;
typedef std::map< std::string, GateValue > value_map;
typedef std::vector< std::string > gate_list;
typedef std::pair< std::string, std::string > choice;
typedef std::vector< choice > choice_list;

enum class DiagnosesType : int
{
	ALL_DIAGNOSES = 0,
	NO_MASKING = 1,
	ALL_MASKING = 2,
	OK_MASKING = 3,
	KO_MASKING = 4
};

inline const char* to_string( DiagnosesType v )
{
    switch( v )
    {
		case DiagnosesType::ALL_DIAGNOSES:	return "All Diagnoses";
		case DiagnosesType::NO_MASKING:		return "No Masking Diagnoses";
		case DiagnosesType::ALL_MASKING:	return "All Masking Diagnoses";
		case DiagnosesType::OK_MASKING:		return "Ok Masking Diagnoses";
		case DiagnosesType::KO_MASKING:		return "Ko Maskning Diagnoses";
    }
}

class Diagnostic
{
	public:
		Diagnostic( const std::string& );
		~Diagnostic();

		void solve( DiagnosesType );

		// Setting some output values to OKM
		void all_diagnoses();
		// Setting some other output values to KOM
		void diagnoses_one_config( value_map& );
		// I don't know yet
		void diagnoses_one_choice();

	
	private:
		// Methods
		void load( const std::string& );

		gate_list* get_ith_ok_subset( int );
		int get_ok_subset_number();
		bool check_cone_intersection( value_map& );
		
		// Attributes
		std::string _name;

		// TODO Should I keep these two maps separated or should I join them in
		// one map of string pair?
		cone_map _cones;
		value_map _values;
		gate_list _ok_gates;
		gate_list _ko_gates;
		DiagnosticSolution _solution;
};

#endif

