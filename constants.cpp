/*
 * Author: Riccardo Orizio (R)
 * Date: 23 February 2016
 *
 * Description: String constants
 *
 */

#include "constants.h"

const std::string StringConstants::PATH_INSTANCES = "./instances/";
const std::string StringConstants::PATH_CIRCUITS = StringConstants::PATH_INSTANCES + "circuits/";
const std::string StringConstants::PATH_SIM_SOLUTION = StringConstants::PATH_INSTANCES + "simulation/";

const std::string StringConstants::FILE_INPUT_CONFIGURATION = StringConstants::PATH_INSTANCES + "input_configuration";
const std::string StringConstants::FILE_FAILING_GATES = StringConstants::PATH_INSTANCES + "failing_gates";
const std::string StringConstants::FILE_INPUT_DATA_DIAGNOSTIC = StringConstants::PATH_INSTANCES + "slide.sim_sol";
const std::string StringConstants::FILE_OUTPUT_FOR_STACCATO = "staccato_input";
const std::string StringConstants::FILE_OUTPUT_OF_STACCATO = "staccato_result";

const std::string StringConstants::EXT_SIM_SOLUTION = ".sim_sol";

const std::string StringConstants::EXEC_STACCATO = "./staccato_m/staccato/staccato";
