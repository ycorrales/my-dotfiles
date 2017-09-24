DOTFILES="~/.dotfiles"

ln -s $DOTFILES/bash_profiles.symlink ~/.bash_profiles
ln -s $DOTFILES/bashrc.symlink ~/.bashrc
ln -s $DOTFILES/aliases.synlink ~/.bash_aliases
ln -s $DOTFILES/globus.symlink ~/.globus
ln -s $DOTFILES/gitconfig.symlink .gitconfig
ln -s $DOTFILES/vim/vimrc.symlink .vimrc
ln -s $DOTFILES/vim/vim_runtime.symlink .vim_runtime
ln -s $DOTFILES/ssh.symlink .ssh

