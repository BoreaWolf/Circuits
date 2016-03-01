/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Implementation of the Gate Cone class
 *
 */

#include "GateCone.h"

GateCone::GateCone()
{
	_cone = std::set< std::string >();
}

GateCone::~GateCone()
{	}

size_t GateCone::size()
{
	return _cone.size();
}

std::set< std::string >::iterator GateCone::begin()
{
	return _cone.begin();
}

std::set< std::string >::iterator GateCone::end()
{
	return _cone.end();
}

void GateCone::insert( std::string& entry )
{
	_cone.insert( entry );
}

void GateCone::join( GateCone& cone )
{
	_cone.insert( cone.begin(), cone.end() );
}

void GateCone::print( const std::string& component_name, FILE* file )
{
	if( _cone.empty() )
		fprintf( file, "No cone for %s because it's an Input Terminal\n",
					component_name.c_str() );
	else
	{
		fprintf( file, "Cone( %s ) = {", component_name.c_str() );
		for( std::set< std::string >::iterator i = _cone.begin(); i != _cone.end(); i++ )
		{
			// Just priting details
			if( i != _cone.begin() )
				fprintf( file, "," );

			fprintf( file, " %s", i->c_str() );
		}
		fprintf( file, " }" );
	}
}
