#!/usr/bin/bash

(
  GATEWAY='bnl_flx0'
  PORT='8022'
  SSH_OPT="-f -N -T -R $PORT:localhost:22 $GATEWAY"
  BC="$(ps aux | grep '^.*/usr/bin/ssh.*${PORT}.*${GATEWAY}' | grep -v 'grep' | wc -l | bc) > 0"
  if [[ $( echo "$BC" | bc ) == 0 ]]; then
    [[ $( echo "$(ps aux | grep $GATEWAY | grep -v 'grep' | wc -l | bc) > 0" | bc ) == 1 ]] && \
    ps aux | grep $GATEWAY | grep -v 'grep' | awk '{print $2}' | xargs kill
    /bin/autossh -M 0 -o "ServerAliveInterval 30" -o "ServerAliveCountMax 3" -o "ExitOnForwardFailure yes" ${SSH_OPT}
  fi
)

## create a remote tunnel to to.infn.it
#if [[ $( echo "$(ps aux | grep 'zoroastro' | grep -v grep | wc -l | bc) > 0" | bc ) == 1 ]]; then
#  ps aux | grep 'zoroastro' | grep -v 'grep' | awk '{print $2}' | xargs kill -9
#fi
#
#/bin/autossh -M 0 -o "ServerAliveInterval 30" -o "ServerAliveCountMax 3" -o "ExitOnForwardFailure yes" \
#             -f -N -T -R 8022:127.0.0.1:22 zoroastro.to.infn.it -l corrales
#
## Create a remote tunnel to FLX server 2 (Ming's House)
#if [[ $( echo "$(ps aux | grep 'ming_felix' | grep -v grep | wc -l | bc) > 0" | bc ) == 1 ]]; then
#  ps aux | grep 'ming_felix' | grep -v 'grep' | awk '{print $2}' | xargs kill -9
#fi
#
#/bin/fwknop -s -n ming-felix
#sleep 2
#/bin/autossh -M 0 -o "ServerAliveInterval 30" -o "ServerAliveCountMax 3" -o "ExitOnForwardFailure yes" \
#             -f -N -T -R 8022:127.0.0.1:22 ming_felix
