#! /bin/bash


function Mac_config(){
    sudo defaults write /Library/Preferences/com.apple.AppleFileServer guestAccess -bool NO
    sudo defaults write /Library/Preferences/SystemConfiguration/com.apple.smb.server AllowGuestAccess -bool NO
    sudo defaults write /Library/Preferences/com.apple.loginwindow SHOWOTHERUSERS_MANAGED -bool FALSE
}

function Make_symlink() {
    local DOTFILES="$HOME/.dotfiles"
    local SYMLINK_FILE=(bash_profile bashrc gitconfig globus oni ssh)
    for file in ${SYMLINK_FILE[@]}; do
        echo "linking $file"
        local FILE=$file
        local FILE_SYM="$FILE${FILE:+".symlink"}"
        ln -sf $DOTFILES/$FILE_SYM $HOME/.$FILE
    done
    #additional links
    echo "linking tmux.conf"
    ln -sf $DOTFILES/tmux/tmux.symlink $HOME/.tmux.conf
}

function Main() {
    Make_symlink
    Mac_config
}

Main $@
unset -f Mac_config
unset -f Make_symlink
unset -f Main
