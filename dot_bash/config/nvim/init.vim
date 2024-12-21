if has('nvim') && ! exists('g:vscode')
  " init.lua
  " Neovim-specific configuration
  " Use the ycm config
  try
    lua << EOF
      local ycm = require("ycm")
      ycm.setup()
EOF
  catch
    echo "Error loading lua settings"
  endtry
else
  try
    source ~/.vim/plugins.vim
  catch
    echo "Error loading pluging files"
  endtry

  try
    source ~/.vim/my_configs.vim
  catch
    echo "Error found in file ~/.vim/my_configs.vim"
  endtry
endif
