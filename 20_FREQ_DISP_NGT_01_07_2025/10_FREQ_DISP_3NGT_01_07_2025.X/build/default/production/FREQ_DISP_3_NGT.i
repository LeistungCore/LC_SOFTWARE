# 1 "FREQ_DISP_3_NGT.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 285 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "FREQ_DISP_3_NGT.c" 2






#pragma config OSC = HS
#pragma config FCMEN = OFF
#pragma config IESO = OFF


#pragma config PWRT = OFF
#pragma config BOR = BOHW
#pragma config BORV = 3


#pragma config WDT = OFF
#pragma config WDTPS = 32768


#pragma config PWMPIN = OFF
#pragma config LPOL = LOW
#pragma config HPOL = LOW


#pragma config FLTAMX = RA5
#pragma config T1OSCMX = LOW
#pragma config MCLRE = ON


#pragma config STVREN = ON
#pragma config BBSIZ = BB256
#pragma config XINST = OFF


#pragma config CP0 = OFF
#pragma config CP1 = OFF


#pragma config CPB = OFF
#pragma config CPD = OFF


#pragma config WRT0 = OFF
#pragma config WRT1 = OFF


#pragma config WRTC = OFF
#pragma config WRTB = OFF
#pragma config WRTD = OFF


#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF


#pragma config EBTRB = OFF

# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/xc.h" 1 3
# 18 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/xc.h" 3
extern const char __xc8_OPTIM_SPEED;

extern double __fpnormalize(double);


# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/xc8debug.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdlib.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdlib.h" 2 3





# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/features.h" 1 3
# 11 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdlib.h" 2 3
# 21 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdlib.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 1 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef long int wchar_t;
# 128 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned size_t;
# 174 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef __int24 int24_t;
# 210 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdlib.h" 2 3

int atoi (const char *);
long atol (const char *);

long long atoll (const char *);

double atof (const char *);


float strtof (const char *restrict, char **restrict);
double strtod (const char *restrict, char **restrict);
long double strtold (const char *restrict, char **restrict);



long strtol (const char *restrict, char **restrict, int);
unsigned long strtoul (const char *restrict, char **restrict, int);

long long strtoll (const char *restrict, char **restrict, int);
unsigned long long strtoull (const char *restrict, char **restrict, int);


unsigned long __strtoxl(const char * s, char ** endptr, int base, char is_signed);

unsigned long long __strtoxll(const char * s, char ** endptr, int base, char is_signed);
# 55 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdlib.h" 3
int rand (void);
void srand (unsigned);

void *malloc (size_t);
void *calloc (size_t, size_t);
void *realloc (void *, size_t);
void free (void *);

          void abort (void);
int atexit (void (*) (void));
          void exit (int);
          void _Exit (int);

void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));







__attribute__((nonreentrant)) void qsort (void *, size_t, size_t, int (*)(const void *, const void *));

int abs (int);
long labs (long);

long long llabs (long long);


typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

typedef struct { long long quot, rem; } lldiv_t;


div_t div (int, int);
ldiv_t ldiv (long, long);

lldiv_t lldiv (long long, long long);


typedef struct { unsigned int quot, rem; } udiv_t;
typedef struct { unsigned long quot, rem; } uldiv_t;
udiv_t udiv (unsigned int, unsigned int);
uldiv_t uldiv (unsigned long, unsigned long);
# 5 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/xc8debug.h" 2 3







#pragma intrinsic(__builtin_software_breakpoint)
extern void __builtin_software_breakpoint(void);
# 24 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/xc.h" 2 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/builtins.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdint.h" 1 3
# 26 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 1 3
# 133 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned __int24 uintptr_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef __int24 intptr_t;
# 164 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;
# 179 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef long int32_t;





typedef long long int64_t;
# 194 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;
# 215 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdint.h" 2 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/builtins.h" 2 3


#pragma intrinsic(__nop)
extern void __nop(void);

#pragma intrinsic(__nopf000)
extern void __nopf000(void);
#pragma intrinsic(__nopffff)
extern void __nopffff(void);
#pragma intrinsic(__nop0000)
extern void __nop0000(void);



#pragma intrinsic(_delay)
extern __attribute__((nonreentrant)) void _delay(uint32_t);
#pragma intrinsic(_delaywdt)
extern __attribute__((nonreentrant)) void _delaywdt(uint32_t);

#pragma intrinsic(_delay3)
extern __attribute__((nonreentrant)) void _delay3(uint8_t);
# 25 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/xc.h" 2 3








# 1 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include/pic18.h" 1 3




# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/htc.h" 1 3






# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/xc.h" 1 3
# 8 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/htc.h" 2 3
# 6 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include/pic18.h" 2 3


# 1 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include/pic18_chip_select.h" 1 3
# 54 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include/pic18_chip_select.h" 3
# 1 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 1 3
# 44 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/__at.h" 1 3
# 45 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 2 3







extern volatile unsigned char PORTA __attribute__((address(0xF80)));

__asm("PORTA equ 0F80h");


typedef union {
    struct {
        unsigned RA0 :1;
        unsigned RA1 :1;
        unsigned RA2 :1;
        unsigned RA3 :1;
        unsigned RA4 :1;
        unsigned RA5 :1;
        unsigned RA6 :1;
        unsigned RA7 :1;
    };
    struct {
        unsigned AN0 :1;
        unsigned AN1 :1;
        unsigned TX :1;
        unsigned RX :1;
        unsigned AN2 :1;
        unsigned MCLR :1;
        unsigned OSC2 :1;
        unsigned OSC1 :1;
    };
    struct {
        unsigned INT0 :1;
        unsigned INT1 :1;
        unsigned CK :1;
        unsigned DT :1;
        unsigned T0CKI :1;
        unsigned :1;
        unsigned CLKO :1;
        unsigned CLKI :1;
    };
    struct {
        unsigned KBI0 :1;
        unsigned KBI1 :1;
        unsigned :2;
        unsigned VREFP :1;
        unsigned :1;
        unsigned T1OSO :1;
        unsigned T1OSI :1;
    };
    struct {
        unsigned :5;
        unsigned NOT_MCLR :1;
    };
    struct {
        unsigned CMP0 :1;
        unsigned :4;
        unsigned nMCLR :1;
        unsigned AN3 :1;
    };
    struct {
        unsigned :6;
        unsigned T1CKI :1;
    };
    struct {
        unsigned ULPWUIN :1;
        unsigned :4;
        unsigned LVDIN :1;
        unsigned :1;
        unsigned RJPU :1;
    };
} PORTAbits_t;
extern volatile PORTAbits_t PORTAbits __attribute__((address(0xF80)));
# 304 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PORTB __attribute__((address(0xF81)));

__asm("PORTB equ 0F81h");


typedef union {
    struct {
        unsigned RB0 :1;
        unsigned RB1 :1;
        unsigned RB2 :1;
        unsigned RB3 :1;
        unsigned RB4 :1;
        unsigned RB5 :1;
        unsigned RB6 :1;
        unsigned RB7 :1;
    };
    struct {
        unsigned PWM0 :1;
        unsigned PWM1 :1;
        unsigned INT2 :1;
        unsigned INT3 :1;
        unsigned PWM2 :1;
        unsigned PWM3 :1;
        unsigned PWM4 :1;
        unsigned PWM5 :1;
    };
    struct {
        unsigned :2;
        unsigned KBI2 :1;
        unsigned KBI3 :1;
        unsigned :2;
        unsigned PGC :1;
        unsigned PGD :1;
    };
    struct {
        unsigned :2;
        unsigned CMP2 :1;
        unsigned CMP1 :1;
    };
    struct {
        unsigned :2;
        unsigned T1OSO :1;
        unsigned T1OSI :1;
    };
    struct {
        unsigned :2;
        unsigned T1CKI :1;
    };
    struct {
        unsigned :3;
        unsigned CCP2_PA2 :1;
    };
} PORTBbits_t;
extern volatile PORTBbits_t PORTBbits __attribute__((address(0xF81)));
# 492 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char OVDCONS __attribute__((address(0xF82)));

__asm("OVDCONS equ 0F82h");


typedef union {
    struct {
        unsigned POUT :6;
    };
    struct {
        unsigned POUT0 :1;
        unsigned POUT1 :1;
        unsigned POUT2 :1;
        unsigned POUT3 :1;
        unsigned POUT4 :1;
        unsigned POUT5 :1;
    };
} OVDCONSbits_t;
extern volatile OVDCONSbits_t OVDCONSbits __attribute__((address(0xF82)));
# 550 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char OVDCOND __attribute__((address(0xF83)));

__asm("OVDCOND equ 0F83h");


typedef union {
    struct {
        unsigned POVD :6;
    };
    struct {
        unsigned POVD0 :1;
        unsigned POVD1 :1;
        unsigned POVD2 :1;
        unsigned POVD3 :1;
        unsigned POVD4 :1;
        unsigned POVD5 :1;
    };
} OVDCONDbits_t;
extern volatile OVDCONDbits_t OVDCONDbits __attribute__((address(0xF83)));
# 608 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char DTCON __attribute__((address(0xF84)));

__asm("DTCON equ 0F84h");


typedef union {
    struct {
        unsigned DTA :6;
        unsigned DTAPS :2;
    };
    struct {
        unsigned DT0 :1;
        unsigned DT1 :1;
        unsigned DT2 :1;
        unsigned DT3 :1;
        unsigned DT4 :1;
        unsigned DT5 :1;
        unsigned DTPS0 :1;
        unsigned DTPS1 :1;
    };
} DTCONbits_t;
extern volatile DTCONbits_t DTCONbits __attribute__((address(0xF84)));
# 684 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PWMCON1 __attribute__((address(0xF85)));

__asm("PWMCON1 equ 0F85h");


typedef union {
    struct {
        unsigned OSYNC :1;
        unsigned UDIS :1;
        unsigned :1;
        unsigned SEVTDIR :1;
        unsigned SEVOPS :4;
    };
    struct {
        unsigned :4;
        unsigned SEVOPS0 :1;
        unsigned SEVOPS1 :1;
        unsigned SEVOPS2 :1;
        unsigned SEVOPS3 :1;
    };
} PWMCON1bits_t;
extern volatile PWMCON1bits_t PWMCON1bits __attribute__((address(0xF85)));
# 750 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PWMCON0 __attribute__((address(0xF86)));

__asm("PWMCON0 equ 0F86h");


typedef union {
    struct {
        unsigned PMOD :3;
        unsigned :1;
        unsigned PWMEN :3;
    };
    struct {
        unsigned PMOD0 :1;
        unsigned PMOD1 :1;
        unsigned PMOD2 :1;
        unsigned :1;
        unsigned PWMEN0 :1;
        unsigned PWMEN1 :1;
        unsigned PWMEN2 :1;
    };
} PWMCON0bits_t;
extern volatile PWMCON0bits_t PWMCON0bits __attribute__((address(0xF86)));
# 816 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char SEVTCMPH __attribute__((address(0xF87)));

__asm("SEVTCMPH equ 0F87h");


typedef union {
    struct {
        unsigned SEVTCMPH :4;
    };
} SEVTCMPHbits_t;
extern volatile SEVTCMPHbits_t SEVTCMPHbits __attribute__((address(0xF87)));
# 836 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char SEVTCMPL __attribute__((address(0xF88)));

__asm("SEVTCMPL equ 0F88h");


