#!/usr/bin/env bash
(
DOTFILES=${DOTFILES?"err_msg"}

pinfo "" > /dev/null 2>&1 || source ${DOTFILES}/shell/add_files/utils.shell

#function for symlink
do_symlink()
{
  local __source=$1
  local __target=$2

  [[ -e $__target && -z "$force" ]] &&\
  { perror "~${__target#HOME} already exists... Skipping.";} || \
  { pinfo  "Creating symlink for $__source $__target"; ln -sfn $__source $__target; }
}


prep_symlink()
{
  local __dir=$1
  local __prefix=${__dir:+$__dir/}$2 #".( basename $1 )"
  local __linkables=$3
  local __ext=${4:-''}

  plog "\n Creating symlinks"
  plog "================================"

  [ ! -d $HOME/$__dir ] && \
    { pdebug "Creating ~/$__dir"; mkdir -p $HOME/$__dir; }

  for __src in $__linkables; do
   local __target="$HOME/$__prefix$( basename $__src $__ext )"

    do_symlink $__src $__target
  done
}

[[ $1 == "-f" ]] && force=1
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
