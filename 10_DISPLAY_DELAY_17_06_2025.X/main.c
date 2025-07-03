//Display Frequency Code Written By Saipan Mujawar. 

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/interrupt.h"
/*
    Main application
*/
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define _XTAL_FREQ 16000000  // Define crystal frequency as 8 MHz (adjust if necessary)

//DIGIT PINS
#define digit5 LATDbits.LATD0  
#define digit4 LATDbits.LATD1
#define digit3 LATDbits.LATD2
#define digit2 LATDbits.LATD3
#define digit1 LATDbits.LATD4 

//FOR LED 
#define DG1_LED LATEbits.LATE1
#define DG2_LED LATBbits.LATB1
#define DG3_LED LATBbits.LATB2
#define DG4_LED LATBbits.LATB3
#define DG5_LED LATBbits.LATB4
#define DR3_LED LATBbits.LATB7

//FOR SWITCH
#define SettingSwitch           PORTAbits.RA3
#define IncreaseVoltageSwitch   PORTAbits.RA5 
#define DecreaseVoltageSwitch   PORTAbits.RA1 
#define UP_Switch               PORTEbits.RE3 
#define DOWN_Switch             PORTAbits.RA2
#define STOP_Switch            PORTAbits.RA4

// Define the sensor pins
#define NPN_SENSOR_1_PIN      PORTEbits.RE2  // Pin27 for first NPN sensor 1(connected to RE2)
#define NPN_SENSOR_2_PIN      PORTCbits.RC2  // Pin36 for second NPN sensor 2(connected to RC2)
#define PHOTO_SENSOR_PIN      PORTBbits.RB0  // Pin8 for photoelectric sensor (connected to RB0)
#define POT_PIN               PORTEbits.RE0  // Pin25 for potentiometer (analog input on RE0)
#define PRESET_SPEED_A        PORTCbits.RC1  // Pin35 for Preset Speed A (connected to RC1)
#define PRESET_SPEED_B        PORTCbits.RC0  // Pin32 for Preset Speed B (connected to RC0)
#define CONTROL_OUTPUT_PIN    PORTAbits.RA6  // Pin5 for Control Output (connected to RA6)

#define FLASH_SAVE_ADDR   0x1F80  // Example: last page of 8KB flash (modify as needed)

// Mode 1 or Stage 1 Variables
uint8_t VOLTAGE = 0, current_voltage;
uint8_t Output_VTG_Stop = 0;
uint16_t FREQUENCY = 40, STOP_FREQ = 0;
unsigned int ON_Delay = 11;  // 3.3 sec
unsigned int OFF_Delay = 11;  // 8.5 sec
uint8_t SOFT_START_Delay = 11;
uint8_t soft_start_step_interval = 1;


// Mode 2 or Stage 2 Variables
volatile bool NPN_Sensor_1;
volatile bool NPN_Sensor_2;
volatile bool PhotoSensor_Flag;
uint16_t Potentiometer_VTG = 0;
uint8_t Speed_A;
uint8_t Speed_B;
uint8_t Control_Output;
uint8_t Current_Out;

// Add global variables
volatile char StartSoftDelay = 0;
volatile unsigned int TMR_SoftDelay = 0;
volatile unsigned int soft_start_voltage = 0;
volatile char SoftStart_Completed = 0;
unsigned int temp_voltage = 0;       // temporary voltage during ramp
unsigned int TMR_On_Delay = 0;
unsigned int TMR_Off_Delay = 0;
uint8_t ON_Delay_Flag = 0;
uint8_t OFF_Delay_Flag = 0;
uint8_t Stop_Controller = 0;
unsigned char buffer[200]; // Start byte + 2x4 bytes + 1 byt
unsigned int Step_Size = 0;
unsigned int Step_Count = 0;


//PATTERNS
const char binary_pattern[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A 10
    0x7C, // b 11
    0x39, // C 12
    0x5E, // d 13
    0x79, // E 14
    0x71, // F 15
    0x76, // G 16
    0x54, // H 17
    0x5C, // I 18
    0x5E, // J 19
    0x73, // K 20
    0x38, // L 21
    0x37, // M 22
    0x50, // N 23
    0x5C, // O 24
    0x73, // P 25
    0x67, // Q 26
    0x50, // R 27
    0x6D, // S 28
    0x78, // T 29
    0x3E, // U 30
    0x1C, // V 31
    0x2A, // W 32
    0x76, // X 33
    0x6E, // Y 34
    0x5B  // Z 35
};

//DISPLAY ARRAYS

unsigned int digits_1[5]; // Example digits to display
unsigned int digits_2[5]; // Example digits to display
unsigned int digits_3[5]; // Example digits to display
unsigned int digits_4[5]; // Example digits to display
unsigned int digits_5[5]; // Example digits to display
unsigned int digits_6[5]; // Example digits to display
unsigned int digits_7[5]; // Example digits to display
unsigned int digits_8[5]; // Example digits to display
unsigned int digits_9[5]; // Example digits to display
unsigned int digits_10[5]; // Example digits to display
unsigned int digits_11[5]; // Example digits to display
unsigned int digits_12[5]; // Example digits to display
unsigned int digits_13[5]; // Example digits to display
unsigned int digits_14[5]; // Example digits to display
unsigned int digits_15[5]; // Example digits to display

unsigned char display_digits = 0x01;  // Example value to check LSB (odd/even check)   
unsigned char segment_pattern; // To hold the segment pattern for each digit
unsigned char current_digit = 0, UpdateModeDelay;  // Start from the 3rd digit (index 2)
unsigned int flag =0;

#define LONG_PRESS_DURATION 2500  // 3000 ms for long press (3 seconds)
#define SHORT_PRESS_THRESHOLD 100  // Minimum press duration for a short press
#define BUTTON_PRESSED 0 // Assuming button is active-low (pressed = 0)
#define BUTTON_RELEASED 1

typedef enum {
    STAGE_0,
    STAGE_1,
    STAGE_2
} Stage;

typedef enum {
    STOP_CONTROLLER_MODE = 0,
    START_CONTROLLER_MODE = 1
} ControllerMode;

Stage currentStage = STAGE_0;
ControllerMode currentMode = STOP_CONTROLLER_MODE;

typedef enum {
    MODE_VOLTAGE,
    MODE_FREQUENCY,
    MODE_ON_DELAY,
    MODE_OFF_DELAY,
    MODE_SOFT_START_DELAY
} Stage1Mode;

typedef enum {
    MODE_NPN_SENSOR_I,
    MODE_SENSOR_II,  
    MODE_PHOTO_SENSOR,
    MODE_SPEED_CONTROL, 
    MODE_SPEED_A_B,
    MODE_CONTROL_OUTPUT,
    MODE_CURRENT_OUTPUT           
} Stage2Mode;

typedef struct {
    // Stage 1
    uint8_t VOLTAGE;
    uint8_t Output_VTG_Stop;
    uint8_t FREQUENCY;
    uint8_t ON_Delay;
    uint8_t OFF_Delay;
    uint8_t SOFT_Delay;

    // Stage 2
    uint8_t NPN_Sensor_1;
    uint8_t NPN_Sensor_2;
    uint8_t Potentiometer_VTG;
    uint8_t Control_Output;
    uint8_t Speed_A;
    uint8_t Speed_B;
    uint8_t PhotoSensor_Flag;
    uint8_t Current_Out;
} system_data_t;
system_data_t systemData;

//Stage currentStage = STAGE_1;
Stage1Mode currentStage1Mode = MODE_VOLTAGE;
Stage2Mode currentStage2Mode = MODE_SPEED_CONTROL;

