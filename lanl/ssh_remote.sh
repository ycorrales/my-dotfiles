#!/usr/bin/bash

if [[ $( echo "$(ps aux | grep 'zoroastro' | grep -v grep | wc -l | bc) > 0" | bc ) == 1 ]]; then
  ps aux | grep 'zoroastro' | grep -v 'grep' | awk '{print $2}' | xargs kill -9
fi
/bin/autossh -M0 -o "ServerAliveInterval 30" -o "ServerAliveCountMax 3" -f -N -T -R 8022:localhost:22 zoroastro.to.infn.it -l corrales -i /home/maps/.ssh/id_rsa_YCM
