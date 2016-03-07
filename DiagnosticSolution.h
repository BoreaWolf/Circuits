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
#include <string>
#include <vector>

typedef std::vector< std::string > gate_list;

inline void print_gatelist( gate_list& list, std::string type, FILE* file )
{
		fprintf( file, "%s: ", type.c_str() );
		for( size_t i = 0; i < list.size(); i++ )
			fprintf( file, "'%s' ", list.at( i ).c_str() );
}

struct SolutionData
{
	gate_list _ok;
	gate_list _ko;
	gate_list _okm;
	gate_list _kom;
	std::vector< gate_list > _mhs;

	SolutionData()
	{
		_ok = gate_list();
		_ko = gate_list();
		_okm = gate_list();
		_kom = gate_list();
		_mhs = std::vector< gate_list >();
	}

	SolutionData( gate_list& ok,
				  gate_list& ko,
				  gate_list& okm,
				  gate_list& kom,
				  std::vector< gate_list > mhs )
	{
		_ok = ok;
		_ko = ko;
		_okm = okm;
		_kom = kom;
		_mhs = mhs;
	}

	~SolutionData()
	{	}

	void print( int solution_number, FILE* file )
	{
		fprintf( file, "Solution %d:\n\t", solution_number );
		print_gatelist( _ok, "OK", file );
		fprintf( file, "\n\t" );
		print_gatelist( _ko, "KO", file );
		fprintf( file, "\n\t" );
		print_gatelist( _okm, "OKM", file );
		fprintf( file, "\n\t" );
		print_gatelist( _kom, "KOM", file );

		fprintf( file, "\n\tMHS:\n" );
		for( size_t i = 0; i < _mhs.size(); i++ )
		{
			fprintf( stdout, "\t\t%lu: {", i );
			for( size_t j = 0; j < _mhs.at( i ).size(); j++ )
			{
				if( j != 0 )
					fprintf( stdout, "," );
				fprintf( stdout, " %s", _mhs.at( i ).at( j ).c_str() );
			}

			fprintf( stdout, " }\n" );
		}
	}
};


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

		void print( FILE* = stdout );
	
	private:
		std::vector< SolutionData > _solutions;
};

#endif

