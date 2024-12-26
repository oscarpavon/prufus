#!/bin/sh

mkdir -vp /tmp/prufus
echo 1 > /tmp/prufus/status
#if already exist clean first
#rm -f /tmp/prufus/status

#echo 1 > /tmp/prufus/status

echo "Installing.."
echo 2 > /tmp/prufus/status
sleep 2
echo "Installed"
echo 8 > /tmp/prufus/status

#rm -vrf /tmp/prufus
