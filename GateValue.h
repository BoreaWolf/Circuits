/*
 * Author: Riccardo Orizio (R)
 * Date: 5 March 2016
 *
 * Description: Enum that represents the possible values of a Gate
 *
 */

#ifndef GATE_VALUE
#define GATE_VALUE

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

#endif

