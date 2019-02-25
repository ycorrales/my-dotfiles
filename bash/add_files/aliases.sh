#
# Alias
#

# General
alias reload='source ~/.bashrc' #reaload bash config
#Detect with `ls` flavor is in use
LS='ls'
colorflag='--color'
gdirfirst='--group-directories-first'
if [[ $OS = "osx_x86-64" ]]; then
  type gls > /dev/null 2>&1 && LS='gls -N' || { colorflag="-G"; gdirfirst=""; } # GNU `ls`
fi

#Filesystem aliases
alias  ..='cd ..'
alias ...='cd ../..'
alias  la="$LS -AF  ${colorflag}"
alias  ll="$LS -lFh ${colorflag} ${gdirfirst} "
alias  lld="ll | grep ^d"
alias  rmv="rm -rfv"

# Helper
alias grep='grep --color=auto'
alias   vi='vim'
alias gits='git status'
alias  clr='clear'
alias  bye='exit'
alias tmux='tmux -u' #allow OpenBSD tmux support UTF-8
alias vimc='vim $DOTFILES/config/nvim/my_configs.vim' #open fast vim config file

#WORKING_DIR
alias goDotfiles='clr; cd ~/$DOTFILES'

alias flush="dscacheutil -flushcache" # Flush Directory Service cache

# ip Addresses
alias ip="dig +short myip.opendns.com @resolver1.opendns.com"
alias localip="ipconfig getifaddr en1"
alias ips="ifconfig -a | perl -nle'/(\d+\.\d+\.\d+\.\d+)/ && print $1'"

# Alias for mac only
if [[ $OS = "osx_x86-64" ]]; then
  alias df='df -h' # disk free, in Gigabytes, not bytes
  alias du='du -h' # calculate disk usage for a folder
  alias dud='du -d 1'
  alias dus='du -hs'
  alias git='hub'
  alias g++='clang++'

  # Kill all the tabs in Chrome to free up memory
  # [C] explained: http://www.commandlinefu.com/commands/view/402/exclude-grep-from-your-grepped-output-of-ps-alias-included-in-description
  alias chromekill="ps ux | grep '[C]hrome Helper --type=renderer' | grep -v extension-process | tr -s ' ' | cut -d ' ' -f2 | xargs kill"

  # Kill Dock
  alias killDock='defaults write com.apple.dock ResetLaunchPad -bool true; killall Dock'

  alias wgetfolder='wget -r -np -nH --cut-dirs=3 -R "index*" '
  # File size
  alias fs="stat -f \"%z bytes\""

  # Empty the Trash on all mounted volumes and the main HDD
  alias emptytrash="sudo rm -rfv /Volumes/*/.Trashes; rm -rfv ~/.Trash"

  # Hide/show all desktop icons (useful when presenting)
  alias hidedesktop="defaults write com.apple.finder CreateDesktop -bool false && killall Finder"
  alias showdesktop="defaults write com.apple.finder CreateDesktop -bool true && killall Finder"

fi

# Alias for personal mac only
if [[ ! $HOSTNAME =~ $SPHENIX_RCF ]]; then
  echo ${ALICE_WORK?"aliases.sh: ALICE_WORK env var not defined"} > /dev/null

  alias vim='nvim' # Using mvim as vim in terminal
  alias mkpdfdoc='source ~/Software/MakePDF/mkPDFdoc.sh'
  #
  #WORKING_DIR
  alias  goITSup="clr; cd $ALICE_WORK/Projects/ITS_Upgrade/"
  alias  goITSupTest="clr; cd $ALICE_WORK/Projects/ITS_Upgrade/assembly_OB/test_OB/"
  alias  goSpectra="clr; cd $ALICE_WORK/Projects/PWGLF_SPECTRA/"
  alias  goSpecRun1="clr; cd $ALICE_WORK/Projects/PWGLF_SPECTRA/SpectraAnalysisRun1"
  alias  goSpecRun2="clr; cd $ALICE_WORK/Projects/PWGLF_SPECTRA/SpectraAnalysisRun2"
  alias  goBjet="clr; cd $ALICE_WORK/Projects/PWGHF_HFCJ/Bjets"
  alias  gosPHENIX="clr; cd ~/Work/sPHENIX/"

  #SECRET TOKEN
  alias   getGoogle='oathtool --totp -b $(cat ~/DOTFILES/backup_codes/google_key.cd)'
  alias getLastPass='oathtool --totp -b $(cat ~/DOTFILES/backup_codes/lastPass.cd)'

  #SSH
  #alias ssh_tunnel_zoro='ssh -fN -L 10022:ali42xl.to.infn.it:22 -l corrales zoroastro.to.infn.it'
  #alias ssh_tunnel_ali42xl='ssh -p 10022 localhost'
  alias ssh_dynamic_tunnel='ssh -CfN -D 1080'
  alias ssh_vnc_tunnel='ssh -fN -L 5900:localhost:5900'

  TRASH_FILE='.DS_Store'
else
  alias l-sphenix='source /opt/sphenix/core/bin/sphenix_setup.sh -n'
  alias l-sphenix-r6='l-sphenix root6'
  TRASH_FILE='0'
fi #end no sSPHENIX RCF

# Recursively delete `.DS_Store` files
function cleanup()
{
  local DIR=${1:-"./"}
  local f
  for f in ${TRASH_FILE[@]}; do
    find $DIR -name $f -type f -ls -delete
  done
}
