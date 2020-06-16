;Group 50 
;Kadir Burak Tokmak e2036200
;Emrah Kösen e1942317 
;Furkan İnalcık e2171643
;THE2_v1 on board
    list P=18F8722 ; 

#include <p18f8722.inc>
config OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF



rg3Pressed udata 0x22
 rg3Pressed
rg2Pressed udata 0x23
 rg2Pressed
rg0Pressed udata 0x25
 rg0Pressed


counter500 udata 0x26
 counter500
counter400 udata 0x27
 counter400
counter350 udata 0x28
 counter350


ballcounter udata 0x2A
 ballcounter
actionflag udata 0x2B
 actionflag

bar udata 0x2E
bar
ball_at_5 udata 0x2D
ball_at_5
collumA udata 0x2F
collumA
collumB udata 0x30
collumB
collumC udata 0x31
collumC
collumD udata 0x32
collumD
collumE udata 0x33
collumE
collumF udata 0x34
collumF


w_temp udata 0x37
w_temp

 status_temp udata 0x38
 status_temp
pclath_temp udata 0x39
 pclath_temp

 timer1low udata 0x40
 timer1low

 timer1high udata 0x41
 timer1high

 carries udata 0x42
 carries

 last3bit udata 0x43
 last3bit

 shiftcounter udata 0x44
 shiftcounter

 L2 udata 0x45
 L2

 L1 udata 0x46
 L1

 HP udata 0x47
 HP

 gamelevel udata 0x48
 gamelevel


org 0x00
goto init

org 0x08
goto isr

 init:
    MOVLW b'000000'
    MOVWF TRISA
    MOVWF TRISB
    MOVWF TRISC
    MOVWF TRISD
    MOVWF TRISE
    MOVWF TRISF
    CLRF TRISH
    CLRF TRISJ

    MOVLW b'00001111'
    MOVWF TRISG

    call init_seven_segment_table
start:
    clrf rg3Pressed
    clrf rg2Pressed
    clrf rg0Pressed

    clrf counter500
    clrf counter400
    clrf counter350

    clrf ballcounter
    clrf actionflag




    clrf collumA
    clrf collumB
    clrf collumC
    clrf collumD
    clrf collumE
    clrf collumF


    clrf w_temp
    clrf status_temp
    clrf pclath_temp
    clrf timer1low
    clrf timer1high
    clrf carries
    clrf last3bit
    clrf shiftcounter
    clrf L2
    clrf L1
    CLRF PORTH
    CLRF PORTJ


    CLRF LATA
    CLRF LATB
    CLRF LATC
    CLRF LATD
    CLRF LATE
    CLRF LATF
    CLRF LATG
    CLRF LATH
    CLRF LATJ

    BCF RCON,7 ; Disable priorities 

    BCF PIE1, 0 ; disable timer1 interrupt
    movlw b'10000001';timer1
    movwf T1CON
    MOVLW b'01000111' ; 8bit timer0 1/256 prescaler
    MOVWF T0CON
    MOVLW b'10100000' ; Enable interrupts and clear flags
    MOVWF INTCON




startState:
    BSF LATA,5
    BSF LATB,5
    MOVLW b'00000011'
    MOVWF bar
    
    movlw d'5'
    movwf HP
    
    movlw d'1'
    movwf gamelevel
    
    call IsPressedRg0  ;STARTing button
    movff TMR1L, timer1low
    movff TMR1H, timer1high
    BSF T0CON,7

GameState:
    MOVLW b'0'
    BTFSC actionflag,1;if game over
    goto init
    MOVLW b'0'
    BTFSC actionflag,0 ;if timer interrupt occure
    CALL WhenActionflag_MoveThemAll


    call IsPressedRg3 ;move the bar left
    call IsPressedRg2 ;move the bar right
    call IsReleasedRg3
    call IsReleasedRg2
    call light_seven_segment ;?
    goto GameState




