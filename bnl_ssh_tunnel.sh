#! /usr/bin/env bash

(
  if [[ $(echo "$( ps -ef | grep 'mail.rhic.bnl' | grep -v 'grep' | wc -l | bc) > 0" | bc ) == 0 ]]; then
    ssh -fNL 1993:mail.rhic.bnl.gov:993 bnl_sdcc    &> /dev/null
  fi

  if [[ $(echo "$( ps -ef | grep 'batch3.phy.bnl.gov' | grep -v 'grep' | wc -l | bc) > 0" | bc ) == 0 ]]; then
    ssh -fNL 3128:batch3.phy.bnl.gov:3128 bnl_cssh  &> /dev/null
  fi
)
