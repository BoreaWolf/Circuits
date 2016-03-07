/*
 * Author: Riccardo Orizio (R)
 * Date: 5 March 2016
 *
 * Description: Class that represents a Diagnostic Solution
 *
 */

#ifndef DIAGNOSTIC_SOLUTION
#define DIAGNOSTIC_SOLUTION

#include <stdio.h>
#include <vector>

class DiagnosticSolution
{
	public:
		DiagnosticSolution();
		~DiagnosticSolution();

		void save( std::vector< gate_list >&,
				   gate_list&,
				   gate_list&,
				   gate_list&,
				   gate_list& );
	
	private:
};

#endif

