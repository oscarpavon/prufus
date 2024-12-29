#!/bin/bash
lsblk -P -d -n -o HOTPLUG,PATH,MODEL,SIZE,LABEL | sed '/HOTPLUG="0"/d; s/\w*=//g; s/" /,/g; s/"//g; s/1,//g;'
