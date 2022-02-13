#! /usr/bin/env bash

(
  if [[ $(echo "$( ps -ef | grep 'mail.rhic.bnl' | grep -v 'grep' | wc -l | bc) > 0" | bc ) == 0 ]]; then
    ssh -fNL 1993:mail.rhic.bnl.gov:993 sdcc_gateway &> /dev/null
  fi
)