WhenActionflag_MoveThemAll:
    BCF actionflag,0
    RLNCF collumA ; rotate 1 bit left so balls move 1 light down
    BCF collumA,6 ; 6 th bit clear


    RLNCF collumB
    BCF collumB,6

    RLNCF collumC
    BCF collumC,6

    RLNCF collumD
    BCF collumD,6

    RLNCF collumE
    BCF collumE,6

    RLNCF collumF
    BCF collumF,6


    call chech_Ball_Bar_intersection ;TODO
    
    incf ballcounter
    movlw d'49'
    CPFSGT ballcounter 
    CALL CreateBall ; random BALL create
    ;RANDon ball olusturduktan sonra latlar? de?i?ti
    movff collumA, LATA ;collumA to LATA
    movff collumB, LATB ;collumB to LATB
    movff collumC, LATC ;collumC to LATC
    movff collumD, LATD ;collumD to LATD
    movff collumE, LATE ;collumE to LATE
    movff collumF, LATF ;collumF to LATF

    BTFSC bar, 0
	bsf LATA,5
    
    BTFSC bar, 1
	bsf LATB,5
    
    BTFSC bar, 2
	bsf LATC,5
    
    BTFSC bar, 3
	bsf LATD,5
    
    BTFSC bar, 4
	bsf LATE,5
    
    BTFSC bar, 5
	bsf LATF,5
    
    
    RETURN ;GOTO GAME STATE BACK


chech_Ball_Bar_intersection:
    BTFSC collumA, 5
	goto checkA
    BTFSC collumB, 5
	goto checkB
    BTFSC collumC, 5
	goto checkC
    BTFSC collumD, 5
	goto checkD
    BTFSC collumE, 5
	goto checkE
    BTFSC collumF, 5
	goto checkF
    return

    checkA:
	BTFSS bar,0
	call decreaseHP
	return

    checkB:
	BTFSS bar,1
	call decreaseHP
	return
    checkC:
	BTFSS bar,2
	call decreaseHP
	return
    checkD:
	BTFSS bar,3
	call decreaseHP
	return
    checkE:
	BTFSS bar,4
	call decreaseHP
	return
    checkF:
	BTFSS bar,5
	call decreaseHP
	return



CreateBall: ;create ball random 0th location TODO
    call shiftcountercheck
    movlw b'0000111'
    andwf timer1low,0,0
    movwf last3bit
    movlw d'6'
    CPFSLT last3bit
    call sub2
    movlw d'0'
    subwf last3bit,0,0
    BTFSC STATUS,Z
    BSF collumA,0
    movlw d'1'
    subwf last3bit,0,0
    BTFSC STATUS,Z
    BSF collumB,0
    movlw d'2'
    subwf last3bit,0,0
    BTFSC STATUS,Z
    BSF collumC,0
    movlw d'3'
    subwf last3bit,0,0
    BTFSC STATUS,Z
    BSF collumD,0
    movlw d'4'
    subwf last3bit,0,0
    BTFSC STATUS,Z
    BSF collumE,0
    movlw d'5'
    subwf last3bit,0,0
    BTFSC STATUS,Z
    BSF collumF,0
    ;movf AstroidF,0,0
    ;IORWF LATF,1,0
  
    
    call shifttimer1

 sub2:
    movlw d'2'
    subwf last3bit,1,0
    call setlevel
    return

    
 decreaseHP:
    decf HP
    movlw d'0'
    CPFSGT HP
    BSF actionflag,1
    return
    
    
    
setlevel:
    movlw d'25'
    CPFSLT ballcounter
    goto set3
    movlw d'10'
    CPFSLT ballcounter
    goto set2
    return
    
set3:
    movlw d'3'
    movwf gamelevel
    return
    
