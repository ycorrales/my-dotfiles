#! /bin/bash

# colors
Cm="\033[35m"
Cy="\033[33m"
Cc="\033[36m"
Cb="\033[34m"
Cg="\033[32m"
Cr="\033[31m"
Cw="\033[37m"
Cz="\033[m"
Br="\033[41m"
By="\033[43m"

_fx3="$HOME/Alice/ITS_UPGRADE/pALPIDEfs-software/fx3/"
OLDWD=$PWD

N=`lsusb | grep "04b4:00f3 Cypress Semiconductor Corp" | wc -l`

[[ ! $N -gt 0 ]] && echo -e "$Cr $N unprogrammed FX3 found. $Cz"; return

if [[ -d $_fx3 ]] ; then 

  echo -e ""
  echo -e "$Cy Entering to $Cr $_fx3 $Cz"
  echo -e ""
  
  cd $_fx3

  echo "$N unprogrammed FX3 found. Trying to program them all..."

  I=0
  while [ "$I" -lt "$N" ]
  do
    echo -e "$Cg Programming... $Cz"
      ./download_fx3 -t RAM -i SlaveFifoSync.img
      sleep 1
        let I=I+1
  done

  echo -e ""
  echo -e "$Cy Returning to $Cr $OLDWD $Cz"
  
  [[ -d $OLDWD ]] && cd $OLDWD
else

  echo -e ""
  echo -e "$Cy Folder $Cr $_fx3 $Cz not found"
  echo -e ""
fi
