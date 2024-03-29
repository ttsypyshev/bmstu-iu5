PRGR SEGMENT
	               ASSUME CS:PRGR, DS:DATA

	BEGIN:         
	               MOV    AX, DATA
	               MOV    DS, AX
	               CALL   INFO

	INIT:          
	               mov    CX,20
	               mov    SI,3

	INPUT:         
	               CALL   GETCH
	               cmp    AL,'$'
	               JE     END_LINE
	               cmp    SI,3
	               JE     END_INPUT
	CONTINUE_INPUT:
	               CALL   HEX
	               inc    SI
	               loop   INPUT

	END_LINE:      
	               push   BX
	               push   CX
	               mov    BX,1
	               dec    SI
	               mov    CX,SI
	               mov    AH,40h
	               mov    DX,offset line
	               int    21h
	               mov    CX,20
	               mov    SI,3

	CLEAR:         
	               mov    line[SI],32
	               inc    SI
	               loop   CLEAR
	               pop    CX
	               pop    BX
	               mov    CX,4
	               CALL   CLRF
	               loop   INIT

	END_INPUT:     
	               cmp    AL,'*'
	               JE     EXIT_PROGRAM
	               JNE    CONTINUE_INPUT

	EXIT_PROGRAM:  
	               CALL   CLRF
	               CALL   CLRF
	               mov    AH,09h
	               lea    DX, msg_input_name
	               int    21h
	               CALL   CLRF
	               mov    DX,offset msg
	               int    21h
	               CALL   GETCH
	               mov    AX,02h
	               int    10h
	               mov    AX,4C00h
	               int    21h

INFO PROC
	               mov    AX,02h
	               int    10h
	               mov    AH,09h
	               mov    DX,offset greet
	               int    21h
	               CALL   CLRF
	               mov    AH,09h
	               mov    DX,offset defl
	               int    21h
	               CALL   CLRF
	               mov    AH,02h
	               mov    DL,36
	               int    21h
	               mov    AH,09h
	               mov    DX,offset info1
	               int    21h
	               CALL   CLRF
	               mov    AH,09h
	               mov    DX,offset info2
	               int    21h
	               CALL   CLRF
	               CALL   CLRF
	               mov    BX,offset hextb
INFO ENDP

GETCH proc
	               mov    AH,01h
	               int    21h
	               RET
GETCH endp

CLRF proc
	               mov    AH,02h
	               mov    DL,10
	               int    21h
	               mov    AH,02h
	               mov    DL,13
	               int    21h
	               RET
CLRF endp

CLRSCR PROC
	               MOV    AX, 02H
	               INT    10H
	               RET
CLRSCR ENDP

HEX proc
	               push   AX
	               shr    AL, 1
	               shr    AL, 1
	               shr    AL, 1
	               shr    AL, 1
	               XLAT
	               mov    line[SI],AL
	               inc    SI
	               pop    AX
	               and    AL, 00001111b
	               XLAT
	               mov    line[SI],AL
	               inc    SI
	               mov    AL,32
	               mov    line[SI],AL
	               RET
HEX endp

prgr ends

data segment
	hextb          db '0123456789ABCDEF'
	line           db 14 dup (' = ')
	divide         db ' = $'
	msg            db 'Press any key to exit... $'
	greet          db 'Type any chars, maximum length - 20$'
	defl           db '----------------------------------$'
	info1          db ' - end of string$'
	info2          db '* - end of input$'
	msg_input_name db 'TSYPYSHEV T.A. UI5-41 Var-20$'
data ends

stk segment stack
	    db 256 dup (0)
stk ends

end BEGIN
