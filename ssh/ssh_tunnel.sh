#! /usr/bin/env bash

(
  [[ ! $(declare -f -F pinfo) ]] && pinfo() echo $1
  [[ ! $(declare -f -F perror) ]] && perror() echo $1

  while getopts ":h" opt; do
    case "$opt" in
      h)
        pinfo "usage $0 <pattern> <ssh_opt>"
        exit 0
        ;;
      :)
        perror "ERROR: option "$OPTARG" needs a value"
        exit 1
        ;;
      \?)
        perror "ERROR: unkown option "$OPTARG""
        exit 1
        ;;
    esac
  done
  shift $(( $OPTIND-1 ))

  [[ "$#" -ne 2 ]] && {perror "usage $0 <pattern> <ssh_opt>"; exit 1;}

  PATTERN=${1}
  SSH_OPT=${2}

  [[ $( echo "$( ps -ef | grep "$PATTERN" | grep -v 'grep' | wc -l | bc) > 0" | bc ) == 1 ]] && \
    kill $(ps -ef | grep "$PATTERN" | grep -v 'grep' | sed -e "s/[ ]\{2,\}/ /g" | cut -d " " -f 2)

  eval ssh "$SSH_OPT" &> /dev/null
)