// Button press detection variables
volatile uint16_t pressDurationSettingSwitch = 0;
volatile uint16_t pressDurationSimultaneous = 0;
volatile uint16_t  uartsendcount = 0;
volatile bool longPressDetectedSettingSwitch = false;
volatile bool longPressDetectedSimultaneous = false;
volatile bool shortPressDetected = false;
volatile bool settingSwitchReleased = true;
uint8_t  DebounceDelay, DebounceDelay_Decrement;
volatile bool StartDebounceDelayTimer = false;
volatile bool DebounceCompleted = false;
volatile bool StartDebounceDelayTimer_Decrement = false;
volatile bool DebounceCompleted_Decrement = false;
volatile uint16_t pressDurationPowerSwitch = 0;
volatile bool shortPressDetectedPowerSwitch = false;
unsigned int UARTFlagDelay = 0;
bool UARTFlag = false;

// All function declaration 
void setup_timer0();
void initSensorPins();
//void initADC();
//unsigned int ADC_Read(unsigned char channel);
void UART_Write_Text(uint8_t *text);
void send_data_human_readable();  // Send data to PIC16F1522;
void control_led_and_7segment_FOR_MODE_VOLTAGE(void);
void control_led_and_7segment_FOR_MODE_FREQUENCY(void);
void control_led_and_7segment_FOR_MODE_ON_DELAY(void);
void control_led_and_7segment_FOR_MODE_OFF_DELAY(void);
void control_led_and_7segment_FOR_MODE_SOFT_START_DELAY(void);
void control_led_and_7segment_FOR_MODE_NPN_SENSOR_I();
void control_led_and_7segment_FOR_MODE_SENSOR_II();
void control_led_and_7segment_FOR_MODE_PHOTO_SENSOR();
void control_led_and_7segment_FOR_MODE_SPEED_CONTROL();
void control_led_and_7segment_FOR_MODE_SPEED_A_B();
void control_led_and_7segment_FOR_MODE_CONTROL_OUTPUT();
void control_led_and_7segment_FOR_MODE_CURRENT_OUTPUT();
void control_led_and_7segment_FOR_MODE_STOP_CONTROLLER(void);
void SaveVariablesToNVM(void);
void StartSoftStartup();
void __interrupt() ISR(void);
void updateMode();
void updateLEDs();

void setup_timer0() {
    // Configure Timer0 for 8-bit mode, system clock (FOSC/4), and prescaler 1:256
    T0CON0bits.T016BIT = 0;  // 8-bit mode
    T0CON0bits.T0OUTPS = 0b0000;
    T0CON1bits.T0CS = 0b010; // Clock source FOSC/4   "FOSC = 16 MHz
    T0CON1bits.T0CKPS = 0b0100; // Prescaler 1:16 for better precision
    T0CON1bits.T0ASYNC = 0b0;
    TMR0L = 6;  // Reload Timer0 for 1 ms
    T0CON0bits.T0EN = 1; // Enable Timer0

    // Enable Timer0 overflow interrupt
    PIR0bits.TMR0IF = 0; // Clear the interrupt flag for Timer0
    PIE0bits.TMR0IE = 1; // Enable Timer0 interrupt
    INTCONbits.GIE = 1;  // Global interrupt enable
    INTCONbits.PEIE = 1; // Peripheral interrupt enable
}
void ADC_Init(void) {
    // Set RE0 as input
    TRISE0 = 1;

    // Set RE0 as analog
    ANSELEbits.ANSE0 = 1;       // Set RE0 as analog input = 1;

    // Select ADC channel RE0 (CHS = 0b100000)
    ADCON0 = 0b10000000; // CHS<5:0> = 100000 (RE0), GO/DONE = 0, ADON = 1
    ADCON1 = 0b10000000; // ADFM = 1 (right justified), FOSC/2 = 000, Vref = VDD

    // Enable ADC
    ADON = 1;

    __delay_ms(2); // Allow time for ADC to stabilize
}

unsigned int Read_ADC(void) {
    ADCON0bits.GOnDONE = 1;                  // Start conversion
    while(ADCON0bits.GOnDONE);              // Wait until conversion is done
    return ((ADRESH << 8) | ADRESL);  // Combine high and low bytes
}

void control_led_and_7segment_FOR_MODE_VOLTAGE(void)
{  
    if (IncreaseVoltageSwitch == 0 && SettingSwitch == 1)    
    {
        StartDebounceDelayTimer = true;
        if(DebounceCompleted)
        if (VOLTAGE <= 239)
        {
            VOLTAGE++;
            StartDebounceDelayTimer = false;
            DebounceCompleted = false;
        }
        digits_1[0] = 0;
        digits_1[1] = 0;
        digits_1[2] = (VOLTAGE / 100) % 10; // Hundreds        // Units
        digits_1[3] = (VOLTAGE / 10) % 10;  // Tens                           // Set the remaining digits to 0
        digits_1[4] = VOLTAGE % 10; 
    }
    
    else if (DecreaseVoltageSwitch == 0 && SettingSwitch == 1)   
    {
        StartDebounceDelayTimer_Decrement = true;
        if(DebounceCompleted_Decrement)
        if (VOLTAGE > 0)
        {
            VOLTAGE--;
            StartDebounceDelayTimer_Decrement = false;
            DebounceCompleted_Decrement = false;
        }
         digits_1[0] = 0;
         digits_1[1] = 0;
         digits_1[2] = (VOLTAGE / 100) % 10; // Hundreds        // Units
         digits_1[3] = (VOLTAGE / 10) % 10;  // Tens                           // Set the remaining digits to 0
         digits_1[4] = VOLTAGE % 10;   
    }
    LATDbits.LATD6 = 1; // Enable ULN
    DG1_LED = 1;  // Turn on LED connected to DG1
    __delay_ms(1); // Let the LED stay on for a moment
    DG1_LED = 0;  // Turn off the LED
    LATDbits.LATD6 = 0; // Disable ULN
    if ( UARTFlag) {
        UARTFlag = false;
        // Transmit sequence
        EUSART1_Write(0xAA); // Start byte or header
        EUSART1_Write(VOLTAGE); // 8-bit voltage
        EUSART1_Write((uint8_t) (FREQUENCY >> 8)); // Send high byte
        EUSART1_Write((uint8_t)(FREQUENCY & 0xFF));   // Send low byte
    }
    flag = 1;
}

