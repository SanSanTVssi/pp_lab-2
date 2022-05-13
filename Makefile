build:
	gcc -o main main.c -lpthread -lm
clean:
	rm -rf ./main
run: build	
	./main
