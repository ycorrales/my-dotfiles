if [ -z $ALICE_WORK ]; then
  export ALICE_WORK="$HOME/Work/Alice"
fi
export ALISOFT="$ALICE_WORK/AliSoft"
export ALIBUILD_WORK_DIR="$ALISOFT/sw"
  eval "`alienv shell-helper`"

export ALICE_ITSUP_AN_SW="$ALICE_WORK/ITS_Upgrade/05_OB-HS_Assembly/OB-HIC-HS_Test/git_test-and-analysis"

alias   ali-cmd="alienv setenv '$( alienv q | grep AliPhysics | grep -v latest )'  -c $@"
alias ali-enter="alienv enter  '$( alienv q | grep AliPhysics | grep -v latest )'"
alias ali-cert='openssl x509 -in "$HOME/.globus/usercert.pem" -noout -dates'

alias root='ali-cmd root -l'

ali-init() {
  aliBuild -z ali-master init AliRoot,AliPhysics
}
ali-build() {
  local ali_master_path="$ALISOFT/ali-master"
  cd ${ali_master_path}
  aliBuild build AliPhysics -d -z r6 -w ../sw/ --default root6
  cd -
}
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
    unalias root; alias root='ali-cmd root -l'
    unalias aliroot
    unalias ali-token
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
  ali-cmd aliroot -b -q "$ALICE_WORK/MyMacros/PrintFileKeys.C\(\"$1\"\)"
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

