#! /usr/bin/env bash

(
  if [[ $(echo "$( ps -ef | grep 'mail.rhic.bnl' | grep -v 'grep' | wc -l | bc) > 0" | bc ) == 0 ]]; then
    ssh -fN -l ycmorales ssh.sdcc.bnl.gov -L 1993:mail.rhic.bnl.gov:993 > /dev/null 2>&1
  fi
)
