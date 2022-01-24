count_words: count_words.o lexer.o -lfl 
	gcc $^ -o $@

count_words.o: count_words.c 
	echo $<
	gcc -c $< 

lexer.o: lexer.c 
	gcc -c $<

lexer.c: lexer.lex
	flex -t $< > $@

.PHONY: clean
clean: 
	rm -f *.o lexer.c count_words
