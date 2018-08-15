#! /usr/bin/env bash

DOTFILES=${DOTFILES?"env_var DOTFILES not defined"}


function _config_myMac(){
  sudo defaults write /Library/Preferences/com.apple.AppleFileServer guestAccess -bool NO
  sudo defaults write /Library/Preferences/SystemConfiguration/com.apple.smb.server \
    AllowGuestAccess -bool NO
  sudo defaults write /Library/Preferences/com.apple.loginwindow SHOWOTHERUSERS_MANAGED \
    -bool FALSE
}

function Main() {
  # sourcing script to create the symbolic link
  if [ -f $DOTFILES/install/link.sh ]; then
    source $DOTFILES/install/link.sh
  fi
  _config_myMac
}

Main $@
unset -f _config_myMac
unset -f Main
