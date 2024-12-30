#!/bin/bash

SED_FORMAT="/HOTPLUG=\"0\"/d;"         # filter USB drives
SED_FORMAT="$SED_FORMAT s/\w*=//g;"    # remove keys
SED_FORMAT="$SED_FORMAT s/\" /\t/g;"   # replace last \" of the values with TAB separator 
SED_FORMAT="$SED_FORMAT s/\"//g;"      # remove first \" of the values
SED_FORMAT="$SED_FORMAT s/^[01]\t//g;" # remove first HOTPLUG field

lsblk -P -d -n -o HOTPLUG,PATH,MODEL,SIZE | sed "${SED_FORMAT}"
