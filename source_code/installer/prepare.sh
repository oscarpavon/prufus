#!/bin/sh

mkdir -vp /tmp/prufus
#if already exist clean first
rm -f /tmp/prufus/status

echo 1 > /tmp/prufus/status