void control_led_and_7segment_FOR_MODE_FREQUENCY(void)
{
    // Check if the UpSwitch is pressed
    if (IncreaseVoltageSwitch == 0 && SettingSwitch == 1)                                   // UP_Switch  IncreaseVoltageSwitch
    {
          StartDebounceDelayTimer = true;
        if(DebounceCompleted)
        if (FREQUENCY <= 399)
        {
            FREQUENCY++;
            StartDebounceDelayTimer = false;
            DebounceCompleted = false;
        }
        digits_2[0] = 0;
        digits_2[1] = 0;
        digits_2[2] = (FREQUENCY / 100) % 10; // Hundreds        // Units
        digits_2[3] = (FREQUENCY / 10) % 10;  // Tens                           // Set the remaining digits to 0
        digits_2[4] = FREQUENCY % 10; 
    }
    // Check if the DownSwitch is pressed
     if (DecreaseVoltageSwitch == 0 && SettingSwitch == 1)                                //  DOWN_Switch  DecreaseVoltageSwitch
     {
          StartDebounceDelayTimer = true;
        if(DebounceCompleted)
        if (FREQUENCY > 40)
        {
            FREQUENCY--;
            StartDebounceDelayTimer = false;
            DebounceCompleted = false;
        }
        digits_2[0] = 0;
        digits_2[1] = 0;
        digits_2[2] = (FREQUENCY / 100) % 10; // Hundreds        // Units
        digits_2[3] = (FREQUENCY / 10) % 10;  // Tens                           // Set the remaining digits to 0
        digits_2[4] = FREQUENCY % 10; 
     }
//    // Check if the UpSwitch is pressed
//    if (IncreaseVoltageSwitch == 0 && SettingSwitch == 1)                                   // UP_Switch  IncreaseVoltageSwitch
//    {
//        // Display "EFULL" on the 7-segment display
//        digits_2[0] = 0x79;  // 'E' in 7-segment
//        digits_2[1] = 0x71;  // 'F' in 7-segment
//        digits_2[2] = 0x3E;  // 'U' in 7-segment
//        digits_2[3] = 0x38;  // 'L' in 7-segment
//        digits_2[4] = 0x38;  // 'L' in 7-segment
//        
//        FREQUENCY = 1;
//    }
//    // Check if the DownSwitch is pressed
//     if (DecreaseVoltageSwitch == 0 && SettingSwitch == 1)                                //  DOWN_Switch  DecreaseVoltageSwitch
//     {
//        // Display "EHALF" on the 7-segment display
//        digits_2[0] = 0x79;  // 'E' in 7-segment
//        digits_2[1] = 0x76;  // 'H' in 7-segment
//        digits_2[2] = 0x77;  // 'A' in 7-segment
//        digits_2[3] = 0x38;  // 'L' in 7-segment
//        digits_2[4] = 0x71;  // 'F' in 7-segment
//        
//        FREQUENCY = 0;
//     }
//    if (UARTFlag) {
//    UARTFlag = false;  // Reset the flag
//
//    // Send current value via UART
//    EUSART1_Write(0xAA); // Start Frame
//    EUSART1_Write(VOLTAGE);
//    EUSART1_Write(FREQUENCY);
//
//    // You can add any other periodic UART-related task here
//    }
    LATDbits.LATD6 = 1; // Enable ULN (LED pin controls)
    DG2_LED = 1;  // Turn on LED connected to RB1
    __delay_ms(1); // Let the LED stay on for a moment
    DG2_LED = 0;  // Turn off the LED
    LATDbits.LATD6 = 0; // Disable ULN (so RE1 pin controls the 7-segment)
    if (UARTFlag) {
        UARTFlag = false;
        EUSART1_Write(0xAA);
        EUSART1_Write(VOLTAGE);
        EUSART1_Write((uint8_t) (FREQUENCY >> 8)); // Send high byte
        EUSART1_Write((uint8_t)(FREQUENCY & 0xFF));   // Send low byte
    }
    
    flag = 2;
}

void control_led_and_7segment_FOR_MODE_ON_DELAY(void)
{
    if (IncreaseVoltageSwitch == 0 && SettingSwitch == 1)                            // UP_Switch  IncreaseVoltageSwitch
    {       
        StartDebounceDelayTimer = true;
        if(DebounceCompleted)
        if (ON_Delay < 98)
        {
            ON_Delay++;
            StartDebounceDelayTimer = false;
            DebounceCompleted = false;
        }
        digits_3[0] = 0;
        digits_3[1] = 0;
        digits_3[2] = 0; // Hundreds        // Units
        digits_3[3] = (ON_Delay / 10) % 10;  // Tens                           // Set the remaining digits to 0
        digits_3[4] = ON_Delay % 10;
    }
    if (DecreaseVoltageSwitch == 0 && SettingSwitch == 1)                            //  DOWN_Switch  DecreaseVoltageSwitch
    {
        StartDebounceDelayTimer_Decrement = true;
        if(DebounceCompleted_Decrement)
        if (ON_Delay > 0)    
        {
            ON_Delay--;
            StartDebounceDelayTimer_Decrement = false;
            DebounceCompleted_Decrement = false;
        }
        digits_3[0] = 0;
        digits_3[1] = 0;
        digits_3[2] = 0; // Hundreds        // Units(ON_Delay / 100) % 10;
        digits_3[3] = (ON_Delay / 10) % 10;  // Tens                           // Set the remaining digits to 0
        digits_3[4] = ON_Delay % 10;
    }
    LATDbits.LATD6 = 1; // Enable ULN
    DG3_LED = 1;  // Turn on LED connected to DG1
    __delay_ms(1); // Let the LED stay on for a moment
    DG3_LED = 0;  // Turn off the LED
    LATDbits.LATD6 = 0; // Disable ULN
    
    if (UARTFlag) {
        UARTFlag = false;
        EUSART1_Write(0xAA);
        EUSART1_Write(VOLTAGE);
        EUSART1_Write((uint8_t) (FREQUENCY >> 8)); // Send high byte
        EUSART1_Write((uint8_t)(FREQUENCY & 0xFF));   // Send low byte
    }
    flag = 3;
}
void control_led_and_7segment_FOR_MODE_OFF_DELAY(void)
{
    if (IncreaseVoltageSwitch == 0 && SettingSwitch == 1)                                   // UP_Switch  IncreaseVoltageSwitch
    {        
        StartDebounceDelayTimer = true;
        if(DebounceCompleted)
        if (OFF_Delay < 98)
        {
            OFF_Delay++;
            StartDebounceDelayTimer = false;
            DebounceCompleted = false;
        }
        digits_4[0] = 0;
        digits_4[1] = 0;
        digits_4[2] = 0; // Hundreds        // Units
        digits_4[3] = (OFF_Delay / 10) % 10;  // Tens                           // Set the remaining digits to 0
        digits_4[4] = OFF_Delay % 10; 
    }
    
     if (DecreaseVoltageSwitch == 0 && SettingSwitch == 1)                              //  DOWN_Switch  DecreaseVoltageSwitch
    {        
        StartDebounceDelayTimer_Decrement = true;
        if(DebounceCompleted_Decrement)
        if (OFF_Delay > 0)
        {
            OFF_Delay--;
            StartDebounceDelayTimer_Decrement = false;
            DebounceCompleted_Decrement = false;
        }
         digits_4[0] = 0;
         digits_4[1] = 0;
         digits_4[2] = 0; // Hundreds        // Units
         digits_4[3] = (OFF_Delay / 10) % 10;  // Tens                           // Set the remaining digits to 0
         digits_4[4] = OFF_Delay % 10;  
    }
    LATDbits.LATD6 = 1; // Enable ULN
    DG4_LED = 1;  // Turn on LED connected to DG1
    __delay_ms(1); // Let the LED stay on for a moment
    DG4_LED = 0;  // Turn off the LED
    LATDbits.LATD6 = 0; // Disable ULN
    if (UARTFlag) {
        UARTFlag = false;
        EUSART1_Write(0xAA);
        EUSART1_Write(VOLTAGE);
        EUSART1_Write((uint8_t) (FREQUENCY >> 8)); // Send high byte
        EUSART1_Write((uint8_t)(FREQUENCY & 0xFF));   // Send low byte
    }
    flag = 4;
}

void control_led_and_7segment_FOR_MODE_SOFT_START_DELAY(void)
{
    if (IncreaseVoltageSwitch == 0 && SettingSwitch == 1)                                  // UP_Switch  IncreaseVoltageSwitch
    {
        StartDebounceDelayTimer = true;
        if(DebounceCompleted)
        if (SOFT_START_Delay < 98)
        {
            SOFT_START_Delay++;
            StartDebounceDelayTimer = false;
            DebounceCompleted = false;
        }
        digits_5[0] = 0;
        digits_5[1] = 0;
        digits_5[2] = 0; // Hundreds        // Units
        digits_5[3] = (SOFT_START_Delay / 10) % 10;  // Tens                           // Set the remaining digits to 0
        digits_5[4] = SOFT_START_Delay % 10; 
    }    
    if (DecreaseVoltageSwitch == 0 && SettingSwitch == 1)                              //  DOWN_Switch  DecreaseVoltageSwitch
    {
        StartDebounceDelayTimer_Decrement = true;
        if(DebounceCompleted_Decrement)
        if (SOFT_START_Delay > 0)
        {
            SOFT_START_Delay--;
            StartDebounceDelayTimer_Decrement = false;
            DebounceCompleted_Decrement = false;
        }
         digits_5[0] = 0;
         digits_5[1] = 0;
         digits_5[2] = 0; // Hundreds        // Units
         digits_5[3] = (SOFT_START_Delay / 10) % 10;  // Tens                           // Set the remaining digits to 0
         digits_5[4] = SOFT_START_Delay % 10;  
    }
    LATDbits.LATD6 = 1; // Enable ULN
    DG5_LED = 1;  // Turn on LED connected to DG1
    __delay_ms(1); // Let the LED stay on for a moment
    DG5_LED = 0;  // Turn off the LED
    LATDbits.LATD6 = 0; // Disable ULN
    if (UARTFlag) {
        UARTFlag = false;
        EUSART1_Write(0xAA);
        EUSART1_Write(VOLTAGE);
        EUSART1_Write((uint8_t) (FREQUENCY >> 8)); // Send high byte
        EUSART1_Write((uint8_t)(FREQUENCY & 0xFF));   // Send low byte
    }
    flag = 5;
}

