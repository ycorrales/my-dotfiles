#! /usr/bin/env bash

(
  SERVER=${1?'ERROR: This script need two argument'}
  PROXY=${2?'ERROR: This script need two argument'}

  [[ $( echo "$( ps -ef | grep "$SERVER" | grep -v 'grep' | wc -l | bc) > 0" | bc ) == 1 ]] && \
    kill $(ps -ef | grep "$SERVER" | grep -v 'grep' | sed -e "s/[ ]\{2,\}/ /g" | cut -d " " -f 2)

  ssh -fNL $SERVER $PROXY &> /dev/null
)
