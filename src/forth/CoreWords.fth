: false 0 ; \ 0 is the false value in Forth
: true -1 ; \ -1 is the traditional true value in Forth, although anything non-zero is considered true
: 1+ 1 + ;
: R@ r> dup >r ;
: 2>R >r >r ;
: 2R> r> r> ;
: 2drop drop drop ;
: cr 10 emit ;



\ : test
\   5 0 DO 
\     I . 
\   LOOP
\ ;

\ : BEGIN
\   here 2>r
\ ; IMMEDIATE

\ : WHILE
\   ?branch 3
\ ; IMMEDIATE

\ : REPEAT
\   2r> execute
\ ; IMMEDIATE


\ : count-up ( n -- )
\   dup . 1+  \ print and increment
\   dup 5 <   \ compare with 5
\   1 ?branch count-up \ if less than 5, jump to count-up
\ ; 

\ : count-up-2 ( n -- )
\   begin
\     dup . 1+ \ print and increment
\   dup 5 < while repeat \ if less than 5, jump to begin
\ ;



\ limits a number to be less than or equal to 5
\ return n if n is less than 5, otherwise return 5
\ : test-5 ( n -- n' )
\   \ dup \ duplicate n so we can return it later
\   5 < \ consume n and return bool, was n less than 5?
\   \ if true, return n
\   ?branch 4 
\   \ if false, return 5
\   invert ?branch 1 5
\ ;

\ : test-5-2 
\   dup 5 >
\   if
\     -1
\   else
\     0
\   then
\ ;

