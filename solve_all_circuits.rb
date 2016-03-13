#!/usr/bin/env ruby

# Authors: Riccardo Orizio
# Date: 1 March 2016
# A program that solves every circuit instance known a given amount of times

require_relative "constants.rb"

time_begin = Time.now

# Reading all instances of the circuit and ordering them by their name, which
# corresponds on their number of components, so their complexity
circuit_files = Dir[ "#{DIR_CIRCUITS}/*#{FILE_EXT_INSTANCE}" ]
circuit_files = circuit_files.zip( circuit_files.map{ |x| x[ /\d+/ ].to_i } )
							 .sort_by( &:last )
							 .collect{ |x| x[ 0 ] }

# Solving the same problem n times
tests_number = ( ARGV[ 0 ] || 5 ).to_i
# I'm also passing the type of Diagnoses that I want to do
# The types are:
#  - ALL_DIAGNOSES
#  - NO_MASKING
#  - ALL_MASKING
#  - OKM_MASKING
#  - KOM_MASKING
circuit_files.each do |circuit|
	(1..tests_number).each do
		system( "#{EXEC_SOLVE_CIRCUIT} #{circuit} ALL_DIAGNOSES" )
	end
end

puts "#{circuit_files.size * tests_number} circuits have been solved in #{Time.now - time_begin} seconds. ʅʕ•ᴥ•ʔʃ\n"
