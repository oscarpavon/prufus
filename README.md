## prufus
![bootloader](screenshot1.png)
Create bootable USB with Windows installer
# Dependencies
- GNU/Linux
- make
- gcc
- GTK-4.16.7
- rsync
- wimlib-imagex (this program divede the big Windows installation file in parts because the restriction of FAT32 filesystem about 4GB per file)
- dosfstools (very important, it's for create the first partition EFI)
- ntfs3g (for creating a second partion for user data and set disk label)

# Build

```
git clone https://github.com/oscarpavon/prufus
cd prufus
make
```
# Development
If you want code navigation and code completation you can use clangd for your text editor
```
./generate_compile_commands.sh
```
