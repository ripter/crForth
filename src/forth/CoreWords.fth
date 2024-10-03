: false 0 ;
: true -1 ;
: 1+ 1 + ;

: R@ R> dup >R ;


: BEGIN
  create loop-inner-func
  does>
; IMMEDIATE

: UNTIL
  branch? 1 loop-inner-func
; IMMEDIATE


: COUNT-UP-2
  dup . 1+ 
  dup 5 > branch? 2 
    9 . 
    10 
; 

: count-up 
  1            
  BEGIN
    DUP .      
    1+         
    DUP 5 >    
  UNTIL
  DROP         
;
