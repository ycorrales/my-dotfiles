source ~/.config/nvim/plugins.vim
"
"" Section General {{{
"
"" Abbreviations
"abbr funciton function
"abbr teh the
"abbr tempalte template
"abbr fitler filter
"abbr cosnt const
"abbr attribtue attribute
"abbr attribuet attribute
"
"let g:python_host_prog = '/usr/local/bin/python2'
"let g:python3_host_prog = '/usr/local/bin/python3'
"
"if (has('nvim'))
"	" show results of substition as they're happening
"	" but don't open a split
"	set inccommand=nosplit
"endif
"
"" }}}
"
"" Section Mappings {{{
"
"" wipout buffer
"nmap <silent> <leader>b :bw<cr>
"
"" shortcut to save
"nmap <leader>, :w<cr>
"
"" set paste toggle
"set pastetoggle=<leader>v
"
"" toggle paste mode
"" map <leader>v :set paste!<cr>
"
"" edit ~/.config/nvim/init.vim
"map <leader>ev :e! ~/.config/nvim/init.vim<cr>
"" edit gitconfig
"map <leader>eg :e! ~/.gitconfig<cr>
"
"" clear highlighted search
"noremap <space> :set hlsearch! hlsearch?<cr>
"
"" activate spell-checking alternatives
"nmap ;s :set invspell spelllang=en<cr>
"
"" markdown to html
"nmap <leader>md :%!markdown --html4tags <cr>
"
"" remove extra whitespace
"nmap <leader><space> :%s/\s\+$<cr>
"nmap <leader><space><space> :%s/\n\{2,}/\r\r/g<cr>
"
"
"nmap <leader>l :set list!<cr>
"
"" Textmate style indentation
"vmap <leader>[ <gv
"vmap <leader>] >gv
"nmap <leader>[ <<
"nmap <leader>] >>
"
"" switch between current and last buffer
"nmap <leader>. <c-^>
"
"" enable . command in visual mode
"vnoremap . :normal .<cr>
"
"map <silent> <C-h> :call functions#WinMove('h')<cr>
"map <silent> <C-j> :call functions#WinMove('j')<cr>
"map <silent> <C-k> :call functions#WinMove('k')<cr>
"map <silent> <C-l> :call functions#WinMove('l')<cr>
"
"map <leader>wc :wincmd q<cr>
"
"" move line mappings
"" ∆ is <A-j> on macOS
"" ˚ is <A-k> on macOS
"nnoremap ∆ :m .+1<cr>==
"nnoremap ˚ :m .-2<cr>==
"inoremap ∆ <Esc>:m .+1<cr>==gi
"inoremap ˚ <Esc>:m .-2<cr>==gi
"vnoremap ∆ :m '>+1<cr>gv=gv
"vnoremap ˚ :m '<-2<cr>gv=gv
"
"" toggle cursor line
"nnoremap <leader>i :set cursorline!<cr>
"
"" scroll the viewport faster
"nnoremap <C-e> 3<C-e>
"nnoremap <C-y> 3<C-y>
"
"" moving up and down work as you would expect
"nnoremap <silent> j gj
"nnoremap <silent> k gk
"nnoremap <silent> ^ g^
"nnoremap <silent> $ g$
"
"" search for word under the cursor
"nnoremap <leader>/ "fyiw :/<c-r>f<cr>
"
"" inoremap <tab> <c-r>=Smart_TabComplete()<CR>
"
"map <leader>r :call RunCustomCommand()<cr>
"" map <leader>s :call SetCustomCommand()<cr>
"let g:silent_custom_command = 0
"
"" helpers for dealing with other people's code
"nmap \t :set ts=4 sts=4 sw=4 noet<cr>
"nmap \s :set ts=4 sts=4 sw=4 et<cr>
"
"nnoremap <silent> <leader>u :call functions#HtmlUnEscape()<cr>
"
"command! Rm call functions#Delete()
"command! RM call functions#Delete() <Bar> q!
"
"" }}}
"
"" Section AutoGroups {{{
"" file type specific settings
"augroup configgroup
"    autocmd!
"
"    " automatically resize panes on resize
"    autocmd VimResized * exe 'normal! \<c-w>='
"    autocmd BufWritePost .vimrc,.vimrc.local,init.vim source %
"    autocmd BufWritePost .vimrc.local source %
"    " save all files on focus lost, ignoring warnings about untitled buffers
"    autocmd FocusLost * silent! wa
"
"    " make quickfix windows take all the lower section of the screen
"    " when there are multiple windows open
"    autocmd FileType qf wincmd J
"    autocmd FileType qf nmap q :q<cr>
"
"    autocmd BufNewFile,BufReadPost *.md set filetype=markdown
"    let g:markdown_fenced_languages = ['css', 'javascript', 'js=javascript', 'json=javascript', 'stylus', 'html']
"
"    " autocmd! BufEnter * call functions#ApplyLocalSettings(expand('<afile>:p:h'))
"
"    autocmd BufNewFile,BufRead,BufWrite *.md syntax match Comment /\%^---\_.\{-}---$/
"augroup END
"
"" }}}
"
"" Section Plugins {{{
"
"" FZF
""""""""""""""""""""""""""""""""""""""
"" Toggle NERDTree
"nmap <silent> <leader>k :NERDTreeToggle<cr>
"" expand to the path of the file in the current buffer
"nmap <silent> <leader>y :NERDTreeFind<cr>
"
"let NERDTreeShowHidden=1
"let NERDTreeDirArrowExpandable = '▷'
"let NERDTreeDirArrowCollapsible = '▼'
"
"let g:fzf_layout = { 'down': '~25%' }
"
"if isdirectory(".git")
"    " if in a git project, use :GFiles
"    nmap <silent> <leader>t :GFiles --cached --others --exclude-standard<cr>
"else
"    " otherwise, use :FZF
"    nmap <silent> <leader>t :FZF<cr>
"endif
"
"nmap <silent> <leader>r :Buffers<cr>
"nmap <silent> <leader>e :FZF<cr>
"nmap <leader><tab> <plug>(fzf-maps-n)
"xmap <leader><tab> <plug>(fzf-maps-x)
"omap <leader><tab> <plug>(fzf-maps-o)
"
"" Insert mode completion
"imap <c-x><c-k> <plug>(fzf-complete-word)
"imap <c-x><c-f> <plug>(fzf-complete-path)
"imap <c-x><c-j> <plug>(fzf-complete-file-ag)
"imap <c-x><c-l> <plug>(fzf-complete-line)
"
"nnoremap <silent> <Leader>C :call fzf#run({
"\   'source':
"\     map(split(globpath(&rtp, "colors/*.vim"), "\n"),
"\         "substitute(fnamemodify(v:val, ':t'), '\\..\\{-}$', '', '')"),
"\   'sink':    'colo',
"\   'options': '+m',
"\   'left':    30
"\ })<CR>
"
"command! FZFMru call fzf#run({
"\  'source':  v:oldfiles,
"\  'sink':    'e',
"\  'options': '-m -x +s',
"\  'down':    '40%'})
"
"command! -bang -nargs=* Find call fzf#vim#grep(
"	\ 'rg --column --line-number --no-heading --follow --color=always '.<q-args>, 1,
"	\ <bang>0 ? fzf#vim#with_preview('up:60%') : fzf#vim#with_preview('right:50%:hidden', '?'), <bang>0)
"
"" Emmet
""""""""""""""""""""""""""""""""""""""
"let g:user_emmet_settings = {
"\  'javascript.jsx': {
"\      'extends': 'jsx',
"\  },
"\}
"
"" Fugitive Shortcuts
""""""""""""""""""""""""""""""""""""""
"nmap <silent> <leader>gs :Gstatus<cr>
"nmap <leader>ge :Gedit<cr>
"nmap <silent><leader>gr :Gread<cr>
"nmap <silent><leader>gb :Gblame<cr>
"
"nmap <leader>m :MarkedOpen!<cr>
"nmap <leader>mq :MarkedQuit<cr>
"nmap <leader>* *<c-o>:%s///gn<cr>
"
"let g:ale_change_sign_column_color = 1
"let g:ale_sign_column_always = 1
"let g:ale_sign_error = '✖'
"let g:ale_sign_warning = '⚠'
"" highlight clear ALEErrorSign
"" highlight clear ALEWarningSign
"
"let g:ale_linters = {
"\   'javascript': ['eslint'],
"\   'typescript': ['tslint', 'tsserver'],
"\	'html': []
"\}
"
"" airline options
"let g:airline_powerline_fonts=1
"let g:airline_left_sep=''
"let g:airline_right_sep=''
"let g:airline_theme='base16'
"let g:airline#extensions#tabline#enabled = 1 " enable airline tabline
"let g:airline#extensions#tabline#tab_min_count = 2 " only show tabline if tabs are being used (more than 1 tab open)
"let g:airline#extensions#tabline#show_buffers = 0 " do not show open buffers in tabline
"let g:airline#extensions#tabline#show_splits = 0
"
"" don't hide quotes in json files
"let g:vim_json_syntax_conceal = 0
"
"let g:SuperTabCrMapping = 0
"" }}}
"
" vim:foldmethod=marker:foldlevel=0
