export ALICE_WORK=${ALICE_WORK:-"$HOME/Work/Alice"}
export ALISOFT=${ALISOFT:-"$ALICE_WORK/AliSoft"}
export ALIBUILD_WORK_DIR=${ALIBUILD_WORK_DIR:-"$ALISOFT/sw"}
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

alien-create-cert()
{
  local _path=${1:-"*.p12"}
  openssl pkcs12 -clcerts -nokeys -in $_path -out usercert.pem
  openssl pkcs12 -nocerts         -in $_path -out userkey.pem
}

ali-init() {
  aliBuild -z alice_sw init AliPhysics,AliDPG
}

ali-build() {
  pushd ${ALISOFT}/alice_sw
  aliBuild build AliPhysics -d -z r6 -w ../sw/ --default root6 && \
  aliBuild build AliDPG -d -w ../sw/
  aliBuild clean
  popd
}

ali-load() {
  alienv load "$ALI"
  type ali-token >/dev/null 2>&1 || alias ali-token="alien-token-init ycorrale"
}

ali-clean() {
  alienv unload "$ALI"
  type ali-token >/dev/null 2>&1 && unalias ali-token
}

ali-find() {
  if [ ! -z $1 ]; then
    find -H ${ALISOFT}/alice_sw -iname $@
  else
    echo "ali-find: missing argument"
    return 1
  fi
}

o2-build(){
 pushd ${ALISOFT}/alice_sw
 aliBuild -d --defaults o2 build O2
 aliBuild clean
 popd
}

o2-load() {
  alienv load "$O2"
}

o2-clean(){
  alienv unload "$O2"
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

