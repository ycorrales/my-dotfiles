if [ -z $ALICE_WORK ]; then
  echo "aliases.sh: ALICE_WORK env var not defined"
fi
#reaload bash config
alias reload='source ~/.bashrc'

#Detect with `ls` flavor is in use
type gls > /dev/null 2>&1
if [[ $? == 0 ]]; then # GNU `ls`
  LS="gls -N"
  colorflag="--color"
  gdirfirst="--group-directories-first"
else # OS X `ls`
  LS=ls
  colorflag="-G"
  gdirfirst=""
fi

#Filesystem aliases
alias ..='cd ..'
alias ...='cd ../..'
alias  la="$LS -AF  ${colorflag}"
alias  ll="$LS -lFh ${colorflag} ${gdirfirst} "
alias  lld="ll | grep ^d"
alias rmv="rm -rfv"
#allow OpenBSD tmux support UTF-8
alias tmux='tmux -u'

# Helper
alias grep='grep --color=auto'
alias df='df -h' # disk free, in Gigabytes, not bytes
alias du='du -h' # calculate disk usage for a folder
alias dud='du -d 1'
alias dus='du -hs'
alias vi='vim'
alias git='hub'
alias gits='git status'
alias g++='clang++'
alias clr='clear'
alias bye='exit'

# Using mvim as vim in terminal
alias vim='nvim'

#open fast vim config file
alias vimc='vimr ~/Software/dotfiles/config/nvim/my_configs.vim'

# IP addresses
alias ip="dig +short myip.opendns.com @resolver1.opendns.com"
alias localip="ipconfig getifaddr en1"
alias ips="ifconfig -a | perl -nle'/(\d+\.\d+\.\d+\.\d+)/ && print $1'"

# Flush Directory Service cache
alias flush="dscacheutil -flushcache"

# Recursively delete `.DS_Store` files
function cleanup()
{
  local DIR=${1:-"./"}
  find $DIR -name '*.DS_Store' -type f -ls -delete
}

# File size
alias fs="stat -f \"%z bytes\""

# Empty the Trash on all mounted volumes and the main HDD
alias emptytrash="sudo rm -rfv /Volumes/*/.Trashes; rm -rfv ~/.Trash"

# Hide/show all desktop icons (useful when presenting)
alias hidedesktop="defaults write com.apple.finder CreateDesktop -bool false && killall Finder"
alias showdesktop="defaults write com.apple.finder CreateDesktop -bool true && killall Finder"

# Kill all the tabs in Chrome to free up memory
# [C] explained: http://www.commandlinefu.com/commands/view/402/exclude-grep-from-your-grepped-output-of-ps-alias-included-in-description
alias chromekill="ps ux | grep '[C]hrome Helper --type=renderer' | grep -v extension-process | tr -s ' ' | cut -d ' ' -f2 | xargs kill"

# Kill Dock
alias killDock='defaults write com.apple.dock ResetLaunchPad -bool true; killall Dock'

alias wgetfolder='wget -r -np -nH --cut-dirs=3 -R "index*" '
alias mkpdfdoc='source ~/Software/MakePDF/mkPDFdoc.sh'
#
#WORKING_DIR
#alias  goAliPhysics='/ali-master/AliPhysics/'
#alias  goAliRoot='cd $HOME/Alice/AliSoft/ali-master/AliRoot/'
#alias  goTaskITSsa='cd $HOME/Alice/AliSoft/ali-master/AliPhysics/PWGLF/SPECTRA/PiKaPr/ITSsa'
alias  goDotfiles='clr; cd ~/Software/dotfiles'
alias  goITSup="clr; cd $ALICE_WORK/Projects/ITS_Upgrade/"
alias  goITSupTest="clr; cd $ALICE_WORK/Projects/ITS_Upgrade/assembly_OB/test_OB/"
alias  goITSupTestHIC="clr; cd $ALICE_WORK/Projects/ITS_Upgrade/assembly_OB/test_OB/results/OBHIC-XXXXX"
alias  goITSupTestHS="clr; cd $ALICE_WORK/Projects/ITS_Upgrade/assembly_OB/test_OB/results/OBHalfStave"
alias  goSpectra="clr; cd $ALICE_WORK/Projects/PWGLF_SPECTRA/"
alias  goSpecRun1="clr; cd $ALICE_WORK/Projects/PWGLF_SPECTRA/SpectraAnalysisRun1"
alias  goSpecRun2="clr; cd $ALICE_WORK/Projects/PWGLF_SPECTRA/SpectraAnalysisRun2"
alias  goBjet="clr; cd $ALICE_WORK/Projects/PWGHF_HFCJ/Bjets"
alias  gosPHENIX="clr; cd ~/Work/sPHENIX/"

#SECRET TOKEN
alias   getGoogle='oathtool --totp -b $(cat ~/Software/dotfiles/backup_codes/google_key.cd)'
alias getLastPass='oathtool --totp -b $(cat ~/Software/dotfiles/backup_codes/lastPass.cd)'

#SSH
#alias ssh_tunnel_zoro='ssh -fN -L 10022:ali42xl.to.infn.it:22 -l corrales zoroastro.to.infn.it'
#alias ssh_tunnel_ali42xl='ssh -p 10022 localhost'
alias ssh_dynamic_tunnel='ssh -CfN -D 1080'
alias ssh_vnc_tunnel='ssh -fN -L 5900:localhost:5900'