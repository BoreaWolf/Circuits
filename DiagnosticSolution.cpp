/*
 * Author: Riccardo Orizio (R)
 * Date: 5 March 2016
 *
 * Description: Implementation of the Diagnostic Solution class
 *
 */

#include "DiagnosticSolution.h"

#ifndef DEBUG
//	#define DEBUG
#endif

DiagnosticSolution::DiagnosticSolution()
{
#ifdef DEBUG
	fprintf( stdout, "DiagnosticSolution::DiagnosticSolution Created %p\n", this );
	fflush( stdout );
#endif
}

DiagnosticSolution::~DiagnosticSolution()
{
#ifdef DEBUG
	fprintf( stdout, "DiagnosticSolution::~DiagnosticSolution Destroying %p\n", this );
	fflush( stdout );
#endif
}

int DiagnosticSolution::size()
{
	return _solutions.size();
}

void DiagnosticSolution::save( std::vector< gate_list >& mhs,
							   gate_list& ok,
							   gate_list& ko,
							   gate_list& okm,
							   gate_list& kom )
{
	_solutions.push_back( SolutionData( ok, ko, okm, kom, mhs ) );
	// User interface stuff
	fprintf( stdout, "." );
	fflush( stdout );
}

void DiagnosticSolution::print( FILE* file )
{
	fprintf( file, "DiagnosticSolution::print Solutions\n" );
	for( size_t i = 0; i < _solutions.size(); i++ )
		_solutions.at( i ).print( i, file );
}