typedef union {
    struct {
        unsigned SEVTCMPL :8;
    };
} SEVTCMPLbits_t;
extern volatile SEVTCMPLbits_t SEVTCMPLbits __attribute__((address(0xF88)));
# 856 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char LATA __attribute__((address(0xF89)));

__asm("LATA equ 0F89h");


typedef union {
    struct {
        unsigned LATA0 :1;
        unsigned LATA1 :1;
        unsigned LATA2 :1;
        unsigned LATA3 :1;
        unsigned LATA4 :1;
        unsigned LATA5 :1;
        unsigned LATA6 :1;
        unsigned LATA7 :1;
    };
    struct {
        unsigned LA0 :1;
        unsigned LA1 :1;
        unsigned LA2 :1;
        unsigned LA3 :1;
        unsigned LA4 :1;
        unsigned LA5 :1;
        unsigned LA6 :1;
        unsigned LA7 :1;
    };
} LATAbits_t;
extern volatile LATAbits_t LATAbits __attribute__((address(0xF89)));
# 968 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char LATB __attribute__((address(0xF8A)));

__asm("LATB equ 0F8Ah");


typedef union {
    struct {
        unsigned LATB0 :1;
        unsigned LATB1 :1;
        unsigned LATB2 :1;
        unsigned LATB3 :1;
        unsigned LATB4 :1;
        unsigned LATB5 :1;
        unsigned LATB6 :1;
        unsigned LATB7 :1;
    };
    struct {
        unsigned LB0 :1;
        unsigned LB1 :1;
        unsigned LB2 :1;
        unsigned LB3 :1;
        unsigned LB4 :1;
        unsigned LB5 :1;
        unsigned LB6 :1;
        unsigned LB7 :1;
    };
} LATBbits_t;
extern volatile LATBbits_t LATBbits __attribute__((address(0xF8A)));
# 1080 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char FLTCONFIG __attribute__((address(0xF8B)));

__asm("FLTCONFIG equ 0F8Bh");


typedef union {
    struct {
        unsigned FLTAEN :1;
        unsigned FLTAMOD :1;
        unsigned FLTAS :1;
        unsigned :4;
        unsigned BRFEN :1;
    };
} FLTCONFIGbits_t;
extern volatile FLTCONFIGbits_t FLTCONFIGbits __attribute__((address(0xF8B)));
# 1119 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PDC2H __attribute__((address(0xF8C)));

__asm("PDC2H equ 0F8Ch");


typedef union {
    struct {
        unsigned PDC2H :6;
    };
} PDC2Hbits_t;
extern volatile PDC2Hbits_t PDC2Hbits __attribute__((address(0xF8C)));
# 1139 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PDC2L __attribute__((address(0xF8D)));

__asm("PDC2L equ 0F8Dh");


typedef union {
    struct {
        unsigned PDC2L :8;
    };
} PDC2Lbits_t;
extern volatile PDC2Lbits_t PDC2Lbits __attribute__((address(0xF8D)));
# 1159 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PDC1H __attribute__((address(0xF8E)));

__asm("PDC1H equ 0F8Eh");


typedef union {
    struct {
        unsigned PDC1H :6;
    };
} PDC1Hbits_t;
extern volatile PDC1Hbits_t PDC1Hbits __attribute__((address(0xF8E)));
# 1179 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PDC1L __attribute__((address(0xF8F)));

__asm("PDC1L equ 0F8Fh");


typedef union {
    struct {
        unsigned PDC1L :8;
    };
} PDC1Lbits_t;
extern volatile PDC1Lbits_t PDC1Lbits __attribute__((address(0xF8F)));
# 1199 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PDC0H __attribute__((address(0xF90)));

__asm("PDC0H equ 0F90h");


typedef union {
    struct {
        unsigned PDC0H :6;
    };
} PDC0Hbits_t;
extern volatile PDC0Hbits_t PDC0Hbits __attribute__((address(0xF90)));
# 1219 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PDC0L __attribute__((address(0xF91)));

__asm("PDC0L equ 0F91h");


typedef union {
    struct {
        unsigned PDC0L :8;
    };
} PDC0Lbits_t;
extern volatile PDC0Lbits_t PDC0Lbits __attribute__((address(0xF91)));
# 1239 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char TRISA __attribute__((address(0xF92)));

__asm("TRISA equ 0F92h");


extern volatile unsigned char DDRA __attribute__((address(0xF92)));

__asm("DDRA equ 0F92h");


typedef union {
    struct {
        unsigned TRISA0 :1;
        unsigned TRISA1 :1;
        unsigned TRISA2 :1;
        unsigned TRISA3 :1;
        unsigned TRISA4 :1;
        unsigned TRISA5 :1;
        unsigned TRISA6 :1;
        unsigned TRISA7 :1;
    };
    struct {
        unsigned RA0 :1;
        unsigned RA1 :1;
        unsigned RA2 :1;
        unsigned RA3 :1;
        unsigned RA4 :1;
        unsigned RA5 :1;
        unsigned RA6 :1;
        unsigned RA7 :1;
    };
} TRISAbits_t;
extern volatile TRISAbits_t TRISAbits __attribute__((address(0xF92)));
# 1354 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
typedef union {
    struct {
        unsigned TRISA0 :1;
        unsigned TRISA1 :1;
        unsigned TRISA2 :1;
        unsigned TRISA3 :1;
        unsigned TRISA4 :1;
        unsigned TRISA5 :1;
        unsigned TRISA6 :1;
        unsigned TRISA7 :1;
    };
    struct {
        unsigned RA0 :1;
        unsigned RA1 :1;
        unsigned RA2 :1;
        unsigned RA3 :1;
        unsigned RA4 :1;
        unsigned RA5 :1;
        unsigned RA6 :1;
        unsigned RA7 :1;
    };
} DDRAbits_t;
extern volatile DDRAbits_t DDRAbits __attribute__((address(0xF92)));
# 1461 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char TRISB __attribute__((address(0xF93)));

__asm("TRISB equ 0F93h");


extern volatile unsigned char DDRB __attribute__((address(0xF93)));

__asm("DDRB equ 0F93h");


typedef union {
    struct {
        unsigned TRISB0 :1;
        unsigned TRISB1 :1;
        unsigned TRISB2 :1;
        unsigned TRISB3 :1;
        unsigned TRISB4 :1;
        unsigned TRISB5 :1;
        unsigned TRISB6 :1;
        unsigned TRISB7 :1;
    };
    struct {
        unsigned RB0 :1;
        unsigned RB1 :1;
        unsigned RB2 :1;
        unsigned RB3 :1;
        unsigned RB4 :1;
        unsigned RB5 :1;
        unsigned RB6 :1;
        unsigned RB7 :1;
    };
} TRISBbits_t;
extern volatile TRISBbits_t TRISBbits __attribute__((address(0xF93)));
# 1576 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
typedef union {
    struct {
        unsigned TRISB0 :1;
        unsigned TRISB1 :1;
        unsigned TRISB2 :1;
        unsigned TRISB3 :1;
        unsigned TRISB4 :1;
        unsigned TRISB5 :1;
        unsigned TRISB6 :1;
        unsigned TRISB7 :1;
    };
    struct {
        unsigned RB0 :1;
        unsigned RB1 :1;
        unsigned RB2 :1;
        unsigned RB3 :1;
        unsigned RB4 :1;
        unsigned RB5 :1;
        unsigned RB6 :1;
        unsigned RB7 :1;
    };
} DDRBbits_t;
extern volatile DDRBbits_t DDRBbits __attribute__((address(0xF93)));
# 1683 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PTPERH __attribute__((address(0xF95)));

__asm("PTPERH equ 0F95h");


typedef union {
    struct {
        unsigned PTPERH :4;
    };
} PTPERHbits_t;
extern volatile PTPERHbits_t PTPERHbits __attribute__((address(0xF95)));
# 1703 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PTPERL __attribute__((address(0xF96)));

__asm("PTPERL equ 0F96h");


typedef union {
    struct {
        unsigned PTPERL :8;
    };
} PTPERLbits_t;
extern volatile PTPERLbits_t PTPERLbits __attribute__((address(0xF96)));
# 1723 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PTMRH __attribute__((address(0xF97)));

__asm("PTMRH equ 0F97h");


typedef union {
    struct {
        unsigned PTMRH :4;
    };
} PTMRHbits_t;
extern volatile PTMRHbits_t PTMRHbits __attribute__((address(0xF97)));
# 1743 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PTMRL __attribute__((address(0xF98)));

__asm("PTMRL equ 0F98h");


typedef union {
    struct {
        unsigned PTMRL :8;
    };
} PTMRLbits_t;
extern volatile PTMRLbits_t PTMRLbits __attribute__((address(0xF98)));
# 1763 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PTCON1 __attribute__((address(0xF99)));

__asm("PTCON1 equ 0F99h");


typedef union {
    struct {
        unsigned :6;
        unsigned PTDIR :1;
        unsigned PTEN :1;
    };
} PTCON1bits_t;
extern volatile PTCON1bits_t PTCON1bits __attribute__((address(0xF99)));
# 1790 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PTCON0 __attribute__((address(0xF9A)));

__asm("PTCON0 equ 0F9Ah");


typedef union {
    struct {
        unsigned PTMOD :2;
        unsigned PTCKPS :2;
        unsigned PTOPS :4;
    };
    struct {
        unsigned PTMOD0 :1;
        unsigned PTMOD1 :1;
        unsigned PTCKPS0 :1;
        unsigned PTCKPS1 :1;
        unsigned PTOPS0 :1;
        unsigned PTOPS1 :1;
        unsigned PTOPS2 :1;
        unsigned PTOPS3 :1;
    };
} PTCON0bits_t;
extern volatile PTCON0bits_t PTCON0bits __attribute__((address(0xF9A)));
# 1872 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char OSCTUNE __attribute__((address(0xF9B)));

__asm("OSCTUNE equ 0F9Bh");


typedef union {
    struct {
        unsigned TUN :5;
        unsigned :1;
        unsigned PLLEN :1;
        unsigned INTSRC :1;
    };
    struct {
        unsigned TUN0 :1;
        unsigned TUN1 :1;
        unsigned TUN2 :1;
        unsigned TUN3 :1;
        unsigned TUN4 :1;
    };
} OSCTUNEbits_t;
extern volatile OSCTUNEbits_t OSCTUNEbits __attribute__((address(0xF9B)));
# 1937 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PIE1 __attribute__((address(0xF9D)));

__asm("PIE1 equ 0F9Dh");


typedef union {
    struct {
        unsigned TMR1IE :1;
        unsigned CMP0IE :1;
        unsigned CMP1IE :1;
        unsigned CMP2IE :1;
        unsigned TXIE :1;
        unsigned RCIE :1;
        unsigned ADIE :1;
    };
    struct {
        unsigned :4;
        unsigned TX1IE :1;
        unsigned RC1IE :1;
    };
} PIE1bits_t;
extern volatile PIE1bits_t PIE1bits __attribute__((address(0xF9D)));
# 2008 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PIR1 __attribute__((address(0xF9E)));

__asm("PIR1 equ 0F9Eh");


typedef union {
    struct {
        unsigned TMR1IF :1;
        unsigned CMP0IF :1;
        unsigned CMP1IF :1;
        unsigned CMP2IF :1;
        unsigned TXIF :1;
        unsigned RCIF :1;
        unsigned ADIF :1;
    };
    struct {
        unsigned :4;
        unsigned TX1IF :1;
        unsigned RC1IF :1;
    };
} PIR1bits_t;
extern volatile PIR1bits_t PIR1bits __attribute__((address(0xF9E)));
# 2079 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char IPR1 __attribute__((address(0xF9F)));

