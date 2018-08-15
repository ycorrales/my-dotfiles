#!/usr/bin/env bash

DOTFILES=${DOTFILES?"err_msg"}

echo -e "\nCreating symlinks"
echo "=============================="
__linkables=$( find -H "$DOTFILES" -maxdepth 3 -name '*.symlink' )
for __file in $__linkables ; do
  __target="$HOME/.$( basename $__file '.symlink' )"
  if [ -e $__target ]; then
    echo "~${__target#$HOME} already exists... Skipping."
  else
    echo "Creating symlink for $__file"
    ln -s $__file $__target
  fi
done

echo -e "\n\ninstalling to ~/.config"
echo "=============================="
if [ ! -d $HOME/.config ]; then
  echo "Creating ~/.config"
  mkdir -p $HOME/.config
fi

for __config in $DOTFILES/config/*; do
    __target=$HOME/.config/$( basename $__config )
  if [ -e $__target ]; then
    echo "~${__target#$HOME} already exists... Skipping."
  else
    echo "Creating symlink for $__config"
    ln -s $__config $__target
  fi
done

# create vim symlinks
# As I have moved off of vim as my full time editor in favor of neovim,
# I feel it doesn't make sense to leave my vimrc intact in the dotfiles repo
# as it is not really being actively maintained. However, I would still
# like to configure vim, so lets symlink ~/.vimrc and ~/.vim over to their
# neovim equivalent.

echo -e "\n\nCreating vim symlinks"
echo "=============================="
VIMFILES=( "$HOME/.vim:$DOTFILES/config/nvim" \
           "$HOME/.vimrc:$DOTFILES/config/nvim/init.vim" )

for __file in "${VIMFILES[@]}"; do
  KEY=${file%%:*}
  VALUE=${file#*:}
  if [ -e ${KEY} ]; then
    echo "${KEY} already exists... skipping."
  else
    echo "Creating symlink for $KEY"
    ln -s ${VALUE} ${KEY}
  fi
done