set2:
    movlw d'2'
    movwf gamelevel
    return



    shifttimer1:
    RRCF timer1low,1,0 ; rotation
    
    BCF carries,0  ; clears the value
    BTFSC STATUS,C ; checks if the carry should be set, if C is zero skip the next line 
    BSF carries,0  ; if C is NOT zero, carries[0] is set
    
    RRCF timer1high,1,0 ; rotation
    
    BCF carries,1 ;changed from 0 to 1
    BTFSC STATUS,C
    BSF carries,1
    
    BCF timer1low,7
    BTFSC carries,1
    BSF timer1low,7
    
    BCF timer1high,7
    BTFSC carries,0
    BSF timer1high,7
    
    incf shiftcounter
    return


    shiftcountercheck:
    movlw d'10'
    CPFSLT shiftcounter      ; shiftcounter 10'dan kucuk degilse complementer'e gidiyor
    call complementer
    return  
    
   complementer:             
    movlw d'10'
    subwf shiftcounter,1,0   ; burada degeri 10 olan shiftcounter'dan 10 cikarip degerini 0 yapiyoruz 
    comf timer1low
    comf timer1high
    return


   














IsPressedRg0:
    BTFSS PORTG, 0
    goto IsPressedRg0
    return

IsPressedRg3:
    MOVLW D'1'
    BTFSS PORTG, 3
    return
    MOVWF rg3Pressed
    return
IsReleasedRg3:
    MOVLW D'0'
    CPFSGT rg3Pressed	    ;if releas set 1 skip goto lata_1
    return
    BTFSC PORTG, 3
    return
    MOVLW D'0'
    MOVWF  rg3Pressed
    call MoveLeft
    return
IsPressedRg2:
    MOVLW D'1'
    BTFSS PORTG, 2
    return
    MOVWF rg2Pressed
    return
IsReleasedRg2:
    MOVLW D'0'
    CPFSGT rg2Pressed	    ;if releas set 1 skip goto lata_1
    return
    BTFSC PORTG, 2
    return
    MOVWF  rg2Pressed
    call MoveRight
    return




MoveLeft:
    BTFSC bar, 0
    return

    RRCF bar,1,0

    ;zeroL:
	BTFSC bar, 0
	    goto firstL
	bsf LATA,5
	bsf LATB,5
	bcf LATC,5
	return
    firstL:
	BTFSC bar, 1
	    goto secondL
	bsf LATB,5
	bsf LATC,5
	bcf LATD,5
	return
    secondL:
	BTFSC bar, 2
	    goto thirdL
	bsf LATC,5
	bsf LATD,5
	bcf LATE,5
	return
    thirdL:
	BTFSC bar, 3
	    goto fourthL
	bsf LATD,5
	bsf LATE,5
	bcf LATF,5
	return
    fourthL:
	bsf LATE,5
	bsf LATF,5
    ;fifthL:

    return



MoveRight:
    BTFSC bar, 5
    return

    RLCF bar,1,0

    ;zeroR:

    ;firstR:
	BTFSC bar, 1
	    goto secondR
	bcf LATA,5
	bsf LATB,5
	bsf LATC,5
	return
    secondR:
	BTFSC bar, 2
	    goto thirdR
	bcf LATB,5
	bsf LATC,5
	bsf LATD,5
	return
    thirdR:
	BTFSC bar, 3
	    goto fourthR
	bcf LATC,5
	bsf LATD,5
	bsf LATE,5
	return
    fourthR:
	bcf LATD,5
	bsf LATE,5
	bsf LATF,5
    ;fifthR:

    return






isr:
    call save_registers
    movlw d'10'
    CPFSGT ballcounter
    goto timer500
    movlw d'25'
    CPFSGT ballcounter
    goto timer400
    movlw d'60'
    CPFSGT ballcounter
    goto timer350
    BSF actionflag,1
    BCF INTCON, 2 ;clear tmr0?f
    movlw d'61' ;256-61 = 195 -- 195*256 = 49920 for 5ms
    movwf TMR0L
    call restore_registers
    RETFIE;stop TODO



timer500:
    incf counter500,f
    movf counter500,w
    sublw d'100'
    btfss STATUS,Z
    goto timer_interrupt_exit500
    clrf counter500
    BSF actionflag,0
timer_interrupt_exit500:
    BCF INTCON, 2 ;clear tmr0?f
    movlw d'61' ;256-61 = 195 -- 195*256 = 49920 for 5ms
    movwf TMR0L
    call restore_registers
    RETFIE