__asm("IPR1 equ 0F9Fh");


typedef union {
    struct {
        unsigned TMR1IP :1;
        unsigned CMP0IP :1;
        unsigned CMP1IP :1;
        unsigned CMP2IP :1;
        unsigned TXIP :1;
        unsigned RCIP :1;
        unsigned ADIP :1;
    };
    struct {
        unsigned :4;
        unsigned TX1IP :1;
        unsigned RC1IP :1;
    };
} IPR1bits_t;
extern volatile IPR1bits_t IPR1bits __attribute__((address(0xF9F)));
# 2150 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PIE2 __attribute__((address(0xFA0)));

__asm("PIE2 equ 0FA0h");


typedef union {
    struct {
        unsigned :2;
        unsigned LVDIE :1;
        unsigned :1;
        unsigned EEIE :1;
        unsigned :2;
        unsigned OSCFIE :1;
    };
} PIE2bits_t;
extern volatile PIE2bits_t PIE2bits __attribute__((address(0xFA0)));
# 2185 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PIR2 __attribute__((address(0xFA1)));

__asm("PIR2 equ 0FA1h");


typedef union {
    struct {
        unsigned :2;
        unsigned LVDIF :1;
        unsigned :1;
        unsigned EEIF :1;
        unsigned :2;
        unsigned OSCFIF :1;
    };
} PIR2bits_t;
extern volatile PIR2bits_t PIR2bits __attribute__((address(0xFA1)));
# 2220 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char IPR2 __attribute__((address(0xFA2)));

__asm("IPR2 equ 0FA2h");


typedef union {
    struct {
        unsigned :2;
        unsigned LVDIP :1;
        unsigned :1;
        unsigned EEIP :1;
        unsigned :2;
        unsigned OSCFIP :1;
    };
} IPR2bits_t;
extern volatile IPR2bits_t IPR2bits __attribute__((address(0xFA2)));
# 2255 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PIE3 __attribute__((address(0xFA3)));

__asm("PIE3 equ 0FA3h");


typedef union {
    struct {
        unsigned :4;
        unsigned PTIE :1;
    };
    struct {
        unsigned :4;
        unsigned TXB2IE :1;
    };
    struct {
        unsigned :4;
        unsigned TXBNIE :1;
    };
} PIE3bits_t;
extern volatile PIE3bits_t PIE3bits __attribute__((address(0xFA3)));
# 2294 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char PIR3 __attribute__((address(0xFA4)));

__asm("PIR3 equ 0FA4h");


typedef union {
    struct {
        unsigned :4;
        unsigned PTIF :1;
    };
    struct {
        unsigned :4;
        unsigned TXBNIF :1;
    };
} PIR3bits_t;
extern volatile PIR3bits_t PIR3bits __attribute__((address(0xFA4)));
# 2324 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char IPR3 __attribute__((address(0xFA5)));

__asm("IPR3 equ 0FA5h");


typedef union {
    struct {
        unsigned :4;
        unsigned PTIP :1;
    };
    struct {
        unsigned :4;
        unsigned TXBNIP :1;
    };
} IPR3bits_t;
extern volatile IPR3bits_t IPR3bits __attribute__((address(0xFA5)));
# 2354 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char EECON1 __attribute__((address(0xFA6)));

__asm("EECON1 equ 0FA6h");


typedef union {
    struct {
        unsigned RD :1;
        unsigned WR :1;
        unsigned WREN :1;
        unsigned WRERR :1;
        unsigned FREE :1;
        unsigned :1;
        unsigned CFGS :1;
        unsigned EEPGD :1;
    };
    struct {
        unsigned :6;
        unsigned EEFS :1;
    };
} EECON1bits_t;
extern volatile EECON1bits_t EECON1bits __attribute__((address(0xFA6)));
# 2420 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char EECON2 __attribute__((address(0xFA7)));

__asm("EECON2 equ 0FA7h");




extern volatile unsigned char EEDATA __attribute__((address(0xFA8)));

__asm("EEDATA equ 0FA8h");




extern volatile unsigned char EEADR __attribute__((address(0xFA9)));

__asm("EEADR equ 0FA9h");




extern volatile unsigned char RCSTA __attribute__((address(0xFAB)));

__asm("RCSTA equ 0FABh");


extern volatile unsigned char RCSTA1 __attribute__((address(0xFAB)));

__asm("RCSTA1 equ 0FABh");


typedef union {
    struct {
        unsigned RX9D :1;
        unsigned OERR :1;
        unsigned FERR :1;
        unsigned ADEN :1;
        unsigned CREN :1;
        unsigned SREN :1;
        unsigned RX9 :1;
        unsigned SPEN :1;
    };
    struct {
        unsigned :3;
        unsigned ADDEN :1;
    };
    struct {
        unsigned :5;
        unsigned SRENA :1;
    };
    struct {
        unsigned :6;
        unsigned RC8_9 :1;
    };
    struct {
        unsigned :6;
        unsigned RC9 :1;
    };
    struct {
        unsigned RCD8 :1;
    };
} RCSTAbits_t;
extern volatile RCSTAbits_t RCSTAbits __attribute__((address(0xFAB)));
# 2550 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
typedef union {
    struct {
        unsigned RX9D :1;
        unsigned OERR :1;
        unsigned FERR :1;
        unsigned ADEN :1;
        unsigned CREN :1;
        unsigned SREN :1;
        unsigned RX9 :1;
        unsigned SPEN :1;
    };
    struct {
        unsigned :3;
        unsigned ADDEN :1;
    };
    struct {
        unsigned :5;
        unsigned SRENA :1;
    };
    struct {
        unsigned :6;
        unsigned RC8_9 :1;
    };
    struct {
        unsigned :6;
        unsigned RC9 :1;
    };
    struct {
        unsigned RCD8 :1;
    };
} RCSTA1bits_t;
extern volatile RCSTA1bits_t RCSTA1bits __attribute__((address(0xFAB)));
# 2651 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char TXSTA __attribute__((address(0xFAC)));

__asm("TXSTA equ 0FACh");


extern volatile unsigned char TXSTA1 __attribute__((address(0xFAC)));

__asm("TXSTA1 equ 0FACh");


typedef union {
    struct {
        unsigned TX9D :1;
        unsigned TRMT :1;
        unsigned BRGH :1;
        unsigned SENDB :1;
        unsigned SYNC :1;
        unsigned TXEN :1;
        unsigned TX9 :1;
        unsigned CSRC :1;
    };
    struct {
        unsigned TX9D1 :1;
        unsigned TRMT1 :1;
        unsigned BRGH1 :1;
        unsigned SENDB1 :1;
        unsigned SYNC1 :1;
        unsigned TXEN1 :1;
        unsigned TX91 :1;
        unsigned CSRC1 :1;
    };
    struct {
        unsigned :6;
        unsigned TX8_9 :1;
    };
    struct {
        unsigned TXD8 :1;
    };
} TXSTAbits_t;
extern volatile TXSTAbits_t TXSTAbits __attribute__((address(0xFAC)));
# 2783 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
typedef union {
    struct {
        unsigned TX9D :1;
        unsigned TRMT :1;
        unsigned BRGH :1;
        unsigned SENDB :1;
        unsigned SYNC :1;
        unsigned TXEN :1;
        unsigned TX9 :1;
        unsigned CSRC :1;
    };
    struct {
        unsigned TX9D1 :1;
        unsigned TRMT1 :1;
        unsigned BRGH1 :1;
        unsigned SENDB1 :1;
        unsigned SYNC1 :1;
        unsigned TXEN1 :1;
        unsigned TX91 :1;
        unsigned CSRC1 :1;
    };
    struct {
        unsigned :6;
        unsigned TX8_9 :1;
    };
    struct {
        unsigned TXD8 :1;
    };
} TXSTA1bits_t;
extern volatile TXSTA1bits_t TXSTA1bits __attribute__((address(0xFAC)));
# 2907 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char TXREG __attribute__((address(0xFAD)));

__asm("TXREG equ 0FADh");


extern volatile unsigned char TXREG1 __attribute__((address(0xFAD)));

__asm("TXREG1 equ 0FADh");




extern volatile unsigned char RCREG __attribute__((address(0xFAE)));

__asm("RCREG equ 0FAEh");


extern volatile unsigned char RCREG1 __attribute__((address(0xFAE)));

__asm("RCREG1 equ 0FAEh");




extern volatile unsigned char SPBRG __attribute__((address(0xFAF)));

__asm("SPBRG equ 0FAFh");


extern volatile unsigned char SPBRG1 __attribute__((address(0xFAF)));

__asm("SPBRG1 equ 0FAFh");




extern volatile unsigned char SPBRGH __attribute__((address(0xFB0)));

__asm("SPBRGH equ 0FB0h");




extern volatile unsigned char CMCON __attribute__((address(0xFB4)));

__asm("CMCON equ 0FB4h");


typedef union {
    struct {
        unsigned CMEN :3;
        unsigned :2;
        unsigned C0OUT :1;
        unsigned C1OUT :1;
        unsigned C2OUT :1;
    };
    struct {
        unsigned CMEN0 :1;
        unsigned CMEN1 :1;
        unsigned CMEN2 :1;
    };
    struct {
        unsigned CM0 :1;
        unsigned CM1 :1;
        unsigned CM2 :1;
        unsigned :2;
        unsigned C2INV :1;
    };
} CMCONbits_t;
extern volatile CMCONbits_t CMCONbits __attribute__((address(0xFB4)));
# 3036 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char CVRCON __attribute__((address(0xFB5)));

__asm("CVRCON equ 0FB5h");


typedef union {
    struct {
        unsigned CVR :4;
        unsigned CVRSS :1;
        unsigned CVRR :1;
        unsigned :1;
        unsigned CVREN :1;
    };
    struct {
        unsigned CVR0 :1;
        unsigned CVR1 :1;
        unsigned CVR2 :1;
        unsigned CVR3 :1;
        unsigned CVREF :1;
    };
} CVRCONbits_t;
extern volatile CVRCONbits_t CVRCONbits __attribute__((address(0xFB5)));
# 3107 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char BAUDCON __attribute__((address(0xFB8)));

__asm("BAUDCON equ 0FB8h");


extern volatile unsigned char BAUDCTL __attribute__((address(0xFB8)));

__asm("BAUDCTL equ 0FB8h");


typedef union {
    struct {
        unsigned ABDEN :1;
        unsigned WUE :1;
        unsigned :1;
        unsigned BRG16 :1;
        unsigned TXCKP :1;
        unsigned RXDTP :1;
        unsigned RCIDL :1;
        unsigned ABDOVF :1;
    };
    struct {
        unsigned :4;
        unsigned SCKP :1;
        unsigned :1;
        unsigned RCMT :1;
    };
    struct {
        unsigned :5;
        unsigned RXCKP :1;
    };
    struct {
        unsigned :1;
        unsigned W4E :1;
    };
} BAUDCONbits_t;
extern volatile BAUDCONbits_t BAUDCONbits __attribute__((address(0xFB8)));
# 3201 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
typedef union {
    struct {
        unsigned ABDEN :1;
        unsigned WUE :1;
        unsigned :1;
        unsigned BRG16 :1;
        unsigned TXCKP :1;
        unsigned RXDTP :1;
        unsigned RCIDL :1;
        unsigned ABDOVF :1;
    };
    struct {
        unsigned :4;
        unsigned SCKP :1;
        unsigned :1;
        unsigned RCMT :1;
    };
    struct {
        unsigned :5;
        unsigned RXCKP :1;
    };
    struct {
        unsigned :1;
        unsigned W4E :1;
    };
} BAUDCTLbits_t;
extern volatile BAUDCTLbits_t BAUDCTLbits __attribute__((address(0xFB8)));
# 3287 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char ADCON2 __attribute__((address(0xFC0)));

