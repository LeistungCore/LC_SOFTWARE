
// Final UART code working with Display
// PIC16F15223 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator Mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_1MHZ// Power-up Default Value for COSC bits (HFINTOSC (1 MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O function on RA4)
#pragma config VDDAR = HI       // VDD Range Analog Calibration Selection bit (Internal analog systems are calibrated for operation between VDD = 2.3V - 5.5V)

// CONFIG2
#pragma config MCLRE = EXTMCLR  // Master Clear Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR)
#pragma config PWRTS = PWRT_OFF // Power-up Timer Selection bits (PWRT is disabled)
#pragma config WDTE = OFF       // WDT Operating Mode bits (WDT disabled; SEN is ignored)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection bit (Brown-out Reset Voltage (VBOR) set to 1.9V)
#pragma config PPS1WAY = OFF    // PPSLOCKED One-Way Set Enable bit (The PPSLOCKED bit can be set and cleared as needed (unlocking sequence is required))
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will not cause a reset)

// CONFIG3

// CONFIG4
#pragma config BBSIZE = BB512   // Boot Block Size Selection bits (512 words boot block size)
#pragma config BBEN = OFF       // Boot Block Enable bit (Boot Block is disabled)
#pragma config SAFEN = OFF      // SAF Enable bit (SAF is disabled)
#pragma config WRTAPP = OFF     // Application Block Write Protection bit (Application Block is not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block is not write-protected)
#pragma config WRTC = OFF       // Configuration Registers Write Protection bit (Configuration Registers are not write-protected)
#pragma config WRTSAF = OFF     // Storage Area Flash (SAF) Write Protection bit (SAF is not write-protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR. MCLRE Configuration bit is ignored.)

// CONFIG5
#pragma config CP = OFF         // User Program Flash Memory Code Protection bit (User Program Flash Memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic16f15224.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>   // For uint8_t

#define _XTAL_FREQ 1000000  // 1 MHz Clock
#define StartPWM 242


volatile unsigned char edge = 0, count = 0;
uint16_t SecondcycleDelay = 242; 


#define NUM_SAMPLES 20      // Number of ADC samples
unsigned char temperature_flag = 0;  // Flag for temperature threshoD
const uint16_t ARR[165] = {'\0'};
extern volatile uint8_t voltage_value; // This is your input voltage

// Variables
//volatile unsigned int voltage_ADC_value = 0;
//volatile unsigned int current_ADC_value = 0;
//volatile unsigned int thermistor_ADC_value = 0;
//
//volatile unsigned int max_voltage_ADC = 0;  
//volatile unsigned int max_current_ADC = 0;  
//volatile unsigned int max_temperature_ADC = 0;  
//volatile unsigned int sample_count = 0;     
//volatile unsigned char sampling_complete = 0;
volatile uint8_t adc_channel_index = 0;  // 0 = Voltage, 1 = Current, 2 = Temperature
volatile uint16_t voltage_val = 0;
volatile uint16_t current_val = 0;
volatile uint16_t temperature_val = 0;
volatile uint16_t timer_counter = 0;  // Count the number of interrupts (10 ms)
const uint16_t Max_RC5 = 512;  // Reference ADC value from RC5 (assumed fixed baseline)
float input_peak_voltage = 0.0;
float input_peak_current = 0.0;


uint8_t rcv_current_value = 0;
uint8_t byte;
uint8_t rcv_FREQUENCY = 0;
char cnt = 0;
char buffer[64];
uint16_t adc_val, max_adc = 900;
uint8_t Trip;
volatile uint8_t rx_buffer[6];
uint8_t timer_value = 0;
int16_t voltage_diff;
int16_t current_diff;
// Function Prototypes
void __interrupt() ISR(void);
void UART_Init(void);
void EUSART1_Write(uint8_t data);
void UART_Write_Text(const uint8_t *text);
uint8_t UART_Read(void);
unsigned int UART_Read_Int(void);
unsigned int ADCRead(unsigned char channel);