void control_led_and_7segment_FOR_MODE_NPN_SENSOR_I(void)
{   
        // Display "P003" on the 7-segment display
        digits_8[0] = 0x00;  // '' in 7-segment
        digits_8[1] = 0x73;  // 'P' in 7-segment
        digits_8[2] = 0x3f;  // '0' in 7-segment
        digits_8[3] = 0x3f;  // '0' in 7-segment
        digits_8[4] = 0x06;  // '3' in 7-segment
    // Read NPN Sensor 1 state and update flag    
    if(NPN_SENSOR_1_PIN == 0) {
        NPN_Sensor_1 = false;  // Sensor low - Controller runningLATDbits.LATD5 = 1; // Enable ULN 
        
        
//        if (UARTFlag) {
//        UARTFlag = false;  // Reset the flag
//
//        // Send current value via UART
//        EUSART1_Write(0xAA); // Start Frame
//        EUSART1_Write(Output_VTG_Stop);
//        EUSART1_Write(FREQUENCY);
//
//        // You can add any other periodic UART-related task here
//        }
    }
    else if (NPN_SENSOR_1_PIN == 1) {
        NPN_Sensor_1 = true;  // Sensor high -Stop controller
        
//        if (UARTFlag) {
//        UARTFlag = false;  // Reset the flag
//
//        // Send current value via UART
//        EUSART1_Write(0xAA); // Start Frame
//        EUSART1_Write(VOLTAGE);
//        EUSART1_Write(FREQUENCY);
//
//        // You can add any other periodic UART-related task here
//        }
    } 
    
    flag = 8;         
}

void control_led_and_7segment_FOR_MODE_SENSOR_II(void)
{   
        // Display "P006" on the 7-segment display
        digits_11[0] = 0x00;  // '' in 7-segment
        digits_11[1] = 0x73;  // 'P' in 7-segment
        digits_11[2] = 0x3f;  // '0' in 7-segment
        digits_11[3] = 0x3f;  // '0' in 7-segment
        digits_11[4] = 0x5b;  // '6' in 7-segment

        // Read NPN Sensor 1 state and update flag
    if(NPN_SENSOR_2_PIN == 0) {
        NPN_Sensor_1 = false;  // Sensor low - Controller running
//        if (UARTFlag) {
//        UARTFlag = false;  // Reset the flag
//
//        // Send current value via UART
//        EUSART1_Write(0xAA); // Start Frame
//        EUSART1_Write(Output_VTG_Stop);
//        EUSART1_Write(FREQUENCY);
////        EUSART1_Write(Output_VTG_Stop);
//        // You can add any other periodic UART-related task here
//        }
        
    }
        
    else if (NPN_SENSOR_2_PIN == 1) {
        NPN_Sensor_1 = true;  // Sensor high - Stop controller
//        if (UARTFlag) {
//        UARTFlag = false;  // Reset the flag
//
//        // Send current value via UART
//        EUSART1_Write(0xAA); // Start Frame
//        EUSART1_Write(VOLTAGE);
//        EUSART1_Write(FREQUENCY);
//        // You can add any other periodic UART-related task here
//        }
    }
    flag = 11;         
}

void control_led_and_7segment_FOR_MODE_PHOTO_SENSOR(void)
{  
//        // Display "P002" on the 7-segment display
        digits_7[0] = 0x00;  // '' in 7-segment
        digits_7[1] = 0x73;  // 'P' in 7-segment
        digits_7[2] = 0x3f;  // '0' in 7-segment
        digits_7[3] = 0x3f;  // '0' in 7-segment
        digits_7[4] = 0x4f;  // '2' in 7-segment

        // Read photoelectric sensor state and update flag
    if (PHOTO_SENSOR_PIN == 1) {
        PhotoSensor_Flag = true;  // Sensor high - Stop controller
    } 
    if(PHOTO_SENSOR_PIN == 0) {
        PhotoSensor_Flag = false;  // Sensor low - Controller running 
    }        
    flag = 7;  
}

void control_led_and_7segment_FOR_MODE_SPEED_CONTROL(void)
{ 
        // Display "P001" on the 7-segment display
        digits_6[0] = 0x00;  // '' in 7-segment
        digits_6[1] = 0x73;  // 'P' in 7-segment
        digits_6[2] = 0x3f;  // '0' in 7-segment
        digits_6[3] = 0x3f;  // '0' in 7-segment
        digits_6[4] = 0x66;  // '1' in 7-segment
        
//    if (UARTFlag) {
//        UARTFlag = false;  // Reset the flag
//     Read ADC value from potentiometer (example: 10-bit value)
//    Potentiometer_VTG = Read_ADC(); //ADC_GetConversion(0b100000)
//    sprintf(buffer, "ADC: %u\n\r", Potentiometer_VTG);
//    UART_Write_Text(buffer);
        // Split the 10-bit value into high byte and low byte
//        highByte = (uint8_t)(Potentiometer_VTG >> 2);  // Top 8 bits
//        lowByte = (uint8_t)((Potentiometer_VTG & 0x03) << 6);  // Bottom 2 bits (shifted left)
//    }
        LATDbits.LATD5 = 1; // Enable ULN
        DG1_LED = 0;  // Turn off the LED
        DG2_LED = 0;  // Turn on LED connected to DG1
        DG3_LED = 0;  // Turn off the LED
        DG4_LED = 0;  // Turn off the LED
        DG5_LED = 1;  // Turn off the LED
        __delay_ms(1); // Let the LED stay on for a moment
        DG1_LED = 0;  // Turn off the LED
        DG2_LED = 0;  // Turn off the LED
        DG3_LED = 0;  // Turn off the LED
        DG4_LED = 0;  // Turn off the LED
        DG5_LED = 0;  // Turn off the LED
        LATDbits.LATD5 = 0; // Disable ULN 
    flag = 6;  
}

