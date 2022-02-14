#! /usr/bin/env bash

(
  set -euo pipefail

  function usage() { echo "Usage: $0 [-f] [-s]" 1>&2; exit 1; }

  function _config_myMac()
  {
    echo "MacOS operating system found. Configuring Mac..."
    sudo defaults write /Library/Preferences/com.apple.AppleFileServer guestAccess -bool NO
    sudo defaults write /Library/Preferences/SystemConfiguration/com.apple.smb.server \
      AllowGuestAccess -bool NO
    sudo defaults write /Library/Preferences/com.apple.loginwindow SHOWOTHERUSERS_MANAGED \
      -bool FALSE
  }

  function Main()
  {
    # Parse options
    local FORSE CONFIG_MAC
    while getopts "fm" arg; do
      case $arg in
        f)
          FORSE=1;
          ;;
        m)
          local CONFIG_MAC=1;
          ;;
        \?)
          usage
          ;;
      esac
    done
    shift $((OPTIND-1))

    [[ $# -gt 0 ]] && usage

    local DOTFILES=${DOTFILES:-"$( cd "$( dirname "$(readlink -f "${BASH_SOURCE[0]}")" && pwd )" > /dev/null 2>&1 && pwd )"}

    if [[ "$OSTYPE" =~ darwin.* ]]; then
      OS="osx_x86-64"
    elif [[ "$OSTYPE" =~ linux-gnu.* ]]; then
      OS="linux"
    else
      OS="unknow"
    fi

    # sourcing script to create the symbolic link
    local files=( "install/link.sh" )
    for file in "${files[@]}"; do
      local FILE_PATH=${DOTFILES}/$file
      # shellcheck source=./install/link.sh
      [ -f "${FILE_PATH}" ] && source "$FILE_PATH" "$FORSE"
    done

    [[ $OS = "osx_x86-64" && -n $CONFIG_MAC ]] && _config_myMac
  }

  Main "$@"
)
