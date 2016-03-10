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
{	}

DiagnosticSolution::DiagnosticSolution( FILE* output_file )
{
	_solutions_found = 0;
	_output_file = output_file;

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
	return _solutions_found;
}

void DiagnosticSolution::save( std::vector< gate_list >& mhs,
							   gate_list& ok,
							   gate_list& ko,
							   gate_list& okm,
							   gate_list& kom )
{
	// Saving the result on file, so I don't store anything in memory
	SolutionData solution_temp = SolutionData( ok, ko, okm, kom, mhs );
	solution_temp.print( _solutions_found, _output_file );
	_solutions_found++;

	// User interface stuff
	if( _solutions_found % PRINTING_GAP == 0 )
	{
		fprintf( stdout, "." );
		fflush( stdout );
	}
}

void DiagnosticSolution::save( std::vector< GateCone >& B,
							   gate_list& ok,
							   gate_list& ko,
							   gate_list& okm,
							   gate_list& kom )
{
	SolutionData solution_temp = SolutionData( ok, ko, okm, kom, B );
	solution_temp.print( _solutions_found, _output_file );
	_solutions_found++;
		
	// User interface stuff
	if( _solutions_found % PRINTING_GAP == 0 )
	{
		fprintf( stdout, "." );
		fflush( stdout );
	}
}

void DiagnosticSolution::print( FILE* file )
{
	fprintf( file, "DiagnosticSolution::print %d solutions found\n",
				_solutions_found );
}
