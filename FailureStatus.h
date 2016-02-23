/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Failure status enum class
 *
 */

#ifndef FAILURE_STATUS
#define FAILURE_STATUS

#include <string>

enum class FailureStatus : int
{
	stuck_to_zero = 0,
	stuck_to_one = 1,
	correct = -1
};

#endif

