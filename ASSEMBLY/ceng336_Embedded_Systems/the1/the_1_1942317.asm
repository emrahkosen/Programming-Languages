
LIST    P=18F8722

#INCLUDE <p18f8722.inc>

CONFIG OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF



 param_1  udata 0X20
 param_1
 param_2  udata 0X21
 param_2
 result  udata 0X22
 result
 add_or_sub udata 0x23
 add_or_sub ; if first bit is 1 add else sub

 s udata h'24'
 s

 s1 udata h'25'
 s1

 s2 udata h'26'
 s2
 ra4_pressed udata h'27'
 ra4_pressed
 re3_pressed udata h'28'
 re3_pressed
 re4_pressed udata h'29'
 re4_pressed

ORG     0x00
goto    main





init
movlw h'00'
movwf TRISB
movwf TRISC
movwf TRISE
clrf  LATB
clrf  LATC
clrf  LATD

movlw b'00010000'; set RA[0:3] as output and RA4 as input
movf TRISA
clrf PORTA

MOVLW 0x1F
MOVWF ADCON1 ; set pins of PORTA as digital

movlw b'0000'
movwf TRISB
clrf PORTB


movlw b'0000'
movwf TRISC
clrf PORTC

movlw b'00000000'
movwf TRISD
clrf PORTD

movlw b'00011000'
movwf TRISE
clrf PORTE


movlw h'00'
movwf add_or_sub ;set to 0
movwf param_1
movwf param_2
movwf result
movwf ra4_pressed
movwf re3_pressed
return





lighting
    MOVLW b'00001111'
    MOVWF LATB
    MOVWF LATC
    MOVLW b'11111111'
    MOVWF LATD
    return

light_out
    call delay_1s
    MOVLW b'0000'
    MOVWF LATB
    MOVWF LATC
    MOVLW b'00000000'
    MOVWF LATD
    return

delay_1s
    movlw 0x64
    movwf s
    goto dongu1

    dongu1:
	movlw 0x64
	movwf s1
	goto dongu11
	dongu11:
		movlw 0x64
		movwf s2
		goto dongu12
	    dongu12:
		    nop
		    nop
		    nop
		    nop
		    nop
		    nop
		    nop
		    DECFSZ s2
		    goto dongu12
		    DECFSZ s1
		    goto dongu11
		    DECFSZ s
		    goto dongu1
    return

choose_operation
    BTFSS PORTA,4
    return
    movlw 0x01
    movwf ra4_pressed
    XORWF add_or_sub
    release_RA4:
	BTFSC PORTA,4
	goto release_RA4
	return

press_RE3
	BTFSS PORTE,3
	return
	movlw 0x01
	movwf re3_pressed
	release_RE3:
	    BTFSC PORTE,3
	    goto release_RE3
	return

press_RE4
    BTFSS PORTE, 4
    return
    movlw 0x01
    movwf re4_pressed
    release_RE4:
	BTFSC PORTE,4
	goto release_RE4
    return





light_PORTB
    movff param_1,PORTB
    return

light_PORTC
    movff param_2,PORTC
    return


subtraction
    movlw 0x00
    XORWF param_1,0
    CPFSEQ param_2
    goto jump
    return
jump:
    XORWF param_2,0
    movwf PORTD
  subst:
    BTFSC PORTD,0
    return
    RRCF PORTD
    BCF PORTD,7;
    goto subst

addition
    movff param_1,result
 adding:
    movff result,PORTD
    BTFSS param_2,0
    return
    RRCF param_2
    RLNCF result
    bsf result,0
    goto adding





set_params
    set_first_param:
	movlw 0x00
	movwf re3_pressed
	call press_RE3
	BTFSC re3_pressed,0
	    goto set_second_param
	call press_RE4
	BTFSS re4_pressed, 0
	    goto set_first_param
	RLNCF param_1
	bsf param_1,0
	movlw 0x00
	BTFSC param_1,4
	movwf param_1
	call light_PORTB
	movlw 0x00
	movwf re4_pressed
	goto set_first_param

    set_second_param:
	movlw 0x00
	movwf re3_pressed
	    call press_RE3
	BTFSC re3_pressed,0
	    goto make_operation
	call press_RE4
	BTFSS re4_pressed, 0
	    goto set_second_param
	RLNCF param_2
	bsf param_2,0
	movlw 0x00
	BTFSC param_2,4
	    movwf param_2
	call light_PORTC
	movlw 0x00
	movwf re4_pressed
	goto set_second_param
    make_operation:
	BTFSS add_or_sub,0
	    call subtraction ;TODO
	BTFSC add_or_sub,0
	    call addition    ;TODO
    return
main:
call init
    call lighting
    loop:
	call light_out
       loop1:
	call choose_operation
	BTFSS ra4_pressed, 0 ;RA4 e 1 defa oldun basidi mi
	goto loop1
	call press_RE3 ; TODO
	BTFSS re3_pressed,0 ; if RE3 is pressed get value of first param
	goto loop1 ; else wait for pressing RA4 or RE3
	call set_params
    movlw 0x00
    movwf ra4_pressed
    movwf re3_pressed
    movwf param_1
    movwf param_2
    MOVWF add_or_sub
    movwf result
goto loop
end
