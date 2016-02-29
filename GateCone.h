/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Gate Cone class, list of other Gates that influences the result
 * of one next gate
 *
 */

#ifndef GATE_CONE
#define GATE_CONE

#include <set>
#include <stdio.h>
#include <string>

class GateCone
{
	public:
		GateCone();
		~GateCone();

		size_t size();
		std::set< std::string >::iterator& begin();
		std::set< std::string >::iterator& end();
		void insert( std::string& );
		void join( GateCone& );
		void print( const std::string&, FILE* = stdout );

	private:
		std::set< std::string > _cone;
};

#endif