__asm("ADCON2 equ 0FC0h");


typedef union {
    struct {
        unsigned ADCS :3;
        unsigned ACQT :3;
        unsigned :1;
        unsigned ADFM :1;
    };
    struct {
        unsigned ADCS0 :1;
        unsigned ADCS1 :1;
        unsigned ADCS2 :1;
        unsigned ACQT0 :1;
        unsigned ACQT1 :1;
        unsigned ACQT2 :1;
    };
} ADCON2bits_t;
extern volatile ADCON2bits_t ADCON2bits __attribute__((address(0xFC0)));
# 3358 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char ADCON1 __attribute__((address(0xFC1)));

__asm("ADCON1 equ 0FC1h");


typedef union {
    struct {
        unsigned PCFG :4;
        unsigned VCFG :1;
    };
    struct {
        unsigned PCFG0 :1;
        unsigned PCFG1 :1;
        unsigned PCFG2 :1;
        unsigned PCFG3 :1;
        unsigned VCFG0 :1;
    };
    struct {
        unsigned :3;
        unsigned CHSN3 :1;
        unsigned VCFG01 :1;
    };
} ADCON1bits_t;
extern volatile ADCON1bits_t ADCON1bits __attribute__((address(0xFC1)));
# 3431 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char ADCON0 __attribute__((address(0xFC2)));

__asm("ADCON0 equ 0FC2h");


typedef union {
    struct {
        unsigned :1;
        unsigned GO_NOT_DONE :1;
    };
    struct {
        unsigned ADON :1;
        unsigned GO_nDONE :1;
        unsigned CHS :2;
        unsigned :3;
        unsigned SEVTEN :1;
    };
    struct {
        unsigned :1;
        unsigned GO :1;
        unsigned CHS0 :1;
        unsigned CHS1 :1;
    };
    struct {
        unsigned :1;
        unsigned DONE :1;
    };
    struct {
        unsigned :1;
        unsigned NOT_DONE :1;
    };
    struct {
        unsigned :1;
        unsigned nDONE :1;
    };
    struct {
        unsigned :1;
        unsigned GO_DONE :1;
    };
    struct {
        unsigned :1;
        unsigned GODONE :1;
        unsigned :5;
        unsigned ADCAL :1;
    };
} ADCON0bits_t;
extern volatile ADCON0bits_t ADCON0bits __attribute__((address(0xFC2)));
# 3552 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned short ADRES __attribute__((address(0xFC3)));

__asm("ADRES equ 0FC3h");




extern volatile unsigned char ADRESL __attribute__((address(0xFC3)));

__asm("ADRESL equ 0FC3h");




extern volatile unsigned char ADRESH __attribute__((address(0xFC4)));

__asm("ADRESH equ 0FC4h");




extern volatile unsigned char T1CON __attribute__((address(0xFCD)));

__asm("T1CON equ 0FCDh");


typedef union {
    struct {
        unsigned :2;
        unsigned NOT_T1SYNC :1;
    };
    struct {
        unsigned TMR1ON :1;
        unsigned TMR1CS :1;
        unsigned nT1SYNC :1;
        unsigned T1OSCEN :1;
        unsigned T1CKPS :2;
        unsigned T1RUN :1;
        unsigned RD16 :1;
    };
    struct {
        unsigned :4;
        unsigned T1CKPS0 :1;
        unsigned T1CKPS1 :1;
    };
    struct {
        unsigned :2;
        unsigned T1SYNC :1;
    };
    struct {
        unsigned :3;
        unsigned SOSCEN :1;
        unsigned :3;
        unsigned T1RD16 :1;
    };
} T1CONbits_t;
extern volatile T1CONbits_t T1CONbits __attribute__((address(0xFCD)));
# 3678 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned short TMR1 __attribute__((address(0xFCE)));

__asm("TMR1 equ 0FCEh");




extern volatile unsigned char TMR1L __attribute__((address(0xFCE)));

__asm("TMR1L equ 0FCEh");




extern volatile unsigned char TMR1H __attribute__((address(0xFCF)));

__asm("TMR1H equ 0FCFh");




extern volatile unsigned char RCON __attribute__((address(0xFD0)));

__asm("RCON equ 0FD0h");


typedef union {
    struct {
        unsigned NOT_BOR :1;
    };
    struct {
        unsigned :1;
        unsigned NOT_POR :1;
    };
    struct {
        unsigned :2;
        unsigned NOT_PD :1;
    };
    struct {
        unsigned :3;
        unsigned NOT_TO :1;
    };
    struct {
        unsigned :4;
        unsigned NOT_RI :1;
    };
    struct {
        unsigned nBOR :1;
        unsigned nPOR :1;
        unsigned nPD :1;
        unsigned nTO :1;
        unsigned nRI :1;
        unsigned :1;
        unsigned SBOREN :1;
        unsigned IPEN :1;
    };
    struct {
        unsigned BOR :1;
        unsigned POR :1;
        unsigned PD :1;
        unsigned TO :1;
        unsigned RI :1;
    };
} RCONbits_t;
extern volatile RCONbits_t RCONbits __attribute__((address(0xFD0)));
# 3832 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char WDTCON __attribute__((address(0xFD1)));

__asm("WDTCON equ 0FD1h");


typedef union {
    struct {
        unsigned SWDTEN :1;
    };
    struct {
        unsigned SWDTE :1;
    };
} WDTCONbits_t;
extern volatile WDTCONbits_t WDTCONbits __attribute__((address(0xFD1)));
# 3860 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char LVDCON __attribute__((address(0xFD2)));

__asm("LVDCON equ 0FD2h");


typedef union {
    struct {
        unsigned LVDL :4;
        unsigned LVDEN :1;
        unsigned IRVST :1;
    };
    struct {
        unsigned LVDL0 :1;
        unsigned LVDL1 :1;
        unsigned LVDL2 :1;
        unsigned LVDL3 :1;
        unsigned :1;
        unsigned IVRST :1;
    };
} LVDCONbits_t;
extern volatile LVDCONbits_t LVDCONbits __attribute__((address(0xFD2)));
# 3925 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char OSCCON __attribute__((address(0xFD3)));

__asm("OSCCON equ 0FD3h");


typedef union {
    struct {
        unsigned SCS :2;
        unsigned IOFS :1;
        unsigned OSTS :1;
        unsigned IRCF :3;
        unsigned IDLEN :1;
    };
    struct {
        unsigned SCS0 :1;
        unsigned SCS1 :1;
        unsigned FLTS :1;
        unsigned :1;
        unsigned IRCF0 :1;
        unsigned IRCF1 :1;
        unsigned IRCF2 :1;
    };
} OSCCONbits_t;
extern volatile OSCCONbits_t OSCCONbits __attribute__((address(0xFD3)));
# 4008 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char T0CON __attribute__((address(0xFD5)));

__asm("T0CON equ 0FD5h");


typedef union {
    struct {
        unsigned T0PS :3;
        unsigned PSA :1;
        unsigned T0SE :1;
        unsigned T0CS :1;
        unsigned T016BIT :1;
        unsigned TMR0ON :1;
    };
    struct {
        unsigned T0PS0 :1;
        unsigned T0PS1 :1;
        unsigned T0PS2 :1;
    };
    struct {
        unsigned :6;
        unsigned T08BIT :1;
    };
} T0CONbits_t;
extern volatile T0CONbits_t T0CONbits __attribute__((address(0xFD5)));
# 4087 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned short TMR0 __attribute__((address(0xFD6)));

__asm("TMR0 equ 0FD6h");




extern volatile unsigned char TMR0L __attribute__((address(0xFD6)));

__asm("TMR0L equ 0FD6h");




extern volatile unsigned char TMR0H __attribute__((address(0xFD7)));

__asm("TMR0H equ 0FD7h");




extern volatile unsigned char STATUS __attribute__((address(0xFD8)));

__asm("STATUS equ 0FD8h");


typedef union {
    struct {
        unsigned C :1;
        unsigned DC :1;
        unsigned Z :1;
        unsigned OV :1;
        unsigned N :1;
    };
    struct {
        unsigned CARRY :1;
        unsigned :1;
        unsigned ZERO :1;
        unsigned OVERFLOW :1;
        unsigned NEGATIVE :1;
    };
} STATUSbits_t;
extern volatile STATUSbits_t STATUSbits __attribute__((address(0xFD8)));
# 4179 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned short FSR2 __attribute__((address(0xFD9)));

__asm("FSR2 equ 0FD9h");




extern volatile unsigned char FSR2L __attribute__((address(0xFD9)));

__asm("FSR2L equ 0FD9h");




extern volatile unsigned char FSR2H __attribute__((address(0xFDA)));

__asm("FSR2H equ 0FDAh");




extern volatile unsigned char PLUSW2 __attribute__((address(0xFDB)));

__asm("PLUSW2 equ 0FDBh");




extern volatile unsigned char PREINC2 __attribute__((address(0xFDC)));

__asm("PREINC2 equ 0FDCh");




extern volatile unsigned char POSTDEC2 __attribute__((address(0xFDD)));

__asm("POSTDEC2 equ 0FDDh");




extern volatile unsigned char POSTINC2 __attribute__((address(0xFDE)));

__asm("POSTINC2 equ 0FDEh");




extern volatile unsigned char INDF2 __attribute__((address(0xFDF)));

__asm("INDF2 equ 0FDFh");




extern volatile unsigned char BSR __attribute__((address(0xFE0)));

__asm("BSR equ 0FE0h");




extern volatile unsigned short FSR1 __attribute__((address(0xFE1)));

__asm("FSR1 equ 0FE1h");




extern volatile unsigned char FSR1L __attribute__((address(0xFE1)));

__asm("FSR1L equ 0FE1h");




extern volatile unsigned char FSR1H __attribute__((address(0xFE2)));

__asm("FSR1H equ 0FE2h");




extern volatile unsigned char PLUSW1 __attribute__((address(0xFE3)));

__asm("PLUSW1 equ 0FE3h");




extern volatile unsigned char PREINC1 __attribute__((address(0xFE4)));

__asm("PREINC1 equ 0FE4h");




extern volatile unsigned char POSTDEC1 __attribute__((address(0xFE5)));

__asm("POSTDEC1 equ 0FE5h");




extern volatile unsigned char POSTINC1 __attribute__((address(0xFE6)));

__asm("POSTINC1 equ 0FE6h");




extern volatile unsigned char INDF1 __attribute__((address(0xFE7)));

__asm("INDF1 equ 0FE7h");




extern volatile unsigned char WREG __attribute__((address(0xFE8)));

__asm("WREG equ 0FE8h");
# 4310 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned short FSR0 __attribute__((address(0xFE9)));

__asm("FSR0 equ 0FE9h");