void UART_Init(void) {
    RX1PPS = 0x14; //RC4->EUSART1:RX1;
    RC3PPS = 0x05;  //RC3->EUSART1:TX1;
    ANSELA = 0x17;
    ANSELC = 0x27;
    ANSELCbits.ANSC3= 0; // Set RC4 as digital
    ANSELCbits.ANSC4 = 0; // Set RC4 as digital
//ABDEN disabled; WUE enabled; BRG16 16bit_generator; SCKP Non-Inverted; 
    BAUD1CON = 0x58; 
    //ADDEN enabled; CREN enabled; SREN disabled; RX9 8-bit; SPEN enabled; 
    RC1STA = 0x90; 
    //TX9D 0x0; BRGH hi_speed; SENDB sync_break_complete; SYNC asynchronous; TXEN enabled; TX9 8-bit; CSRC client; 
    TX1STA = 0x26; 
    //SPBRGL 25; 
    SP1BRGL = 0xD0; 
    //SPBRGH 0; 
    SP1BRGH = 0x0; 
    // Enable UART RX Interrupt
    PIE1bits.RC1IE = 1;   // Enable EUSART1 RX interrupt
    PIR1bits.RC1IF = 0;   // Clear interrupt flag
//    INTCONbits.PEIE = 1;  // Enable peripheral interrupt
//    INTCONbits.GIE = 1;   // Enable global interrupt
}

void EUSART1_Write(uint8_t txData)
{
    while (!PIR1bits.TX1IF);  // Wait until UART is ready for the next byte
    TX1REG = txData;
}

void UART_Write_Text(const uint8_t *text) {
    while (*text != '\0') {
        EUSART1_Write(*text);
        text++;
    }
}
unsigned int ADCRead(unsigned char channel) {
    ADCON0bits.CHS = channel;  
    __delay_us(50);             // Acquisition delay for accuracy
    ADCON0bits.GO = 1;          // Start ADC conversion
    while (ADCON0bits.GO);      
    return ((unsigned int)(ADRESH << 8) | ADRESL); 
}

//uint8_t get_TMR0L_from_voltage(uint8_t voltage)
//{
//    if ((voltage >= 0) && (voltage <= 5)) {
//        return 140;
//    }
//    else if (voltage <= 10) {
//        return 149;
//    }
//    else if (voltage <= 12) {
//        return 156;
//    }
//    else if (voltage <= 20) {
//        return 164;
//    }
//    else if (voltage <= 29) {
//        return 172;
//    }
//    else if (voltage <= 38) {
//        return 180;
//    }
//    else if (voltage <= 63) {
//        return 187;
//    }
//    else if (voltage <= 80) {
//        return 195;
//    }
//    else if (voltage <= 100) {
//        return 203;
//    }
//    else if (voltage <= 115) {
//        return 210;
//    }
//    else if (voltage <= 133) {
//        return 218;
//    }
//    else if (voltage <= 152) {
//        return 226;
//    }
//    else if (voltage <= 172) {
//        return 235;
//    }
//    else if (voltage <= 185) {
//        return 242;
//    }
//    else if (voltage <= 200) {
//        return 248;
//    }
//    else if (voltage <= 230){ // voltage > 200 (up to 230 or beyond)
//        return 252;
//    }
//}
uint8_t get_TMR0L_from_voltage(uint8_t voltage)
{
    if(voltage <= 5){
        return 149;
    }
    else if (voltage <= 10) {
        return 149;
    }
    else if (voltage <= 15) {
        return 149;
    }
    else if (voltage <= 20) {
        return 149;
    }
    else if (voltage <= 30) {
        return 149;
    }
    else if (voltage <= 35) {
        return 149;
    }
    else if (voltage <= 40) {
        return 149;
    }
    else if (voltage <= 50) {
        return 156;
    }
    else if (voltage <= 60) {
        return 164;
    }
    else if (voltage <= 69) {
        return 172;
    }
    else if (voltage <= 78) {
        return 180;
    }
    else if (voltage <= 115) {
        return 187;
    }
    else if (voltage <= 140) {
        return 195;
    }
    else if (voltage <= 160) {
        return 203;
    }
    else if (voltage <= 170) {
        return 210;
    }
    else if (voltage <= 180) {
        return 218;
    }
    else if (voltage <= 190) {
        return 226;
    }
    else if (voltage <= 200) {
        return 235;
    }
    else if (voltage <= 210) {
        return 242;
    }
    else if (voltage <= 220) {
        return 248;
    }
    else if (voltage <= 230) { // voltage > 200 (up to 230 or beyond)
        return 252;
    }
}

