#!/bin/sh

mkdir -vp /tmp/prufus
echo 1 > /tmp/prufus/status
#if already exist clean first
#rm -f /tmp/prufus/status

#echo 1 > /tmp/prufus/status
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

echo "Installed"
echo 8 > /tmp/prufus/status

#rm -vrf /tmp/prufus
