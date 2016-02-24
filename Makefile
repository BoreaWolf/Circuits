# Riccardo Orizio
# 23 February 2016
# Makefile

# Compiler
CCC = clang++
COPT = -std=c++11

# Targets
TARGETS = simulation diagnoses

# Objects
OBJ = circuit.o circuit_set.o component.o constants.o

GATES = AndGate.h NandGate.h NorGate.h NotGate.h OrGate.h XnorGate.h XorGate.h
HEADERS = GateStatus.h InputTerminal.h LogicalGate.h OutputTerminal.h $(GATES)

# Dependencies
# Main programs
simulation:		simulation.cpp $(OBJ) $(HEADERS)
	$(CCC) $(COPT) $(OBJ) simulation.cpp -o simulation
#	diagnoses:		diagnoses.cpp
#		$(CCC) $(COPT) diagnoses.cpp -o diagnoses

# Intermediate objects
circuit.o:		Circuit.h Circuit.cpp
	$(CCC) $(COPT) -c Circuit.cpp -o circuit.o

circuit_set.o:	CircuitSet.h CircuitSet.cpp
	$(CCC) $(COPT) -c CircuitSet.cpp -o circuit_set.o

component.o:	Component.h Component.cpp
	$(CCC) $(COPT) -c Component.cpp -o component.o

constants.o:	constants.h constants.cpp
	$(CCC) $(COPT) -c constants.cpp -o constants.o

# Everything all together
all: $(TARGETS)

# Cleaning
clean:
	rm -f ./*.o simulation diagnoses
