/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Constants file
 *
 */

#ifndef CONSTANTS
#define CONSTANTS

#include <string>

class StringConstants
{
	public:
		static const std::string PATH_INSTANCES;
		static const std::string PATH_CIRCUITS;
		static const std::string PATH_SIM_SOLUTION;

		static const std::string FILE_INPUT_CONFIGURATION;
		static const std::string FILE_FAILING_GATES;
		static const std::string FILE_INPUT_DATA_DIAGNOSTIC;
		static const std::string FILE_OUTPUT_FOR_STACCATO;
		static const std::string FILE_OUTPUT_OF_STACCATO;

		static const std::string EXT_SIM_SOLUTION;

		static const std::string EXEC_STACCATO;
};

#endif
