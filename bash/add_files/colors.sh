# Using \[ and \] around colors is necessary to prevent
# issues with command line editing/browsing/completion

function plog(){
  echo -e "$COLOR_YELLOW $1 $COLOR_NONE" | gsed 's/\(\\\[\|\\\]\)//g'
}
function pinfo(){
  echo -e "$COLOR_LIGHTGREEN $1 $COLOR_NONE" | gsed 's/\(\\\[\|\\\]\)//g'
}
function pdebug(){
  echo -e "$COLOR_BLUE $1 $COLOR_NONE" | gsed 's/\(\\\[\|\\\]\)//g'
}
function perror(){
  echo -e "$COLOR_RED $1 $COLOR_NONE" | gsed 's/\(\\\[\|\\\]\)//g'
}

COLOR_BLACK="\[\033[0;30m\]"
COLOR_BLUE="\[\033[0;34m\]"
COLOR_GREEN="\[\033[0;32m\]"
COLOR_CYAN="\[\033[0;36m\]"
COLOR_PINK="\[\033[0;35m\]"
COLOR_RED="\[\033[0;31m\]"
COLOR_PURPLE="\[\033[0;35m\]"
COLOR_BROWN="\[\033[0;33m\]"
COLOR_LIGHTGRAY="\[\033[0;37m\]"
COLOR_DARKGRAY="\[\033[1;30m\]"
COLOR_LIGHTBLUE="\[\033[1;34m\]"
COLOR_LIGHTGREEN="\[\033[1;32m\]"
COLOR_LIGHTCYAN="\[\033[1;36m\]"
COLOR_LIGHTRED="\[\033[1;31m\]"
COLOR_LIGHTPURPLE="\[\033[1;35m\]"
COLOR_YELLOW="\[\033[1;33m\]"
COLOR_WHITE="\[\033[1;37m\]"
COLOR_NONE="\[\033[0m\]"
