#!/usr/bin/env ruby

# Authors: Riccardo Orizio
# Date: 1 March 2016
# Parameters

# Constants for dealing with files created
# File extensions
FILE_EXT_INSTANCE = ".txt"
FILE_EXT_INITIAL_CONF = ".conf"
FILE_EXT_FAILURE_GATES = ".gates"

# Dir locations
DIR_INSTANCES = "./instances"
DIR_CIRCUITS = DIR_INSTANCES + "/circuits"
DIR_INITIAL_CONF = DIR_INSTANCES + "/init_conf"
DIR_FAILURE_GATES = DIR_INSTANCES + "/fail_gates"

# Exec file
EXEC_CIRCUIT_SIMULATION = "./simulation"
EXEC_CREATE_INSTANCE = "./create_instance.rb"
EXEC_SOLVE_CIRCUIT = "./solve_circuit.rb"
