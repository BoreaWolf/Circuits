#!/usr/bin/env ruby

# Authors: Riccardo Orizio
# Date: 1 March 2016
# A program that generates the input files related to a given circuit

require_relative "constants.rb"

# Reading the circuit file given in input
circuit_filename = ARGV[ 0 ]

if circuit_filename == nil then
	puts "Error: I need a circuit file to proceed"
	exit( -1 )
end

# Reading how many input terminal this circuit has and storing the internal
# gates, so I can create some failing gates
input_terminal = File.open( circuit_filename, "r" ).read.scan( /INPUT/ ).size
gates_terminal = File.open( circuit_filename, "r" ).read.scan( /([A-Z]\d+) =/ ).flatten

# Creating an initial configuration for the input terminals
# Randoming values 0/1 for each one of them
initial_conf = Array.new( input_terminal ){ rand( 0..1 ) }

# Creating the filename considering also how many other files of this type for
# this circuit are present
initial_conf_filename = circuit_filename.gsub( "./", "" )
										.gsub( DIR_CIRCUITS[2..DIR_CIRCUITS.size-1], DIR_INITIAL_CONF )
										.gsub( FILE_EXT_INSTANCE, "" )

# Counting how many files are already there
init_conf_files = Dir.glob( "#{DIR_INITIAL_CONF}/*" ).select{ |x| File.file? x }
init_conf_files = init_conf_files.map{ |x| x.scan( /#{initial_conf_filename}.(\d+)#{FILE_EXT_INITIAL_CONF}/ ) }.flatten.map( &:to_i ).sort
conf_number = if init_conf_files.empty? then
				  1
			  else
				  Integer( init_conf_files.last ) + 1
			  end

# Creating the file and writing the informations on it
initial_conf_filename += ".#{conf_number}#{FILE_EXT_INITIAL_CONF}"
init_conf_file = File.open( initial_conf_filename, "w" )
initial_conf.each{ |x| init_conf_file.printf( "%d", x ) }
init_conf_file.close

# Creating some failing gates

# Extracting a random number of elements that will represent how many gates have
# problems and writing them to the failure file
failure_gates_filename = initial_conf_filename.gsub( DIR_INITIAL_CONF, DIR_FAILURE_GATES )
											  .gsub( FILE_EXT_INITIAL_CONF, FILE_EXT_FAILURE_GATES )
failure_gates_file = File.open( failure_gates_filename, "w" )
gates_terminal.sample( rand( 1..gates_terminal.size-1 ) ).each do |x|
	failure_gates_file.printf( "%s s%d\n", x, rand( 0..1 ) )
end
failure_gates_file.close

puts "Created: ʕʘ̅͜ʘ̅ʔ"
puts " - Initial conf '#{initial_conf_filename}'"
puts " - Failing gates '#{failure_gates_filename}'"
