if [ -z $ALICE_WORK ]; then
  echo "aliases.sh: ALICE_WORK env var not defined"
fi
#reaload bash config
alias reload='source ~/.bashrc'

#Detect with `ls` flavor is in use
if gls --color > /dev/null 2>&1; then # GNU `ls`
  colorflag="--color"
else # OS X `ls`
  colorflag="-G"
fi

#Filesystem aliases
alias ..='cd ..'
alias ...='cd ../..'
alias ....="cd ../../.."
alias .....="cd ../../../.."

alias   l="gls -lah ${colorflag}"
alias  la="gls -AF  ${colorflag}"
alias  ll="gls -lFhrt ${colorflag} --group-directories-first "
alias lld="gls -l   ${colorflag} | grep ^d"
alias  dds='ll'
alias rmv="rm -rfv"

# Helper
alias grep='grep --color=auto'
alias df='df -h' # disk free, in Gigabytes, not bytes
alias du='du -h -c' # calculate disk usage for a folder
alias dud='du -d 1 -h'
alias dus='du -hs'
alias vi='vim'
alias git='hub'
alias gits='git status'
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

alias chrome="/Applications/Google\\ \\Chrome.app/Contents/MacOS/Google\\ \\Chrome"
alias canary="/Applications/Google\\ Chrome\\ Canary.app/Contents/MacOS/Google\\ Chrome\\ Canary"

# Kill Dock
alias killDock='defaults write com.apple.dock ResetLaunchPad -bool true; killall Dock'

#alias ssh_tunnel_zoro='sudo ssh -fN -L 10022:ali42xl.to.infn.it:22 -l corrales zoroastro.to.infn.it'
#alias ssh_tunnel_ali42xl='ssh -p 10022 localhost'
alias wgetfolder='wget -r -np -nH --cut-dirs=3 -R "index*" '
alias mkpdfdoc='source ~/Software/MakePDF/mkPDFdoc.sh'
#
alias itstesths='ssh itstesths'
alias itsteststave='ssh itsteststave'

#WORKING_DIR
#alias  goAliPhysics='/ali-master/AliPhysics/'
#alias  goAliRoot='cd $HOME/Alice/AliSoft/ali-master/AliRoot/'
#alias  goTaskITSsa='cd $HOME/Alice/AliSoft/ali-master/AliPhysics/PWGLF/SPECTRA/PiKaPr/ITSsa'
alias  goITSup="clr; cd $ALICE_WORK/ITS_Upgrade/"
alias  goITSupTest="clr; cd $ALICE_WORK/ITS_Upgrade/OB-HS_Assembly/OB-HIC-HS_Test/"
alias  goITSupTestHIC="clr; cd $ALICE_WORK/ITS_Upgrade/OB-HS_Assembly/OB-HIC-HS_Test/OB-HIC_Test"
alias  goITSupTestHS="clr; cd $ALICE_WORK/ITS_Upgrade/OB-HS_Assembly/OB-HIC-HS_Test/OB-HS_Test"
alias  goSpectra="clr; cd $ALICE_WORK/PWGLF_SPECTRA/"
alias  goSpecRun1="clr; cd $ALICE_WORK/PWGLF_SPECTRA/SpectraAnalysisRun1"
alias  goSpecRun2="clr; cd $ALICE_WORK/PWGLF_SPECTRA/SpectraAnalysisRun2"
alias  goBjet="clr; cd $ALICE_WORK/PWGHF_HFCJ/Bjets"

#SECRET TOKEN
alias   getGoogle='oathtool --totp -b xvkjuinfzztepik2tfm2fntdby2v4ywe'
alias getLastPass='oathtool --totp -b gcf6nqnmwozgzlzh'
