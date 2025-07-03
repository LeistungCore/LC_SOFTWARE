// Frequency Control Project code written by Saipan Mujawar
// PIC18F1330 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator (HS Oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = BOHW       // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3L
#pragma config PWMPIN = OFF     // PWM Output Pins Reset State Control bit (PWM outputs disabled upon Reset)
#pragma config LPOL = LOW       // Low-Side Transistors Polarity bit (Even PWM Output Polarity Control bit) (PWM0, PWM2 and PWM4 are active-high (default))
#pragma config HPOL = LOW       // High Side Transistors Polarity bit (Odd PWM Output Polarity Control bit) (PWM1, PWM3 and PWM5 are active-high (default))

// CONFIG3H
#pragma config FLTAMX = RA5     // FLTA Mux bit (FLTA input is muxed onto RA5)
#pragma config T1OSCMX = LOW    // T1OSO/T1CKI MUX bit (T1OSO/T1CKI pin resides on RB2)
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR pin enabled, RA5 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Reset on stack overflow/underflow enabled)
#pragma config BBSIZ = BB256    // Boot Block Size Select bits (256 Words (512 Bytes) Boot Block size)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit Block 0 (000800-000FFF) (Block 0 is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit Block 1 (001000-001FFF) (Block 1 is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Code Protection bit (Boot Block Memory Area) (Boot Block is not code-protected)
#pragma config CPD = OFF        // Code Protection bit (Data EEPROM) (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit Block 0 (000800-000FFF) (Block 0 is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit Block 1 (001000-001FFF) (Block 1 is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Write Protection bit (Configuration Registers) (Configuration registers are not write-protected)
#pragma config WRTB = OFF       // Write Protection bit (Boot Block Memory Area) (Boot Block is not write-protected)
#pragma config WRTD = OFF       // Write Protection bit (Data EEPROM) (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit Block 0 (000800-000FFF) (Block 0 is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit Block 1 (001000-001FFF) (Block 1 is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Table Read Protection bit (Boot Block Memory Area) (Boot Block is not protected from table reads executed in other blocks)

#include <xc.h>
#include <stdint.h>
#include <stdlib.h>  // For itoa()

#define _XTAL_FREQ 10000000  // 10 MHz system clock

// Configuration bits (adjust these as needed for your MCU setup)
// #pragma config statements here...

// Global Variables
volatile uint8_t rx_buffer[5]; // Buffer for received bytes
volatile uint8_t cnt = 0; // Counter for received bytes
volatile uint8_t data_received = 0; // Flag: 1 when full frame received
uint16_t TMR_VAL;
volatile unsigned char Start_HSM = 0; // Interrupt flag

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
// Sine Value Storage
uint16_t sine_table1[62];

uint8_t byte;
#define START_BYTE 0xAA

// Initialize PWM for High-Speed Frequency MOSFET Drive
void PWM_Init(void) {
    PTPERH = 0x00; // Set PWM period high byte
    PTPERL = 0xFA; // 10 kHz PWM period

    PTCON0bits.PTMOD = 0b00; // Free-running mode
    PTCON0bits.PTOPS = 0b0000;
    PTCON0bits.PTCKPS = 0b00; // Prescaler = 1:1
    PTCON1bits.PTEN = 1; // Enable PWM timer

    PWMCON0bits.PWMEN = 0b001; // Enable PWM1 on RB1
    PWMCON0bits.PMOD = 0b001;
    PDC0L = 0x00 & 0xFF; // Lower 8 bits of duty cycle
    PDC0H = (0x00 >> 8); // Upper 6 bits of duty cycle
}

