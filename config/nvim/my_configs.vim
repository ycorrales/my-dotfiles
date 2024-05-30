if $USER == 'ycorrales' || $USER == 'ycmorales' || $USER == 'l329869'

  " Section General
  " {{{

  " top
  set nocompatible  " not compatible with vi
  set autoread      " detect when a file is changed
  set history=1000  " change history to 1000
  set number                  " show line numbers
  " set relativenumber          " show relative line numbers
  set formatoptions=c
  set textwidth=120
  set wrap                    " turn on line wrapping
  set wrapmargin=8            " wrap lines when coming within n characters from side
  set linebreak               " set soft wrapping
  set autoindent              " automatically set indent of new line
  set smartindent

  set backupdir=~/.vim-tmp,~/.tmp,~/tmp,/var/tmp,/tmp
  set directory=~/.vim-tmp,~/.tmp,~/tmp,/var/tmp,/tmp

  " Ignore compiled files
  set path+=**
  set wildmenu
  set wildignore+=comma,separated,list,of,file,patterns
  set wildignore=*.o,*~,*.pyc
  if has("win16") || has("win32")
    set wildignore+=.git\*,.hg\*,.svn\*
  else
    set wildignore+=*/.git/*,*/.hg/*,*/.svn/*,*/.DS_Store
  endif

  let $LANG='en_US'

  " Some basic configuration
  syntax on                     " Enable syntax highlighting
  set t_Co=256                  " Explicitly tell vim that the terminal supports 256 colors"

  " Error bells
  set noerrorbells
  set visualbell
  set t_vb=
  set tm=800                    " set timeoutlen to 800 milliseconds

  " toggle invisible characters
  set list
  set listchars=tab:→\ ,eol:¬,trail:⋅,extends:❯,precedes:❮
  set showbreak=↪              " show ellipsis at breaking

  " make backspace behave in a sane manner
  set backspace=indent,eol,start

  " Tab control
  set expandtab               " insert spaces rather than a tab for <Tab>
  set smarttab                " tab respects 'tabstop', 'shiftwidth', and 'softtabstop'
  set tabstop=2               " the visible width of tabs
  set softtabstop=2           " edit as if the tabs are 4 characters wide
  set shiftwidth=2            " number of spaces to use for indent and unindent
  set shiftround              " round indent to a multiple of 'shiftwidth'
  set completeopt+=longest

  " code folding settings
  set foldmethod=syntax       " fold based on indent
  set foldlevelstart=99
  set foldnestmax=10          " deepest fold is 10 levels
  set foldenable              " don't fold by default
  set foldlevel=1
  set foldcolumn=1            " Add a bit extra margin to the left
  set modeline
  set modelines=2

  set clipboard=unnamed

  set ttyfast                 " faster redrawing

  if &diff
    set diffopt-=internal
    set diffopt+=vertical
  endif

  set laststatus=2            " show the status line all the time
  set so=7                    " set 7 lines to the cursors - when moving vertical
  set wildmenu                " enhanced command line completion
  set hidden                  " current buffer can be put into background
  set showcmd                 " show incomplete commands
  set noshowmode              " don't show which mode disabled for PowerLine
  set wildmode=list,longest,list  " complete files like a shell
  set scrolloff=3             " lines of text around cursor
  set shell=$SHELL
  set cmdheight=1             " command bar height
  set title                   " set terminal title

  " Searching
  set ignorecase              " case insensitive searching
  set smartcase               " case-sensitive if expresson contains a capital letter
  set hlsearch                " highlight search results
  set incsearch               " set incremental search, like modern browsers
  set nolazyredraw            " don't redraw while executing macros
  set magic                   " Set magic on, for regex

  set showmatch               " show matching braces
  set mat=2                   " how many tenths of a second to blink


  if has('mouse')
    set mouse=a
    " set ttymouse=xterm2
  endif

  " Height of the command bar
  set cmdheight=2
  " }}}

  " Section User Interface
  " {{{

  " Return to last edit position when opening files (You want this!)
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif

  " Set font according to system
  if has("mac") || has("macunix")
    set gfn=Hack:h12,Source\ Code\ Pro:h12,Meslo\ LG\ M\ DZ:h13
  elseif has("win16") || has("win32")
    set gfn=Hack:h14,Source\ Code\ Pro:h12,itstream\ Vera\ Sans\ Mono:h11
  elseif has("gui_gtk2")
    set gfn=Monospace\ 13
  elseif has("linux")
    set gfn=Monospace\ 13
  elseif has("unix")
    set gfn=Monospace\ 13
  endif

  " Disable scrollbars (real hackers don't use scrollbars for navigation!)
  set guioptions-=r
  set guioptions-=R
  set guioptions-=l
  set guioptions-=L

  " switch cursor to line when in insert mode, and block when not
  set guicursor=n-v-c:block,i-ci-ve:ver25,r-cr:hor20,o:hor50
        \,a:blinkwait700-blinkoff400-blinkon250-Cursor/lCursor
        \,sm:block-blinkwait175-blinkoff150-blinkon175

  " disable background color erase
  if &term =~ '256color'
    set t_ut=
  endif

  " Use Unix as the standard file type
  set ffs=unix,dos,mac

  "Credit joshdick
  "Use 24-bit (true-color) mode in Vim/Neovim when outside tmux.
  "If you're using tmux version 2.2 or later, you can remove the outermost $TMUX check and use tmux's 24-bit color support
  "(see < http://sunaku.github.io/tmux-24bit-color.html#usage > for more information.)
  if (empty($TMUX))
    if (has("nvim"))
      "For Neovim 0.1.3 and 0.1.4 < https://github.com/neovim/neovim/pull/2198 >
      let $NVIM_TUI_ENABLE_TRUE_COLOR=1
    endif
    "For Neovim > 0.1.5 and Vim > patch 7.4.1799 < https://github.com/vim/vim/commit/61be73bb0f965a895bfb064ea3e55476ac175162 >
    "Based on Vim patch 7.4.1770 (`guicolors` option) < https://github.com/vim/vim/commit/8a633e3427b47286869aa4b96f2bfc1fe65b25cd >
    " < https://github.com/neovim/neovim/wiki/Following-HEAD#20160511 >
    if (has("termguicolors"))
      set termguicolors
    endif
  else
    set term=screen-256color
  endif

  " Colorscheme
  if has("gui_running")
    colorscheme one
    set background=dark
    let g:one_allow_italics = 1 " I love italic for comments
    """"""""""""""""""""""""""""""""""""""""""
    " => colorscheme one
    " one#highlight(group, fg, bg, attribute)
    """"""""""""""""""""""""""""""""""""""""""
    call one#highlight('vimLineComment', '808080', '', '')
  else
    colorscheme one
    set background=dark
  endif

  " }}}

  " Secttion Mappings
  " {{{

  " set a map leader for more key combos
  let mapleader   = "\\"
  let g:mapleader = "\\"

  """"""""""""""""""""""""""""""
  " => Visual mode related
  """"""""""""""""""""""""""""""
  " Visual mode pressing * or # searches for the current selection
  " Super useful! From an idea by Michael Naumann
  vnoremap <silent> * :<C-u>call VisualSelection('', '')<cr>/<C-r>=@/<cr><cr>
  vnoremap <silent> # :<C-u>call VisualSelection('', '')<cr>?<C-r>=@/<cr><cr>

  " Copy to X11 primary clipboard with mouse
  vnoremap <LeftRelease> "*ygv

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => autocomplete
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  "inoremap <D-[> <C-P>
  "inoremap <D-]> <C-N>

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Parenthesis/bracket
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  vnoremap <leader>(  <esc>`>a)<esc>`<i(<esc>
  vnoremap <leader>[  <esc>`>a]<esc>`<i[<esc>
  vnoremap <leader>{  <esc>`>a}<esc>`<i{<esc>
  vnoremap <leader>'  <esc>`>a'<esc>`<i'<esc>
  vnoremap <leader>"  <esc>`>a"<esc>`<i"<esc>

  "remap esc
  "inoremap jk <esc>

  " shortcut to save
  inoremap :w <esc>:w!<cr>

  " :W sudo saves the file
  " (useful for handling the permission-denied error)
  command W w !sudo tee % > /dev/null

  " Disable highlight when <leader><cr> is pressed
  map <silent> <leader><cr>    :nohlsearch<bar>:echo<cr>
  map <silent> <leader><space> :set hlsearch! hlsearch?<cr>

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Fast editing and reloading of vimrc configs
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  map <leader>cf :e! ~/.config/nvim/my_configs.vim<cr>
  map <leader>pf :e! ~/.config/nvim/plugins.vim<cr>

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Command mode related
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " Smart mappings on the command line
  cno $h e ~/
  cno $d e ~/Desktop/
  cno $c <C-\>eCurrentFileDir("e")<cr>
  cno $t <C-\>eCurrentFileDir("tabe")<cr>

  cnoreabbrev <expr> te getcmdtype() == ":" && getcmdline() == 'te' ? 'tabe' : 'te'

  " $q is super useful when browsing on the command line
  " it deletes everything until the last slash
  cno $q <C-\>eDeleteTillSlash()<cr>

  " Map <Space> to / (search) and Ctrl-<Space> to ? (backwards search)
  map <space> /
  map <C-space> ?

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Moving around, tabs, windows and buffers
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

  "move in insert mode
  inoremap <C-a> <esc>^<esc>i
  inoremap <C-e> <esc>g_<esc>a

  nmap <leader>bn :bnext<cr>
  nmap <leader>bp :bprevious<cr>
  " Close all the buffers
  nmap <leader>ba :bufdo bd<cr>
  " Delete current bufer
  nmap <leader>bd :bdelete<cr>

  " Useful mappings for managing tabs
  nmap <leader>tn :tabnew<cr>
  nmap <leader>to :tabonly<cr>
  nmap <leader>tc :tabclose<cr>
  nmap <leader>tm :tabmove
  nmap <leader>t<leader> :tabnext

  " Let 'l' toggle between this and the last accessed tab
  let g:lasttab = 1
  nmap <leader>l :exe "tabn ".g:lasttab<cr>
  au TabLeave * let g:lasttab = tabpagenr()

  " Opens a new tab with the current buffer's path
  " Super useful when editing files in the same directory
  nmap <leader>te :tabedit <C-r>=expand("%:p:h")<cr>/

  " Switch CWD to the directory of the open buffer
  nmap <leader>cd :cd %:p:h<cr>:pwd<cr>

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Editing mappings
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  nmap <leader>o o<esc>
  nmap <leader>O O<esc>

  " Move 1 more lines up or down in normal and visual selection modes.
  nnoremap K :m .-2<CR>==
  nnoremap J :m .+1<CR>==
  vnoremap K :m '<-2<CR>gv=gv
  vnoremap J :m '>+1<CR>gv=gv

  if has("mac") || has("macunix")
    nmap <leader>j <M-j>
    nmap <leader>k <M-k>
    vmap <leader>j <M-j>
    vmap <leader>k <M-k>
  endif

  " Map auto complete of (, [, {, <,", ',
  inoremap <leader>) ()<esc>i
  inoremap <leader>] []<esc>i
  inoremap <leader>} {}<esc>i
  inoremap <leader>> <><esc>i
  inoremap <leader>' ''<esc>i
  inoremap <leader>" ""<esc>i
  inoremap <leader>$ $$<esc>i

  " C++
  inoremap #I #include <esc>a
  inoremap #_ //_____________________________________________________________________________

  "
  nmap ;; :%s:::g<Left><Left><Left>
  nmap ;' :%s:::gc<Left><Left><Left><Left>
  vmap ;; :s:::g<Left><Left><Left>

  cno <C-l> <Right>
  cno <C-h> <Left>

  " Remove the Windows ^M - when the encodings gets messed up
  noremap <leader>m mmHmt:%s/<C-v><cr>//ge<cr>'tzt'm

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Spell checking
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " Pressing \ss will toggle and untoggle spell checking
  map <leader>ss :setlocal spell!<cr>

  " Shortcuts using <leader>
  map <leader>sn ]s
  map <leader>sp [s
  map <leader>sa zg
  map <leader>s? z=


  " }}}

  " Section Plugins
  " {{{

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Nerd Tree and Nerd Tree Tab
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " close NERDTree after a file is opened
  let g:NERDTreeQuitOnOpen=0
  " show hidden files in NERDTree
  let NERDTreeShowHidden=1
  " Toggle NERDTree
  nmap <silent> <leader>k :NERDTreeToggle<cr>
  " expand to the path of the file in the current buffer
  nmap <silent> <leader>y :NERDTreeTabFind<cr>
  "let g:NERDTreeWinPos = "left"
  "let NERDTreeIgnore = ['\.pyc$', '__pycache__']
  "let g:NERDTreeWinSize=30
  "map <leader>nm :NERDTreeMirrorToggle<cr>
  "map <leader>nb :NERDTreeFromBookmark
  "            \setlength{\itemsep}{5 cm}

  """""""""""""""""""""""""""""""
  " => MRU plugin
  """""""""""""""""""""""""""""""
  "let MRU_Max_Entries = 400
  "map <leader>f :MRU<CR>

  """""""""""""""""""""""""""""""
  " => CTRL-P
  """""""""""""""""""""""""""""""
  nmap <silent> <leader>r :CtrlPMRU<cr>
  nmap <silent> <leader>b :CtrlPBuffer<cr>
  nmap <silent> <leader>f :CtrlP<cr>
  let g:ctrlp_map = '<leader>t'
  let g:ctrlp_dotfiles=1
  let g:ctrlp_working_path_mode = 'ra'
  " CtrlP ignore patterns
  let g:ctrlp_custom_ignore = {
            \ 'dir': '\.git$\|node_modules$\|\.hg$\|\.svn$',
            \ 'file': '\.exe$\|\.so$'
            \ }

  " search the nearest ancestor that contains .git, .hg, .svn
  let g:ctrlp_working_path_mode = 2
  ""let g:ctrlp_max_height = 20
  ""let g:ctrlp_custom_ignore = 'node_modules\|^\.DS_Store\|^\.git\|^\.coffee'


  """"""""""""""""""""""""""""""
  " => SearchHi
  """"""""""""""""""""""""""""""
  highlight link Searchlight Incsearch
  "let g:searchant_map_stop = 0
  "nmap <leader><cr> <Plug>SearchantStop

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => ClangFormat
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  let g:clang_format#code_style = "llvm"
  let g:clang_format#style_options = {
        \ "AccessModifierOffset": -1,
        \ "AlignEscapedNewlinesLeft": "true",
        \ "AlignTrailingComments": "true",
        \ "AllowAllParametersOfDeclarationOnNextLine": "false",
        \ "AllowShortFunctionsOnASingleLine": "true",
        \ "AllowShortIfStatementsOnASingleLine": "false",
        \ "AllowShortLoopsOnASingleLine": "false",
        \ "AlwaysBreakTemplateDeclarations": "true",
        \ "BinPackParameters": "true",
        \ "BreakBeforeBinaryOperators": "false",
        \ "BreakBeforeBraces": "Linux",
        \ "BreakBeforeTernaryOperators": "true",
        \ "BreakConstructorInitializersBeforeComma": "false",
        \ "ColumnLimit": 120,
        \ "ConstructorInitializerAllOnOneLineOrOnePerLine": "true",
        \ "ConstructorInitializerIndentWidth": 2,
        \ "ContinuationIndentWidth": 2,
        \ "Cpp11BracedListStyle": "false",
        \ "DerivePointerBinding": "false",
        \ "ExperimentalAutoDetectBinPacking": "false",
        \ "IndentCaseLabels": "true",
        \ "IndentFunctionDeclarationAfterType": "true",
        \ "IndentWidth":     2,
        \ "Language":        'Cpp',
        \ "MaxEmptyLinesToKeep": 1,
        \ "KeepEmptyLinesAtTheStartOfBlocks": "true",
        \ "NamespaceIndentation": "None",
        \ "ObjCSpaceAfterProperty": "false",
        \ "ObjCSpaceBeforeProtocolList": "false",
        \ "PenaltyBreakBeforeFirstCallParameter": 1,
        \ "PenaltyBreakComment": 300,
        \ "PenaltyBreakFirstLessLess": 120,
        \ "PenaltyBreakString": 1000,
        \ "PenaltyExcessCharacter": 1000000,
        \ "PenaltyReturnTypeOnItsOwnLine": 200,
        \ "SortIncludes": "false",
        \ "SpaceBeforeAssignmentOperators": "true",
        \ "SpaceBeforeParens": "ControlStatements",
        \ "SpaceInEmptyParentheses": "false",
        \ "SpacesBeforeTrailingComments": 1,
        \ "SpacesInAngles":  "false",
        \ "SpacesInContainerLiterals": "true",
        \ "SpacesInCStyleCastParentheses": "false",
        \ "SpacesInParentheses": "false",
        \ "Standard":        "Cpp11",
        \ "TabWidth":        2,
        \ "UseTab":          "Never"}

  noremap = :silent <C-u>ClangFormat<cr>

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Syntastic (syntax checker)
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  let g:syntastic_mode_map = { 'mode': 'passive', 'active_filetypes':   [],'passive_filetypes': [] }
  noremap <C-w>e :SyntasticCheck<CR>
  noremap <C-w>f :SyntasticToggleMode<CR>

  set statusline+=%#warningmsg#
  set statusline+=%{SyntasticStatuslineFlag()}
  set statusline+=%*

  let g:syntastic_always_populate_loc_list=1
  let g:syntastic_auto_loc_list=1
  let g:syntastic_check_on_open=1
  let g:syntastic_check_on_wq=0

  " Python
  let g:syntastic_python_checkers=['pyflakes']

  " Javascript
  let g:syntastic_javascript_checkers = ['jshint']

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => lightline
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  let g:lightline = {
        \ 'colorscheme': 'one',
        \ 'active': {
        \   'left': [ ['mode', 'paste'],
        \             ['fugitive', 'readonly', 'filename', 'modified'] ],
        \   'right': [ [ 'lineinfo' ], ['percent'] ]
        \ },
        \ 'component': {
        \   'readonly': '%{&filetype=="help"?"":&readonly?"🔒":""}',
        \   'modified': '%{&filetype=="help"?"":&modified?"+":&modifiable?"":"-"}',
        \   'fugitive': '%{exists("*fugitive#head")?fugitive#head():""}'
        \ },
        \ 'component_visible_condition': {
        \   'readonly': '(&filetype!="help"&& &readonly)',
        \   'modified': '(&filetype!="help"&&(&modified||!&modifiable))',
        \   'fugitive': '(exists("*fugitive#head") && ""!=fugitive#head())'
        \ },
        \ 'separator': { 'left': ' ', 'right': ' ' },
        \ 'subseparator': { 'left': ' ', 'right': ' ' }
        \ }

  """""""""""""""""""
  " vim-markdown
  """""""""""""""""""
  let vim_markdown_preview_github=1
  let vim_markdown_preview_hotkey='<leader>md'
  " }}}

  " Section Extra
  " {{{

  " Smart way to move between windows
  nmap <C-j> :call WinMove('j')<cr>
  nmap <C-k> :call WinMove('k')<cr>
  nmap <C-h> :call WinMove('h')<cr>
  nmap <C-l> :call WinMove('l')<cr>

  " Window movement shortcuts
  " move to the window in the direction shown, or create a new window
  function! WinMove(key)
      let t:curwin = winnr()
      exec "wincmd ".a:key
      if (t:curwin == winnr())
          if (match(a:key,'[jk]'))
              wincmd v
          else
              wincmd s
          endif
          exec "wincmd ".a:key
      endif
  endfunction

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Misc
  """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  "set formatprg=astyle
  "au FileType c,cpp setlocal comments-=:// comments+=f:// "remove auto comment in line

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " =>  Whitespace fixes
  """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  hi ExtraWhitespace ctermfg=0 ctermbg=12 guifg=#000000 guibg=#ff0000
  autocmd VimEnter,BufEnter,WinEnter * call ExtraWhitespaceColor()
  fun! ExtraWhitespaceColor()
    " Nicer line number
    let &nuw=len(line('$'))+2
    " Highlight trailing whitespace (\s\+$) or
    " space before tabs (\s\+\ze\t)
    " \s finds whitespace (or tabs).
    " \+ finds one or more occurrences.
    " \ze end found
    call matchadd('ExtraWhitespace', '\s\+$\| \+\ze\t')
  endfun

  """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " move tabs to the end for new, single buffers (exclude splits)
  """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  autocmd BufNew * if winnr('$') == 1 | tablast | endif

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Turn persistent undo on
  "    means that you can undo even when you close a buffer/VIM
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  "try
  "  set undodir=~/.vim_runtime/temp_dirs/undodir
  "  set undofile
  "catch
  "endtry

  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " => Helper functions
  """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
  " Delete trailing white space on save, useful for some filetypes ;)
  fun! CleanExtraSpaces()
      let save_cursor = getpos(".")
      let old_query = getreg('/')
      silent! %s/\s\+$//e " e flag means no error is displayed
      call setpos('.', save_cursor)
      call setreg('/', old_query)
  endfun

  fun! DeleteTillSlash()
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
  endfun

  " get current file dir
  fun! CurrentFileDir(cmd)
    return a:cmd . " " . expand("%:p:h") . "/"
  endfun

  " Returns true if paste mode is enabled
  fun! HasPaste()
      if &paste
          return 'PASTE MODE  '
      endif
      return ''
  endfun

  " Don't close window, when deleting a buffer
  command! Bclose call <SID>BufcloseCloseIt()
  fun! <SID>BufcloseCloseIt()
     let l:currentBufNum = bufnr("%")
     let l:alternateBufNum = bufnr("#")

     if buflisted(l:alternateBufNum)
       buffer #
     else
       bnext
     endif

     if bufnr("%") == l:currentBufNum
       new
     endif

     if buflisted(l:currentBufNum)
       execute("bdelete! ".l:currentBufNum)
     endif
  endfun

  fun! CmdLine(str)
      exe "menu Foo.Bar :" . a:str
      emenu Foo.Bar
      unmenu Foo
  endfun

  fun! VisualSelection(direction, extra_filter) range
      let l:saved_reg = @"
      execute "normal! vgvy"

      let l:pattern = escape(@", "\\/.*'$^~[]")
      let l:pattern = substitute(l:pattern, "\n$", "", "")

      if a:direction == 'gv'
          call CmdLine("Ack '" . l:pattern . "' " )
      elseif a:direction == 'replace'
          call CmdLine("%s" . '/'. l:pattern . '/')
      endif

      let @/ = l:pattern
      let @" = l:saved_reg
  endfun

  " Change defaults hi colors
  fun! HiSet()
     " make the highlighting of tabs and other non-text less annoying
     hi SpecialKey ctermfg=238
     hi NonText ctermfg=238
     hi IncSearch cterm=NONE ctermbg=red ctermfg=0 gui=NONE guibg=#ff0000 guifg=#000000
     " Highligth current line number
     hi clear CursorLine
     hi CursorLineNR ctermfg=darkgreen cterm=bold guifg=darkgreen gui=bold
     " Change color for Comment
     hi Comment guifg=lightgreen
  endfun

  " Highlight current cursor line number only
  set cursorline
  call HiSet()
  augroup HiSet
    au!
    autocmd ColorScheme * call HiSet()
  augroup END

  " highlight git conflicts
  match ErrorMsg '^\(<\|=\|>\)\{7\}\([^=].\+\)\?$'
  " }}}

  " Section Filetypes
  " {{{

  if has("autocmd")
   au BufWritePre * :call CleanExtraSpaces()
  endif

  "Set formatoptions
  augroup ft
    autocmd! FileType * set formatoptions-=ro
  augroup END

  """"""""""""""""""""""""""""""
  " => C++ section
  """"""""""""""""""""""""""""""
  "au FileType cpp set colorcolumn=80,100

  au FileType cpp map <leader>c :s/^/\/\//<cr><leader><space><leader><cr>
  au FileType cpp map <leader>u :s/^\/\///<cr><leader><space><leader><cr>

  map <leader>]] :s/^/  /<cr><leader><cr>gv
  map <leader>[[ :s/\s\s//<cr><leader><cr>gv

  "map <leader>= :%!astyle<CR>    ====> No used, ClangFormat instead


  """"""""""""""""""""""""""""""
  " => Python section
  """"""""""""""""""""""""""""""
  let python_highlight_all = 1
  au FileType python syn keyword pythonDecorator True None False self

  au BufNewFile,BufRead *.jinja set syntax=htmljinja
  au BufNewFile,BufRead *.mako set ft=mako

  au FileType python map <buffer> F :set foldmethod=indent<cr>

  au FileType python inoremap <buffer> $r return
  au FileType python inoremap <buffer> $i import
  au FileType python inoremap <buffer> $p print
  au FileType python inoremap <buffer> $f #--- <esc>a
  au FileType python map <buffer> <leader>1 /class
  au FileType python map <buffer> <leader>2 /def
  au FileType python map <buffer> <leader>C ?class
  au FileType python map <buffer> <leader>D ?def
  au FileType python set cindent
  au FileType python set cinkeys-=0#
  au FileType python set indentkeys-=0#

  au FileType python map <leader>c :s/^/#/<cr><leader><space><leader><cr>
  au FileType python map <leader>u :s/^#//<cr><leader><space><leader><cr>



  """"""""""""""""""""""""""""""
  " => JavaScript section
  """"""""""""""""""""""""""""""
  au FileType javascript call JavaScriptFold()
  au FileType javascript setl fen
  au FileType javascript setl nocindent

  au FileType javascript imap <c-t> $log();<esc>hi
  au FileType javascript imap <c-a> alert();<esc>hi

  au FileType javascript inoremap <buffer> $r return
  au FileType javascript inoremap <buffer> $f //--- PH<esc>FP2xi

  function! JavaScriptFold()
      setl foldmethod=syntax
      setl foldlevelstart=1
      syn region foldBraces start=/{/ end=/}/ transparent fold keepend extend

      function! FoldText()
          return substitute(getline(v:foldstart), '{.*', '{...}', '')
      endfunction
      setl foldtext=FoldText()
  endfunction

  " }}}

endif

" vim: fdm=marker fdl=0
