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
	found_new_solution();
}

void DiagnosticSolution::save( std::vector< GateCone >& B,
							   gate_list& ok,
							   gate_list& ko,
							   gate_list& okm,
							   gate_list& kom )
{
	SolutionData solution_temp = SolutionData( ok, ko, okm, kom, B );
	solution_temp.print( _solutions_found, _output_file );
	found_new_solution();
}

void DiagnosticSolution::found_new_solution()
{
	_solutions_found++;

	// User interface stuff
	if( fmod( _solutions_found, PRINTING_GAP ) == 0 )
	{
		fprintf( stdout, "." );
		fflush( stdout );
		fprintf( _output_file, "%.0lf ", _solutions_found );
		if( fmod( _solutions_found, PRINTING_GAP * 10 ) == 0 )
			fprintf( _output_file, "\n" );
		fflush( _output_file );
	}
}

void DiagnosticSolution::print( FILE* file )
{
	fprintf( file, "DiagnosticSolution::print %.0lf solutions found\n",
				_solutions_found );
}
