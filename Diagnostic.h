/*
 * Author: Riccardo Orizio (R)
 * Date: 4 March 2016
 *
 * Description: Class that represents the Diagnostics
 *
 */

#ifndef DIAGNOSTIC
#define DIAGNOSTIC

#include "GateCone.h"

#include <fstream>
#include <regex>
#include <map>
#include <stdio.h>
#include <string>

enum class GateValue : int
{
	OK = 0,
	KO = 1,
	OKM = 2,
	KOM = 3
};

inline const char* to_string( GateValue v )
{
    switch( v )
    {
		case GateValue::OK:		return "OK";
		case GateValue::KO:		return "KO";
		case GateValue::OKM:	return "OKM";
		case GateValue::KOM:	return "KOM";
    }
}

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
	
	private:
		// Methods
		void load( const std::string& );
		
		// Attributes
		std::string _name;

		// TODO Should I keep these two maps separated or should I join them in
		// one map of string pair?
		std::map< std::string, GateCone > _cones;
		std::map< std::string, GateValue > _values;
};

#endif

