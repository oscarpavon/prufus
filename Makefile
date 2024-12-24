CFLAGS := $(shell pkg-config --cflags gtk4)
CLINKS := $(shell pkg-config --libs gtk4)

prufus: main.c user_interface.o usb_validator.o scripts_names.h
	cc $(CFLAGS) usb_validator.o user_interface.o main.c -o prufus $(CLINKS)

user_interface.o: user_interface.c
	cc $(CFLAGS) -c user_interface.c

usb_validator.o: usb_validator.c
	cc $(CFLAGS) -c usb_validator.c

main_compile_command.o: main.c
	cc $(CFLAGS) -c main.c

compile_commands: main_compile_command.o
	make --always-make --dry-run

clean:
	rm -f prufus
	rm -f *.o
