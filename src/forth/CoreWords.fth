: 1+
  1 +
;

: BEGIN
  create loop-inner-func
  does>
; IMMEDIATE

: UNTIL
  ;
  branch? 1 loop-inner-func
; IMMEDIATE



: count-up 
  1            
  BEGIN
    DUP .      
    1+         
    DUP 5 >    
  UNTIL
  DROP         
;
