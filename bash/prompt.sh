# Using \[ and \] around colors is necessary to prevent
# issues with command line editing/browsing/completion!
  c_red='\[\e[01;31m\]'
c_green='\[\e[01;32m\]'
c_lyell='\[\e[01;33m\]'
c_lblue='\[\e[01;34m\]'
c_marge='\[\e[01;35m\]'
c_dgray='\[\e[38;5;241m\]'
c_clear='\[\e[0m\]'


# remove trailing slash in folder name completation
#bind 'set mark-directories off'
function __myPS1_PWD() {
  local myPWD=$PWD
  [[ "$myPWD" =~ ^"$HOME"(/|$) ]] && myPWD="~${myPWD#$HOME}"
  let WIDTH=${COLUMNS}/3
  while [[ ${#myPWD} -gt $WIDTH && ${myPWD} != ${PWD##*/} ]]; do
    myPWD=${myPWD#*/};
    local PRE='.../'
  done
  echo "${PRE:=""}${myPWD}"
}


# indicate a job (for example, vim) has been backgrounded
# If there is a job in the background, display a ✱
__suspended_jobs()
{
  local sj
  sj=$(jobs 2>/dev/null | tail -n 1)
  local MSG
  if [[ $sj == "" ]]; then
    MSG=' '
  else
    MSG='*'
  fi

  printf "${c_green}%-10s${c_clear}" "$MSG"
}


__git_eread ()
{
	local f="$1"
	shift
	test -r "$f" && read "$@" <"$f"
}


__git_dirty()
{
  # check if we're in a git repo
  git rev-parse --is-inside-work-tree &>/dev/null || return

  # check if it's dirty
  git diff --quiet --ignore-submodules &>/dev/null;
  if [[ $? -eq 1 ]]; then
      echo "${c_red}✗${c_clear}"
  else
    git diff --no-ext-diff --cached --quiet && \
      echo "${c_green}✔${c_clear}"              || \
      echo "${c_lyell}✔${c_clear}"
  fi
}


__upstream_branch() {
  remote=$(git for-each-ref --format='%(upstream:short)' $(git symbolic-ref -q HEAD)) 2>/dev/null
  if [[ $remote != "" ]]; then
    echo "$c_dgray($remote)$c_clear"
  fi
}

#retrieve git information like branch name and etc...
#code taken from git-prompt.sh
__git_info()
{
  #preserve exit status
  local exit=$?
	local detached=no
	local printf_format=' (%s)'

  case "$#" in
    0|1) print_format="${1:-$print_format}"
      ;;
    *) return $exit
      ;;
  esac

  local repo_info rev_parse_exit_code
	repo_info="$(git rev-parse --git-dir --is-inside-git-dir \
		--is-bare-repository --is-inside-work-tree \
		--short HEAD 2>/dev/null)"
	rev_parse_exit_code="$?"

	if [ -z "$repo_info" ]; then
		return $exit
	fi

  	local short_sha=""
	if [ "$rev_parse_exit_code" = "0" ]; then
		short_sha="${repo_info##*$'\n'}"
		repo_info="${repo_info%$'\n'*}"
	fi
	local inside_worktree="${repo_info##*$'\n'}"
	repo_info="${repo_info%$'\n'*}"
	local bare_repo="${repo_info##*$'\n'}"
	repo_info="${repo_info%$'\n'*}"
	local inside_gitdir="${repo_info##*$'\n'}"
	local g="${repo_info%$'\n'*}"

  if [ "true" = "$inside_worktree" ] &&
	   [ -n "${GIT_PS1_HIDE_IF_PWD_IGNORED-}" ] &&
	   [ "$(git config --bool bash.hideIfPwdIgnored)" != "false" ] &&
	   git check-ignore -q .
	then
		return $exit
	fi

  local r=""
	local b=""
	local step=""
	local total=""
	if [ -d "$g/rebase-merge" ]; then
		__git_eread "$g/rebase-merge/head-name" b
		__git_eread "$g/rebase-merge/msgnum" step
		__git_eread "$g/rebase-merge/end" total
		if [ -f "$g/rebase-merge/interactive" ]; then
			r="|REBASE-i"
		else
			r="|REBASE-m"
		fi
	else
		if [ -d "$g/rebase-apply" ]; then
			__git_eread "$g/rebase-apply/next" step
			__git_eread "$g/rebase-apply/last" total
			if [ -f "$g/rebase-apply/rebasing" ]; then
				__git_eread "$g/rebase-apply/head-name" b
				r="|REBASE"
			elif [ -f "$g/rebase-apply/applying" ]; then
				r="|AM"
			else
				r="|AM/REBASE"
			fi
		elif [ -f "$g/MERGE_HEAD" ]; then
			r="|MERGING"
		elif [ -f "$g/CHERRY_PICK_HEAD" ]; then
			r="|CHERRY-PICKING"
		elif [ -f "$g/REVERT_HEAD" ]; then
			r="|REVERTING"
		elif [ -f "$g/BISECT_LOG" ]; then
			r="|BISECTING"
		fi

    if [ -n "$b" ]; then
      :
    elif [ -n "$g/HEAD" ]; then
      # symlink symbolic ref
      b="$(git symbolic-ref HEAD 2>/dev/null)"
    else
      local head=""
      if ! __eread "$g/HEAD" head; then
        return exit
      fi
      # is it a symbolic ref?
      b="${head#ref: }"
      if [ "$head" = "$b" ]; then
        detached=yes
        b="$(git describe --contains --all HEAD 2>/dev/null)" ||
        b="$shor_sha..."
        b="($b)"
      fi
    fi
  fi

  if [ -n "$step" ] && [ -n "$total" ]; then
		r="$r $step/$total"
	fi

  local w=""
	local i=""
	local s=""
	local u=""
	local c=""
	local p=""

	if [ "true" = "$inside_gitdir" ]; then
		if [ "true" = "$bare_repo" ]; then
			c="BARE:"
		else
			b="GIT_DIR!"
		fi
	elif [ "true" = "$inside_worktree" ]; then
		if [ -n "${GIT_PS1_SHOWDIRTYSTATE-}" ] &&
		   [ "$(git config --bool bash.showDirtyState)" != "false" ]
		then
			git diff --no-ext-diff --quiet || w="*"
			git diff --no-ext-diff --cached --quiet || i="+"
			if [ -z "$short_sha" ] && [ -z "$i" ]; then
				i="#"
			fi
		fi
		if [ -n "${GIT_PS1_SHOWSTASHSTATE-}" ] &&
		   git rev-parse --verify --quiet refs/stash >/dev/null
		then
			s="$"
		fi

		if [ -n "${GIT_PS1_SHOWUNTRACKEDFILES-}" ] &&
		   [ "$(git config --bool bash.showUntrackedFiles)" != "false" ] &&
		   git ls-files --others --exclude-standard --directory --no-empty-directory --error-unmatch -- ':/*' >/dev/null 2>/dev/null
		then
			u="%${ZSH_VERSION+%}"
		fi

		if [ -n "${GIT_PS1_SHOWUPSTREAM-}" ]; then
			__git_ps1_show_upstream
		fi
	fi

	local z="${GIT_PS1_STATESEPARATOR-" "}"

  local bad_color="$c_red"
	local ok_color="$c_green"
	local flags_color="$c_lblue"

	local branch_color=""
	if [ $detached = no ]; then
		branch_color="$ok_color"
	else
	  branch_color="$bad_color"
	fi
	c="$branch_color$c"

	z="$c_clear$z"
	if [ "$w" = "*" ]; then
		w="$bad_color$w"
	fi
	if [ -n "$i" ]; then
		i="$ok_color$i"
	fi
	if [ -n "$s" ]; then
		s="$flags_color$s"
	fi
	if [ -n "$u" ]; then
		u="$bad_color$u"
	fi
	r="$c_clear$r"

	b=${b##refs/heads/}
	local f="$w$i$s$u"
	echo "$c$b${f:+$z$f}$r$p"
}

# get the status of the current branch and it's remote
# If there are changes upstream, display a ⇣
# If there are changes that have been committed but not yet pushed, display a ⇡
__git_arrows()
{
  # do nothing if there is no upstream configured
  git rev-parse --abbrev-ref @'{u}' &>/dev/null || return

  local arrows=""
  local status
  arrow_status="$(git rev-list --left-right --count HEAD...@'{u}' 2>/dev/null)"

  # do nothing if the command failed
  (( !$? )) || return
  # split on tabs
  arrow_status=(${arrow_status//$'\t'/ })
  local left=${arrow_status[0]} right=${arrow_status[1]}
  (( ${right:-0} > 0 )) && arrows+="\[\033[38;5;11m\]⇣\[\033[0m\]"
  (( ${left:-0}  > 0 )) && arrows+="\[\033[38;5;12m\]⇡\[\033[0m\]"

  echo $arrows
}

git_msg() {
  local GIT_PS1_HIDE_IF_PWD_IGNORED=1
  local GIT_PS1_SHOWDIRTYSTATE=
  local GIT_PS1_SHOWSTASHSTATE=1
  local GIT_PS1_SHOWUNTRACKEDFILES=1
  local GIT_PS1_STATESEPARATOR=""
  printf "%s %s%s" `__git_dirty` `__git_info` `__git_arrows`
}

PROMPT_SYMBOL='❯'
function prompt_command()
{
  local SHOW_FEATURE
  [[ -n $ROOTSYS ]] && SHOW_FEATURE=0 ||  SHOW_FEATURE=1

  if [[ $SHOW_FEATURE == 1 ]]; then
    PS1="${c_green}[\u on \h:${c_lyell}$(__myPS1_PWD)${c_green}]$(__suspended_jobs)$(git_msg)\n${c_green}${PROMPT_SYMBOL}${c_clear} "
  else
    PS1="${c_green}[\u on \h:${c_lyell}$(__myPS1_PWD)${c_green}]\n${c_green}${PROMPT_SYMBOL}${c_clear} "
  fi
}

function safe_append_prompt_command {
    local prompt_re

    # Set OS dependent exact match regular expression
    if [[ ${OSTYPE} == darwin* ]]; then
      # macOS
      prompt_re="[[:<:]]${1}[[:>:]]"
    else
      # Linux, FreeBSD, etc.
      prompt_re="\<${1}\>"
    fi

    if [[ ${PROMPT_COMMAND} =~ ${prompt_re} ]]; then
      return
    elif [[ -z ${PROMPT_COMMAND} ]]; then
      PROMPT_COMMAND="${1}"
    else
      PROMPT_COMMAND="${1};${PROMPT_COMMAND}"
    fi
}

safe_append_prompt_command prompt_command

