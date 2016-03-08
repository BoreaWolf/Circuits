/*
 * Author: Riccardo Orizio (R)
 * Date: 8 March 2016
 *
 * Description: Enum the represents the possible types of Diagnoses
 *
 */

#ifndef DIAGNOSES_TYPE
#define DIAGNOSES_TYPE

enum class DiagnosesType : int
{
	ALL_DIAGNOSES = 0,
	NO_MASKING = 1,
	ALL_MASKING = 2,
	OKM_MASKING = 3,
	KOM_MASKING = 4
};

inline const char* to_string( DiagnosesType v )
{
    switch( v )
    {
		case DiagnosesType::ALL_DIAGNOSES:	return "All Diagnoses";
		case DiagnosesType::NO_MASKING:		return "No Masking Diagnoses";
		case DiagnosesType::ALL_MASKING:	return "All Masking Diagnoses";
		case DiagnosesType::OKM_MASKING:	return "OKM Masking Diagnoses";
		case DiagnosesType::KOM_MASKING:	return "KOM Masking Diagnoses";
    }
}

#endif

