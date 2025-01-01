
.PHONY: prufus

prufus:
	make -C source_code

installer:
	make -C source_code/installer

distributable_directory:
	mkdir -vp distributable/prufus_installer/prufus/scripts
	mkdir -vp distributable/prufus_installer/installer

distributable: distributable_directory prufus installer
	cp prufus ./distributable/prufus_installer/prufus/prufus
	cp -vr scripts ./distributable/prufus_installer/prufus/
	cp -v icon/icon.png ./distributable/prufus_installer/prufus
	cp -v prufus.desktop ./distributable/prufus_installer/prufus/prufus.desktop
	cp ./source_code/installer/setup ./distributable/prufus_installer/
	cp ./source_code/installer/graphics_sudo ./distributable/prufus_installer/installer/
	cp ./source_code/installer/install.sh ./distributable/prufus_installer/installer/
	cp ./source_code/installer/prepare.sh ./distributable/prufus_installer/installer/
	cp ./logo.png ./distributable/prufus_installer/installer
	cd ./distributable/ && zip -r prufus_installer.zip ./prufus_installer/


install:
	cp prufus /usr/bin/
	cp ./scripts/prufus.sh /usr/bin/
	mkdir -p /usr/libexec/prufus
	cp ./scripts/get_usb_disks.sh /usr/libexec/prufus/
	cp ./scripts/graphics_sudo /usr/libexec/prufus/
	mkdir -p /usr/share/icons/prufus
	cp ./icon/icon.png /usr/share/icons/prufus/prufus.png
	cp ./prufus.desktop /usr/share/applications
	cp ./prufus.desktop /home/${SUDO_USER}/Desktop/
	chmod 777 /home/${SUDO_USER}/Desktop/prufus.desktop

uninstall:
	rm -rf /usr/libexec/prufus
	rm -f /usr/bin/prufus
	rm -f /usr/bin/prufus.sh
	rm -rf /usr/share/icons/prufus
	rm -f /usr/share/applications/prufus.desktop
	rm -f /home/${SUDO_USER}/Desktop/prufus.desktop

clean:
	make -C source_code clean
	make -C source_code/installer clean
	rm -f prufus
