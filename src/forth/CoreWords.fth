: false 0 ;
: true -1 ;
: 1+ 1 + ;
: R@ R> dup >R ;


: BEGIN
  here >r >r 
; IMMEDIATE

: WHILE
  ?branch 3
; IMMEDIATE

: REPEAT
  r> r> execute
; IMMEDIATE


: count-up 
  dup . 1+ 
  dup 5 <
  ?branch 1 count-up
; 

: count-up-2 
  begin
    dup . 1+
  dup 5 < while repeat 
;
