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

typedef std::set< std::string >::iterator GateConeIterator;

class GateCone
{
	public:
		GateCone();
		~GateCone();

		size_t size();
		GateConeIterator begin();
		GateConeIterator end();
		std::string element_at( int );
		void insert( std::string& );

		// Set operations
		GateCone join( GateCone& );
		GateCone complement( GateCone& );
		GateCone intersection( GateCone& );

		bool intersecate( GateCone& );
		bool empty();
		bool has_element( const std::string& );

		void print( const std::string&, FILE* = stdout );

	private:
		std::set< std::string > _cone;
};


#endif