extern volatile unsigned char FSR0L __attribute__((address(0xFE9)));

__asm("FSR0L equ 0FE9h");




extern volatile unsigned char FSR0H __attribute__((address(0xFEA)));

__asm("FSR0H equ 0FEAh");




extern volatile unsigned char PLUSW0 __attribute__((address(0xFEB)));

__asm("PLUSW0 equ 0FEBh");




extern volatile unsigned char PREINC0 __attribute__((address(0xFEC)));

__asm("PREINC0 equ 0FECh");




extern volatile unsigned char POSTDEC0 __attribute__((address(0xFED)));

__asm("POSTDEC0 equ 0FEDh");




extern volatile unsigned char POSTINC0 __attribute__((address(0xFEE)));

__asm("POSTINC0 equ 0FEEh");




extern volatile unsigned char INDF0 __attribute__((address(0xFEF)));

__asm("INDF0 equ 0FEFh");




extern volatile unsigned char INTCON3 __attribute__((address(0xFF0)));

__asm("INTCON3 equ 0FF0h");


typedef union {
    struct {
        unsigned INT1IF :1;
        unsigned INT2IF :1;
        unsigned INT3IF :1;
        unsigned INT1IE :1;
        unsigned INT2IE :1;
        unsigned INT3IE :1;
        unsigned INT1IP :1;
        unsigned INT2IP :1;
    };
    struct {
        unsigned INT1F :1;
        unsigned INT2F :1;
        unsigned INT3F :1;
        unsigned INT1E :1;
        unsigned INT2E :1;
        unsigned INT3E :1;
        unsigned INT1P :1;
        unsigned INT2P :1;
    };
} INTCON3bits_t;
extern volatile INTCON3bits_t INTCON3bits __attribute__((address(0xFF0)));
# 4478 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char INTCON2 __attribute__((address(0xFF1)));

__asm("INTCON2 equ 0FF1h");


typedef union {
    struct {
        unsigned :7;
        unsigned NOT_RBPU :1;
    };
    struct {
        unsigned RBIP :1;
        unsigned INT3IP :1;
        unsigned TMR0IP :1;
        unsigned INTEDG3 :1;
        unsigned INTEDG2 :1;
        unsigned INTEDG1 :1;
        unsigned INTEDG0 :1;
        unsigned nRBPU :1;
    };
    struct {
        unsigned :1;
        unsigned INT3P :1;
        unsigned :5;
        unsigned RBPU :1;
    };
} INTCON2bits_t;
extern volatile INTCON2bits_t INTCON2bits __attribute__((address(0xFF1)));
# 4565 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned char INTCON __attribute__((address(0xFF2)));

__asm("INTCON equ 0FF2h");


typedef union {
    struct {
        unsigned RBIF :1;
        unsigned INT0IF :1;
        unsigned TMR0IF :1;
        unsigned RBIE :1;
        unsigned INT0IE :1;
        unsigned TMR0IE :1;
        unsigned PEIE_GIEL :1;
        unsigned GIE_GIEH :1;
    };
    struct {
        unsigned :1;
        unsigned INT0F :1;
        unsigned T0IF :1;
        unsigned :1;
        unsigned INT0E :1;
        unsigned T0IE :1;
        unsigned PEIE :1;
        unsigned GIE :1;
    };
    struct {
        unsigned :6;
        unsigned GIEL :1;
        unsigned GIEH :1;
    };
} INTCONbits_t;
extern volatile INTCONbits_t INTCONbits __attribute__((address(0xFF2)));
# 4682 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile unsigned short PROD __attribute__((address(0xFF3)));

__asm("PROD equ 0FF3h");




extern volatile unsigned char PRODL __attribute__((address(0xFF3)));

__asm("PRODL equ 0FF3h");




extern volatile unsigned char PRODH __attribute__((address(0xFF4)));

__asm("PRODH equ 0FF4h");




extern volatile unsigned char TABLAT __attribute__((address(0xFF5)));

__asm("TABLAT equ 0FF5h");





extern volatile __uint24 TBLPTR __attribute__((address(0xFF6)));


__asm("TBLPTR equ 0FF6h");




extern volatile unsigned char TBLPTRL __attribute__((address(0xFF6)));

__asm("TBLPTRL equ 0FF6h");




extern volatile unsigned char TBLPTRH __attribute__((address(0xFF7)));

__asm("TBLPTRH equ 0FF7h");




extern volatile unsigned char TBLPTRU __attribute__((address(0xFF8)));

__asm("TBLPTRU equ 0FF8h");





extern volatile __uint24 PCLAT __attribute__((address(0xFF9)));


__asm("PCLAT equ 0FF9h");



extern volatile __uint24 PC __attribute__((address(0xFF9)));


__asm("PC equ 0FF9h");




extern volatile unsigned char PCL __attribute__((address(0xFF9)));

__asm("PCL equ 0FF9h");




extern volatile unsigned char PCLATH __attribute__((address(0xFFA)));

__asm("PCLATH equ 0FFAh");




extern volatile unsigned char PCLATU __attribute__((address(0xFFB)));

__asm("PCLATU equ 0FFBh");




extern volatile unsigned char STKPTR __attribute__((address(0xFFC)));

__asm("STKPTR equ 0FFCh");


typedef union {
    struct {
        unsigned STKPTR :5;
        unsigned :1;
        unsigned STKUNF :1;
        unsigned STKFUL :1;
    };
    struct {
        unsigned SP0 :1;
        unsigned SP1 :1;
        unsigned SP2 :1;
        unsigned SP3 :1;
        unsigned SP4 :1;
        unsigned :2;
        unsigned STKOVF :1;
    };
} STKPTRbits_t;
extern volatile STKPTRbits_t STKPTRbits __attribute__((address(0xFFC)));
# 4850 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile __uint24 TOS __attribute__((address(0xFFD)));


__asm("TOS equ 0FFDh");




extern volatile unsigned char TOSL __attribute__((address(0xFFD)));

__asm("TOSL equ 0FFDh");




extern volatile unsigned char TOSH __attribute__((address(0xFFE)));

__asm("TOSH equ 0FFEh");




extern volatile unsigned char TOSU __attribute__((address(0xFFF)));

__asm("TOSU equ 0FFFh");
# 4889 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include\\proc/pic18f1330.h" 3
extern volatile __bit ABDEN __attribute__((address(0x7DC0)));


extern volatile __bit ABDOVF __attribute__((address(0x7DC7)));


extern volatile __bit ACQT0 __attribute__((address(0x7E03)));


extern volatile __bit ACQT1 __attribute__((address(0x7E04)));


extern volatile __bit ACQT2 __attribute__((address(0x7E05)));


extern volatile __bit ADCAL __attribute__((address(0x7E17)));


extern volatile __bit ADCS0 __attribute__((address(0x7E00)));


extern volatile __bit ADCS1 __attribute__((address(0x7E01)));


extern volatile __bit ADCS2 __attribute__((address(0x7E02)));


extern volatile __bit ADDEN __attribute__((address(0x7D5B)));


extern volatile __bit ADEN __attribute__((address(0x7D5B)));


extern volatile __bit ADFM __attribute__((address(0x7E07)));


extern volatile __bit ADIE __attribute__((address(0x7CEE)));


extern volatile __bit ADIF __attribute__((address(0x7CF6)));


extern volatile __bit ADIP __attribute__((address(0x7CFE)));


extern volatile __bit ADON __attribute__((address(0x7E10)));


extern volatile __bit AN0 __attribute__((address(0x7C00)));


extern volatile __bit AN1 __attribute__((address(0x7C01)));


extern volatile __bit AN2 __attribute__((address(0x7C04)));


extern volatile __bit AN3 __attribute__((address(0x7C06)));


extern volatile __bit BOR __attribute__((address(0x7E80)));


extern volatile __bit BRFEN __attribute__((address(0x7C5F)));


extern volatile __bit BRG16 __attribute__((address(0x7DC3)));


extern volatile __bit BRGH __attribute__((address(0x7D62)));


extern volatile __bit BRGH1 __attribute__((address(0x7D62)));


extern volatile __bit C0OUT __attribute__((address(0x7DA5)));


extern volatile __bit C1OUT __attribute__((address(0x7DA6)));


extern volatile __bit C2INV __attribute__((address(0x7DA5)));


extern volatile __bit C2OUT __attribute__((address(0x7DA7)));


extern volatile __bit CARRY __attribute__((address(0x7EC0)));


extern volatile __bit CCP2_PA2 __attribute__((address(0x7C0B)));


extern volatile __bit CFGS __attribute__((address(0x7D36)));


extern volatile __bit CHS0 __attribute__((address(0x7E12)));


extern volatile __bit CHS1 __attribute__((address(0x7E13)));


extern volatile __bit CHSN3 __attribute__((address(0x7E0B)));


extern volatile __bit CK __attribute__((address(0x7C02)));


extern volatile __bit CLKI __attribute__((address(0x7C07)));


extern volatile __bit CLKO __attribute__((address(0x7C06)));


extern volatile __bit CM0 __attribute__((address(0x7DA0)));


extern volatile __bit CM1 __attribute__((address(0x7DA1)));


extern volatile __bit CM2 __attribute__((address(0x7DA2)));


extern volatile __bit CMEN0 __attribute__((address(0x7DA0)));


extern volatile __bit CMEN1 __attribute__((address(0x7DA1)));


extern volatile __bit CMEN2 __attribute__((address(0x7DA2)));


extern volatile __bit CMP0 __attribute__((address(0x7C00)));


extern volatile __bit CMP0IE __attribute__((address(0x7CE9)));


extern volatile __bit CMP0IF __attribute__((address(0x7CF1)));


extern volatile __bit CMP0IP __attribute__((address(0x7CF9)));


extern volatile __bit CMP1 __attribute__((address(0x7C0B)));


extern volatile __bit CMP1IE __attribute__((address(0x7CEA)));


extern volatile __bit CMP1IF __attribute__((address(0x7CF2)));


extern volatile __bit CMP1IP __attribute__((address(0x7CFA)));


extern volatile __bit CMP2 __attribute__((address(0x7C0A)));


extern volatile __bit CMP2IE __attribute__((address(0x7CEB)));


extern volatile __bit CMP2IF __attribute__((address(0x7CF3)));


extern volatile __bit CMP2IP __attribute__((address(0x7CFB)));


extern volatile __bit CREN __attribute__((address(0x7D5C)));


extern volatile __bit CSRC __attribute__((address(0x7D67)));


extern volatile __bit CSRC1 __attribute__((address(0x7D67)));


extern volatile __bit CVR0 __attribute__((address(0x7DA8)));


extern volatile __bit CVR1 __attribute__((address(0x7DA9)));


extern volatile __bit CVR2 __attribute__((address(0x7DAA)));


extern volatile __bit CVR3 __attribute__((address(0x7DAB)));


extern volatile __bit CVREF __attribute__((address(0x7DAC)));


extern volatile __bit CVREN __attribute__((address(0x7DAF)));


extern volatile __bit CVRR __attribute__((address(0x7DAD)));


extern volatile __bit CVRSS __attribute__((address(0x7DAC)));


extern volatile __bit DC __attribute__((address(0x7EC1)));


extern volatile __bit DONE __attribute__((address(0x7E11)));


extern volatile __bit DT __attribute__((address(0x7C03)));


extern volatile __bit DT0 __attribute__((address(0x7C20)));


