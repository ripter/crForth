: false 0 ; \ 0 is the false value in Forth
: true -1 ; \ -1 is the traditional true value in Forth, although anything non-zero is considered true
: 1+ 1 + ;
: R@ r> dup >r ;
: 2>R >r >r ;
: 2R> r> r> ;
: 2drop drop drop ;
: cr 10 emit ;

: type2 ( addr u -- )
  0 DO              \ loop from 0 to u-1
    dup i + c@ emit \ print the character at addr+
  loop
;

