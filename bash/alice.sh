ALICE_SOFT_DIR="${HOME}/Alice/AliSoft"
export ALIBUILD_WORK_DIR="${ALICE_SOFT_DIR}/sw"
 eval "`alienv shell-helper`"

 ALICE_ROOT_DIR="${ALICE_SOFT_DIR}/ali-root/AliRoot"
 ALICE_PHYS_DIR="${ALICE_SOFT_DIR}/ali-root/AliPhysics"

#ALIROOT ALIASES
alias    root="root -l"
alias aliroot="aliroot -l"

alias  alils="alienv q | grep AliPhysics | grep -v latest"
#
#export ROOT5="AliPhysics/r5-1"
export ROOT6="VO_ALICE@AliPhysics::latest-r6-root6"

#
SINGLE_CMD='alienv setenv'
MODULE_ALIROOT=${ROOT6}
alias  alicmd="${SINGLE_CMD} ${ROOT6} -c $@"
alias aliload="alienv load $ROOT6"
alias aliclean="alienv unload $ROOT6"
alias alienter="alienv enter $ROOT6"
#
alias  alitoken="alien-token-init ycorrale"
#
#
alias alicert='openssl x509 -in "$HOME/.globus/usercert.pem" -noout -dates'
alias alifind='find ~/Alice/AliSoft/ali-master/ -iname'

function aliprint() {
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

