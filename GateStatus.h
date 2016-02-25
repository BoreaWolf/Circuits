/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: Gate status enum class
 *
 */

#ifndef GATE_STATUS
#define GATE_STATUS

#define GATE_UNKNOWN_VALUE -1

enum class GateStatus : int
{
	correct = -1,
	stuck_to_zero = 0,
	stuck_to_one = 1
};

#endif

