if [ -z $ALICE_WORK ]; then
  export ALICE_WORK="$HOME/Work/Alice"
fi
export ALISOFT="$ALICE_WORK/AliSoft"
export ALICESW="$ALISOFT/alice_sw"
export ALIBUILD_WORK_DIR="$ALISOFT/sw"
  eval "`alienv shell-helper`"

export ALICE_ITSUP_AN_SW="$ALICE_WORK/ITS_Upgrade/05_OB-HS_Assembly/OB-HIC-HS_Test/git_test-and-analysis"

alias   ali-cmd="alienv setenv '$( alienv q | grep AliPhysics | grep -v latest )'  -c $@"
alias ali-enter="alienv enter  '$( alienv q | grep AliPhysics | grep -v latest )'"
alias ali-cert='openssl x509 -in "$HOME/.globus/usercert.pem" -noout -dates'

alias root="root -l"
alias ali='ali-cmd root'
alias o2='alienv setenv VO_ALICE@O2::latest -c root -l'

ali-init() {
  aliBuild -z alice_sw init AliRoot,AliPhysics
}

ali-build() {
  cd ${ALICESW}
  aliBuild build AliPhysics -d -z r6 -w ../sw/ --default root6
  cd -
}

ali-load() {
  alienv load "$( alienv q | grep AliPhysics | grep -v latest )"
  if [[ $? == 0 ]]; then
    alias ali-token="alien-token-init ycorrale"
  fi
}

ali-clean() {
  alienv unload "$( alienv q | grep AliPhysics | grep -v latest )"
   if [[ $? == 0 ]]; then
    unalias ali-token
  fi
}

ali-find() {
  if [ ! -z $1 ]; then
    find -H ${ALICESW} -iname $@
  else
    echo "ali-find: missing argument"
    return 1
  fi
}

o2-build(){
 cd ${ALICESW}
 aliBuild -d --defaults o2 build O2
 cd -
}

o2-load() {
  alienv load "VO_ALICE@O2::latest"
}

o2-clean(){
  alienv unload "VO_ALICE@O2::latest"
}

root-print() {
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

