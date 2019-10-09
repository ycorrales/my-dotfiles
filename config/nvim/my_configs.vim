if $USER == 'ycorrales' || $USER == 'ycmorales'
" Section General {{{
set nocompatible            " not compatible with vi
set autoread                " detect when a file is changed

set history=1000            " change history to 1000
set textwidth=120

"set backupdir=~/.vim-tmp,~/.tmp,~/tmp,/var/tmp,/tmp
"set directory=~/.vim-tmp,~/.tmp,~/tmp,/var/tmp,/tmp

" Ignore compiled files
set wildignore=*.o,*~,*.pyc
if has("win16") || has("win32")
    set wildignore+=.git\*,.hg\*,.svn\*
else
    set wildignore+=*/.git/*,*/.hg/*,*/.svn/*,*/.DS_Store
endif

let $LANG='en_US'

" Format the status line
"*** Deprecated
" "set statusline=\ %{HasPaste()}%F%m%r%h\ %w\ \ CWD:\ %r%{getcwd()}%h\ \ \ Line:\ %l\ \ Column:\ %c
"*** using airline for a fancy statusline
"
" Return to last edit position when opening files (You want this!)
au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
" }}}
" Section User Interface {{{

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => GUI related
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Set font according to system
if has("mac") || has("macunix")
  "set gfn=Hack:h12,Source\ Code\ Pro:h12,Meslo\ LG\ M\ DZ:h13
elseif has("win16") || has("win32")
  set gfn=Hack:h14,Source\ Code\ Pro:h12,itstream\ Vera\ Sans\ Mono:h11
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

" Use Unix as the standard file type
set ffs=unix,dos,mac

" Colorscheme
if has("gui_running")
  colorscheme neodark
else
  colorscheme neodark
endif
set background=dark

" Some basic configuration
set timeoutlen=250000

syntax on     " Enable syntax highlighting
set t_Co=256  " Explicitly tell vim that the terminal supports 256 colors"

" switch cursor to line when in insert mode, and block when not
set guicursor=n-v-c:block,i-ci-ve:ver25,r-cr:hor20,o:hor50
      \,a:blinkwait700-blinkoff400-blinkon250-Cursor/lCursor
      \,sm:block-blinkwait175-blinkoff150-blinkon175

if &term =~ '256color'
  " disable background color erase
  set t_ut=
endif

" make the highlighting of tabs and other non-text less annoying
highlight SpecialKey ctermfg=238
highlight NonText ctermfg=238
highlight IncSearch cterm=NONE ctermbg=red ctermfg=0 gui=NONE guibg=#ff0000 guifg=#000000

set number                  " show line numbers
" set relativenumber          " show relative line numbers

set wrap                    " turn on line wrapping
set wrapmargin=8            " wrap lines when coming within n characters from side
set linebreak               " set soft wrapping
set autoindent              " automatically set indent of new line
set smartindent

" toggle invisible characters
set list
set listchars=tab:→\ ,eol:¬,trail:⋅,extends:❯,precedes:❮
set showbreak=↪              " show ellipsis at breaking

" highlight conflicts
match ErrorMsg '^\(<\|=\|>\)\{7\}\([^=].\+\)\?$'

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

set clipboard=unnamed

set ttyfast                 " faster redrawing
set diffopt+=vertical
set laststatus=2            " show the satus line all the time
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

" error bells
set noerrorbells
set visualbell
set t_vb=
set tm=500

if has('mouse')
  set mouse=a
  " set ttymouse=xterm2
endif

" Height of the command bar
set cmdheight=2

" }}}
" Secttion Mappings {{{

" set a map leader for more key combos
let mapleader   = '\'
let g:mapleader = '\'

""""""""""""""""""""""""""""""
" => Visual mode related
""""""""""""""""""""""""""""""
" Visual mode pressing * or # searches for the current selection
" Super useful! From an idea by Michael Naumann
vnoremap <silent> * :<C-u>call VisualSelection('', '')<CR>/<C-R>=@/<CR><CR>
vnoremap <silent> # :<C-u>call VisualSelection('', '')<CR>?<C-R>=@/<CR><CR>

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
nmap <leader>w :w!<cr>