timer400:
    incf counter400,f
    movf counter400,w
    sublw d'80'
    btfss STATUS,Z
    goto timer_interrupt_exit400
    clrf counter400
    BSF actionflag,0
timer_interrupt_exit400:
    BCF INTCON, 2 ;clear tmr0?f
    movlw d'61' ;256-61 = 195 -- 195*256 = 49920 for 5ms
    movwf TMR0L
    call restore_registers
    RETFIE


timer350:
    incf counter350,f
    movf counter350,w
    sublw d'70'
    btfss STATUS,Z
    goto timer_interrupt_exit350
    clrf counter350
    BSF actionflag,0
timer_interrupt_exit350:
    BCF INTCON, 2 ;clear tmr0?f
    movlw d'61' ;256-61 = 195 -- 195*256 = 49920 for 5ms
    movwf TMR0L
    call restore_registers
    RETFIE






light_seven_segment:
    call light_D0
    call light_D3
    return

init_seven_segment_table: ; We create an array with FSR0 on address 100h
    LFSR FSR0, 100h
    MOVLW  b'00111111'	; 7-Segment = 0
    MOVWF POSTINC0
    MOVLW  b'00000110'	; 7-Segment = 1
    MOVWF POSTINC0
    MOVLW  b'01011011'	; 7-Segment = 2
    MOVWF POSTINC0
    MOVLW  b'01001111'	; 7-Segment = 3
    MOVWF POSTINC0
    MOVLW  b'01100110'	; 7-Segment = 4
    MOVWF POSTINC0
    MOVLW  b'01101101'	; 7-Segment = 5
    MOVWF POSTINC0
    MOVLW  b'01111101'	; 7-Segment = 6
    MOVWF POSTINC0
    MOVLW  b'00000111'	; 7-Segment = 7
    MOVWF POSTINC0
    MOVLW  b'01111111'	; 7-Segment = 8
    MOVWF POSTINC0
    MOVLW  b'01100111'	; 7-Segment = 9
    MOVWF INDF0		; No need to increment
    RETURN


light_D0:
    movf HP, 0  ; Use second digit of the player2's score here
    call seven_segment_table
    movwf   LATJ
    bsf     LATH, 3
    call    DELAY
    bcf     LATH, 3
    return

 light_D3:
    movf gamelevel, 0  ; Use first digit of the player1's score here
    call seven_segment_table
    movwf   LATJ
    bsf     LATH, 0
    call    DELAY
    bcf     LATH, 0
    return
    
seven_segment_table:
    LFSR FSR0, 100h
    ADDWF FSR0L
    MOVF INDF0, 0
    RETURN
    
DELAY:
    movlw d'50'
    movwf L2

LOOP2:
    movlw d'255'
    movwf L1

LOOP1:
    decfsz L1,F
        goto LOOP1
    decfsz L2,F
        goto LOOP2
    return

 save_registers:
    movwf 	w_temp          ;Copy W to TEMP register
    swapf 	STATUS, w       ;Swap status to be saved into W
    clrf 	STATUS          ;bank 0, regardless of current bank, Clears IRP,RP1,RP0
    movwf 	status_temp     ;Save status to bank zero STATUS_TEMP register
    movf 	PCLATH, w       ;Only required if using pages 1, 2 and/or 3
    movwf 	pclath_temp     ;Save PCLATH into W
    clrf 	PCLATH          ;Page zero, regardless of current page
    return

                                                                                                                                                                                                                                                                                                                                           
 restore_registers:
    movf 	pclath_temp, w  ;Restore PCLATH
    movwf 	PCLATH          ;Move W into PCLATH
    swapf 	status_temp, w  ;Swap STATUS_TEMP register into W
    movwf 	STATUS          ;Move W into STATUS register                                                            
    swapf 	w_temp, f       ;Swap W_TEMP
    swapf 	w_temp, w       ;Swap W_TEMP into W
    return





END    