void control_led_and_7segment_FOR_MODE_SPEED_A_B(void)
{   
        // Display "P005" on the 7-segment display
        digits_10[0] = 0x00;  // '' in 7-segment
        digits_10[1] = 0x73;  // 'P' in 7-segment
        digits_10[2] = 0x3f;  // '0' in 7-segment
        digits_10[3] = 0x3f;  // '0' in 7-segment
        digits_10[4] = 0x6d;  // '5' in 7-segment
        
        if (PRESET_SPEED_A == 1)                                  // UP_Switch  IncreaseVoltageSwitch
        {
            Speed_A = 1;
        }
        if (PRESET_SPEED_A == 0)                              //  DOWN_Switch  DecreaseVoltageSwitch
        {
            Speed_A = 0;
            LATDbits.LATD5 = 1; // Enable ULN
            DG1_LED = 1;  // Turn off the LED
            DG2_LED = 0;  // Turn on LED connected to DG1
            DG3_LED = 0;  // Turn off the LED
            DG4_LED = 0;  // Turn off the LED
            DG5_LED = 0;  // Turn off the LED
            __delay_ms(1); // Let the LED stay on for a moment
            DG1_LED = 0;  // Turn off the LED
            DG2_LED = 0;  // Turn off the LED
            DG3_LED = 0;  // Turn off the LED
            DG4_LED = 0;  // Turn off the LED
            DG5_LED = 0;  // Turn off the LED
            LATDbits.LATD5 = 0; // Disable ULN
        }
        if (PRESET_SPEED_B == 1)                                  // UP_Switch  IncreaseVoltageSwitch
        {
            Speed_B = 1;
            
        }
        if (PRESET_SPEED_B == 0)                              //  DOWN_Switch  DecreaseVoltageSwitch
        { 
            Speed_B = 0;
            LATDbits.LATD5 = 1; // Enable ULN
            DG1_LED = 0;  // Turn off the LED
            DG2_LED = 0;  // Turn on LED connected to DG1
            DG3_LED = 1;  // Turn off the LED
            DG4_LED = 0;  // Turn off the LED
            DG5_LED = 0;  // Turn off the LED
            __delay_ms(1); // Let the LED stay on for a moment
            DG1_LED = 0;  // Turn off the LED
            DG2_LED = 0;  // Turn off the LED
            DG3_LED = 0;  // Turn off the LED
            DG4_LED = 0;  // Turn off the LED
            DG5_LED = 0;  // Turn off the LED
            LATDbits.LATD5 = 0; // Disable ULN 
        }
    flag = 10;         
}

void control_led_and_7segment_FOR_MODE_CONTROL_OUTPUT(void)
{   
        // Display "P004" on the 7-segment display
        digits_9[0] = 0x00;  // '' in 7-segment
        digits_9[1] = 0x73;  // 'P' in 7-segment
        digits_9[2] = 0x3f;  // '0' in 7-segment
        digits_9[3] = 0x3f;  // '0' in 7-segment
        digits_9[4] = 0x7d;  // '4' in 7-segment 
      
      if(CONTROL_OUTPUT_PIN == 0){
          
          Control_Output = 0;
      }
      if(CONTROL_OUTPUT_PIN == 1){
          
          Control_Output = 1;
      }
      if (UARTFlag) {
        UARTFlag = false;  // Reset the flag
        EUSART1_Write(0xAA); // Start Frame
        sprintf(buffer, "Control Out: %u\n\r", Control_Output);
        UART_Write_Text(buffer);
      }
    flag = 9;    
}

void control_led_and_7segment_FOR_MODE_CURRENT_OUTPUT(void)
{   
        // Display "P007" on the 7-segment display
        digits_12[0] = 0x00;  // '' in 7-segment
        digits_12[1] = 0x73;  // 'P' in 7-segment
        digits_12[2] = 0x3f;  // '0' in 7-segment
        digits_12[3] = 0x3f;  // '0' in 7-segment
        digits_12[4] = 0x07;  // '7' in 7-segment

        // Read NPN Sensor 1 state and update flag
        flag = 12;         
}

void control_led_and_7segment_FOR_MODE_STOP_CONTROLLER(void) 
{
    // Display "P007" on 7-segment
    digits_15[0] = 0x00;
    digits_15[1] = 0x6D;  // 'P'
    digits_15[2] = 0x78;  // '0'
    digits_15[3] = 0x3f;  // '0'
    digits_15[4] = 0x73;  // '7'
       
    Stop_Controller = 1;
    ON_Delay_Flag = 0;
    currentStage = STAGE_0;

    LATDbits.LATD5 = 1;
    DG1_LED = 0;
    DG2_LED = 1;
    DG3_LED = 0;
    DG4_LED = 0;
    DG5_LED = 0;
    __delay_ms(1);
    DG1_LED = DG2_LED = DG3_LED = DG4_LED = DG5_LED = 0;
    LATDbits.LATD5 = 0;
    if (UARTFlag) {
            UARTFlag = false;

            EUSART1_Write(0xAA); // Start Frame
            EUSART1_Write(Output_VTG_Stop); // Gradually decreasing value
            EUSART1_Write((uint8_t) (STOP_FREQ >> 8)); // Send high byte
            EUSART1_Write((uint8_t)(STOP_FREQ & 0xFF));   // Send low byte
        
    } 
    flag = 15;
}

