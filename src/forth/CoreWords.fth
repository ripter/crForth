: false 0 ;
: true -1 ;
: 1+ 1 + ;
: R@ R> dup >R ;


: BEGIN
  latest  
; IMMEDIATE

: WHILE
  ?branch 1
; IMMEDIATE

: REPEAT
  .
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
