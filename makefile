CC = gcc

MYFLAGS = -g -O2 -Wall -fcommon

TARGET = simturing

OBJFILES = decodArgs.o decodc.o exec.o main.o stack.o

default: all

all:
	$(MAKE) $(TARGET)

# regras para gerar o executavel
$(TARGET): $(OBJFILES) 
	$(CC) -o $(TARGET) $(OBJFILES) 

# regras de compilação
decodArgs.o: decodArgs.c decodArgs.h
	$(CC) -c $(MYFLAGS) decodArgs.c  

decodc.o: decodc.c decodc.h
	$(CC) -c $(MYFLAGS) decodc.c  

exec.o: exec.c exec.h decodc.h decodArgs.h stack.h
	$(CC) -c $(MYFLAGS) exec.c  

main.o: main.c main.h exec.h decodc.h decodArgs.h stack.h
	$(CC) -c $(MYFLAGS) main.c  

stack.o: stack.c stack.h decodc.h
	$(CC) -c $(MYFLAGS) stack.c 

clean:
	rm -f *.o
	rm -f $(TARGET)

clear:
	rm -f *.o
