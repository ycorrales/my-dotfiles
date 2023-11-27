#! /usr/bin/bash
(
SESSIONNAME='my_bnl_flx'
STARTDIR='/home/mvtx/felix-mvtx'
tmux has-session -t "$SESSIONNAME"  &> /dev/null

if [ $? != 0 ]
  then
    tmux new-session -s $SESSIONNAME -c $STARTDIR -n "" -d
    tmux select-pane -t 0; tmux split-window -t $SESSIONNAME:0 -h -c "$HOME"
    tmux select-pane -t 1; tmux split-window -t $SESSIONNAME:0 -h -c "$HOME"
    tmux select-pane -t 0; tmux split-window -t $SESSIONNAME:0 -v -c "$HOME"
    tmux select-pane -t 2; tmux split-window -t $SESSIONNAME:0 -v -c "$HOME"
    tmux select-pane -t 4; tmux split-window -t $SESSIONNAME:0 -v -c "$HOME"

    for pane in $( seq 0 5 ); do
      tmux select-pane -t "$pane"
      tmux send-keys -t $SESSIONNAME:0 "ssh bnl_flx$pane" C-m
      tmux send-keys -t $SESSIONNAME:0 "clear && source /home/mvtx/software/setup.sh" C-m
    done
fi
tmux select-window -t $SESSIONNAME:0
tmux select-pane -t 0
tmux attach -t $SESSIONNAME
)
