#!/bin/sh
idProc=$(ps | grep aliroot | grep -v grep | cut -d " " -f 1)
echo "${idProc}"
rm top.txt
rm memV.txt
rm memR.txt
while true; do
   top -l 1 -pid "${idProc}"  > top.txt      #su osx
   #top -b -n1 -p $1  > top.txt  #su unix

   sleep 1
   #su unix
   # cat top.txt | grep $1 | cut -c 24-27  >> memV.txt
   # cat top.txt | grep $1 | cut -c 30-32  >> memR.txt
   #su osx
   cat top.txt | grep "${idProc}" | cut -c 46-48 >> memR.txt

done