extern volatile __bit DT1 __attribute__((address(0x7C21)));


extern volatile __bit DT2 __attribute__((address(0x7C22)));


extern volatile __bit DT3 __attribute__((address(0x7C23)));


extern volatile __bit DT4 __attribute__((address(0x7C24)));


extern volatile __bit DT5 __attribute__((address(0x7C25)));


extern volatile __bit DTPS0 __attribute__((address(0x7C26)));


extern volatile __bit DTPS1 __attribute__((address(0x7C27)));


extern volatile __bit EEFS __attribute__((address(0x7D36)));


extern volatile __bit EEIE __attribute__((address(0x7D04)));


extern volatile __bit EEIF __attribute__((address(0x7D0C)));


extern volatile __bit EEIP __attribute__((address(0x7D14)));


extern volatile __bit EEPGD __attribute__((address(0x7D37)));


extern volatile __bit FERR __attribute__((address(0x7D5A)));


extern volatile __bit FLTAEN __attribute__((address(0x7C58)));


extern volatile __bit FLTAMOD __attribute__((address(0x7C59)));


extern volatile __bit FLTAS __attribute__((address(0x7C5A)));


extern volatile __bit FLTS __attribute__((address(0x7E9A)));


extern volatile __bit FREE __attribute__((address(0x7D34)));


extern volatile __bit GIE __attribute__((address(0x7F97)));


extern volatile __bit GIEH __attribute__((address(0x7F97)));


extern volatile __bit GIEL __attribute__((address(0x7F96)));


extern volatile __bit GIE_GIEH __attribute__((address(0x7F97)));


extern volatile __bit GO __attribute__((address(0x7E11)));


extern volatile __bit GODONE __attribute__((address(0x7E11)));


extern volatile __bit GO_DONE __attribute__((address(0x7E11)));


extern volatile __bit GO_NOT_DONE __attribute__((address(0x7E11)));


extern volatile __bit GO_nDONE __attribute__((address(0x7E11)));


extern volatile __bit IDLEN __attribute__((address(0x7E9F)));


extern volatile __bit INT0 __attribute__((address(0x7C00)));


extern volatile __bit INT0E __attribute__((address(0x7F94)));


extern volatile __bit INT0F __attribute__((address(0x7F91)));


extern volatile __bit INT0IE __attribute__((address(0x7F94)));


extern volatile __bit INT0IF __attribute__((address(0x7F91)));


extern volatile __bit INT1 __attribute__((address(0x7C01)));


extern volatile __bit INT1E __attribute__((address(0x7F83)));


extern volatile __bit INT1F __attribute__((address(0x7F80)));


extern volatile __bit INT1IE __attribute__((address(0x7F83)));


extern volatile __bit INT1IF __attribute__((address(0x7F80)));


extern volatile __bit INT1IP __attribute__((address(0x7F86)));


extern volatile __bit INT1P __attribute__((address(0x7F86)));


extern volatile __bit INT2 __attribute__((address(0x7C0A)));


extern volatile __bit INT2E __attribute__((address(0x7F84)));


extern volatile __bit INT2F __attribute__((address(0x7F81)));


extern volatile __bit INT2IE __attribute__((address(0x7F84)));


extern volatile __bit INT2IF __attribute__((address(0x7F81)));


extern volatile __bit INT2IP __attribute__((address(0x7F87)));


extern volatile __bit INT2P __attribute__((address(0x7F87)));


extern volatile __bit INT3 __attribute__((address(0x7C0B)));


extern volatile __bit INT3E __attribute__((address(0x7F85)));


extern volatile __bit INT3F __attribute__((address(0x7F82)));


extern volatile __bit INT3IE __attribute__((address(0x7F85)));


extern volatile __bit INT3IF __attribute__((address(0x7F82)));


extern volatile __bit INT3IP __attribute__((address(0x7F89)));


extern volatile __bit INT3P __attribute__((address(0x7F89)));


extern volatile __bit INTEDG0 __attribute__((address(0x7F8E)));


extern volatile __bit INTEDG1 __attribute__((address(0x7F8D)));


extern volatile __bit INTEDG2 __attribute__((address(0x7F8C)));


extern volatile __bit INTEDG3 __attribute__((address(0x7F8B)));


extern volatile __bit INTSRC __attribute__((address(0x7CDF)));


extern volatile __bit IOFS __attribute__((address(0x7E9A)));


extern volatile __bit IPEN __attribute__((address(0x7E87)));


extern volatile __bit IRCF0 __attribute__((address(0x7E9C)));


extern volatile __bit IRCF1 __attribute__((address(0x7E9D)));


extern volatile __bit IRCF2 __attribute__((address(0x7E9E)));


extern volatile __bit IRVST __attribute__((address(0x7E95)));


extern volatile __bit IVRST __attribute__((address(0x7E95)));


extern volatile __bit KBI0 __attribute__((address(0x7C00)));


extern volatile __bit KBI1 __attribute__((address(0x7C01)));


extern volatile __bit KBI2 __attribute__((address(0x7C0A)));


extern volatile __bit KBI3 __attribute__((address(0x7C0B)));


extern volatile __bit LA0 __attribute__((address(0x7C48)));


extern volatile __bit LA1 __attribute__((address(0x7C49)));


extern volatile __bit LA2 __attribute__((address(0x7C4A)));


extern volatile __bit LA3 __attribute__((address(0x7C4B)));


extern volatile __bit LA4 __attribute__((address(0x7C4C)));


extern volatile __bit LA5 __attribute__((address(0x7C4D)));


extern volatile __bit LA6 __attribute__((address(0x7C4E)));


extern volatile __bit LA7 __attribute__((address(0x7C4F)));


extern volatile __bit LATA0 __attribute__((address(0x7C48)));


extern volatile __bit LATA1 __attribute__((address(0x7C49)));


extern volatile __bit LATA2 __attribute__((address(0x7C4A)));


extern volatile __bit LATA3 __attribute__((address(0x7C4B)));


extern volatile __bit LATA4 __attribute__((address(0x7C4C)));


extern volatile __bit LATA5 __attribute__((address(0x7C4D)));


extern volatile __bit LATA6 __attribute__((address(0x7C4E)));


extern volatile __bit LATA7 __attribute__((address(0x7C4F)));


extern volatile __bit LATB0 __attribute__((address(0x7C50)));


extern volatile __bit LATB1 __attribute__((address(0x7C51)));


extern volatile __bit LATB2 __attribute__((address(0x7C52)));


extern volatile __bit LATB3 __attribute__((address(0x7C53)));


extern volatile __bit LATB4 __attribute__((address(0x7C54)));


extern volatile __bit LATB5 __attribute__((address(0x7C55)));


extern volatile __bit LATB6 __attribute__((address(0x7C56)));


extern volatile __bit LATB7 __attribute__((address(0x7C57)));


extern volatile __bit LB0 __attribute__((address(0x7C50)));


extern volatile __bit LB1 __attribute__((address(0x7C51)));


extern volatile __bit LB2 __attribute__((address(0x7C52)));


extern volatile __bit LB3 __attribute__((address(0x7C53)));


extern volatile __bit LB4 __attribute__((address(0x7C54)));


extern volatile __bit LB5 __attribute__((address(0x7C55)));


extern volatile __bit LB6 __attribute__((address(0x7C56)));


extern volatile __bit LB7 __attribute__((address(0x7C57)));


extern volatile __bit LVDEN __attribute__((address(0x7E94)));


extern volatile __bit LVDIE __attribute__((address(0x7D02)));


extern volatile __bit LVDIF __attribute__((address(0x7D0A)));


extern volatile __bit LVDIN __attribute__((address(0x7C05)));


extern volatile __bit LVDIP __attribute__((address(0x7D12)));


extern volatile __bit LVDL0 __attribute__((address(0x7E90)));


extern volatile __bit LVDL1 __attribute__((address(0x7E91)));


extern volatile __bit LVDL2 __attribute__((address(0x7E92)));


extern volatile __bit LVDL3 __attribute__((address(0x7E93)));


extern volatile __bit MCLR __attribute__((address(0x7C05)));


extern volatile __bit NEGATIVE __attribute__((address(0x7EC4)));


extern volatile __bit NOT_BOR __attribute__((address(0x7E80)));


extern volatile __bit NOT_DONE __attribute__((address(0x7E11)));


extern volatile __bit NOT_MCLR __attribute__((address(0x7C05)));


extern volatile __bit NOT_PD __attribute__((address(0x7E82)));


extern volatile __bit NOT_POR __attribute__((address(0x7E81)));


extern volatile __bit NOT_RBPU __attribute__((address(0x7F8F)));


extern volatile __bit NOT_RI __attribute__((address(0x7E84)));


extern volatile __bit NOT_T1SYNC __attribute__((address(0x7E6A)));


extern volatile __bit NOT_TO __attribute__((address(0x7E83)));


extern volatile __bit OERR __attribute__((address(0x7D59)));


extern volatile __bit OSC1 __attribute__((address(0x7C07)));


extern volatile __bit OSC2 __attribute__((address(0x7C06)));


extern volatile __bit OSCFIE __attribute__((address(0x7D07)));


extern volatile __bit OSCFIF __attribute__((address(0x7D0F)));


extern volatile __bit OSCFIP __attribute__((address(0x7D17)));


extern volatile __bit OSTS __attribute__((address(0x7E9B)));


extern volatile __bit OSYNC __attribute__((address(0x7C28)));


extern volatile __bit OV __attribute__((address(0x7EC3)));


extern volatile __bit OVERFLOW __attribute__((address(0x7EC3)));


extern volatile __bit PCFG0 __attribute__((address(0x7E08)));


extern volatile __bit PCFG1 __attribute__((address(0x7E09)));


extern volatile __bit PCFG2 __attribute__((address(0x7E0A)));


extern volatile __bit PCFG3 __attribute__((address(0x7E0B)));


extern volatile __bit PD __attribute__((address(0x7E82)));


extern volatile __bit PEIE __attribute__((address(0x7F96)));


extern volatile __bit PEIE_GIEL __attribute__((address(0x7F96)));


extern volatile __bit PGC __attribute__((address(0x7C0E)));


extern volatile __bit PGD __attribute__((address(0x7C0F)));


extern volatile __bit PLLEN __attribute__((address(0x7CDE)));


extern volatile __bit PMOD0 __attribute__((address(0x7C30)));


extern volatile __bit PMOD1 __attribute__((address(0x7C31)));


extern volatile __bit PMOD2 __attribute__((address(0x7C32)));


extern volatile __bit POR __attribute__((address(0x7E81)));


extern volatile __bit POUT0 __attribute__((address(0x7C10)));


extern volatile __bit POUT1 __attribute__((address(0x7C11)));


extern volatile __bit POUT2 __attribute__((address(0x7C12)));


extern volatile __bit POUT3 __attribute__((address(0x7C13)));


extern volatile __bit POUT4 __attribute__((address(0x7C14)));


extern volatile __bit POUT5 __attribute__((address(0x7C15)));


extern volatile __bit POVD0 __attribute__((address(0x7C18)));


extern volatile __bit POVD1 __attribute__((address(0x7C19)));


extern volatile __bit POVD2 __attribute__((address(0x7C1A)));


extern volatile __bit POVD3 __attribute__((address(0x7C1B)));


extern volatile __bit POVD4 __attribute__((address(0x7C1C)));


extern volatile __bit POVD5 __attribute__((address(0x7C1D)));