" :W sudo saves the file
" (useful for handling the permission-denied error)
command W w !sudo tee % > /dev/null

" set paste toggle
"*** deprecated
"set pastetoggle=<leader>v
" toggle paste mode
"map <leader>v :set paste!<cr>
"*** using plugin fix-vim-paste

" Disable highlight when <leader><cr> is pressed
map <silent> <leader><cr>    :nohlsearch<Bar>:echo<cr>
map <silent> <leader><Space> :set hlsearch! hlsearch?<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Fast editing and reloading of vimrc configs
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
map <leader>fc :tabe! ~/.config/nvim/my_configs.vim<cr>
map <leader>fp :tabe! ~/.config/nvim/plugins.vim<cr>

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

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Moving around, tabs, windows and buffers
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Bash like keys for the command line
cnoremap <C-A> <Home>
cnoremap <C-E> <End>
cnoremap <C-K> <C-U>

cnoremap <C-P> <Up>
cnoremap <C-N> <Down>

"move in insert mode
inoremap <C-A> <esc>^<esc>i
inoremap <C-E> <esc>g_<esc>a
"move in normal mode
noremap <C-A> ^
noremap <C-E> g_

" Smart way to move between windows
map <C-j> <C-W>j
map <C-k> <C-W>k
map <C-h> <C-W>h
map <C-l> <C-W>l

map <leader>bn :bnext<cr>
map <leader>bp :bprevious<cr>
" Close all the buffers
map <leader>ba :bufdo bd<cr>
" Delete current bufer
map <leader>bd :bdelete<cr>

" Useful mappings for managing tabs
map <leader>tn :tabnew<cr>
map <leader>to :tabonly<cr>
map <leader>tc :tabclose<cr>
map <leader>tm :tabmove
map <leader>t<leader> :tabnext

" Let 'l' toggle between this and the last accessed tab
let g:lasttab = 1
nmap <Leader>l :exe "tabn ".g:lasttab<CR>
au TabLeave * let g:lasttab = tabpagenr()

" Opens a new tab with the current buffer's path
" Super useful when editing files in the same directory
map <leader>te :tabedit <c-r>=expand("%:p:h")<cr>/

" Switch CWD to the directory of the open buffer
map <leader>cd :cd %:p:h<cr>:pwd<cr>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Editing mappings
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
nmap <leader>o o<esc>
nmap <leader>O O<esc>

" Move a line of text using ALT+[jk] or Command+[jk] on mac
nmap <M-j> mz:m+<cr>`z
nmap <M-k> mz:m-2<cr>`z
vmap <M-j> :m'>+<cr>`<my`>mzgv`yo`z
vmap <M-k> :m'<-2<cr>`>my`<mzgv`yo`z

if has("mac") || has("macunix")
  nmap <leader>j <M-j>
  nmap <leader>k <M-k>
  vmap <leader>j <M-j>
  vmap <leader>k <M-k>
endif
"
"
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


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => C++ comment and uncomment
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
map <leader>c :s/^/\/\//<CR><leader><CR>
map <leader>cc :s/^/#/<CR><leader><CR>
map <leader>u :s/^\/\///<CR><leader><CR>
map <leader>uu :s/\s\s\/\///<CR><leader><CR>

"map <leader>] :s/^/  /<CR><Leader><CR>
"map <leader>[ :s/\s\s//<CR><Leader><CR>

"map <leader>= :%!astyle<CR>    ====> No used, ClangFormat instead

" Remove the Windows ^M - when the encodings gets messed up
noremap <Leader>m mmHmt:%s/<C-V><cr>//ge<cr>'tzt'm

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
" Section Plugins {{{
""""""""""""""""""""""""""""""
" => bufExplorer plugin
""""""""""""""""""""""""""""""
"let g:bufExplorerDefaultHelp=0
"let g:bufExplorerShowRelativePath=1
"let g:bufExplorerFindActive=1
"let g:bufExplorerSortBy='name'
"map <leader>o :BufExplorer<cr>

""""""""""""""""""""""""""""""
" => MRU plugin
""""""""""""""""""""""""""""""
"let MRU_Max_Entries = 400
"map <leader>f :MRU<CR>

