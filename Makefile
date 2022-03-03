.phony all:
all: ssi

ssi: ssi.c
	gcc ssi.c ssi_list.c -lreadline

.PHONY clean:
clean:
	-rm -rf *.o *.exe