extern volatile __bit PSA __attribute__((address(0x7EAB)));


extern volatile __bit PTCKPS0 __attribute__((address(0x7CD2)));


extern volatile __bit PTCKPS1 __attribute__((address(0x7CD3)));


extern volatile __bit PTDIR __attribute__((address(0x7CCE)));


extern volatile __bit PTEN __attribute__((address(0x7CCF)));


extern volatile __bit PTIE __attribute__((address(0x7D1C)));


extern volatile __bit PTIF __attribute__((address(0x7D24)));


extern volatile __bit PTIP __attribute__((address(0x7D2C)));


extern volatile __bit PTMOD0 __attribute__((address(0x7CD0)));


extern volatile __bit PTMOD1 __attribute__((address(0x7CD1)));


extern volatile __bit PTOPS0 __attribute__((address(0x7CD4)));


extern volatile __bit PTOPS1 __attribute__((address(0x7CD5)));


extern volatile __bit PTOPS2 __attribute__((address(0x7CD6)));


extern volatile __bit PTOPS3 __attribute__((address(0x7CD7)));


extern volatile __bit PWM0 __attribute__((address(0x7C08)));


extern volatile __bit PWM1 __attribute__((address(0x7C09)));


extern volatile __bit PWM2 __attribute__((address(0x7C0C)));


extern volatile __bit PWM3 __attribute__((address(0x7C0D)));


extern volatile __bit PWM4 __attribute__((address(0x7C0E)));


extern volatile __bit PWM5 __attribute__((address(0x7C0F)));


extern volatile __bit PWMEN0 __attribute__((address(0x7C34)));


extern volatile __bit PWMEN1 __attribute__((address(0x7C35)));


extern volatile __bit PWMEN2 __attribute__((address(0x7C36)));


extern volatile __bit __attribute__((__deprecated__)) RA0 __attribute__((address(0x7C00)));


extern volatile __bit __attribute__((__deprecated__)) RA1 __attribute__((address(0x7C01)));


extern volatile __bit __attribute__((__deprecated__)) RA2 __attribute__((address(0x7C02)));


extern volatile __bit __attribute__((__deprecated__)) RA3 __attribute__((address(0x7C03)));


extern volatile __bit __attribute__((__deprecated__)) RA4 __attribute__((address(0x7C04)));


extern volatile __bit __attribute__((__deprecated__)) RA5 __attribute__((address(0x7C05)));


extern volatile __bit __attribute__((__deprecated__)) RA6 __attribute__((address(0x7C06)));


extern volatile __bit __attribute__((__deprecated__)) RA7 __attribute__((address(0x7C07)));


extern volatile __bit __attribute__((__deprecated__)) RB0 __attribute__((address(0x7C08)));


extern volatile __bit __attribute__((__deprecated__)) RB1 __attribute__((address(0x7C09)));


extern volatile __bit __attribute__((__deprecated__)) RB2 __attribute__((address(0x7C0A)));


extern volatile __bit __attribute__((__deprecated__)) RB3 __attribute__((address(0x7C0B)));


extern volatile __bit __attribute__((__deprecated__)) RB4 __attribute__((address(0x7C0C)));


extern volatile __bit __attribute__((__deprecated__)) RB5 __attribute__((address(0x7C0D)));


extern volatile __bit __attribute__((__deprecated__)) RB6 __attribute__((address(0x7C0E)));


extern volatile __bit __attribute__((__deprecated__)) RB7 __attribute__((address(0x7C0F)));


extern volatile __bit RBIE __attribute__((address(0x7F93)));


extern volatile __bit RBIF __attribute__((address(0x7F90)));


extern volatile __bit RBIP __attribute__((address(0x7F88)));


extern volatile __bit RBPU __attribute__((address(0x7F8F)));


extern volatile __bit RC1IE __attribute__((address(0x7CED)));


extern volatile __bit RC1IF __attribute__((address(0x7CF5)));


extern volatile __bit RC1IP __attribute__((address(0x7CFD)));


extern volatile __bit RC8_9 __attribute__((address(0x7D5E)));


extern volatile __bit RC9 __attribute__((address(0x7D5E)));


extern volatile __bit RCD8 __attribute__((address(0x7D58)));


extern volatile __bit RCIDL __attribute__((address(0x7DC6)));


extern volatile __bit RCIE __attribute__((address(0x7CED)));


extern volatile __bit RCIF __attribute__((address(0x7CF5)));


extern volatile __bit RCIP __attribute__((address(0x7CFD)));


extern volatile __bit RCMT __attribute__((address(0x7DC6)));


extern volatile __bit RD __attribute__((address(0x7D30)));


extern volatile __bit RD16 __attribute__((address(0x7E6F)));


extern volatile __bit RI __attribute__((address(0x7E84)));


extern volatile __bit RJPU __attribute__((address(0x7C07)));


extern volatile __bit RX __attribute__((address(0x7C03)));


extern volatile __bit RX9 __attribute__((address(0x7D5E)));


extern volatile __bit RX9D __attribute__((address(0x7D58)));


extern volatile __bit RXCKP __attribute__((address(0x7DC5)));


extern volatile __bit RXDTP __attribute__((address(0x7DC5)));


extern volatile __bit SBOREN __attribute__((address(0x7E86)));


extern volatile __bit SCKP __attribute__((address(0x7DC4)));


extern volatile __bit SCS0 __attribute__((address(0x7E98)));


extern volatile __bit SCS1 __attribute__((address(0x7E99)));


extern volatile __bit SENDB __attribute__((address(0x7D63)));


extern volatile __bit SENDB1 __attribute__((address(0x7D63)));


extern volatile __bit SEVOPS0 __attribute__((address(0x7C2C)));


extern volatile __bit SEVOPS1 __attribute__((address(0x7C2D)));


extern volatile __bit SEVOPS2 __attribute__((address(0x7C2E)));


extern volatile __bit SEVOPS3 __attribute__((address(0x7C2F)));


extern volatile __bit SEVTDIR __attribute__((address(0x7C2B)));


extern volatile __bit SEVTEN __attribute__((address(0x7E17)));


extern volatile __bit SOSCEN __attribute__((address(0x7E6B)));


extern volatile __bit SP0 __attribute__((address(0x7FE0)));


extern volatile __bit SP1 __attribute__((address(0x7FE1)));


extern volatile __bit SP2 __attribute__((address(0x7FE2)));


extern volatile __bit SP3 __attribute__((address(0x7FE3)));


extern volatile __bit SP4 __attribute__((address(0x7FE4)));


extern volatile __bit SPEN __attribute__((address(0x7D5F)));


extern volatile __bit SREN __attribute__((address(0x7D5D)));


extern volatile __bit SRENA __attribute__((address(0x7D5D)));


extern volatile __bit STKFUL __attribute__((address(0x7FE7)));


extern volatile __bit STKOVF __attribute__((address(0x7FE7)));


extern volatile __bit STKUNF __attribute__((address(0x7FE6)));


extern volatile __bit SWDTE __attribute__((address(0x7E88)));


extern volatile __bit SWDTEN __attribute__((address(0x7E88)));


extern volatile __bit SYNC __attribute__((address(0x7D64)));


extern volatile __bit SYNC1 __attribute__((address(0x7D64)));


extern volatile __bit T016BIT __attribute__((address(0x7EAE)));


extern volatile __bit T08BIT __attribute__((address(0x7EAE)));


extern volatile __bit T0CKI __attribute__((address(0x7C04)));


extern volatile __bit T0CS __attribute__((address(0x7EAD)));


extern volatile __bit T0IE __attribute__((address(0x7F95)));


extern volatile __bit T0IF __attribute__((address(0x7F92)));


extern volatile __bit T0PS0 __attribute__((address(0x7EA8)));


extern volatile __bit T0PS1 __attribute__((address(0x7EA9)));


extern volatile __bit T0PS2 __attribute__((address(0x7EAA)));


extern volatile __bit T0SE __attribute__((address(0x7EAC)));


extern volatile __bit T1CKPS0 __attribute__((address(0x7E6C)));


extern volatile __bit T1CKPS1 __attribute__((address(0x7E6D)));


extern volatile __bit T1OSCEN __attribute__((address(0x7E6B)));


extern volatile __bit T1RD16 __attribute__((address(0x7E6F)));


extern volatile __bit T1RUN __attribute__((address(0x7E6E)));


extern volatile __bit T1SYNC __attribute__((address(0x7E6A)));


extern volatile __bit TMR0IE __attribute__((address(0x7F95)));


extern volatile __bit TMR0IF __attribute__((address(0x7F92)));


extern volatile __bit TMR0IP __attribute__((address(0x7F8A)));


extern volatile __bit TMR0ON __attribute__((address(0x7EAF)));


extern volatile __bit TMR1CS __attribute__((address(0x7E69)));


extern volatile __bit TMR1IE __attribute__((address(0x7CE8)));


extern volatile __bit TMR1IF __attribute__((address(0x7CF0)));


extern volatile __bit TMR1IP __attribute__((address(0x7CF8)));


extern volatile __bit TMR1ON __attribute__((address(0x7E68)));


extern volatile __bit TO __attribute__((address(0x7E83)));


extern volatile __bit TRISA0 __attribute__((address(0x7C90)));


extern volatile __bit TRISA1 __attribute__((address(0x7C91)));


extern volatile __bit TRISA2 __attribute__((address(0x7C92)));


extern volatile __bit TRISA3 __attribute__((address(0x7C93)));


extern volatile __bit TRISA4 __attribute__((address(0x7C94)));


extern volatile __bit TRISA5 __attribute__((address(0x7C95)));


extern volatile __bit TRISA6 __attribute__((address(0x7C96)));


extern volatile __bit TRISA7 __attribute__((address(0x7C97)));


extern volatile __bit TRISB0 __attribute__((address(0x7C98)));


extern volatile __bit TRISB1 __attribute__((address(0x7C99)));


extern volatile __bit TRISB2 __attribute__((address(0x7C9A)));


extern volatile __bit TRISB3 __attribute__((address(0x7C9B)));


extern volatile __bit TRISB4 __attribute__((address(0x7C9C)));


extern volatile __bit TRISB5 __attribute__((address(0x7C9D)));


extern volatile __bit TRISB6 __attribute__((address(0x7C9E)));


extern volatile __bit TRISB7 __attribute__((address(0x7C9F)));


extern volatile __bit TRMT __attribute__((address(0x7D61)));


extern volatile __bit TRMT1 __attribute__((address(0x7D61)));


extern volatile __bit TUN0 __attribute__((address(0x7CD8)));


extern volatile __bit TUN1 __attribute__((address(0x7CD9)));


extern volatile __bit TUN2 __attribute__((address(0x7CDA)));


extern volatile __bit TUN3 __attribute__((address(0x7CDB)));


extern volatile __bit TUN4 __attribute__((address(0x7CDC)));


extern volatile __bit TX __attribute__((address(0x7C02)));


extern volatile __bit TX1IE __attribute__((address(0x7CEC)));


extern volatile __bit TX1IF __attribute__((address(0x7CF4)));


extern volatile __bit TX1IP __attribute__((address(0x7CFC)));


extern volatile __bit TX8_9 __attribute__((address(0x7D66)));


extern volatile __bit TX9 __attribute__((address(0x7D66)));


extern volatile __bit TX91 __attribute__((address(0x7D66)));


extern volatile __bit TX9D __attribute__((address(0x7D60)));