// Interrupt Service Routine (ISR) for Timer0
void __interrupt() ISR(void) {

    if (PIR0bits.TMR0IF) {
        PIR0bits.TMR0IF = 0;  // Clear Timer0 interrupt flag
        TMR0L = 6;  // Reload Timer0 for 1 ms overflow
        T0CON0bits.T0EN = 1; // Enable Timer0
         
        if (!ON_Delay_Flag && currentStage == STAGE_1) {
            TMR_On_Delay++;
            if (TMR_On_Delay == (ON_Delay * 100)) {
            ON_Delay_Flag = 1;
            OFF_Delay_Flag = 0;
            TMR_On_Delay = 0;

            // Prepare soft start
            soft_start_voltage = 0;
            SoftStart_Completed = 0;

            if (SOFT_START_Delay != 0) {
                soft_start_step_interval = (SOFT_START_Delay * 100) / VOLTAGE;  // Spread delay over VOLTAGE steps
                if (soft_start_step_interval == 0) soft_start_step_interval = 1; // Avoid division by 0 or too fast update
            } else {
                soft_start_step_interval = 1;
                }
            }
        }
        
        if (!OFF_Delay_Flag && currentMode == STOP_CONTROLLER_MODE && Stop_Controller == 1) {
            TMR_Off_Delay++;
        if (TMR_Off_Delay == (OFF_Delay * 100)) {
            OFF_Delay_Flag = 1;
            TMR_Off_Delay = 0;
            } 
        }
        if (ON_Delay_Flag && !SoftStart_Completed) {
            StartSoftDelay = 1;

            TMR_SoftDelay++;
            if (TMR_SoftDelay >= soft_start_step_interval) {  // use calculated variable step
                TMR_SoftDelay = 0;

                if (soft_start_voltage < VOLTAGE) {
                    soft_start_voltage++;
                } else {
                    SoftStart_Completed = 1;
                    StartSoftDelay = 0;
                }
            }
        }

        UpdateModeDelay++;
        if (UpdateModeDelay == 10){
            updateMode();  // Check and update mode transitions every 10ms
            UpdateModeDelay = 0;
        }            
        if(StartDebounceDelayTimer)
        {
            DebounceDelay++;
            if(DebounceDelay == 100)
            {
                DebounceCompleted = true;
                DebounceDelay = 0;
            }
        }
        if(StartDebounceDelayTimer_Decrement)
        {
            DebounceDelay_Decrement++;
            if(DebounceDelay_Decrement == 150)
            {
                DebounceCompleted_Decrement = true;
                DebounceDelay_Decrement = 0;
            }
        }
        
         // UART Flag Logic: Every 400 ms
        UARTFlagDelay++;
        if (UARTFlagDelay >= 5000) {
            UARTFlag = true;
            UARTFlagDelay = 0;
        }   
//        NVMcnt++;
//        if(NVMcnt >= 300){
//            NVMcnt = 0;
//            saveFlag = 1;
//        }
             // Handle PowerSwitch press
      if (STOP_Switch == BUTTON_PRESSED) {
          pressDurationPowerSwitch++;
          if (pressDurationPowerSwitch >= SHORT_PRESS_THRESHOLD && pressDurationPowerSwitch < LONG_PRESS_DURATION) {
              shortPressDetectedPowerSwitch = true;
              pressDurationPowerSwitch = 0;
              
          } 
          }
 // Handle SettingSwitch press
        if (SettingSwitch == BUTTON_PRESSED && IncreaseVoltageSwitch == BUTTON_RELEASED) {
            pressDurationSettingSwitch++;
            settingSwitchReleased = false; // Button is still being pressed
            if (pressDurationSettingSwitch >= LONG_PRESS_DURATION) {
                longPressDetectedSettingSwitch = true;
            }
        } else {
            if (pressDurationSettingSwitch >= SHORT_PRESS_THRESHOLD && pressDurationSettingSwitch < LONG_PRESS_DURATION) {
                shortPressDetected = true;
            }
            pressDurationSettingSwitch = 0;
            settingSwitchReleased = true; // Button released
            longPressDetectedSettingSwitch = false; // Reset long press detection
        }

        // Handle simultaneous press of SettingSwitch + IncreaseVoltageSwitch
        if (SettingSwitch == BUTTON_PRESSED && IncreaseVoltageSwitch == BUTTON_PRESSED) {
            pressDurationSimultaneous++;
            if (pressDurationSimultaneous >= LONG_PRESS_DURATION) {
                longPressDetectedSimultaneous = true;
            }
        } else {
            pressDurationSimultaneous = 0;
            longPressDetectedSimultaneous = false;
        }
        // Your original display logic for 7-segment control
        if (flag == 1) {
            segment_pattern = binary_pattern[digits_1[current_digit]]; 
        } else if (flag == 2) {
            segment_pattern = binary_pattern[digits_2[current_digit]];// digits_2[current_digit];
        } else if (flag == 3) {
            segment_pattern = binary_pattern[digits_3[current_digit]];
            if (current_digit == 3) {
                segment_pattern |= 0x80;
            }
        } else if (flag == 4) {
            segment_pattern = binary_pattern[digits_4[current_digit]];
            if (current_digit == 3) {
                segment_pattern |= 0x80;
            }
        } else if (flag == 5) {
            segment_pattern = binary_pattern[digits_5[current_digit]];
            if (current_digit == 3) {
                segment_pattern |= 0x80;
            }
        } else if (flag == 6) {
            segment_pattern = digits_6[current_digit];
        } else if (flag == 7) {
            segment_pattern = digits_7[current_digit];
        } else if (flag == 8) {
            segment_pattern = digits_8[current_digit];
        } else if (flag == 9) {
            segment_pattern = digits_9[current_digit];
        }else if (flag == 10) {
            segment_pattern = digits_10[current_digit];
        }else if (flag == 11) {
            segment_pattern = digits_11[current_digit];
        }else if (flag == 12) {
            segment_pattern = digits_12[current_digit];   
        }
        else if (flag == 15) {
            segment_pattern = digits_15[current_digit];   
        }

        // Control the segments (PORTB)
        LATDbits.LATD6=0;
        LATB = segment_pattern;
        
        // Use bitwise AND to check the segment pattern for RE1 control
        if (segment_pattern & 0x01) {  // If LSB of the pattern is 1, RE1 should be high
            PORTEbits.RE1 = 1;  // Set RE1 HIGH
        } else {
            PORTEbits.RE1 = 0;  // Set RE1 LOW
        }

        // Toggle display_digits to test the condition
        display_digits ^= 0x01;  // Toggle the LSB (odd -> even -> odd)
        LATDbits.LATD6=0;
        // Update the digit control (digit3, digit4, digit5, etc.)
        if (flag == 2 || flag == 1) {
            switch (current_digit) {
                case 2:
                    digit3 = 1;
                    __delay_ms(1);
                    digit3 = 0;
                    break;
                case 3:
                    digit4 = 1;
                    __delay_ms(1);
                    digit4 = 0;
                    break;
                case 4:
                    digit5 = 1;
                    __delay_ms(1);
                    digit5 = 0;
                    break;
            }
        } else if (flag == 6 || flag == 7 || flag == 8 || flag == 9 || flag == 10
                || flag == 11 || flag == 12 || flag == 15 ) {   
            switch (current_digit) {
                case 0:
                    digit1 = 1;
                    __delay_ms(1);
                    digit1 = 0;
                    break;
                case 1:
                    digit2 = 1;
                    __delay_ms(1);
                    digit2 = 0;
                    break;
                case 2:
                    digit3 = 1;
                    __delay_ms(1); 
                    digit3 = 0;
                    break;
                case 3:
                    digit4 = 1;
                    __delay_ms(1); 
                    digit4 = 0;
                    break;
                case 4:
                    digit5 = 1;
                    __delay_ms(1);
                    digit5 = 0;
                    break;
            }
        }
                // Update the digit control (digit3, digit4, digit5, etc.)
        else {
            switch (current_digit) {    
                case 3:
                    digit4 = 1; 
                    __delay_ms(1);
                    digit4 = 0;
                    break;
                case 4:
                    digit5 = 1;
                    __delay_ms(1); 
                    digit5 = 0;
                    break;
            }
        }
        LATDbits.LATD6=0; 
        // Move to the next digit (circular)
        current_digit++;
        if (current_digit >= 5) {
            current_digit = 0; // Start from the first digit again
        }
    }
    //    / interrupt handler
    if(INTCONbits.PEIE == 1)
    {
        if(PIE7bits.NVMIE == 1 && PIR7bits.NVMIF == 1)
        {
            NVM_ISR();
        }
        if(PIE3bits.TX1IE == 1 && PIR3bits.TX1IF == 1)
        {
            EUSART1_TxInterruptHandler();
        } 
        else if(PIE3bits.RC1IE == 1 && PIR3bits.RC1IF == 1)
        {
            EUSART1_RxInterruptHandler();
        } 
        else
        {
            //Unhandled Interrupt
        }
    }
}

