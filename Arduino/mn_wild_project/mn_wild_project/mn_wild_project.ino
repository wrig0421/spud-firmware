typedef enum
{
    PIN_RELAY_LEFT_STROBE = 10, // or 9,10,11
    PIN_RELAY_RIGHT_STROBE = 9, // or 8,10,11
    PIN_REMOTE_INTERRUPT = 2, // sense when button pressed
    PIN_AUDIO_TRIG_0 = 6, // drive low to play music in slot 0
    PIN_AUDIO_TRIG_1 = 7 // drive low to play music in slot 1
} pin_e;


#define ENABLE_SERIAL_DEBUG 

#define STROBE_ON   LOW
#define STROBE_OFF  HIGH

unsigned long g_debounce_delay_ms = 2000; // ms
unsigned long g_isr_timestamp_ms = 0; // ms
unsigned long g_active_time_ms = 3000;
//unsigned long g_active_time_ms = (1000 * 60 * 3);
bool g_remote_interrupt_detected = false;


// this function auto clears the interrupt detected flag
static bool remote_interrupt_detected(void)
{
    bool return_val = false;
    if (g_remote_interrupt_detected)
    {
        return_val = true;
        g_remote_interrupt_detected = false;
    }
    return return_val;
}


static void handle_interrupt(void)
{
    digitalWrite(PIN_RELAY_LEFT_STROBE, HIGH);
    digitalWrite(PIN_RELAY_RIGHT_STROBE, HIGH);
    digitalWrite(PIN_AUDIO_TRIG_0, HIGH);
    //digitalWrite(PIN_AUDIO_TRIG_1, LOW);    
}

static void reset_io(void)
{
    digitalWrite(PIN_RELAY_LEFT_STROBE, LOW);
    digitalWrite(PIN_RELAY_RIGHT_STROBE, LOW);
    digitalWrite(PIN_AUDIO_TRIG_0, LOW);
    //digitalWrite(PIN_AUDIO_TRIG_1, LOW);  
}


void setup() 
{
#if defined(ENABLE_SERIAL_DEBUG)
    Serial.begin(9600);
#endif
    //delay(3000);
    // put your setup code here, to run once:
    pinMode((byte)PIN_RELAY_LEFT_STROBE, OUTPUT);
    pinMode((byte)PIN_RELAY_RIGHT_STROBE, OUTPUT);
    pinMode((byte)PIN_REMOTE_INTERRUPT, INPUT);
    pinMode((byte)PIN_AUDIO_TRIG_0, OUTPUT);
    pinMode((byte)PIN_AUDIO_TRIG_1, OUTPUT);
    digitalWrite(PIN_RELAY_LEFT_STROBE, HIGH);
    digitalWrite(PIN_RELAY_RIGHT_STROBE, HIGH);
    digitalWrite(PIN_AUDIO_TRIG_0, LOW);
    digitalWrite(PIN_AUDIO_TRIG_1, LOW);    
    //interrupts(); // only needed for the case where interrupts have been disabled w/ `noInterrupts` call
    attachInterrupt(digitalPinToInterrupt((byte)PIN_REMOTE_INTERRUPT), isr_remote, LOW); 
}

void loop() 
{
    // put your main code here, to run repeatedly:
    if (remote_interrupt_detected())
    {
        noInterrupts();
        handle_interrupt();
#if defined(ENABLE_SERIAL_DEBUG)
        Serial.println("Interrupts handled");
        Serial.println("delaying");
#endif
        delay(g_active_time_ms);
        reset_io();
#if defined(ENABLE_SERIAL_DEBUG)
        Serial.println("IO reset");
#endif
        interrupts();
    }
}


void isr_remote(void)
{
    if ((millis() - g_isr_timestamp_ms) > g_debounce_delay_ms)
    {
#if defined(ENABLE_SERIAL_DEBUG)
    Serial.println("REMOTE_ISR");
#endif
        g_isr_timestamp_ms = millis();
        g_remote_interrupt_detected = true;
        //handle_interrupt(); 
        //while(1);
    }
    else 
    {
        return;
    }
    
}