extern volatile __bit TX9D1 __attribute__((address(0x7D60)));


extern volatile __bit TXB2IE __attribute__((address(0x7D1C)));


extern volatile __bit TXBNIE __attribute__((address(0x7D1C)));


extern volatile __bit TXBNIF __attribute__((address(0x7D24)));


extern volatile __bit TXBNIP __attribute__((address(0x7D2C)));


extern volatile __bit TXCKP __attribute__((address(0x7DC4)));


extern volatile __bit TXD8 __attribute__((address(0x7D60)));


extern volatile __bit TXEN __attribute__((address(0x7D65)));


extern volatile __bit TXEN1 __attribute__((address(0x7D65)));


extern volatile __bit TXIE __attribute__((address(0x7CEC)));


extern volatile __bit TXIF __attribute__((address(0x7CF4)));


extern volatile __bit TXIP __attribute__((address(0x7CFC)));


extern volatile __bit UDIS __attribute__((address(0x7C29)));


extern volatile __bit ULPWUIN __attribute__((address(0x7C00)));


extern volatile __bit VCFG __attribute__((address(0x7E0C)));


extern volatile __bit VCFG0 __attribute__((address(0x7E0C)));


extern volatile __bit VCFG01 __attribute__((address(0x7E0C)));


extern volatile __bit VREFP __attribute__((address(0x7C04)));


extern volatile __bit W4E __attribute__((address(0x7DC1)));


extern volatile __bit WR __attribute__((address(0x7D31)));


extern volatile __bit WREN __attribute__((address(0x7D32)));


extern volatile __bit WRERR __attribute__((address(0x7D33)));


extern volatile __bit WUE __attribute__((address(0x7DC1)));


extern volatile __bit ZERO __attribute__((address(0x7EC2)));


extern volatile __bit nBOR __attribute__((address(0x7E80)));


extern volatile __bit nDONE __attribute__((address(0x7E11)));


extern volatile __bit nMCLR __attribute__((address(0x7C05)));


extern volatile __bit nPD __attribute__((address(0x7E82)));


extern volatile __bit nPOR __attribute__((address(0x7E81)));


extern volatile __bit nRBPU __attribute__((address(0x7F8F)));


extern volatile __bit nRI __attribute__((address(0x7E84)));


extern volatile __bit nT1SYNC __attribute__((address(0x7E6A)));


extern volatile __bit nTO __attribute__((address(0x7E83)));
# 55 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include/pic18_chip_select.h" 2 3
# 9 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include/pic18.h" 2 3
# 19 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include/pic18.h" 3
__attribute__((__unsupported__("The " "flash_write" " routine is no longer supported. Please use the MPLAB X MCC."))) void flash_write(const unsigned char *, unsigned int, __far unsigned char *);
__attribute__((__unsupported__("The " "EraseFlash" " routine is no longer supported. Please use the MPLAB X MCC."))) void EraseFlash(unsigned long startaddr, unsigned long endaddr);






# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/errata.h" 1 3
# 28 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include/pic18.h" 2 3
# 156 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include/pic18.h" 3
__attribute__((__unsupported__("The " "Read_b_eep" " routine is no longer supported. Please use the MPLAB X MCC."))) unsigned char Read_b_eep(unsigned int badd);
__attribute__((__unsupported__("The " "Busy_eep" " routine is no longer supported. Please use the MPLAB X MCC."))) void Busy_eep(void);
__attribute__((__unsupported__("The " "Write_b_eep" " routine is no longer supported. Please use the MPLAB X MCC."))) void Write_b_eep(unsigned int badd, unsigned char bdat);
# 188 "C:/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC18Fxxxx_DFP/1.6.159/xc8\\pic\\include/pic18.h" 3
__attribute__((__unsupported__("The READTIMER" "3" "() macro is not available with the current device."))) unsigned short __readtimer3(void);



unsigned char __t1rd16on(void);
unsigned char __t3rd16on(void);
# 34 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include/xc.h" 2 3
# 60 "FREQ_DISP_3_NGT.c" 2
# 69 "FREQ_DISP_3_NGT.c"
volatile uint8_t rx_buffer[5];
volatile uint8_t cnt = 0;
volatile uint8_t data_received = 0;
uint16_t TMR_VAL;
volatile unsigned char Start_HSM = 0;

const float sine_table[] = {
    0.000000, 0.017452, 0.034899, 0.052336, 0.069756, 0.087156, 0.104528, 0.121869, 0.139173, 0.156434,
    0.173648, 0.190809, 0.207912, 0.224951, 0.241922, 0.258819, 0.275637, 0.292371, 0.309017, 0.325568,
    0.342020, 0.358368, 0.374606, 0.390731, 0.406736, 0.422618, 0.438371, 0.453990, 0.469471, 0.484809,
    0.500000, 0.515038, 0.529919, 0.544639, 0.559193, 0.573576, 0.587785, 0.601815, 0.615661, 0.629320,
    0.642787, 0.656059, 0.669130, 0.681998, 0.694658, 0.707107, 0.719339, 0.731353, 0.743144, 0.754710,
    0.766044, 0.777146, 0.788010, 0.798635, 0.809017, 0.819152, 0.829038, 0.838671, 0.848048, 0.857167,
    0.866025, 0.874619, 0.882947, 0.891006, 0.898794, 0.906307, 0.913545, 0.920504, 0.927183, 0.933580,
    0.939692, 0.945518, 0.951056, 0.956304, 0.961261, 0.965926, 0.970295, 0.974370, 0.978147, 0.981627,
    0.984808, 0.987688, 0.990268, 0.992546, 0.994522, 0.996195, 0.997564, 0.998630, 0.999391, 0.999848,
    1.000000
};

uint16_t sine_table1[];

uint8_t byte;



void PWM_Init(void) {
    PTPERH = 0x00;
    PTPERL = 0xFA;

    PTCON0bits.PTMOD = 0b00;
    PTCON0bits.PTOPS = 0b0000;
    PTCON0bits.PTCKPS = 0b00;
    PTCON1bits.PTEN = 1;

    PWMCON0bits.PWMEN = 0b001;
    PWMCON0bits.PMOD = 0b001;
    PDC0L = 0x00 & 0xFF;
    PDC0H = (0x00 >> 8);
}


void Timer1_Init(void) {


    TMR1H = (TMR_VAL >> 8);
    TMR1L = TMR_VAL & 0xFF;

    T1CONbits.RD16 = 1;

    T1CONbits.T1CKPS = 0b01;
    T1CONbits.T1OSCEN = 0;
    T1CONbits.nT1SYNC = 0;
    T1CONbits.TMR1CS = 0;

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}


void USART_Init(const long int baudrate) {
    uint16_t valor_SPBRG = (10000000 / (16UL * baudrate)) - 1;

    if (valor_SPBRG <= 255) {
        TXSTAbits.BRGH = 1;
        BAUDCONbits.BRG16 = 0;
        SPBRG = valor_SPBRG;
        SPBRGH = 0;
    } else {
        TXSTAbits.BRGH = 0;
        BAUDCONbits.BRG16 = 1;
        SPBRG = valor_SPBRG & 0xFF;
        SPBRGH = (valor_SPBRG >> 8) & 0xFF;
    }

    TRISAbits.RA3 = 1;
    TRISAbits.RA2 = 0;

    TXSTAbits.SYNC = 0;
    TXSTAbits.TXEN = 1;
    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;

    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1;
    IPR1bits.RCIP = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}


void INTOSC_Init(void) {
    OSCCONbits.IDLEN = 1;
}

void __attribute__((picinterrupt(("")))) ISR() {
    if (PIR1bits.RCIF) {
        byte = RCREG;
        PIR1bits.RCIF = 0;

        if (cnt == 0 && byte != 0xAA) {
            return;
        }

        rx_buffer[cnt++] = byte;


        if (cnt >= 4) {
            data_received = 1;
            cnt = 0;
        }
    }


    if (TMR1IF) {
        TMR1H = (TMR_VAL >> 8);
        TMR1L = TMR_VAL & 0xFF;

        LATBbits.LATB0 = !LATBbits.LATB0;
        Start_HSM = 1;
        TMR1IF = 0;
    }
}


void main(void) {
    TRISB0 = 0;
    LATBbits.LATB0 = 0;
    TRISB1 = 0;
    LATBbits.LATB1 = 0;
    TRISB4 = 0;
    LATBbits.LATB4 = 0;
    TRISA6 = 1;
    TRISA7 = 1;

    uint8_t Voltage = 0, count = 0, i, j, Vin = 220, newVtg, edge;
    uint16_t frequency = 0, newfreq = 0, Output_Voltage;
    float T = 0.0f, Ag = 0.0f;
    INTOSC_Init();
    PWM_Init();
    USART_Init(1200);
    Timer1_Init();

    while (1) {
        if (data_received) {
            Voltage = rx_buffer[1];
            frequency = ((uint16_t) rx_buffer[2] << 8) | rx_buffer[3];

            data_received = 0;
        }
        if ((frequency != newfreq) || (Voltage != newVtg)) {
            T1CONbits.TMR1ON = 1;
            newfreq = frequency;
            newVtg = Voltage;

            Output_Voltage = (uint16_t)(((uint32_t)newVtg * 100) / Vin);


            TMR_VAL = 65535 - (10000000 / (16 * (uint16_t) frequency));
            T = 2500.0f / (float) frequency;
            Ag = 90.0f / T;
            count = (uint8_t) T;
            for ( j = 0; j < count; j++) {
                uint8_t angle = (uint8_t) (j * Ag + 0.5);
                if (angle > 90) angle = 90;
                sine_table1[j] = (uint16_t) Output_Voltage * sine_table[angle];
            }
        }
        if (Start_HSM == 1 && edge == 0) {

            for (i = 0; i < count; i++) {
                uint16_t PWM_Duty = sine_table1[i];
                PWM_Duty = (0xFFFF) & (PWM_Duty << 2);
                PDC0L = PWM_Duty & 0xFF;
                PDC0H = (PWM_Duty >> 8);
                _delay((unsigned long)((85)*(10000000/4000000.0)));
            }
            for (i = (count - 1); i > 0; i--) {
                uint16_t PWM_Duty = sine_table1[i];
                PWM_Duty = (0xFFFF) & (PWM_Duty << 2);
                PDC0L = PWM_Duty & 0xFF;
                PDC0H = (PWM_Duty >> 8);
                _delay((unsigned long)((85)*(10000000/4000000.0)));
            }
            Start_HSM = 0;
            edge = 1;
        }
        else if (Start_HSM == 1 && edge == 1) {

                                                  for (i = (count - 1); i > 0; i--) {
                uint16_t PWM_Duty = sine_table1[i];
                PWM_Duty = (0xFFFF) & (PWM_Duty << 2);
                PDC0L = PWM_Duty & 0xFF;
                PDC0H = (PWM_Duty >> 8);
                _delay((unsigned long)((85)*(10000000/4000000.0)));
            }
                                                      for (i = 0; i < count; i++) {
                uint16_t PWM_Duty = sine_table1[i];
                PWM_Duty = (0xFFFF) & (PWM_Duty << 2);
                PDC0L = PWM_Duty & 0xFF;
                PDC0H = (PWM_Duty >> 8);
                _delay((unsigned long)((85)*(10000000/4000000.0)));
            }
            Start_HSM = 0;
            edge = 0;
        }
    }
}
