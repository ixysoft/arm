set tabstop=4
set softtabstop=4
set shiftwidth=4
set expandtab
set nu
set cindent
set smartindent
set smarttab
set autoindent
set showmatch
set whichwrap=<,>,h,l
set backspace=2
" Uncomment the following to have Vim jump to the last position when
" reopening a file
if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
  au FileType make setlocal noexpandtab
endif
