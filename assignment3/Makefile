all: smsh2 smsh3 smsh4

smsh2: smsh2.c execute.c splitline.c smsh.h
	gcc smsh2.c execute.c splitline.c smsh.h -o smsh2

pipeline: pipeline.c
	gcc pipeline.c -o pipeline
	
clean: 
	rm *.x