void main(void) 
{
    OSCCON = 0x70;
    
    // Pin Configurations
    TRISAbits.TRISA5 = 0;   
    LATAbits.LATA5 = 1;     

    TRISCbits.TRISC0 = 1;    
    
    // Set UART pins
    TRISCbits.TRISC4 = 1;  // RX pin (RC4)
    TRISCbits.TRISC3 = 0;  // TX pin (RC3)
    
    edge = 0;
    count = 0;

    // IOC (Interrupt on Change) configuration
    IOCCPbits.IOCCP0 = 1; // 0x01;        
    IOCCNbits.IOCCN0 = 1; // 0x01;  
    IOCCFbits.IOCCF0 = 0;
     
    PIR0bits.IOCIF = 0;
    PIE0bits.IOCIE = 1;            
         
    INTCONbits.PEIE = 1;             
    INTCONbits.GIE = 1;   
    INTCONbits.INTEDG = 0;

//     ADC Configuration
    TRISCbits.TRISC2 = 1; // Voltage ADC (AN2)
    TRISAbits.TRISA2 = 1; // Current ADC (AN0)
    TRISAbits.TRISA4 = 1; // Temperature ADC (AN4)

//    ADCON0 = 0x01;   
//    ADCON1 = 0x40;  
    
    // ADC Configuration
    TRISCbits.TRISC2 = 1; // Voltage ADC (RC2)
    ANSELCbits.ANSC2 = 1; // Enable analog on RC2
    TRISAbits.TRISA2 = 1; // Current ADC (RA2)
    ANSELAbits.ANSA2 = 1; // Enable analog on RC2
    TRISAbits.TRISA4 = 1; // Temperature ADC (RAA4)
    ANSELAbits.ANSA4 = 1; // Enable analog on RC2
    TRISCbits.TRISC5 = 1; // Voltage ADC (RC5)
    ANSELCbits.ANSC5 = 1; // Enable analog on RC2

//    ADCON0 = 0x01;   
//    ADCON1 = 0x40;  
//    ADCON0 = 0b00001000; // CHS = RA2 (bit 7-2), GO = 0, ON = 0 (yet)
     ADCON0 = 0b01010100; // CHS = RC5 (bit 7-2), GO = 0, ON = 0 (yet)
//    ADCON0 = 0b01001000; // CHS = RC2 (bit 7-2), GO = 0, ON = 0 (yet)
//    ADCON0 = 0b00010000; // CHS = RA4 (bit 7-2), GO = 0, ON = 0 (yet)
    ADCON1 = 0b11100000; // Right-justified (FM=1), FOSC/16 (CS=101), VREF+ = VDD
    PIR1bits.ADIF = 0;     //Clear the ADC interrupt flag
    PIE1bits.ADIE = 1;     //Enable ADC interrupt.
    ADCON0bits.ON = 1;   // Enable ADC
    ADCON0bits.GO = 1; // Start ADC conversion

//    // Timer0 Configuration
    T0CON0bits.MD16 = 0;  
    T0CON0bits.OUTPS = 0x00; 
    T0CON1bits.ASYNC = 0;
    T0CON1bits.CS = 0b010;   
    T0CON1bits.CKPS = 0x04; 
    TMR0H = 0;
    TMR0L = 0;     
    PIR0bits.TMR0IF = 0; // 0x00;
    PIE0bits.TMR0IE = 1;  
    T0CON0bits.EN = 1;    
    UART_Init();
    
    // Infinite loop
    while(1) {
        timer_value = get_TMR0L_from_voltage(rcv_current_value); 
        // Check the timer_counter for channel switching
        if (timer_counter >= 3) {  // Every 30 ms (3 * 10 ms)
            timer_counter = 0;  // Reset the counter

            // Switch ADC channel based on the current index
            switch (adc_channel_index) {
                case 0:  // Voltage Channel (RC2 = AN2)
                    ADCON0bits.CHS = 0b010010; // Channel 2 (RC2)
                    break;

                case 1:  // Current Channel (RA2 = AN0)
                    ADCON0bits.CHS = 0b000010; // Channel 0 (RA2)
                    break;

                case 2:  // Temperature Channel (RA4 = AN4)
                    ADCON0bits.CHS = 0b000100; // Channel 4 (RA4)
                    break;
            }

            // Start ADC conversion for the new channel
            ADCON0bits.GO = 1;

            // Update the channel index for the next cycle
            adc_channel_index++;
            if (adc_channel_index > 2) {
                adc_channel_index = 0;  // Cycle back to voltage channel
            }
        }
        // Do voltage and current peak calculation
         voltage_diff = voltage_val - Max_RC5;
         current_diff = current_val - Max_RC5;

        input_peak_voltage = voltage_diff * 1.0064853f;
        input_peak_current = current_diff * 0.048828125f;
//        if(adc_val <= max_adc){
//            Trip = 1;
//        }
//        sprintf(buffer, "P:%u\r\n", adc_val);
//        
//        UART_Write_Text(buffer);
        // Periodically send ADC values over UART
//        sprintf(buffer, "V:%u C:%u T:%u\r\n", voltage_val, current_val, temperature_val);
//        UART_Write_Text(buffer);
        
        // Output on UART every 500 ms
        sprintf(buffer, "Vpk:%.2f Ipk:%.2f T:%u\r\n", input_peak_voltage, input_peak_current, temperature_val);
        UART_Write_Text((uint8_t*)buffer);
//        EUSART1_Write(rcv_ON_Delay);
//        __delay_ms(1000);
//        EUSART1_Write(timer_value);
//        __delay_ms(1000);
    }
}