""""""""""""""""""""""""""""""
" => CTRL-P
""""""""""""""""""""""""""""""
"let g:ctrlp_working_path_mode = 0
"
"let g:ctrlp_map = '<c-f>'
"map <leader>j :CtrlP<cr>
"map <leader>z :CtrlPBuffer<cr>
"
"let g:ctrlp_max_height = 20
"let g:ctrlp_custom_ignore = 'node_modules\|^\.DS_Store\|^\.git\|^\.coffee'

""""""""""""""""""""""""""""""
" => Searchant
""""""""""""""""""""""""""""""
let g:searchant_all = 1
let g:searchant_map_stop = 0
nmap <leader><cr> <Plug>SearchantStop

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

noremap = :silent <C-u>ClangFormat<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Netrw
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Load Explore
noremap <leader>e :<C-u>Lexplore<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Nerd Tree and Nerd Tree Tab
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"let g:NERDTreeWinPos = "left"
"let NERDTreeShowHidden=0
"let NERDTreeIgnore = ['\.pyc$', '__pycache__']
"let g:NERDTreeWinSize=30
"map <leader>nn :NERDTreeToggle<cr>
"map <leader>nf :NERDTreeTabFind<cr>
"map <leader>nm :NERDTreeMirrorToggle<cr>
"map <leader>nb :NERDTreeFromBookmark
"            \setlength{\itemsep}{5 cm}


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
"let g:syntastic_python_checkers=['pyflakes']

" Javascript
"let g:syntastic_javascript_checkers = ['jshint']

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Git gutter (Git diff)
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:gitgutter_enabled=0
nnoremap <leader>d :GitGutterToggle<cr>
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => lightline
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:lightline = {
      \ 'colorscheme': 'wombat',
      \ }

let g:lightline = {
      \ 'colorscheme': 'wombat',
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
" }}}
" Section Extra {{{

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Misc
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"set formatprg=astyle
"au FileType c,cpp setlocal comments-=:// comments+=f:// "remove auto comment in line


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" =>  Whitespace fixes
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
highlight ExtraWhitespace ctermfg=0 ctermbg=12 guifg=#000000 guibg=#ff0000
autocmd VimEnter,BufEnter,WinEnter * call ExtraWhitespaceColor()
fun! ExtraWhitespaceColor()
  let &nuw=len(line('$'))+2               " Nicer line numbers
  call matchadd('ExtraWhitespace', '\zs\(\S\zs\s\{1,}$\)')
endfun
match ExtraWhitespace /\s\+$/

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" move tabs to the end for new, single buffers (exclude splits)
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"autocmd BufNew * if winnr('$') == 1 | tablast | endif


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
    silent! %s/\s\+$//e
    call setpos('.', save_cursor)
   call setreg('/', old_query)
endfun

if has("autocmd")
    autocmd BufWritePre *.txt,*.js,*.py,*.wiki,*.sh,*.coffee,*.C,*.h,*.c,*.cpp :call CleanExtraSpaces()
endif

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

" Returns true if paste mode is enabled
function! HasPaste()
    if &paste
        return 'PASTE MODE  '
    endif
    return ''
endfunction

" Don't close window, when deleting a buffer
command! Bclose call <SID>BufcloseCloseIt()
function! <SID>BufcloseCloseIt()
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
endfunction

function! CmdLine(str)
    exe "menu Foo.Bar :" . a:str
    emenu Foo.Bar
    unmenu Foo
endfunction

function! VisualSelection(direction, extra_filter) range
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
endfunction
" }}}
" Section Filetypes {{{
""""""""""""""""""""""""""""""
" => C++ section
""""""""""""""""""""""""""""""
au FileType cpp set colorcolumn=80,100


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


""""""""""""""""""""""""""""""
" => CoffeeScript section
"""""""""""""""""""""""""""""""
"function! CoffeeScriptFold()
"    setl foldmethod=indent
"    setl foldlevelstart=1
"endfunction
"au FileType coffee call CoffeeScriptFold()

"au FileType gitcommit call setpos('.', [0, 1, 1, 0])


""""""""""""""""""""""""""""""
" => Shell section
""""""""""""""""""""""""""""""
if exists('$TMUX')
    set term=screen-256color
endif
" }}}
end

" vim:foldmethod=marker:foldlevel=0
