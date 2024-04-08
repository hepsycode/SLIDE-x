NAME = c_entry
COMP = arm-none-eabi
COPS = -march=armv4t -c
AOPS = --warn --fatal-warnings

all: $(NAME).o startup.o 00000000.bin 

00000000.bin: rip $(NAME).elf
	./rip $(NAME).elf
	#diff 00000000.bin $(NAME).elf

$(NAME).o: 
	$(COMP)-gcc $(COPS) $(NAME).c -o $(NAME).o

startup.o:
	$(COMP)-as startup.s $(AOPS) -o startup.o

rip:
	gcc rip.c -o rip

$(NAME).elf: $(NAME).o startup.o 
	$(COMP)-ld startup.o $(NAME).o -T arm-memmap.ld -o $(NAME).elf

clean:
	rm -f *.elf
	rm -f *.o
	rm -f rip
	rm -f *.bin