void updateMode(void) {

    // POWER SWITCH LOGIC (toggle start/stop and stage 0 <-> 1)
    if (shortPressDetectedPowerSwitch) {
        if (currentMode == STOP_CONTROLLER_MODE) {
            currentMode = START_CONTROLLER_MODE;
            currentStage = STAGE_1;
            currentStage1Mode = MODE_VOLTAGE;
            __delay_ms(500);
        } else {
            currentMode = STOP_CONTROLLER_MODE;
            currentStage = STAGE_0;
            __delay_ms(500);
        }
        shortPressDetectedPowerSwitch = false;
    }

    // Allow only if system is active
    if (currentMode == START_CONTROLLER_MODE) {

        // STAGE TRANSITION (Setting + IncreaseVoltage long press)
        if (longPressDetectedSimultaneous) {
            if (currentStage == STAGE_1) {
                currentStage = STAGE_2;
                currentStage2Mode = MODE_NPN_SENSOR_I;
            } else if (currentStage == STAGE_2) {
                currentStage = STAGE_1;
                currentStage1Mode = MODE_VOLTAGE;
            }
            __delay_ms(1000);
            longPressDetectedSimultaneous = false;
        }

        // LONG PRESS ON SETTING SWITCH (Voltage <-> Frequency)
        if (longPressDetectedSettingSwitch) {
            if (currentStage == STAGE_1 && currentStage1Mode == MODE_VOLTAGE) {
                currentStage1Mode = MODE_FREQUENCY;
            } else if (currentStage == STAGE_1) {
                currentStage1Mode = MODE_VOLTAGE;
            }
            __delay_ms(1000);
            longPressDetectedSettingSwitch = false;
        }

        // SHORT PRESS TO CYCLE MODES
        if (shortPressDetected) {
            if (currentStage == STAGE_1) {
                switch (currentStage1Mode) {
                    case MODE_FREQUENCY:
                        currentStage1Mode = MODE_ON_DELAY;
                        break;
                    case MODE_ON_DELAY:
                        currentStage1Mode = MODE_OFF_DELAY; 
                        break;
                    case MODE_OFF_DELAY:
                        currentStage1Mode = MODE_SOFT_START_DELAY; 
                        break;
                    case MODE_SOFT_START_DELAY:
                        currentStage1Mode = MODE_FREQUENCY; 
                        break;
                    default:
                        break;
                }
            } else if (currentStage == STAGE_2) {
                switch (currentStage2Mode) {
                    case MODE_NPN_SENSOR_I:
                        currentStage2Mode = MODE_SENSOR_II; 
                        break;
                    case MODE_SENSOR_II:
                        currentStage2Mode = MODE_PHOTO_SENSOR; 
                        break;
                    case MODE_PHOTO_SENSOR:
                        currentStage2Mode = MODE_SPEED_CONTROL; 
                        break;
                    case MODE_SPEED_CONTROL:
                        currentStage2Mode = MODE_SPEED_A_B; 
                        break;
                    case MODE_SPEED_A_B:
                        currentStage2Mode = MODE_CONTROL_OUTPUT; 
                        break;
                    case MODE_CONTROL_OUTPUT:
                        currentStage2Mode = MODE_CURRENT_OUTPUT; 
                        break;
                    case MODE_CURRENT_OUTPUT:
                        currentStage2Mode = MODE_NPN_SENSOR_I;
                        break;
                    default:
                        break;
                }
            }
            shortPressDetected = false;
        }
    }

    updateLEDs();
}
void updateLEDs() {
    if (currentMode == STOP_CONTROLLER_MODE) {
        // STAGE_0: system is OFF
        DG1_LED = 0;
        DG2_LED = 1;
        DG3_LED = 0;
        DG4_LED = 0;
        DG5_LED = 0;
        control_led_and_7segment_FOR_MODE_STOP_CONTROLLER();
    } 
    else if (currentStage == STAGE_1) {
        switch (currentStage1Mode) {
            case MODE_VOLTAGE:
                DG1_LED = 1;
                DG2_LED = 0;
                DG3_LED = 0; 
                DG4_LED = 0;
                DG5_LED = 0;
                control_led_and_7segment_FOR_MODE_VOLTAGE();
                break;
            case MODE_FREQUENCY:
                DG1_LED = 0;
                DG2_LED = 1;
                DG3_LED = 0; 
                DG4_LED = 0; 
                DG5_LED = 0;
                control_led_and_7segment_FOR_MODE_FREQUENCY();
                break;
            case MODE_ON_DELAY:
                DG1_LED = 0;
                DG2_LED = 0; 
                DG3_LED = 1; 
                DG4_LED = 0;
                DG5_LED = 0;
                control_led_and_7segment_FOR_MODE_ON_DELAY();
                break;
            case MODE_OFF_DELAY:
                DG1_LED = 0;
                DG2_LED = 0; 
                DG3_LED = 0;
                DG4_LED = 1; 
                DG5_LED = 0;
                control_led_and_7segment_FOR_MODE_OFF_DELAY(); 
                break;
            case MODE_SOFT_START_DELAY:
                DG1_LED = 0;
                DG2_LED = 0;
                DG3_LED = 0; 
                DG4_LED = 0;
                DG5_LED = 1;
                control_led_and_7segment_FOR_MODE_SOFT_START_DELAY(); 
                break;
        }
    }
    else if (currentStage == STAGE_2) {
        switch (currentStage2Mode) {
            case MODE_NPN_SENSOR_I:
                control_led_and_7segment_FOR_MODE_NPN_SENSOR_I();
                break;
            case MODE_SENSOR_II:
                control_led_and_7segment_FOR_MODE_SENSOR_II();
                break;
            case MODE_PHOTO_SENSOR:
                control_led_and_7segment_FOR_MODE_PHOTO_SENSOR();
                break;
            case MODE_SPEED_CONTROL:
                DG1_LED = 0;
                DG2_LED = 0; 
                DR3_LED = 0; 
                DG4_LED = 0; 
                DG5_LED = 1;
                control_led_and_7segment_FOR_MODE_SPEED_CONTROL();
                break;
            case MODE_SPEED_A_B:
                    DG1_LED = 0; 
                    DG2_LED = 0;
                    DR3_LED = 1; 
                    DG4_LED = 0;
                    DG5_LED = 0;
                control_led_and_7segment_FOR_MODE_SPEED_A_B(); 
                break;
            case MODE_CONTROL_OUTPUT:
                control_led_and_7segment_FOR_MODE_CONTROL_OUTPUT();
                break;
            case MODE_CURRENT_OUTPUT:
                control_led_and_7segment_FOR_MODE_CURRENT_OUTPUT(); 
                break;
        }
    }
}      


// UART Write Text Function
void UART_Write_Text(uint8_t *text) {
    while (*text != '\0') {  // Loop until the null terminator is encountered
        EUSART1_Write(*text);  // Transmit each character
        text++;                // Move to the next character
    }
}
//void SaveVariablesToNVM(void)
//{
//    // Save Mode 1 variables
//    CONFIGURATION_Write(NVM_VOLTAGE_ADDR, VOLTAGE);
//    CONFIGURATION_Write(NVM_OUTPUT_VTG_STOP_ADDR, Output_VTG_Stop);
//    CONFIGURATION_Write(NVM_FREQUENCY_ADDR, FREQUENCY);
//    CONFIGURATION_Write(NVM_ON_DELAY_ADDR, ON_Delay);
//    CONFIGURATION_Write(NVM_OFF_DELAY_ADDR, OFF_Delay);
//    CONFIGURATION_Write(NVM_SOFT_DELAY_ADDR, SOFT_Delay);
//
//    // Save Mode 2 variables
//    CONFIGURATION_Write(NVM_POTENTIOMETER_VTG_ADDR, Potentiometer_VTG);
//    CONFIGURATION_Write(NVM_PHOTOSENSOR_FLAG_ADDR, (uint8_t)PhotoSensor_Flag);
//    CONFIGURATION_Write(NVM_NPN_SENSOR_1_ADDR, (uint8_t)NPN_Sensor_1);
//    CONFIGURATION_Write(NVM_CONTROL_OUTPUT_ADDR, Control_Output);
//    CONFIGURATION_Write(NVM_SPEED_A_ADDR, Speed_A);
//    CONFIGURATION_Write(NVM_SPEED_B_ADDR, Speed_B);
//    CONFIGURATION_Write(NVM_NPN_SENSOR_2_ADDR, (uint8_t)NPN_Sensor_2);
//    CONFIGURATION_Write(NVM_CURRENT_OUT_ADDR, Current_Out);
//}
void SaveSystemDataToFlash(void)
{
    flash_data_t flashBuffer[PROGMEM_PAGE_SIZE] = {0};
    uint8_t *src = (uint8_t*)&systemData;

    for (uint8_t i = 0; i < sizeof(systemData); i += 2)
    {
        flashBuffer[i / 2] = src[i];
        if ((i + 1) < sizeof(systemData))
            flashBuffer[i / 2] |= ((uint16_t)src[i + 1] << 8);
    }

    FLASH_PageErase(FLASH_SAVE_ADDR);
    FLASH_RowWrite(FLASH_SAVE_ADDR, flashBuffer);
}

