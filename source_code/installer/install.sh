#!/bin/sh

check_error(){
if [ $? != 0 ];
then
  echo e > /tmp/prufus/status
  echo "ERROR"
  exit
fi
}

echo "Installing.."
echo 2 > /tmp/prufus/status
apt update
check_error
apt install libgtk-4-1
check_error
apt install wimtools
check_error
apt install ntfs-3g
check_error
apt install dosfstools
check_error

echo 3 > /tmp/prufus/status

FILE_PATH="`readlink -f "$0"`"
DIR="`dirname "$FILE_PATH"`"

cp -v $DIR/../prufus/prufus /usr/bin/
cp -v $DIR/../prufus/scripts/prufus.sh /usr/bin/
mkdir -p /usr/libexec/prufus
cp -v $DIR/../prufus/scripts/get_usb_disks.sh /usr/libexec/prufus/
cp -v $DIR/../prufus/scripts/graphics_sudo /usr/libexec/prufus/
mkdir -p /usr/share/icons/prufus
cp -v $DIR/../prufus/icon.png /usr/share/icons/prufus/prufus.png
cp -v $DIR/../prufus/prufus.desktop /usr/share/applications
cp $DIR/../prufus/prufus.desktop $HOME/Desktop/
chmod 777 $HOME/Desktop/prufus.desktop


echo "Installed"
echo 8 > /tmp/prufus/status

#rm -vrf /tmp/prufus
