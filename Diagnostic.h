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

#include <fstream>
#include <regex>
#include <map>
#include <math.h>
#include <stdio.h>
#include <string>

typedef int sbra;
typedef std::map< std::string, GateCone > cone_map;
typedef std::map< std::string, GateValue > value_map;

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
		void all_diagnoses();
		void diagnoses_one_config( value_map* );
		void diagnoses_one_choice();

	
	private:
		// Methods
		void load( const std::string& );

		value_map* get_ith_ok_subset( int );
		int get_ok_subset_number();
		bool check_cone_interesection( value_map* );
		
		// Attributes
		std::string _name;

		// TODO Should I keep these two maps separated or should I join them in
		// one map of string pair?
		cone_map _cones;
		value_map _values;
		std::vector< std::string > _ok_gates;
		std::vector< std::string > _ko_gates;
		DiagnosticSolution _solution;
};

#endif

