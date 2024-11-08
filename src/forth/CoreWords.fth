: FALSE 0 ; \ 0 is the false value in Forth
: TRUE -1 ; \ -1 is the traditional true value in Forth, although anything non-zero is considered true
: 1+    ( n1 -- n2 ) 1 + ;                      \ https://forth-standard.org/standard/core/OnePlus
: R@    ( -- x ) ( R: x -- x ) r> dup >r ;      \ https://forth-standard.org/standard/core/RFetch
: 2>R   ( x1 x2 -- ) ( R: -- x1 x2 ) >r >r ;    \ https://forth-standard.org/standard/core/TwotoR
: 2R>   ( -- x1 x2 ) ( R: x1 x2 -- ) r> r> ;    \ https://forth-standard.org/standard/core/TwoRfrom
: 2DROP ( x1 x2 -- )  drop drop ;               \ https://forth-standard.org/standard/core/TwoDROP
: OVER  ( x1 x2 -- x1 x2 x1 ) >r dup r> swap ;  \ https://forth-standard.org/standard/core/OVER
: NIP   ( x1 x2 -- x2 ) swap drop ;             \ https://forth-standard.org/standard/core/NIP
: 2DUP  ( x1 x2 -- x1 x2 x1 x2 ) over over ;    \ https://forth-standard.org/standard/core/TwoDUP
: CR    ( -- ) 10 emit ;                        \ https://forth-standard.org/standard/core/CR

\ https://forth-standard.org/standard/core/MAX
\ : MAX ( n1 n2 -- n ) 
\   2dup > if 
\     drop
\   else
\     nip
\   then
\ ;

\ https://forth-standard.org/standard/core/qDO
\ : ?DO ( n1 n2 -- )
\     2dup = if 2drop else DO then 
\ ;


\ https://forth-standard.org/standard/core/TYPE
\ : TYPE ( addr u -- )
\   0 max 0 do       \ loop from 0 to u-1
\     dup i + c@ emit \ print the character at addr+
\   loop
\   drop              \ drop the addr
\ ;

