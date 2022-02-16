#!/usr/bin/bash

# create a remote tunnel to to.infn.it
if [[ $( echo "$(ps aux | grep 'zoroastro' | grep -v grep | wc -l | bc) > 0" | bc ) == 1 ]]; then
  ps aux | grep 'zoroastro' | grep -v 'grep' | awk '{print $2}' | xargs kill -9
fi

/bin/autossh -M 0 -o "ServerAliveInterval 30" -o "ServerAliveCountMax 3" -o "ExitOnForwardFailure yes" \
             -f -N -T -R 8022:127.0.0.1:22 zoroastro.to.infn.it -l corrales

# Create a remote tunnel to FLX server 2 (Ming's House)
if [[ $( echo "$(ps aux | grep 'ming_felix' | grep -v grep | wc -l | bc) > 0" | bc ) == 1 ]]; then
  ps aux | grep 'ming_felix' | grep -v 'grep' | awk '{print $2}' | xargs kill -9
fi

/bin/fwknop -s -n ming-felix
sleep 2
/bin/autossh -M 0 -o "ServerAliveInterval 30" -o "ServerAliveCountMax 3" -o "ExitOnForwardFailure yes" \
             -f -N -T -R 8022:127.0.0.1:22 ming_felix
