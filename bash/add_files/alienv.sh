if [[ ! -z "$(type alienv 2> /dev/null)" ]]; then
  export ALICE_WORK=${ALICE_WORK:-"$HOME/Work/Alice"}
  export ALISOFT=${ALISOFT:-"$ALICE_WORK/AliSoft"}
  export ALIBUILD_WORK_DIR=${ALIBUILD_WORK_DIR:-"$ALISOFT/sw"}
    eval "`alienv shell-helper`"

  O2="VO_ALICE@O2::latest"
  ALI="VO_ALICE@AliPhysics::latest"
  ROOT="VO_ALICE@ROOT::latest"

  alias    o2-cmd="alienv setenv $O2 -c $@"
  alias   ali-cmd="alienv setenv $ALI  -c $@"
  alias ali-enter="alienv enter  $ALI"
  alias  ali-cert='openssl x509 -in "$HOME/.globus/usercert.pem" -noout -dates'

  alias   rl='alienv setenv $ROOT -c root -l'
  alias  ali='ali-cmd root -l'
  alias   o2='o2-cmd  root -l'

  alien-create-cert()
  {
    local _path=${1:-"*.p12"}
    openssl pkcs12 -clcerts -nokeys -in $_path -out usercert.pem
    openssl pkcs12 -nocerts         -in $_path -out userkey.pem
  }

  ali-init() {
    pushd ${ALISOFT}
    aliBuild -z alice_sw init AliPhysics@master
    popd
  }

  ali-build() {
    local sw_path=~/.sw
    local old_alibuild_path=$ALIBUILD_WORK_DIR
    ln -s $ALIBUILD_WORK_DIR $sw_path
    ALIBUILD_WORK_DIR=$sw_path
    pushd ${ALISOFT}/alice_sw
    aliBuild build AliPhysics -d -z r6 -w $ALIBUILD_WORK_DIR --default user-next-root6
    #&& aliBuild build AliDPG -d -w $ALIBUILD_WORK_DIR
    aliBuild clean
    rm -rfv $sw_path
    popd
    ALIBUILD_WORK_DIR=$old_alibuild_path
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

  o2-init() {
    pushd ${ALISOFT}
    aliBuild init O2@dev -d -z alice_sw --default o2
    popd
  }

  o2-build(){
  pushd ${ALISOFT}/alice_sw
  aliBuild build O2 -d -w $ALIBUILD_WORK_DIR --defaults o2
  aliBuild clean
  popd
  }

  o2-load() {
    alienv load "$O2"
  }

  o2-clean(){
    alienv unload "$O2"
  }

  rl-ls()
  {
    rl <<EOF
    gMyUtils->ShowFileKeys("$1")
    .q
EOF
  }

  alien_kill_all_jobs() {
    local MAX=$1
    for JOBID in $( ali-cmd alien_ps | grep -v '-' | grep 'ycorrale' | awk '{print $2}' | sed 's/.*\(..........\)/\1/' ); do
      if [ -z "$MAX" ]; then
        ali-cmd alien_kill "$JOBID"
      elif [[ $JOBID < $MAX ]]; then
        ali-cmd alien_kill "$JOBID"
      fi
    done
  }

  alien_merge_rbyr() {

    function LastField() {
      local LINE="$1"
      local FIELD
      local i=1
      while [ "${FIELD}x" == 'x' ]; do
        FIELD=$(echo "$LINE" | rev | cut -d"/" -f"$i" | rev)
        let i=$i+1
      done
      echo "$FIELD"
    }

    local MIN_NUM_ARG=1
    if [[ $# -lt ${MIN_NUM_ARG} ]]; then
      echo "Only $# number of arguments. Must be at least 2"
      return;
    fi
    local DIRBASE=$1
    local FILESTOMERGE=$2
    local re='^[0-9]+$'
    [[ ${FILESTOMERGE} =~ $re ]] || FILESTOMERGE="-1"
    local CMD="alien_ls"
    local ALIEN_HOME_PATH="/alice/cern.ch/user/y/ycorrale"
    local FULL_PATH=${ALIEN_HOME_PATH}/${DIRBASE}/output/
    local FOLDER=$( LastField "${DIRBASE}")
    echo "Creating and entering the main folder $FOLDER"
    mkdir -p $FOLDER
    pushd $FOLDER
    for RUN_NUM in $(aliCmd ${CMD} $FULL_PATH | grep -E '^[0-9]+' ); do
      local DIR_NAME=${RUN_NUM}
      mkdir -p ${DIR_NAME}
      echo "Entering to $DIR_NAME"
      cd $DIR_NAME
ali -l -b <<END
  gMyUtils->MergeFromFind("$FULL_PATH/$DIR_NAME","AnalysisResults.root", 1, ${FILESTOMERGE})
  .q
END
      cd ..
    done
    echo "Exiting main folder ..."
    popd
  }
fi

# Execute alidock within the appropriate Python virtual environment
if [[ -d $HOME/.virtualenvs/alidock ]]; then
  function alidock() {
    (
      source "/Users/ycorrales/.virtualenvs/alidock/bin/activate" && command alidock "$@"; exit $?;
    )
  }
fi
