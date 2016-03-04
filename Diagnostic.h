/*
 * Author: Riccardo Orizio (R)
 * Date: 4 March 2016
 *
 * Description: Class that represents the Diagnostics
 *
 */

#ifndef DIAGNOSTIC
#define DIAGNOSTIC

#include <fstream>
#include <regex>
#include <stdio.h>
#include <string>
#include <vector>


class Diagnostic
{
	public:
		Diagnostic( const std::string&, const std::string& );
		~Diagnostic();

		void solve();
	
	private:
		// Methods
		void load( const std::string& );
		
		// Attributes
		std::string _name;
		std::string _diagnostic;
};

#endif

