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
alias  ll="gls -lFh ${colorflag} --group-directories-first "
alias lld="gls -l   ${colorflag} | grep ^d"
alias  ff='ll'
alias rmf="rm -rfv"

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

# IP addresses
alias ip="dig +short myip.opendns.com @resolver1.opendns.com"
alias localip="ipconfig getifaddr en1"
alias ips="ifconfig -a | perl -nle'/(\d+\.\d+\.\d+\.\d+)/ && print $1'"

# Flush Directory Service cache
alias flush="dscacheutil -flushcache"

# Recursively delete `.DS_Store` files
alias cleanup="find . -name '*.DS_Store' -type f -ls -delete"

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

#ALIROOT
alias    root="root -l"
alias aliroot="aliroot -l"

alias  ali_ls="alienv q | grep AliPhysics | grep -v latest"
#
export ROOT5="AliPhysics/r5-1"
export ROOT6="VO_ALICE@ROOT::latest-r6-root6"

#
SINGLE_CMD='alienv setenv'
MODULE_ALIROOT=${ROOT5}
alias  ali_cmd="${SINGLE_CMD} ${ROOT5} -c $@"
alias ali_load="alienv load $ROOT5"
#
alias  ali_token="alien-token-init ycorrale"
alias  nitty='$HOME/Library/Python/2.7/bin/nitty'
#
#
alias ali_cert='openssl x509 -in "$HOME/.globus/usercert.pem" -noout -dates'
alias ali_find='find ~/Alice/AliSoft/ali-master/ -iname'

function ali_Print() {
 aliroot -b -q $HOME/Alice/MyMacros/PrintFileKeys.C\(\"$1\"\)
}

function kill_all_jobs()
{
  MAX=$1
  for JOBID in $(alien_ps | grep -v '-' | grep 'ycorrale' | awk '{print $2}' | sed 's/.*\(.........\)/\1/'); do
    if [ -z "$MAX" ]; then
      alien_kill "$JOBID"
    elif [[ $JOBID < $MAX ]]; then
      alien_kill "$JOBID"
    fi
  done
}

#WORKING_DIR
alias  goITSup="clr; cd $HOME/Alice/Upgrade_ITS/"
alias  goITSupTest="clr; cd $HOME/Alice/Upgrade_ITS/05_OB-HS_Assembly/OB-HIC-HS_Test/"
alias  goITSupTestHIC="clr; cd $HOME/Alice/Upgrade_ITS/05_OB-HS_Assembly/OB-HIC-HS_Test/OB-HIC_Test"
alias  goITSupTestHS="clr; cd $HOME/Alice/Upgrade_ITS/05_OB-HS_Assembly/OB-HIC-HS_Test/OB-HS_Test"
alias  goSpecRun1="clr; cd $HOME/Alice/PWGLF_SPECTRA/SpectraAnalysisRun1"
alias  goSpecRun2="clr; cd $HOME/Alice/PWGLF_SPECTRA/SpectraAnalysisRun2"
alias  goBjet="clr; cd $HOME/Alice/PWGHF_HFCJ/Bjets"

#SECRET KEY
alias   getGoogle='oathtool --totp -b 4tylumrlosezfsqlwol2heahoekqsfne'
alias getLastPass='oathtool --totp -b gcf6nqnmwozgzlzh'
