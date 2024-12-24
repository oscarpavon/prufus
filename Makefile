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

install:
	mkdir -p /usr/libexec/prufus
	cp prufus_devices.sh /usr/libexec/prufus/
	cp prufus_dev_names.sh /usr/libexec/prufus/
	cp prufus_dev_sizes.sh /usr/libexec/prufus/
	cp prufus /usr/bin/
	cp prufus.sh /usr/bin/
	cp prufus_sudo /usr/bin/
	cp prufus_launcher /usr/bin/
	mkdir -p /usr/share/icons/prufus
	cp ./icon/icon.png /usr/share/icons/prufus/prufus.png

uninstall:
	rm -rf /usr/libexec/prufus
	rm -f /usr/bin/prufus_sudo
	rm -f /usr/bin/prufus
	rm -f /usr/bin/prufus.sh
	rm -f /usr/bin/prufus_launcher
	rm -rf /usr/share/icons/prufus

clean:
	rm -f prufus
	rm -f *.o
