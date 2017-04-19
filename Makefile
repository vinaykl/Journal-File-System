compile:
	gcc journal.c read.c write.c newDataId.c allocate.c deallocate.c faulthandle.c lockmanager.c -o JFS
run:
	./JFS $(STRING) 