void __interrupt() ISR(void)
{
  if (IOCCFbits.IOCCF0) {// if (PIR0bits.IOCIF ) {           //if (IOCCFbits.IOCCF0 ) { 
        
//      LATAbits.LATA5 = 1;

        timer_counter++;  // Increment the interrupt counter (10 ms intervals)
//        timer_value = get_TMR0L_from_voltage(rcv_current_value);
        if(rcv_FREQUENCY == 1){
            if (edge == 0) {
                LATAbits.LATA5 = 1;
                TMR0H = 0;
                TMR0L = timer_value;
                T0CON0bits.EN = 1;
                edge = 1;
            } 
            else if (edge == 1) {
                LATAbits.LATA5 = 1;
                TMR0H = 0;
                TMR0L = timer_value;
                T0CON0bits.EN = 1;
                edge = 0;
            }
        }
        else if(rcv_FREQUENCY == 0){
            if (edge == 0) {
                LATAbits.LATA5 = 1;
                TMR0H = 0;
                TMR0L = timer_value;
                T0CON0bits.EN = 1;
                edge++;
            } 
            else if (edge == 1) {
                LATAbits.LATA5 = 1;
                TMR0H = 0;
                TMR0L = 0;
                T0CON0bits.EN = 0;
                edge = 0;
            }
            
        }
////        PIR0bits.IOCIF = 0;
        IOCCFbits.IOCCF0 = 0; // Clear interrupt flag
    }
//    
  else if (PIR0bits.TMR0IF) {     
        if (count == 0) {
            LATAbits.LATA5 = 0;
            TMR0H = 0;
            TMR0L = 242; // For 1 ms TRIAC DRIVE   
            T0CON0bits.EN = 1;
            count = 1;
        } 
        else if(count == 1) {
            LATAbits.LATA5 = 1;
            TMR0H = 0;
            TMR0L = 0;
            T0CON0bits.EN = 0;      // Stop timer after TRIAC Driven
            count = 0;  
        }
        PIR0bits.TMR0IF = 0; 
    }
   if (PIR1bits.RC1IF) {
        PIR1bits.RC1IF = 0;
        byte = RC1REG;
//        rx_buffer[cnt] = RC1REG;
//        cnt++;
//        if (cnt == 3) {
//            // Full frame received
//            rcv_current_value = rx_buffer[1];
//            rcv_FREQUENCY     = rx_buffer[2];
//
//            data_received = 1;
//            cnt = 0; // Reset for next frame
//        }
//        rcv_ON_Delay = byte;
        if (cnt == 0 && byte != 0xAA) {
            // Wait for start byte 
            return;
        }

        rx_buffer[cnt++] = byte;

        if (cnt >= 3) {
            // Full frame received
            rcv_current_value = rx_buffer[1];
            rcv_FREQUENCY     = rx_buffer[2];
            cnt = 0; // Reset for next frame
        }

    }
//  if(PIR1bits.ADIF){
//        PIR1bits.ADIF = 0;
//        adc_val = (ADRESH<<8) | ADRESL;
//        ADCON0bits.GO = 1; // Start ADC conversion
//        
//      }
  // Check if the ADC conversion is done
        if (PIR1bits.ADIF) {  // ADC interrupt flag
            PIR1bits.ADIF = 0;  // Clear the ADC interrupt flag
            uint16_t adc_result = (ADRESH << 8) | ADRESL;  // Combine the result

            // Store ADC values based on the current channel
            switch (adc_channel_index) {
                case 0:  // Voltage
                    voltage_val = adc_result;
                    break;
                case 1:  // Current
                    current_val = adc_result;
                    break;
                case 2:  // Temperature
                    temperature_val = adc_result;
                    break;
            }

            // Start the next ADC conversion
            ADCON0bits.GO = 1;
        }
}
