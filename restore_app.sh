#! /bin/bash

#script to restore application preferences from backup

BK_LIBRARY="/Volumes/Data/BackUp/user_Library"
USER_LIBRARY="$HOME/Library"

#iTerm
rsync -avrn "$BK_LIBRARY/Application\ Support/iTerm" "$USER_LIBRARY/Application\ Support"
