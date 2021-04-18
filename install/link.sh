#!/usr/bin/env bash
(
DOTFILES=${DOTFILES?"err_msg"}

pinfo "" > /dev/null 2>&1 || source ${DOTFILES}/shell/add_files/utils.shell

#function for symlink
do_symlink()
{
  local SRC=$1
  local TGT=$2
  local S_SRC="~${SRC#$HOME}"
  local S_TGT="~${TGT#$HOME}"

  if test -e $TGT &&  test -z "$DO_FORCE"; then
    perror "$S_TGT already exists... Skipping.";
  else
    pinfo  "Creating symlink for $S_SRC $S_TGT";
    #ln -sfn $__source $__target;
  fi
}


prep_symlink()
{
  local DIR=$1
  local PREFIX=${DIR:+$DIR/}$2 #".( basename $1 )"
  local LINKABLES=$3
  local EXT=$4

  plog "\n Creating symlinks"
  plog "================================"

  [ ! -d $HOME/$DIR ] && \
    { pdebug "Creating ~/$DIR"; mkdir -p $HOME/$DIR; }

  for SRC in $LINKABLES; do
    SRC=$PREFIX$( basename $SRC $EXT )
    local TGT="$HOME/$SRC"
    do_symlink $SRC $TGT
  done
}

[ $1 = "-f" ] && DO_FORCE=1

# do_symlink dir prefix links_list [force]
prep_symlink ''        '.' "$( find -H "$DOTFILES" -maxdepth 3 -name '*.symlink' )" '.symlink'
prep_symlink '.ssh'    ''  "$DOTFILES/ssh/*"
prep_symlink '.config' ''  "$DOTFILES/config/*"
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
  do_symlink $VALUE $KEY
done
)
