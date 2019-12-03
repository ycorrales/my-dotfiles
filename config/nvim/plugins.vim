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

call plug#begin('~/.vim/plugged')

" colorschemes
Plug 'joshdick/onedark.vim'
Plug 'chriskempson/base16-vim'

" utilities
"Plug 'scrooloose/nerdtree', { 'on': ['NERDTreeToggle', 'NERDTreeFind'] } | Plug 'Xuyuanp/nerdtree-git-plugin' | Plug 'ryanoasis/vim-devicons' " file drawer
Plug 'benmills/vimux' " tmux integration for vim
Plug 'vim-airline/vim-airline' " fancy statusline
Plug 'vim-airline/vim-airline-themes' " themes for vim-airline
Plug 'tpope/vim-fugitive' " amazing git wrapper for vim
Plug 'tpope/vim-rhubarb' " hub extension for fugitive
Plug 'JamshedVesuna/vim-markdown-preview'
" plugin from vim
Plug 'itchyny/lightline.vim'
Plug 'rhysd/vim-clang-format'
Plug 'timakro/vim-searchant'
Plug 'vim-scripts/peaksea'
Plug 'KeitaNakamura/neodark.vim'
Plug 'skielbasa/vim-material-monokai'
Plug 'mkitt/tabline.vim'
Plug 'vim-syntastic/syntastic'
Plug 'airblade/vim-gitgutter'
Plug 'kassio/neoterm'
Plug 'ryanpcmcquen/fix-vim-pasting'

call plug#end()

