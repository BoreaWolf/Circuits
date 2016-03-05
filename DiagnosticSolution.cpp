/*
 * Author: Riccardo Orizio (R)
 * Date: 5 March 2016
 *
 * Description: Implementation of the Diagnostic Solution class
 *
 */

#include "DiagnosticSolution.h"

#ifndef DEBUG
#define DEBUG
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
