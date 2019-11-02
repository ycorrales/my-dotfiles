# allow forward history searching with CTRL-s
[[ $- == *i* ]] && stty -ixon

# Using \[ and \] around colors is necessary to prevent
# issues with command line editing/browsing/completion

export COLOR_BLACK="\033[0;30m"
export COLOR_BLUE="\033[0;34m"
export COLOR_GREEN="\033[0;32m"
export COLOR_CYAN="\033[0;36m"
export COLOR_PINK="\033[0;35m"
export COLOR_RED="\033[0;31m"
export COLOR_PURPLE="\033[0;35m"
export COLOR_BROWN="\033[0;33m"
export COLOR_LIGHTGRAY="\033[0;37m"
export COLOR_DARKGRAY="\033[1;30m"
export COLOR_LIGHTBLUE="\033[1;34m"
export COLOR_LIGHTGREEN="\033[1;32m"
export COLOR_LIGHTCYAN="\033[1;36m"
export COLOR_LIGHTRED="\033[1;31m"
export COLOR_LIGHTPURPLE="\033[1;35m"
export COLOR_YELLOW="\033[1;33m"
export COLOR_WHITE="\033[1;37m"
export COLOR_NONE="\033[0m"

function plog(){
  echo -e "$COLOR_YELLOW $1 $COLOR_NONE"
}
function pinfo(){
  echo -e "$COLOR_LIGHTGREEN $1 $COLOR_NONE"
}
function pdebug(){
  echo -e "$COLOR_BLUE $1 $COLOR_NONE"
}
function perror(){
  echo -e "$COLOR_RED $1 $COLOR_NONE"
}
