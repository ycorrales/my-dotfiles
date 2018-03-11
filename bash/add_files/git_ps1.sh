# this is specific to the location of the current version of git, installed by homebrew
git_prompt_f=/usr/local/Cellar/git/2.13.0/etc/bash_completion.d/git-prompt.sh

if test -f $git_prompt_f; then
  source $git_prompt_f
fi
