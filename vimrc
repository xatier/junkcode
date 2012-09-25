" All system-wide defaults are set in $VIMRUNTIME/debian.vim (usually just
" /usr/share/vim/vimcurrent/debian.vim) and sourced by the call to :runtime
" you can find below.  If you wish to change any of those settings, you should
" do it in this file (/etc/vim/vimrc), since debian.vim will be overwritten
" everytime an upgrade of the vim packages is performed.  It is recommended to
" make changes after sourcing debian.vim since it alters the value of the
" 'compatible' option.

" This line should not be removed as it ensures that various options are
" properly set to work with the Vim-related packages available in Debian.
runtime! debian.vim

" Uncomment the next line to make Vim more Vi-compatible
" NOTE: debian.vim sets 'nocompatible'.  Setting 'compatible' changes numerous
" options, so any other options should be set AFTER setting 'compatible'.
"set compatible

" Vim5 and later versions support syntax highlighting. Uncommenting the
" following enables syntax highlighting by default.
if has("syntax")
  syntax on
endif

" If using a dark background within the editing area and syntax highlighting
" turn on this option as well
"set background=dark

" Uncomment the following to have Vim jump to the last position when
" reopening a file
"if has("autocmd")
"  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
"endif

" Uncomment the following to have Vim load indentation rules and plugins
" according to the detected filetype.
"if has("autocmd")
"  filetype plugin on
" indent on
"endif

" The following are commented out as they cause vim to behave a lot
" differently from regular Vi. They are highly recommended though.
"set showcmd		" Show (partial) command in status line.
"set showmatch		" Show matching brackets.
"set ignorecase		" Do case insensitive matching
"set smartcase		" Do smart case matching
"set incsearch		" Incremental search
"set autowrite		" Automatically save before commands like :next and :make
"set hidden             " Hide buffers when they are abandoned
"set mouse=a		" Enable mouse usage (all modes)

" Source a global configuration file if available
if filereadable("/etc/vim/vimrc.local")
  source /etc/vim/vimrc.local
endif


" -- extend settings of vim ------------------------------------------------



"###########################################################################
" multi-encoding setting
"###########################################################################

if has("multi_byte")
"set bomb
set fileencodings=ucs-bom,utf-8,cp936,big5,euc-jp,euc-kr,latin1
" CJK environment detection and corresponding setting
if v:lang =~ "^zh_CN"
" Use cp936 to support GBK, euc-cn == gb2312
set encoding=cp936
set termencoding=cp936
set fileencoding=cp936
elseif v:lang =~ "^zh_TW"
" cp950, big5 or euc-tw
" Are they equal to each other?
set encoding=big5
set termencoding=big5
set fileencoding=big5
elseif v:lang =~ "^ko"
" Copied from someone's dotfile, untested
set encoding=euc-kr
set termencoding=euc-kr
set fileencoding=euc-kr
elseif v:lang =~ "^ja_JP"
" Copied from someone's dotfile, untested
set encoding=euc-jp
set termencoding=euc-jp
set fileencoding=euc-jp
endif
" Detect UTF-8 locale, and replace CJK setting if needed
if v:lang =~ "utf8$" || v:lang =~ "UTF-8$"
set encoding=utf-8
set termencoding=utf-8
set fileencoding=utf-8
endif
else
echoerr "Sorry, this version of (g)vim was not compiled with multi_byte"
endif




"###########################################################################
" Gerneral settings
"###########################################################################

" syntax highlighting
syntax on


" line number
"set number


" make tab = four spaces
set expandtab
set tabstop=4
set shiftwidth=4


" highlight search results and ignore case
set hlsearch
set ignorecase
set smartcase
set incsearch 


" make < and  > as a pair, useful in C++
set matchpairs+=<:>


" don't do auto indent while pasting
"set paste


" automatically read the file again when it changed outside vim
set autoread


" always show current position (replace this with statusline)
"set ruler


set showmode
set autoindent
set smartindent


filetype plugin indent on


"###########################################################################
" color settings
"###########################################################################

" colorscheme
colo ron
" using ':colo [tab]' to change colorscheme



" number of colors 256
set t_Co=256


" change line (?)
set colorcolumn=80
hi ColorColumn ctermbg=red

set bg=dark





"###########################################################################
" statusline and cursorline
"###########################################################################

set laststatus=2
set statusline=\ %F%m%r%y[%{strlen(&fenc)?&fenc:&enc}]%h%w%=[%l,%3v]\ --%p%%--\ \  
hi  statusline ctermfg=green ctermbg=darkblue


set cursorline
set cursorcolumn
hi CursorLine term=none cterm=none ctermbg=none ctermbg=none
hi CursorColumn term=none cterm=none ctermbg=none ctermbg=none
au InsertEnter * hi CursorLine term=none cterm=underline
au InsertLeave * hi CursorLine term=none cterm=none ctermbg=none
au InsertEnter * hi CursorColumn term=none ctermbg=darkblue
au InsertLeave * hi CursorColumn term=none cterm=none ctermbg=none


"###########################################################################
" key mappings
"###########################################################################

" F7 to close syntax high-lighting
map <F7> :if exists("syntax_on") <BAR>
\ syntax off <BAR><CR>
\ else <BAR>
\ syntax enable <BAR>
\ endif <CR>


" for C/C++ files
" F9 to compile, F8 to run, F5 to build
au FileType c map <F9> :!gcc -std=c99 -Wall -Wextra -pedantic -Ofast % -lm -o %:r<CR>
au FileType cpp map <F9> :!g++ -std=c++0x -Wall -Wextra -pedantic -Ofast % -lm -o %:r<CR>
au FileType c,cpp map <F8> :!./%:r<CR>
au FileType c,cpp map <F5> :w<CR> :make<CR>


" for Perl files
" K to lookup current word in perldoc
au FileType perl nmap K :!perldoc <cword> <bar><bar> perldoc -f <cword><CR><CR>


" F5 to run a script
map <F5> :!./%<CR>


