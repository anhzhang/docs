
#define the suffixes
.SUFFIXES:	.tex

#macro definitions
SHELL = /bin/sh
LATEX = pdflatex

.tex.aux:	
	$(LATEX) $<


all:	OpenMPIUserManual.pdf

OpenMPIUserManual.pdf: OpenMPIUserManual.tex *.tex
	$(LATEX) OpenMPIUserManual

force:
	$(LATEX) OpenMPIUserManual


clean:
	rm -f *.aux *.nav *.snm *.toc *.log *.dvi *.out *.lol