//void LoadVariablesFromNVM(void)
//{
//    // Load Mode 1 variables
//    VOLTAGE = CONFIGURATION_Read(NVM_VOLTAGE_ADDR);
//    Output_VTG_Stop = CONFIGURATION_Read(NVM_OUTPUT_VTG_STOP_ADDR);
//    FREQUENCY = CONFIGURATION_Read(NVM_FREQUENCY_ADDR);
//    ON_Delay = CONFIGURATION_Read(NVM_ON_DELAY_ADDR);
//    OFF_Delay = CONFIGURATION_Read(NVM_OFF_DELAY_ADDR);
//    SOFT_Delay = CONFIGURATION_Read(NVM_SOFT_DELAY_ADDR);
//
//    // Load Mode 2 variables
//    Potentiometer_VTG = CONFIGURATION_Read(NVM_POTENTIOMETER_VTG_ADDR);
//    PhotoSensor_Flag = (CONFIGURATION_Read(NVM_PHOTOSENSOR_FLAG_ADDR) != 0);
//    NPN_Sensor_1 = (CONFIGURATION_Read(NVM_NPN_SENSOR_1_ADDR) != 0);
//    Control_Output = CONFIGURATION_Read(NVM_CONTROL_OUTPUT_ADDR);
//    Speed_A = CONFIGURATION_Read(NVM_SPEED_A_ADDR);
//    Speed_B = CONFIGURATION_Read(NVM_SPEED_B_ADDR);
//    NPN_Sensor_2 = (CONFIGURATION_Read(NVM_NPN_SENSOR_2_ADDR) != 0);
//    Current_Out = CONFIGURATION_Read(NVM_CURRENT_OUT_ADDR);
//}
void LoadSystemDataFromFlash(void)
{
    flash_address_t address = FLASH_SAVE_ADDR;
    flash_data_t flashWord;
    uint8_t *dest = (uint8_t*)&systemData;

    for (uint8_t i = 0; i < sizeof(systemData); i += 2)
    {
        flashWord = FLASH_Read(address);
        dest[i] = (uint8_t)flashWord;
        if ((i + 1) < sizeof(systemData))
            dest[i + 1] = (uint8_t)(flashWord >> 8);
        address++;
    }
}

void main(void) 
{
    SYSTEM_Initialize();
//    ADC_Initialize();
    EUSART1_Initialize();
//    LoadSystemDataFromFlash();
    
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 
   
    TRISD = 0x00; // define PORTD as output
    PORTD = 0x00; // initialize PORTD pins to active low
    TRISE = 0x00;
    TRISB = 0x00; // Set PORTB as output for the display
    ADCON1 = 0x0F;
    
    // Set U3_PIN1 (RD6) as output U1_PIN4
    TRISDbits.TRISD6 = 0;
    LATDbits.LATD6 = 0;
    // Set U3_PIN2 (RD5) as output U1_PIN3
    TRISDbits.TRISD5 = 0;
    LATDbits.LATD5=0;
    // Set DG5 LED (RE1) as output U1_PIN26 (S5)
    PORTEbits.RE1 = 0; 
    RE1 = 1;
    // Set Program Pin4 (RB7) as output U1_PIN17 (S8)
    PORTBbits.RB7 = 0; 
    RB7 = 1;
    // Set Power _Button (RA4) as input U1_PIN23 (SW5)
    PORTAbits.RA4 = 1;
    ANSELAbits.ANSA4= 0;  //set ra4 digital input
    WPUAbits.WPUA4 = 1;
    // Set Setting_Button (RA3) as input U1_PIN22 (SW4)
    TRISA3=1;
    PORTAbits.RA3 = 1;
    ANSELAbits.ANSA3 = 0;  //set ra3 digital input
    WPUAbits.WPUA3 = 1; 
    // Set Increment _Button (RA5) as input U1_PIN24 (SW6)
    TRISA5 = 1;               // Configure RA5 as input
    ANSELAbits.ANSA5 = 0;     // Set RA5 to digital mode (disable analog)
    WPUAbits.WPUA5 = 1;       // Enable pull-up resistor on RA5
    PORTAbits.RA5 = 1;        // (Optional) Set RA5 high - this could be redundant since it's input
     
    // Set Decrement _Button (RA1) as input U1_PIN20 (SW2)
    PORTAbits.RA1 = 1;
    ANSELAbits.ANSA1 = 0;  //set ra1 digital input
    WPUAbits.WPUA1 = 1;
    
    // Set UART RX & TX (RC6 & RC7) as input U1_PIN44 & output U1_PIN1
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 0;
        // Set NPN_SENSOR_1_PIN (RE2) as input
    TRISAbits.TRISA6 = 1;   // RE2 as input (First NPN sensor)
    PORTAbits.RA6 = 1;
    ANSELAbits.ANSA6 = 0;  //set ra3 digital input
    WPUAbits.WPUA6 = 0;
    
    // Set NPN_SENSOR_1_PIN (RE2) as input
    TRISEbits.TRISE2 = 1;   // RE2 as input (First NPN sensor)
//    PORTEbits.RE2 = 1;
    ANSELEbits.ANSE2 = 0;  //set ra3 digital input
    WPUEbits.WPUE2 = 0; 
    
    // Set NPN_SENSOR_2_PIN (RC2) as input
    TRISCbits.TRISC2 = 1;   // RC2 as input (Second NPN sensor)
//    PORTCbits.RC2 = 1;
    ANSELCbits.ANSC2 = 0;  //set ra3 digital input
    WPUCbits.WPUC2 = 0; 
    
    // Set PRESET_B (RC0) as input
    TRISCbits.TRISC0 = 1;   // RC2 as input (Second NPN sensor)
//    PORTCbits.RC0 = 1;
    ANSELCbits.ANSC0 = 0;  //set ra3 digital input
    WPUCbits.WPUC0 = 0; 
    
    // Set NPN_PRESET_PIN (RC1) as input
    TRISCbits.TRISC1 = 1;   // RC2 as input (Second NPN sensor)
    PORTCbits.RC1 = 1;
    ANSELCbits.ANSC1 = 0;  //set ra3 digital input
    WPUCbits.WPUC1 = 0; 
    
    // Set PHOTO_SENSOR_PIN (RE0) as input (Photoelectric sensor)
    TRISBbits.TRISB0 = 1;   // RE0 as input (Photoelectric sensor)
    PORTBbits.RB0 = 1;
    ANSELBbits.ANSB0 = 0;  //set ra3 digital input
    WPUBbits.WPUB0 = 1;
    
    // Set other pins as needed based on your application
    TRISCbits.TRISC4 = 0;
    PORTCbits.RC4 = 0;
//    ANSELCbits.ANSC4 = 0;
//    WPUCbits.WPUC4 = 0; 
    LATCbits.LATC4 = 1;
    
    // Set other pins as needed based on your application
//    TRISCbits.TRISC5 = 1;
//    ANSELCbits.ANSC5 = 0;  //set ra3 digital input
//    WPUCbits.WPUC5 = 1; 
    
    // Set NPN_PRESET_PIN (RE0) as ADC input
//    TRISEbits.TRISE0 = 1;       // Set RE0 as input
//    ANSELEbits.ANSE0 = 1;       // Set RE0 as analog input
//    WPUEbits.WPUE0 = 0;         // Disable weak pull-up (for cleaner ADC reads)
    
    // Set other pins as needed based on your application
//    TRISDbits.TRISD7 = 0;
//    PORTDbits.RD7 = 0;
//    LATDbits.LATD7 = 1;
    
//     Set other pins as needed based on your application
//    TRISCbits.TRISC3 = 0;
//    PORTCbits.RC3 = 0;
//    LATCbits.LATC3 = 0;
    
////     Set other pins as needed based on your application
//    TRISCbits.TRISC1 = 0;
//    PORTCbits.RC1 = 0;
//    LATCbits.LATC1 = 0;
    
    DG1_LED = 0;
    DG2_LED = 0;
    DG3_LED = 0;
    DG4_LED = 0;
    DG5_LED = 0;
  // Initialize hardware and peripherals
    setup_timer0();
    ADC_Init();
//    initSensorPins();   // Initialize sensor input pins
//    send_data_human_readable();  // Send data to PIC16F1524
    // Main loop
    while (1) {
//        if(saveFlag == 1){
////            SaveSystemDataToFlash();  // Save variables to NVM
////            saveFlag = 0;
//        }
    }
}
