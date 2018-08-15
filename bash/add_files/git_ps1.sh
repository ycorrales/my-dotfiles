# this is specific to the location of the current version of git, installed by homebrew
git_prompt_f=/Library/Developer/CommandLineTools/usr/share/git-core/git-prompt.sh

if test -f $git_prompt_f; then
  source $git_prompt_f
fi
