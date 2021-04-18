#! /usr/bin/env bash

(
  USE_USER=${1:-$(whoami)}
  echo "Changing write access to user $USE_USER"

  sudo chown -R $USE_USER /usr/local/Cellar
  sudo chown -R $USE_USER /usr/local/Homebrew
  sudo chown -R $USE_USER /usr/local/var/homebrew
  sudo chown -R $USE_USER /usr/local/Caskroom

  sudo chown -R $USE_USER /usr/local/Frameworks /usr/local/bin /usr/local/etc /usr/local/etc/bash_completion.d /usr/local/include /usr/local/lib /usr/local/lib/pkgconfig /usr/local/lib/python3.7/site-packages /usr/local/opt /usr/local/sbin /usr/local/share /usr/local/share/aclocal /usr/local/share/doc /usr/local/share/info /usr/local/share/locale /usr/local/share/man /usr/local/share/man/man1 /usr/local/share/man/man3 /usr/local/share/man/man4 /usr/local/share/man/man5 /usr/local/share/man/man7 /usr/local/share/man/man8 /usr/local/share/zsh
)