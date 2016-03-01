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

# Launching the solver on this instances
system( "#{EXEC_CIRCUIT_SIMULATION} #{circuit_filename} #{init_filename} #{gates_filename}" )

puts "Solved '#{circuit_filename}' in #{Time.now - time_begin} seconds. ʕっ˘ڡ˘ςʔ\n"
