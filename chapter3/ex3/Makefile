# simple makefile including a generated file 

include foo.mk
$(warning Finished include)

.PHONY: tmp
tmp:
	echo $(MAKECMDGOALS)

foo.mk: bar.mk
	m4 --define=FILENAME=$@ bar.mk > $@
