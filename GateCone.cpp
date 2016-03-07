/*
 * Author: Riccardo Orizio (R)
 * Date: 24 February 2016
 *
 * Description: Implementation of the Gate Cone class
 *
 */

#include "GateCone.h"

#ifndef DEBUG
//	#define DEBUG
#endif

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

std::string GateCone::element_at( int position )
{
	GateConeIterator result = _cone.begin();
	while( (position--) > 0 )
		result++;
	return *result;
}

void GateCone::insert( std::string& entry )
{
	_cone.insert( entry );
}

GateCone GateCone::join( GateCone& cone )
{
	GateCone result = GateCone( *this );

	result._cone.insert( cone.begin(), cone.end() );

	return result;
}

GateCone GateCone::complement( GateCone& cone )
{
	// Copying the current cone into the resulting one
	GateCone result = GateCone( *this );

	// Going on every element of the argument cone and if I find one its
	// elements also in the current cone then I'll delete from the current one
	for( std::set< std::string >::iterator it = cone.begin();
		 it != cone.end();
		 it++ )
		if( result._cone.find( *it ) != result._cone.end() )
		{
#ifdef DEBUG
			fprintf( stdout, "GateCone::complement found '%s' between ",
						it->c_str() );
			print( "" );
			fprintf( stdout, " " );
			cone.print( "" );
			fprintf( stdout, ": removed\n" );
#endif
			result._cone.erase( *it );
		}

	return result;
}

GateCone GateCone::intersection( GateCone& cone )
{
#ifdef DEBUG
	fprintf( stdout, "GateCone::intersection between " );
	print( "" );
	fprintf( stdout, " " );
	cone.print( "" );
	fprintf( stdout, "{ " );
#endif

	GateCone result = GateCone();

	for( std::set< std::string >::iterator it = cone.begin();
		 it != cone.end();
		 it++ )
	{
		if( _cone.find( *it ) != _cone.end() )
		{
#ifdef DEBUG
			fprintf( stdout, "%s ", it->c_str() );
#endif
			result._cone.insert( *it );
		}
	}

#ifdef DEBUG
	fprintf( stdout, "}\n" );
#endif

	return result;
}

bool GateCone::intersecate( GateCone& cone )
{
	// Passing every element of the argument cone and checking if I find it in
	// the current one
	for( std::set< std::string >::iterator it = cone.begin();
		 it != cone.end();
		 it++ )
		if( _cone.find( *it ) != _cone.end() )
		{
#ifdef DEBUG
			fprintf( stdout, "GateCone::intersecate found '%s' between ",
						it->c_str() );
			print( "" );
			fprintf( stdout, " " );
			cone.print( "" );
			fprintf( stdout, "\n" );
#endif
			return true;
		}

	// No intersections have been found between the two cones
	return false;
}

bool GateCone::empty()
{
	return _cone.empty();
}

bool GateCone::has_element( const std::string& entry )
{
	if( _cone.find( entry ) != _cone.end() )
		return true;
	else
		return false;
}

void GateCone::print( const std::string& component_name, FILE* file )
{
	// Instead of writing a sort of message error when I find an empty cone
	// (happens when an Output Terminal is directly connected with an Input
	// Terminal), I'll treat this particular case in the same way of the others,
	// at the end I will have an empty list of components

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
