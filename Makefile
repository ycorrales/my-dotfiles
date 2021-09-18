SHELL:=/bin/bash
#Makefile

################################################################################
################################################################################
################################################################################
EXCLUDE_PATHS = ! -path './config/nvim/*' ! -path './vscode.symlink/*'
EXCLUDE_SHELLCHECK_CODES = -e SC2009 -e SC2126
shell_check_all:
	find . -iname "*.sh" $(EXCLUDE_PATHS) | xargs shellcheck -x -s bash -Calways $(EXCLUDE_SHELLCHECK_CODES)

shell_check_apply:
	-(find . -iname "*.sh" $(EXCLUDE_PATHS) | sed 's|^./||g' \
		| xargs shellcheck -s bash -f diff > shellcheck.patch)
	git apply shellcheck.patch

help:
	(cat Makefile | grep '##')

%:
	@:
