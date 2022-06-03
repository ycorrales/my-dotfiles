#! /usr/bin/env bash

(
  [[ $( echo "$( ps -ef | grep 'mail.rhic.bnl' | grep -v 'grep' | wc -l | bc) > 0" | bc ) == 1 ]] && \
    kill $(ps -ef | grep 'mail.rhic.bnl' | grep -v 'grep' | sed -e "s/[ ]\{2,\}/ /g" | cut -d " " -f 2)

  ssh -fNL 1993:mail.rhic.bnl.gov:993 bnl_sdcc    &> /dev/null

  [[ $( echo "$( ps -ef | grep 'batch3.phy.bnl.gov' | grep -v 'grep' | wc -l | bc) > 0" | bc ) == 1 ]] && \
    kill $(ps -ef | grep 'batch3.phy.bnl.gov' | grep -v 'grep' | sed -e "s/[ ]\{2,\}/ /g" | cut -d " " -f 2)

  ssh -fNL 3128:batch3.phy.bnl.gov:3128 bnl_cssh  &> /dev/null

)
