/*
 * Author: Riccardo Orizio (R)
 * Date: 5 March 2016
 *
 * Description: Class that represents a Diagnostic Solution
 *
 */

#ifndef DIAGNOSTIC_SOLUTION
#define DIAGNOSTIC_SOLUTION

#include "./GateCone.h"

#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>

#define PRINTING_GAP 1000

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
	std::vector< GateCone > _collection_B;
	std::vector< gate_list > _mhs;

	SolutionData()
	{
		_ok = gate_list();
		_ko = gate_list();
		_okm = gate_list();
		_kom = gate_list();
		_collection_B = std::vector< GateCone >();
		_mhs = std::vector< gate_list >();
	}

	SolutionData( gate_list& ok,
				  gate_list& ko,
				  gate_list& okm,
				  gate_list& kom,
				  std::vector< gate_list >& mhs )
	{
		_ok = ok;
		_ko = ko;
		_okm = okm;
		_kom = kom;
		_collection_B = std::vector< GateCone >();
		_mhs = mhs;
	}

	SolutionData( gate_list& ok,
				  gate_list& ko,
				  gate_list& okm,
				  gate_list& kom,
				  std::vector< GateCone >& B )
	{
		_ok = ok;
		_ko = ko;
		_okm = okm;
		_kom = kom;
		_collection_B = B;
		_mhs = std::vector< gate_list >();
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

		// Depending on which kind of data I stored I print different things
		// MHS
		if( _mhs.size() > 0 )
		{
			fprintf( file, "\n\tMHS:\n" );
			for( size_t i = 0; i < _mhs.size(); i++ )
			{
				fprintf( file, "\t\t%lu: {", i );
				for( size_t j = 0; j < _mhs.at( i ).size(); j++ )
				{
					if( j != 0 )
						fprintf( file, "," );
					fprintf( file, " %s", _mhs.at( i ).at( j ).c_str() );
				}

				fprintf( file, " }\n" );
			}
		}
		// Collection B
		else
		{
			fprintf( file, "\n\tCollection B:\n" );
			for( size_t i = 0; i < _collection_B.size(); i++ )
			{
				fprintf( file, "\t\t" );
				_collection_B.at( i ).print( std::to_string( i ), file );
				fprintf( file, "\n" );
			}
		}
	}
};

class DiagnosticSolution
{
	public:
		DiagnosticSolution();
		DiagnosticSolution( FILE* );
		~DiagnosticSolution();

		int size();

		// Saving the result of the MHS
		void save( std::vector< gate_list >&,
				   gate_list&,
				   gate_list&,
				   gate_list&,
				   gate_list& );

		// Saving the Collection B
		void save( std::vector< GateCone >&,
				   gate_list&,
				   gate_list&,
				   gate_list&,
				   gate_list& );

		// New solution found
		void found_new_solution( bool = false );

		void print( FILE* = stdout );
	
	private:
		double _solutions_found;
		FILE* _output_file;
};

#endif

