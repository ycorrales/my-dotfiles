#!/usr/bin/env bash
(
DOTFILES=${DOTFILES?"err_msg"}

source ${DOTFILES}/bash/add_files/colors.sh

#function for symlink
function do_symlink(){

  local __dir=".${1:+"$1/"}" #".( basename $1 )"
  local __linkables=$2
  local __ext=${3:-''}
  echo -e "\n $COLOR_YELLOW Creating symlinks"
  echo -e "================================ $COLOR_NONE"
  [ ! -d $HOME/$__dir ] && { echo -e "$COLOR_BLUE Creating ~/$__dir $COLOR_NONE"; mkdir -p $HOME/$__dir; }
  for __link in $__linkables; do
  __target="$HOME/$__dir$( basename $__link $__ext )"
  [ -e $__target ] && \
  { echo -e "$COLOR_RED ~${__target#HOME} already exists... Skipping. $COLOR_NONE"; } || \
  { echo -e "Creating symlink for $__link"; ln -s $__link $__target; }
  done
}

do_symlink '' "$( find -H "$DOTFILES" -maxdepth 3 -name '*.symlink' )" '.symlink'
do_symlink "ssh" "$DOTFILES/ssh/*" 
do_symlink "config" "$DOTFILES/config/*"

# create vim symlinks
# As I have moved off of vim as my full time editor in favor of neovim,
# I feel it doesn't make sense to leave my vimrc intact in the dotfiles repo
# as it is not really being actively maintained. However, I would still
# like to configure vim, so lets symlink ~/.vimrc and ~/.vim over to their
# neovim equivalent.

echo -e "\n $COLOR_YELLOW Creating vim symlinks"
echo -e "============================== $COLOR_NONE"
VIMFILES=( "$HOME/.vim:$DOTFILES/config/nvim" \
           "$HOME/.vimrc:$DOTFILES/config/nvim/init.vim" )
for __file in "${VIMFILES[@]}"; do
  KEY=${__file%%:*}
  VALUE=${__file#*:}
  [ -e ${KEY} ] && \
  { echo -e "$COLOR_RED ${KEY} already exists... skipping. $COLOR_NONE"; } || \
  { echo "Creating symlink for $KEY";  ln -s ${VALUE} ${KEY}; }
done
)
