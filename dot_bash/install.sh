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
    local FORCE=""
    local CONFIG_MAC=""
    local CLEAN=""
    while getopts "cfm" arg; do
      case $arg in
        f)
          FORCE=1
          ;;
        m)
          CONFIG_MAC=1
          ;;
        c)
          CLEAN=1
          ;;
        \?)
          usage
          ;;
      esac
    done
    shift $((OPTIND-1))

    [[ $# -gt 0 ]] && usage

    [[ -n "${FORCE}" ]] && unset DOTFILES
    local DOTFILES=${DOTFILES:-"$( cd "$( dirname "$(readlink -f "${BASH_SOURCE:-"$0"}")" )" && pwd )"}

    if [[ "$OSTYPE" =~ darwin.* ]]; then
      OS="osx_x86-64"
    elif [[ "$OSTYPE" =~ linux-gnu.* ]]; then
      OS="linux"
    else
      OS="unknow"
    fi

    [[ -n "$CLEAN" ]] && { cd ~; \
    rm .globus .vim .vscode .zsh .ssh/id_* .ssh/config .config/nvim; \
    rm .alidock-config.yaml .bash_profile .bashrc .bnlbox \.cadaverrc; \
    rm .fwknoprc .gitconfig .inputrc .netrc .rootrc .shrc .tmux.conf .vimrc .zshrc rootlogon.C; \
    cd -; exit 0; }

    # sourcing script to create the symbolic link
    local files=( "install/link.sh" )
    for file in "${files[@]}"; do
      local FILE_PATH=${DOTFILES}/$file
      # shellcheck source=./install/link.sh
      [ -f "${FILE_PATH}" ] && source "$FILE_PATH" "$FORCE"
    done

    [[ $OS = "osx_x86-64" && -n "$CONFIG_MAC" ]] && _config_myMac

    return 0
  }

  Main "$@"
)
