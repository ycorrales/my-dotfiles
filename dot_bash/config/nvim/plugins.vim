" check whether vim-plug is installed and install it if necessary
let plugpath = expand('<sfile>:p:h'). '/autoload/plug.vim'
if !filereadable(plugpath)
    if executable('curl')
        let plugurl = 'https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
        call system('curl -fLo ' . shellescape(plugpath) . ' --create-dirs ' . plugurl)
        if v:shell_error
            echom "Error downloading vim-plug. Please install it manually.\n"
            exit
        endif
    else
        echom "vim-plug not installed. Please install it manually or install curl.\n"
        exit
    endif
endif

call plug#begin('~/.local/share/nvim/lazy')

" colorschemes
" Plug 'KeitaNakamura/neodark.vim'
 Plug 'rakr/vim-one'
" utilities
" Plug 'scrooloose/nerdtree', { 'on': ['NERDTreeToggle', 'NERDTreeFind'] } | Plug 'Xuyuanp/nerdtree-git-plugin' | Plug 'ryanoasis/vim-devicons' " file drawer
if ! exists('g:vscode')
  Plug 'itchyny/lightline.vim'
endif
 Plug 'tpope/vim-fugitive' " amazing git wrapper for vim
 Plug 'tpope/vim-rhubarb' " hub extension for fugitive
 Plug 'ctrlpvim/ctrlp.vim' " fuzzy file finder
 Plug 'preservim/nerdtree'
 Plug 'rhysd/vim-clang-format'
 "Plug 'vim-scripts/peaksea'
 "Plug 'skielbasa/vim-material-monokai'
 "Plug 'mkitt/tabline.vim'
 Plug 'vim-syntastic/syntastic'
 Plug 'airblade/vim-gitgutter'
 "Plug 'kassio/neoterm'
 "Plug 'ryanpcmcquen/fix-vim-pasting'

 if v:version > 810 || has('nvim')
   Plug 'PeterRincker/vim-searchlight'
   Plug 'benmills/vimux' " tmux integration for vim
   Plug 'iamcco/markdown-preview.nvim', { 'do': { -> mkdp#util#install() }}
 endif

 call plug#end()
