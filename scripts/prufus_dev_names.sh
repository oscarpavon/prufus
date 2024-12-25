#!/bin/sh
fdisk -l 2>&1 | grep "Disk model" | awk '{printf ("%s %s\n",$3, $4)}'
