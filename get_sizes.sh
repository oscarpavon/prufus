#!/bin/sh
fdisk -l 2>&1 | grep "Disk /" | awk '{printf ("%s %s\n",$3, $4)}' | sed 's/,$//g'
