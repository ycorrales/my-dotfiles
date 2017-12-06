if $USER == 'ycorrales'

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => GUI related
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " Set font according to system
  if has("mac") || has("macunix")
    set gfn=Hack:h12,Source\ Code\ Pro:h12,Meslo\ LG\ M\ DZ:h13
  elseif has("win16") || has("win32")
    set gfn=Hack:h14,Source\ Code\ Pro:h12,Bitstream\ Vera\ Sans\ Mono:h11
  elseif has("gui_gtk2")
    set gfn=Hack\ 14,Source\ Code\ Pro\ 12,Bitstream\ Vera\ Sans\ Mono\ 11
  elseif has("linux")
    set gfn=Hack\ 14,Source\ Code\ Pro\ 12,Bitstream\ Vera\ Sans\ Mono\ 11
  elseif has("unix")
    set gfn=Monospace\ 13
  endif

  " Disable scrollbars (real hackers don't use scrollbars for navigation!)
  set guioptions-=r
  set guioptions-=R
  set guioptions-=l
  set guioptions-=L

  " Colorscheme
  if has("gui_running")
    colorscheme peaksea
  else
    colorscheme ir_black
  endif
  set background=dark

  highlight IncSearch ctermbg=red ctermfg=0 guibg=#ff0000 guifg=#000000
  " Some basic configuration
  set timeoutlen=1000
  "set completeopt+=longest

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Added/modified options wrt to basic
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " avoid typo pressing esc
  inoremap § <esc>

  " Disable highlight when <leader><cr> is pressed
  map <silent> <leader><cr>    :nohlsearch<Bar>:echo<cr>
  map <silent> <leader><Space> :set hlsearch! hlsearch?<CR>

	" better tab completion (like bash)
	set wildmode=longest,list,full

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Fast editing and reloading of vimrc configs
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  map <leader>e :tabe! ~/.vim_runtime/my_configs.vim<cr>
  autocmd! bufwritepost ~/.vim_runtime/my_configs.vim source ~/.vim_runtime/my_configs.vim

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " move tabs to the end for new, single buffers (exclude splits)
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  autocmd BufNew * if winnr('$') == 1 | tablast | endif
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Turn persistent undo on
  "    means that you can undo even when you close a buffer/VIM
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  try
    set undodir=~/.vim_runtime/temp_dirs/undodir
    set undofile
  catch
  endtry

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Command mode related
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " Smart mappings on the command line
  cno $b tabe ~/.vim_runtime/vimrcs/basic.vim
  cno $p tabe ~/.vim_runtime/vimrcs/plugins_config.vim

  cno $h e ~/
  cno $d e ~/Desktop/
  cno $c e <C-\>eCurrentFileDir("e")<cr>
  cno $t tabe <C-\>eCurrentFileDir("e")<cr>

  cnoreabbrev <expr> te getcmdtype() == ":" && getcmdline() == 'te' ? 'tabe' : 'te'

  " $q is super useful when browsing on the command line
  " it deletes everything until the last slash
  cno $q <C-\>eDeleteTillSlash()<cr>

  " Bash like keys for the command line
  cnoremap <C-A> <Home>
  cnoremap <C-E> <End>
  cnoremap <C-K> <C-U>

  cnoremap <C-P> <Up>
  cnoremap <C-N> <Down>

  " Map ½ to something useful
  map ½ $
  cmap ½ $
  imap ½ $

  "move in insert mode
  inoremap <C-A> <esc>^<esc>i
  inoremap <C-E> <esc>g_<esc>a

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => autocomplete
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  inoremap <D-[> <C-P>
  inoremap <D-]> <C-N>

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Parenthesis/bracket
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  vnoremap <leader>(  <esc>`>a)<esc>`<i(<esc>
  vnoremap <leader>[  <esc>`>a]<esc>`<i[<esc>
  vnoremap ${  <esc>`>a}<esc>`<i{<esc>
  vnoremap $'  <esc>`>a'<esc>`<i'<esc>
  vnoremap $"  <esc>`>a"<esc>`<i"<esc>

  " Map auto complete of (, [, {, <,", ',
  inoremap <leader>) ()<esc>i
  inoremap <leader>] []<esc>i
  inoremap <leader>} {}<esc>i
  inoremap <leader>> <><esc>i
  "inoremap ${} <esc>o{<esc>o}<esc>O
  inoremap <leader>' ''<esc>i
  inoremap <leader>" ""<esc>i
  inoremap <leader>$ $$<esc>i

  " C++
  inoremap #I #include <esc>a

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => General abbreviations
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  iab xdate <c-r>=strftime("%d/%m/%y %H:%M:%S")<cr>

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Omni complete functions
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  autocmd FileType css set omnifunc=csscomplete#CompleteCSS

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => C++ comment and uncomment
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  map <leader>c :s/^/\/\//<CR><leader><CR>
  map <leader>cc :s/^/#/<CR><leader><CR>
  map <leader>u :s/^\/\///<CR><leader><CR>
  map <leader>uu :s/\s\s\/\///<CR><leader><CR>

  map <D-]> :s/^/  /<CR><Leader><CR>
  map <D-[> :s/\s\s//<CR><Leader><CR>

  map <leader>= :%!astyle<CR>
  au FileType c,cpp setlocal comments-=:// comments+=f:// "remove auto comment in line
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " =>  Whitespace fixes
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  highlight ExtraWhitespace ctermbg=red guibg=red
  match ExtraWhitespace /\s\+$/

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Misc
  " """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  set nu
  set formatprg=astyle

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Helper functions
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

  func! DeleteTillSlash()
    let g:cmd = getcmdline()

    if has("win16") || has("win32")
      let g:cmd_edited = substitute(g:cmd, "\\(.*\[\\\\]\\).*", "\\1", "")
    else
      let g:cmd_edited = substitute(g:cmd, "\\(.*\[/\]\\).*", "\\1", "")
    endif

    if g:cmd == g:cmd_edited
      if has("win16") || has("win32")
        let g:cmd_edited = substitute(g:cmd, "\\(.*\[\\\\\]\\).*\[\\\\\]", "\\1", "")
      else
        let g:cmd_edited = substitute(g:cmd, "\\(.*\[/\]\\).*/", "\\1", "")
      endif
    endif

    return g:cmd_edited
  endfunc

  " get current file dir
  func! CurrentFileDir(cmd)
    return a:cmd . " " . expand("%:p:h") . "/"
  endfunc

end
