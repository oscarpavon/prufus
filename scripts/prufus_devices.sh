#!/bin/sh
fdisk -l 2>&1 | grep "Disk /" | awk '{print $2}' | sed 's/://g'


