# Riccardo Orizio
# 23 February 2016
# Makefile

# Compiler
CCC = clang++
COPT = -std=c++11

# Targets
TARGETS = simulation doctor 

# Objects
GATES = and_gate.o gate_cone.o input_terminal.o logical_gate.o nand_gate.o \
		nor_gate.o not_gate.o output_terminal.o or_gate.o xnor_gate.o \
		xor_gate.o
OBJ_SIM = circuit.o circuit_comparison.o circuit_solution.o component.o \
	  constants.o $(GATES)
OBJ_DIA = constants.o diagnostic.o diagnostic_solution.o gate_cone.o

HEADERS_SIM = GateStatus.h
HEADERS_DIA = DiagnosesType.h GateValue.h

# Dependencies
# Main programs
simulation:		simulation.cpp $(OBJ_SIM) $(HEADERS_SIM)
	$(CCC) $(COPT) $(OBJ_SIM) simulation.cpp -o simulation
doctor:		doctor.cpp $(OBJ_DIA) $(HEADERS_DIA)
	$(CCC) $(COPT) $(OBJ_DIA) doctor.cpp -o doctor 

# Simulation related
# Intermediate objects
circuit.o:		Circuit.h Circuit.cpp
	$(CCC) $(COPT) -c Circuit.cpp -o circuit.o

component.o:	Component.h Component.cpp
	$(CCC) $(COPT) -c Component.cpp -o component.o

constants.o:	constants.h constants.cpp
	$(CCC) $(COPT) -c constants.cpp -o constants.o

# Other stuff
circuit_solution.o:	CircuitSolution.h CircuitSolution.cpp
	$(CCC) $(COPT) -c CircuitSolution.cpp -o circuit_solution.o
circuit_comparison.o:	CircuitComparison.h CircuitComparison.cpp
	$(CCC) $(COPT) -c CircuitComparison.cpp -o circuit_comparison.o

# Gates
input_terminal.o:	InputTerminal.h InputTerminal.cpp
	$(CCC) $(COPT) -c InputTerminal.cpp -o input_terminal.o
output_terminal.o:	OutputTerminal.h OutputTerminal.cpp
	$(CCC) $(COPT) -c OutputTerminal.cpp -o output_terminal.o

logical_gate.o:	LogicalGate.h LogicalGate.cpp
	$(CCC) $(COPT) -c LogicalGate.cpp -o logical_gate.o
and_gate.o:		AndGate.h AndGate.cpp
	$(CCC) $(COPT) -c AndGate.cpp -o and_gate.o
nand_gate.o:	NandGate.h NandGate.cpp
	$(CCC) $(COPT) -c NandGate.cpp -o nand_gate.o
nor_gate.o:		NorGate.h NorGate.cpp
	$(CCC) $(COPT) -c NorGate.cpp -o nor_gate.o
not_gate.o:		NotGate.h NotGate.cpp
	$(CCC) $(COPT) -c NotGate.cpp -o not_gate.o
or_gate.o:		OrGate.h OrGate.cpp
	$(CCC) $(COPT) -c OrGate.cpp -o or_gate.o
xnor_gate.o:	XnorGate.h XnorGate.cpp
	$(CCC) $(COPT) -c XnorGate.cpp -o xnor_gate.o
xor_gate.o:		XorGate.h XorGate.cpp
	$(CCC) $(COPT) -c XorGate.cpp -o xor_gate.o

gate_cone.o:	GateCone.h GateCone.cpp
	$(CCC) $(COPT) -c GateCone.cpp -o gate_cone.o

# Diagnostic related
diagnostic.o:	Diagnostic.h Diagnostic.cpp
	$(CCC) $(COPT) -c Diagnostic.cpp -o diagnostic.o

diagnostic_solution.o:	DiagnosticSolution.h DiagnosticSolution.cpp
	$(CCC) $(COPT) -c DiagnosticSolution.cpp -o diagnostic_solution.o

# Everything all together
all: $(TARGETS)

# Cleaning
clean:
	rm -f ./*.o
	rm -f simulation
	rm -f doctor

instances_clean:
	rm -f ./instances/init_conf/*.conf
	rm -f ./instances/fail_gates/*.gates
	rm -f ./instances/simulation/*.sim_sol
