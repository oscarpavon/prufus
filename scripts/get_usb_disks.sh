#!/bin/bash
 
SED_FORMAT=\
 '/HOTPLUG="0"/d;' # filter USB drives
 's/\w*=//g;'	   # remove keys
 's/" /\t/g; '     # replace last \" of the values with TAB separator 
 's/"//g;'	   # remove first \" of the values
 's/[01]\t//g;'    # remove first HOTPLUG field

lsblk -P -d -n -o HOTPLUG,PATH,MODEL,SIZE | sed ${SED_FORMAT}
