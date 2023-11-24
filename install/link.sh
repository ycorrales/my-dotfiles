#!/usr/bin/env bash

(
  set -euo pipefail

  DOTFILES=${DOTFILES?"err_msg"}

  pinfo "" > /dev/null 2>&1 || source "${DOTFILES}/shell/add_files/utils.shell"

  #function for symlink
  function do_symlink()
  {
    local TARGET=${1:-}
    local LINK=${2:-}
    local S_TARGET="~${TARGET#$HOME}"
    local S_LINK="~${LINK#$HOME}"

    if test -e "$LINK" &&  test -z "$DO_FORCE"; then
      perror "$S_LINK already exists... Skipping.";
    else
      pinfo  "Creating symlink $S_LINK for $S_TARGET";
      ln -nsf "$TARGET" "$LINK";
    fi
  }

  function prep_symlink()
  {
    local DIR=${1:-} #
    local PREFIX=${DIR:+$DIR/}${2:-} #".( basename $1 )"
    local LINKABLES=${3:-}
    local EXT=${4:-}

    plog "\n Creating symlinks"
    plog "================================"

    [ ! -d "$HOME"/"$DIR" ] && \
      { pdebug "Creating ~/$DIR"; mkdir -p "$HOME"/"$DIR"; }

    for TARGET in $LINKABLES; do
      local LINK_NAME="$HOME/$PREFIX$( basename "$TARGET" "$EXT" )"
      do_symlink "$TARGET" "$LINK_NAME"
    done
  }

  DO_FORCE=${1:-""}
  [[ "$( bc -l <<< "$( ssh -V 2> >(sed 's,^[^0-9]*,,;s,[^\.0-9].*,,') ) < '7.0'" )" == "1" ]] && \
    SSH_CONFIG_6="$DOTFILES/ssh/config_6"

  ln -nsf "${SSH_CONFIG_6:-"$DOTFILES/ssh/config_7"}" "$DOTFILES/ssh/config"

  # do_symlink dir prefix links_list [force]
  prep_symlink ''        '.' "$( find -H "$DOTFILES" -maxdepth 3 -name '*.symlink' )" '.symlink'
  prep_symlink '.ssh'    ''  "$( find -H "$DOTFILES/ssh" -maxdepth 1 \( -type f -o -type l \) \
    \( -name 'config' -o -name 'id_*' -o -name 'rc' \) )"
  prep_symlink '.config' ''  "$( find -H "$DOTFILES/config" -maxdepth 1 ! -path "$DOTFILES/config" )"
  prep_symlink ''        ''  "$DOTFILES/root/rootlogon.C"

  # create vim symlinks
  # As I have moved off of vim as my full time editor in favor of neovim,
  # I feel it doesn't make sense to leave my vimrc intact in the dotfiles repo
  # as it is not really being actively maintained. However, I would still
  # like to configure vim, so lets symlink ~/.vimrc and ~/.vim over to their
  # neovim equivalent.

  plog "\n Creating vim symlinks"
  plog "=============================="
  VIMFILES=( "$HOME/.vim:$DOTFILES/config/nvim" \
             "$HOME/.vimrc:$DOTFILES/config/nvim/init.vim" )
  for __file in "${VIMFILES[@]}"; do
    KEY=${__file%%:*}
    VALUE=${__file#*:}
    do_symlink "$VALUE" "$KEY"
  done
)
