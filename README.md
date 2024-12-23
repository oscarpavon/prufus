## prufus
![bootloader](screenshot1.png)
You can create a bootable USB with Windows installer from GNU/Linux. And then you can install Windows on another computer. Useful for computer repair people or if you want to go back to Windows from Linux after a disappointment.  
This is an open source project with GPL 3 license. That means you can modify it like you want, change the name or even sell it as long as you distribute with your changes to the source code.  
This program it's for only GNU/Linux
# Dependencies
- GNU/Linux
- make
- gcc
- GTK-4.16.7
- rsync
- wimlib-imagex (this program divide the big Windows installation file in parts because the restriction of FAT32 filesystem about 4GB per file)
- dosfstools (very important, it's for create the first partition EFI)
- ntfs3g (for creating a second partition for user data and set disk label)
## Linux Mint/Ubuntu
### Build dependency
```
sudo apt-get install git
sudo apt-get install libgtk-4-dev
```
### Runtime dependency
```
sudo apt install wimtools
```
# Build

```
git clone https://github.com/oscarpavon/prufus
cd prufus
make
```
# Warning
Every command for manipulate disks in GNU/Linux are for privilege user. You don't even can seen your USB without "sudo". And the GUI need "sudo" for format the USB.  
This program only work with GPT partitions tables. Only UEFI is supported and only EFI will be supported.
NONE Windows hack here like remove TPM requirement. And never will be implemented neither.

# Development
If you want code navigation and code completation you can use clangd for your text editor
```
./generate_compile_commands.sh
```

# How to use
You can use
```
sudo ./prufus
```
to execute it. Or create a ".desktop" with "prufus_launcher", it does not work outside the build directory without "prufus_launcher".  
Or! the GUI call a script named "make_usb.sh", you can pass two arguments in it like:

```
sudo make_usb.sh ./Downloads/Windows.iso /dev/sdb
```

You can ask in:
[Threads](https://www.threads.net/@oscar0pavon)
