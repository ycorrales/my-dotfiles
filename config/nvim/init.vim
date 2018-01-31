source ~/.vim_runtime/plugins.vim

try
  source ~/.vim_runtime/my_configs.vim
catch
  echo "Error found in file ~/.vim_runtime/init.vim"
endtry
