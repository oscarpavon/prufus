#!/bin/bash
lsblk -n -P -d -p -I8 -o NAME,LABEL,SIZE
