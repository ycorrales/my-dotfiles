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
