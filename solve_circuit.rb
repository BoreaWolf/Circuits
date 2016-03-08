#!/usr/bin/env ruby

# Authors: Riccardo Orizio
# Date: 1 March 2016
# A program that solves a given circuit instance, generating a different initial
# configuration and failing gates every time

require_relative "constants.rb"

# Reading the circuit file given in input
circuit_filename = ARGV[ 0 ]

if circuit_filename == nil then
	puts "Error: I need a circuit file to proceed"
	exit( -1 )
end

# Creating the instance for the requested circuit
system( "#{EXEC_CREATE_INSTANCE} #{circuit_filename}" )

# Retrieving the last two created files so I can pass them to the circuit solver
# I don't check if the files that I'm taking are correct, I suppose so because
# it's a script and the new files are created just now
init_filename = Dir[ "#{DIR_INITIAL_CONF}/*#{FILE_EXT_INITIAL_CONF}" ].max_by{ |f| File.mtime( f ) }
gates_filename = Dir[ "#{DIR_FAILURE_GATES}/*#{FILE_EXT_FAILURE_GATES}" ].max_by{ |f| File.mtime( f ) }

# Keeping track of the time requested to solve the circuit
time_begin = Time.now

# Launching the solver on this instance
system( "#{EXEC_CIRCUIT_SIMULATION} #{circuit_filename} #{init_filename} #{gates_filename}" )

# Executing also the diagnostic part on the current circuit
# Reading the possible diagnostic types from the correspoding file
diagnoses_type = File.open( FILE_DIAGNOSES_TYPES )
					 .read
					 .scan( /^\t(\w+) = (\d+)/ )
# Reading the type of diagnoses requested, according with the name read from the
# enum DiagnosesType
# If no Diagnoses is suggested I set the ALL_DIAGNOSES
chosen_diagnoses = diagnoses_type.select{ |type, value| type == ARGV[ 1 ] }.flatten[1]
if chosen_diagnoses.class == NilClass then
	chosen_diagnoses = 0
end

# Retrieving the last simulation file
simulated_output = Dir[ "#{DIR_SIMULATION}/*#{FILE_EXT_SIMULATION}" ].max_by{ |f| File.mtime( f ) }

# It doesn't have a lot of sense running the same circuit on every diagnoses
# possible, I'll just run it requesting every diagnoses
system( "#{EXEC_CIRCUIT_DIAGNOSTIC} #{simulated_output} #{chosen_diagnoses}" )

#	diagnoses_type.each do |type, value|
#		system( "#{EXEC_CIRCUIT_DIAGNOSTIC} #{simulated_output} #{value}" )
#	end

puts "Solved '#{circuit_filename}' in #{Time.now - time_begin} seconds. ʕっ˘ڡ˘ςʔ\n"
