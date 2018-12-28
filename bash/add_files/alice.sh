if [ -z $ALICE_WORK ]; then
  export ALICE_WORK="$HOME/Work/Alice"
fi
export ALISOFT="$ALICE_WORK/AliSoft"
export ALIBUILD_WORK_DIR="$ALISOFT/sw"
  eval "`alienv shell-helper`"

O2="VO_ALICE@O2::latest"
ALI="VO_ALICE@AliPhysics::latest"

alias    o2-cmd="alienv setenv $O2 -c $@"
alias   ali-cmd="alienv setenv $ALI  -c $@"
alias ali-enter="alienv enter  $ALI"
alias  ali-cert='openssl x509 -in "$HOME/.globus/usercert.pem" -noout -dates'

alias root='root -l'
alias ali='ali-cmd root'
alias  o2='o2-cmd  root'

ali-init() {
  aliBuild -z alice_sw init AliRoot,AliPhysics,AliDPG
}

ali-build() {
  pushd ${ALICESW}
  aliBuild build AliPhysics -d -z r6 -w ../sw/ --default root6
  aliBuild build AliDPG -d -w ../sw/
  popd
}

ali-load() {
  alienv load "$( alienv q | grep AliPhysics | grep -v latest )"
  type ali-token >/dev/null 2>&1 || alias ali-token="alien-token-init ycorrale"
}

ali-clean() {
  alienv unload "$( alienv q | grep AliPhysics | grep -v latest )"
  type ali-token >/dev/null 2>&1 && unalias ali-token
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

