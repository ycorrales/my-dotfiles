#! /usr/bin/env bash
(
  DOTFILES=${DOTFILES:-"$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd )"}

  if test $OSTYPE = "darwin"*; then
    OS="osx_x86-64"
  elif test $OSTYPE = "linux-gnu"; then
    OS="linux"
  else
    OS="unkonw"
  fi

  function _config_myMac()
  {
    echo ""
    echo "MacOS operating system found. Configuring Mac..."
    sudo defaults write /Library/Preferences/com.apple.AppleFileServer guestAccess -bool NO
    sudo defaults write /Library/Preferences/SystemConfiguration/com.apple.smb.server \
      AllowGuestAccess -bool NO
    sudo defaults write /Library/Preferences/com.apple.loginwindow SHOWOTHERUSERS_MANAGED \
      -bool FALSE
  }

  function Main()
  {
    # sourcing script to create the symbolic link
    test -f $DOTFILES/install/link.sh && source $DOTFILES/install/link.sh
    test $OS="osx_x86-64" && _config_myMac
  }

  Main $@
)