// Timer 1 Initialization to Drive LOW SPEED FREQUENCY with 50% Duty Cycle
void Timer1_Init(void) {
    //Load initial value
//    TMR_VAL = (65535 - (_XTAL_FREQ / (16 * FREQ))); // newfreq = 40, XTAL = 16000000
    TMR1H = (TMR_VAL >> 8);
    TMR1L = TMR_VAL & 0xFF;

    T1CONbits.RD16 = 1;
    //    T1CONbits.T1RD16 = 0;
    T1CONbits.T1CKPS = 0b01;
    T1CONbits.T1OSCEN = 0;
    T1CONbits.nT1SYNC = 0;
    T1CONbits.TMR1CS = 0;

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

// Initialize USART to Interface with Display PCB Controller
void USART_Init(const long int baudrate) {
    uint16_t valor_SPBRG = (_XTAL_FREQ / (16UL * baudrate)) - 1;

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

    TRISAbits.RA3 = 1; // RX input
    TRISAbits.RA2 = 0; // TX output

    TXSTAbits.SYNC = 0; // Async mode
    TXSTAbits.TXEN = 1; // Enable TX
    RCSTAbits.SPEN = 1; // Enable serial port (TX/RX)
    RCSTAbits.CREN = 1; // Enable continuous RX

    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1; // Enable RX interrupt
    IPR1bits.RCIP = 1; // High priority
    INTCONbits.PEIE = 1; // Enable peripheral interrupts
    INTCONbits.GIE = 1; // Enable global interrupts
}

// Clock Initialization Setting for External Crystal Oscillator
void INTOSC_Init(void) {
    OSCCONbits.IDLEN = 1;
}

void __interrupt() ISR() {
    if (PIR1bits.RCIF) {
        byte = RCREG;
        PIR1bits.RCIF = 0;
        // Wait for start byte
        if (cnt == 0 && byte != START_BYTE) {
            return;
        }

        rx_buffer[cnt++] = byte;

        // Expecting 4 bytes: start + voltage + freq_high + freq_low
        if (cnt >= 4) {
            data_received = 1;
            cnt = 0;
        }
    }

    // Timer ISR remains unchanged
    if (TMR1IF) {
        TMR1H = (TMR_VAL >> 8);
        TMR1L = TMR_VAL & 0xFF;

        LATBbits.LATB0 = !LATBbits.LATB0;
        Start_HSM = 1;
        TMR1IF = 0;
    }
}

// Main function
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
    USART_Init(1200); // Initialize USART at 9600 baud
    Timer1_Init();

    while (1) {
        if (data_received) {
            Voltage = rx_buffer[1];
            frequency = ((uint16_t) rx_buffer[2] << 8) | rx_buffer[3]; // Third and fourth bytes //rx_buffer[2];

            data_received = 0;
        }
        if ((frequency != newfreq) || (Voltage != newVtg)) {
            T1CONbits.TMR1ON = 1;
            newfreq = frequency;
            newVtg = Voltage; 
//            Output_Voltage = (uint8_t)(((uint16_t)newVtg / (uint16_t)Vin) * 100);
            Output_Voltage = (uint16_t)(((uint32_t)newVtg * 100) / Vin); // Adjusted to use uint32_t for larger range

//            USART_Write(frequency);
            TMR_VAL = 65535 - (_XTAL_FREQ / (16 * (uint16_t) frequency));
            T = 2500.0f / (float) frequency; // frequency = 80.0f Hz
            Ag = 90.0f / T; // Calculate angle increment
            count = (uint8_t) T;
            for ( j = 0; j < count; j++) { // Call the function and store the result in new array
                uint8_t angle = (uint8_t) (j * Ag + 0.5); // Round to nearest integer
                if (angle > 90) angle = 90; // Ensure within bounds
                sine_table1[j] = (uint16_t) Output_Voltage * sine_table[angle];
            }
        }
        if (Start_HSM == 1 && edge == 0) { // Generate sine wave
//            LATBbits.LATB4 = !LATBbits.LATB4;
            for (i = 0; i < count; i++) {
                uint16_t PWM_Duty = sine_table1[i];
                PWM_Duty = (0xFFFF) & (PWM_Duty << 2);
                PDC0L = PWM_Duty & 0xFF;
                PDC0H = (PWM_Duty >> 8);
                __delay_us(85);
            }
            for (i = (count - 1); i > 0; i--) {
                uint16_t PWM_Duty = sine_table1[i];
                PWM_Duty = (0xFFFF) & (PWM_Duty << 2);
                PDC0L = PWM_Duty & 0xFF;
                PDC0H = (PWM_Duty >> 8);
                __delay_us(85);
            }
            Start_HSM = 0;
            edge = 1;
        }
        else if (Start_HSM == 1 && edge == 1) { // Generate sine wave
//            LATBbits.LATB4 = !LATBbits.LATB4;
        /*    for (i = 0; i < count; i++) {  */   for (i = (count - 1); i > 0; i--) {
                uint16_t PWM_Duty = sine_table1[i];
                PWM_Duty = (0xFFFF) & (PWM_Duty << 2);
                PDC0L = PWM_Duty & 0xFF;
                PDC0H = (PWM_Duty >> 8);
                __delay_us(85);
            }
        /*    for (i = (count - 1); i > 0; i--) {  */ for (i = 0; i < count; i++) {
                uint16_t PWM_Duty = sine_table1[i];
                PWM_Duty = (0xFFFF) & (PWM_Duty << 2);
                PDC0L = PWM_Duty & 0xFF;
                PDC0H = (PWM_Duty >> 8);
                __delay_us(85);
            }
            Start_HSM = 0;
            edge = 0;
        }
    }
}