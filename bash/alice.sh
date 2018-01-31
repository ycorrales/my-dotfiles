ALICE_SOFT_DIR="${HOME}/Alice/AliSoft"
export ALIBUILD_WORK_DIR="${ALICE_SOFT_DIR}/sw"
 eval "`alienv shell-helper`"

 ALICE_ROOT_DIR="${ALICE_SOFT_DIR}/ali-root/AliRoot"
 ALICE_PHYS_DIR="${ALICE_SOFT_DIR}/ali-root/AliPhysics"

 export ALICE_ITSUP_TEST_DIR="$HOME/Alice/ITSupgrade/05_OB-HS_Assembly/OB-HIC-HS_Test/git_test-and-analysis"
#ALIROOT ALIASES
alias  alils="alienv q | grep AliPhysics | grep -v latest"
#
#export ROOT5="AliPhysics/r5-1"
export ROOT6=
#
SINGLE_CMD='alienv setenv'
MODULE_ALIROOT="VO_ALICE@AliPhysics::latest-r6-root6"
MODULE_ROOT="VO_ALICE@ROOT::latest-r6-root6"

alias  alicmd="${SINGLE_CMD} ${MODULE_ALIROOT} -c $@"
alias aliload="alienv load ${MODULE_ALIROOT}"
alias aliclean="alienv unload ${MODULE_ALIROOT}"
alias alienter="alienv enter ${MODULE_ALIROOT}"
#
alias     root="root -l"
alias  aliroot="aliroot -l"
alias alitoken="alien-token-init ycorrale"
alias    nitty="nitty"

#
#
alias alicert='openssl x509 -in "$HOME/.globus/usercert.pem" -noout -dates'
alias alifind='find ~/Alice/AliSoft/ali-master/ -iname'

function aliprint() {
  local MAIN_CMD="aliroot -b -q $HOME/Alice/MyMacros/PrintFileKeys.C\(\"$1\"\)"
}

function kill_all_jobs()
{
  MAX=$1
  for JOBID in $(alicmd alien_ps | grep -v '-' | grep 'ycorrale' | awk '{print $2}' | sed 's/.*\(..........\)/\1/'); do
    if [ -z "$MAX" ]; then
      alicmd alien_kill "$JOBID"
    elif [[ $JOBID < $MAX ]]; then
      alicmd alien_kill "$JOBID"
    fi
  done
}

