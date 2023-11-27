#! /usr/bin/env bash

(
  PATTERN=${1?'ERROR: This script need 2 argument'}
  SSH_OPT=${2?'ERROR: This script need 2 argument'}

  [[ $( echo "$( ps -ef | grep "$PATTERN" | grep -v 'grep' | wc -l | bc) > 0" | bc ) == 1 ]] && \
    kill $(ps -ef | grep "$PATTERN" | grep -v 'grep' | sed -e "s/[ ]\{2,\}/ /g" | cut -d " " -f 2)

  ssh "$SSH_OPT" &> /dev/null
)
