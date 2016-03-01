# Riccardo Orizio
# 8 February 2016
# Makefile for documentation

# Targets
CHAPTERS = introduction problem simulation diagnostic results
TARGETS = report $(CHAPTERS)

# Dependencies
report: report.mmd introduction.mmd problem.mmd simulation.mmd \
		diagnostic.mmd results.mmd

# Everything all together
all: $(TARGETS)

# Compiling: the command is the same for every target
$(TARGETS):
	multimarkdown -t latex $^ -o $@.tex && latexmk $@ -pdf

# Cleaning
clean:
	rm -f ./*.{pdf,aux,fls,ind,glo,ist,out,idx,ilg,toc,log,tex,fdb_latexmk,lof,bbl,blg,brf}
