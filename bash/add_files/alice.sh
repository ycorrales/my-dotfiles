export ALIBUILD_WORK_DIR="$HOME/Alice/AliSoft/sw"
  eval "`alienv shell-helper`"

export ALICE_ITSUP_AN_SW="$HOME/Alice/ITS_Upgrade/05_OB-HS_Assembly/OB-HIC-HS_Test/git_test-and-analysis"

alias ali-build='aliBuild build AliPhysics -d -z r6 -w ../sw/ --default root6'
alias   ali-cmd="alienv setenv '$( alienv q | grep AliPhysics | grep -v latest )'  -c $@"
alias ali-enter="alienv enter  '$( alienv q | grep AliPhysics | grep -v latest )'"
alias ali-cert='openssl x509 -in "$HOME/.globus/usercert.pem" -noout -dates'

ali-load() {
  alienv load "$( alienv q | grep AliPhysics | grep -v latest )"
  if [[ $? == 0 ]]; then
    alias     root="root -l"
    alias  aliroot="root -l"
    alias ali-token="alien-token-init ycorrale"
  fi
}

ali-clean() {
  alienv unload "$( alienv q | grep AliPhysics | grep -v latest )"
   if [[ $? == 0 ]]; then
    unset root
    unset aliroot
    unset alitoken
  fi
}

ali-find() {
  if [ ! -z $1 ]; then
    find -H ~/Alice/AliSoft/ali-master/ -iname $@
  else
    echo "ali-find: missing argument"
    return 1
  fi

}

ali-print() {
  ali-cmd aliroot -b -q "$HOME/Alice/MyMacros/PrintFileKeys.C\(\"$1\"\)"
}

kill_all_jobs() {
  local MAX=$1
  for JOBID in $( ali-cmd alien_ps | grep -v '-' | grep 'ycorrale' | awk '{print $2}' | sed 's/.*\(..........\)/\1/' ); do
    if [ -z "$MAX" ]; then
      ali-cmd alien_kill "$JOBID"
    elif [[ $JOBID < $MAX ]]; then
      ali-cmd alien_kill "$JOBID"
    fi
  done
}

