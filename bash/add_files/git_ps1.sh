# this is specific to the location of the current version of git, installed by homebrew
git_prompt_f=/usr/local/Cellar/git/2.20.1/etc/bash_completion.d/git-prompt.sh
[[ $HOSTNAME =~ $SPHENIX_RCF ]] && \
  git_prompt_f=/usr/share/doc/git/contrib/completion/git-prompt.sh
[[ -f $git_prompt_f ]] && source $git_prompt_f
unset git_prompt
