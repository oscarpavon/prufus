## prufus
![bootloader](screenshot1.png)
Create bootable USB with Windows installer
# Dependencies
- GNU/Linux
- make
- gcc
- GTK-4.16.7
- rsync
- wimlib-imagex
- dosfstools
- ntfs3g

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
