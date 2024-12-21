## prufus
![bootloader](screenshot1.png)
You can create a bootable USB with Windows installer from GNU/Linux. And then can install Windows in other computer. Useful for computer repair people or if you want to go back to Windows from Linux after a disappointment
# Dependencies
- GNU/Linux
- make
- gcc
- GTK-4.16.7
- rsync
- wimlib-imagex (this program divide the big Windows installation file in parts because the restriction of FAT32 filesystem about 4GB per file)
- dosfstools (very important, it's for create the first partition EFI)
- ntfs3g (for creating a second partion for user data and set disk label)

# Build

```
git clone https://github.com/oscarpavon/prufus
cd prufus
make
```
# Warning
Every command for manipulate disks in GNU/Linux are for privilege user. You don't even can seen your USB without "sudo". And the GUI need "sudo" for format the USB

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
to execute it. Or create a ".desktop" with "prufus_launcher", it does not work outside the build directoy without "prufus_launcher"
