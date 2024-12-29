
prufus:
	make -C source_code

installer:
	make -C source_code/installer

distributable_directory:
	mkdir -vp distributable/prufus/scripts
	mkdir -vp distributable/installer

distributable: distributable_directory prufus installer
	cp prufus ./distributable/prufus/prufus
	cp -vr scripts ./distributable/prufus/
	cp -v icon/icon.png ./distributable/prufus
	cp -v prufus.desktop ./distributable/prufus
	cp ./source_code/installer/setup ./distributable/
	cp ./source_code/installer/graphics_sudo ./distributable/installer/
	cp ./source_code/installer/install.sh ./distributable/installer/
	cp ./source_code/installer/prepare.sh ./distributable/installer/
	cp ./logo.png ./distributable/installer
	cd distributable
	zip -r prufus_installer.zip ./distributable/installer/ ./distributable/prufus/ ./distributable
	mv prufus_installer.zip ./distributable


install:
	cp prufus /usr/bin/
	mkdir -p /usr/libexec/prufus
	cp ./scripts/get_usb_disks.sh /usr/libexec/prufus/
	cp ./scripts/prufus.sh /usr/bin/
	cp ./scripts/prufus_sudo /usr/bin/
	cp ./scripts/prufus_launcher /usr/bin/
	mkdir -p /usr/share/icons/prufus
	cp ./icon/icon.png /usr/share/icons/prufus/prufus.png
	cp ./prufus.desktop /usr/share/applications
	cp ./prufus.desktop /home/${SUDO_USER}/Desktop/
	chmod 777 /home/${SUDO_USER}/Desktop/prufus.desktop

uninstall:
	rm -rf /usr/libexec/prufus
	rm -f /usr/bin/prufus_sudo
	rm -f /usr/bin/prufus
	rm -f /usr/bin/prufus.sh
	rm -f /usr/bin/prufus_launcher
	rm -rf /usr/share/icons/prufus
	rm -f /usr/share/applications/prufus.desktop
	rm -f /home/${SUDO_USER}/Desktop/prufus.desktop

clean:
	make -C source_code clean
	make -C source_code/installer clean
	rm -f prufus
