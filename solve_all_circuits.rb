#!/usr/bin/env ruby

# Authors: Riccardo Orizio
# Date: 1 March 2016
# A program that solves every circuit instance known

require_relative "constants.rb"

time_begin = Time.now

# Reading all instances of the circuit and ordering them by their name, which
# corresponds on their number of components, so their complexity
circuit_files = Dir[ "#{DIR_CIRCUITS}/*#{FILE_EXT_INSTANCE}" ]
circuit_files = circuit_files.zip( circuit_files.map{ |x| x[ /\d+/ ].to_i } )
							 .sort_by( &:last )
							 .collect{ |x| x[ 0 ] }

circuit_files.each do |circuit|
	system( "#{EXEC_SOLVE_CIRCUIT} #{circuit}" )
end

puts "#{circuit_files.size} circuits have been solved in #{Time.now - time_begin} seconds. ʅʕ•ᴥ•ʔʃ\n"
