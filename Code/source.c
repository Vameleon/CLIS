//Written by Tariq A
//I am thankful to Adafruit's library NeoPixel, however,
//There are many things to be imporved in the lib.
//Website: www.tariq.world
//Project: CRGB Leds Indication System (CLIS) - Hobby and free time project
//Hardware: ESP32 WiFi module
//IDE: Arduino IDE
//Compiled: On windows 64-bit machine
//The source code is put in a single file, since this is a simple collective code.
















#include <Adafruit_NeoPixel.h>
#include <Preferences.h>
#include <WiFi.h>




#define LONG_CRGB_P    12              //PHY pin
#define LONG_CRGB_NUM  (57)   //number of leds on the strip
#define LONG_NEIGHBOR_NUM    (8)      //Series of similar colors "Neighbors"
                                //Remember that Leds NUM and Neighbor num should
                                //be dividisble so all leds wil.
                                //For example if you have 10 leds
                                //choose neighrs to be 5
                                //So you get two different colors at a time
#define LONG_SIDE_NUM   8       //Number of leds on the side to be used

#define SHORT_CRGB_P    14
#define SHORT_CRGB_NUM    (8)         //number of leds on the strip
#define SHORT_NEIGHBOR_NUM  (4)

//Keep the following order at all times
#define RED         0
#define GREEN       1
#define BLUE        2
#define YELLOW      3
#define LIME        4
#define ORANGE      5
#define MAGENTA     6
#define PURPLE      7
#define TURQUOISE   8 
#define WHITE       9

#define UART_PRD    3           //every 3 secs

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel LONG_CRGB = Adafruit_NeoPixel(LONG_CRGB_NUM, LONG_CRGB_P, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel SHORT_CRGB = Adafruit_NeoPixel(SHORT_CRGB_NUM, SHORT_CRGB_P, NEO_GRB + NEO_KHZ800);
typedef Adafruit_NeoPixel   CRGB_STRIP;     //Investigate


//CRGB SHORT_CRGB[SHORT_CRGB_NUM];    //declare our strip and give it an ID
//CRGB LONG_CRGB[LONG_CRGB_NUM];      //declare our strip and give it an ID

//---------------------End of Definition---------------------------------------//





//-----------------------------Declaration-------------------------//
typedef enum MODES {NONE,BLINK_SIDES,BLINK_WHOLE,FLASH_SIDES,FLASH_WHOLE,RAINBOW_WHOLE};
MODES INDICATE_M = RAINBOW_WHOLE;
uint8_t BLINK_ROUNDS = 4;
uint8_t BLINK_SIDES_COLOR = RED;
uint8_t BLINK_WHOLE_COLOR = ORANGE;
uint16_t BLINK_ON_PRD = 69;
uint16_t BLINK_OFF_PRD = 120;


uint16_t RAINBOW_SHUFFLE_PRD = 20;      //Every x seconds

uint32_t RED_C,GREEN_C,BLUE_C,YELLOW_C,LIME_C,ORANGE_C,MAGENTA_C,PURPLE_C,TURQUOISE_C,WHITE_C;
uint32_t PALLETE []={RED_C,GREEN_C,BLUE_C,YELLOW_C,LIME_C,ORANGE_C,MAGENTA_C,PURPLE_C,TURQUOISE_C,WHITE_C};
int PALLETE_ELEMENTS = sizeof(PALLETE)/sizeof(PALLETE[0]);        //return num of elements



typedef struct COLOR_CONTENT {
     uint32_t R,G,B;
};
//RED_COMP,GREEN_COMP,
//BLUE_COMP,YELLOW_COMP,LIME_COMP,
//ORANGE_COMP,MAGENTA_COMP,PURPLE_COMP,TURQUOISE_COMP;

//Array of structs
COLOR_CONTENT COLOR_CONTENT_ARY[10];

float DEF_PALLETE_BRIGHTNESS = 20.0; //Global color brightness in %, 0-100


//------WiFi-------//

const char* SSID     = "SSID_NAME_HERE";
const char* PASSWORD = "SSID_PASSWORD_HERE";
WiFiServer ESP32_HTTP_SRV(80);

//----------------//


  //------------------------------INTERRUPT-------------------------//
volatile uint16_t UART_PRD_CNT = 0;
volatile uint16_t RAINBOW_SHUFFLE_PRD_CNT = 0;
//Create pointer of type hw_timer and name it to timer
hw_timer_t * tmr = NULL;
//create variable portMux of type portMUX to sync between main and ISR
portMUX_TYPE Mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR parallelisation() {
  portENTER_CRITICAL_ISR(&Mux);
  UART_PRD_CNT++;
  RAINBOW_SHUFFLE_PRD_CNT++;
  portEXIT_CRITICAL_ISR(&Mux);
 
}


  //------------------------------END OF INTERRUPT-------------------------//







void INIT_ESP32(void);
void init_timer(void);
void init_WiFi(void);
void WiFi_connection_handler(void);
void CONNECTION_SEND_HTTP_RESPONSE(WiFiClient);
void CONNECTION_ANALYZE_HTTP_REQ(String);
void MODE_SERVICE(void);
void SET_COLORS(void);
void INIT_BRIGHTNESS(float);
void long_rainbow(uint16_t);
void short_rainbow(uint16_t);
void set_long(uint16_t, uint16_t, uint8_t );
void set_short(uint16_t, uint16_t, uint8_t);
void clr_long_crgb(uint16_t,uint16_t);
void clr_short_crgb(uint16_t,uint16_t);
void delay_us (uint32_t);
//-------------------------End of Declaration--------------------------//


void setup() {
 
    INIT_ESP32 ();
    init_timer();
    init_WiFi();
}




void loop()
{
    if (UART_PRD_CNT >= UART_PRD)
    {
        Serial.printf("Program is in loop\n");
        Serial.printf("Current Mode is %i\n",INDICATE_M);
        Serial.printf("You have %i Elements in your Pallete\n",PALLETE_ELEMENTS);
        Serial.printf("Printing your PAllete's int values: \n");
        for (int u=0;u<PALLETE_ELEMENTS;u++)
        {
             Serial.printf("-->%u\n",PALLETE[u]);
               
        }
        Serial.printf("%d ms Since Interrupt triggered\n",(UART_PRD_CNT-UART_PRD));
    
        Serial.printf("------------------------------------------\n");
        UART_PRD_CNT = 0;

    }

    //INDICATE(INDICATE_M);
    WiFi_connection_handler();
    MODE_SERVICE();
    

    //debug
    //Serial.printf("Printing Magneta int value now: %i\n",Magenttta);
    //Serial.printf("Poll: Current color value is: %i\n",LONG_CRGB.getPixelColor(11));

     









    

    //INIT_BRIGHTNESS(10.0);

    //Light the sides of the long CRGB
   
    //Light whole short
    

    
    //long_rainbow(LONG_CRGB_NUM);
    //short_rainbow(SHORT_CRGB_NUM);
  
    
}






void INIT_ESP32()
{
    
    delay(1000);
    pinMode(LONG_CRGB_P, OUTPUT);
    pinMode(SHORT_CRGB_P, OUTPUT);
    Serial.begin(115200);
    Serial.printf("Initiating the MCU.....\n");
    
    //increment "boot_cnt"
    Preferences Pref;
    Pref.begin("my-app", false);
    unsigned int cur_boot_cnt = Pref.getUInt("boot_cnt", 0);
    cur_boot_cnt+=1;      
    Serial.printf("Boot #: %d\n", cur_boot_cnt);
    Pref.putUInt("boot_cnt", cur_boot_cnt);
    Pref.end();
    
    delay( 5000 ); // power-up safety delay
    
    //Initiate lib
    LONG_CRGB.begin();       // Initialize
    SHORT_CRGB.begin();      // Initialize                    
    
    LONG_CRGB.show();        // to off (black)
    SHORT_CRGB.show();       // to off (black) 
   
    SET_COLORS();             //Initialize color values
    INIT_BRIGHTNESS(DEF_PALLETE_BRIGHTNESS);
    delay( 5000 ); // power-up safety delay
}  



void init_timer()
{
  //------------------------------INTERRUPT-------------------------//
  ////Prescaler 80
  tmr = timerBegin(0, 80, true);
  
  //Timer "timer" as 1st arg, the address of the function that will handle the interrupt as 2nd arg
  //interrupt to be generated is edge (true) or level (false).
  timerAttachInterrupt(tmr, &parallelisation, true);
  
  //Timer "timer" is 1st arg. Second is value of the counter
  // until interrupt is generated (Value of counter in us, in this case every 1s), 3rd arg->
  //indicating if the timer should automatically reload upon generating the interrupt.  
  timerAlarmWrite(tmr, 1000000, true);
  //
  timerAlarmEnable(tmr);
  //----------------------------------------------------------------//
}





void init_WiFi()
{
    uint8_t frst_exec=1;

    Serial.println();
    Serial.println(SSID);
    Serial.printf(" is target SSID\n");

    WIFI_BEGIN_EDGE:WiFi.begin(SSID, PASSWORD);

    for (uint8_t r=0;r<10;r++)
    {

        
        if (WiFi.status() != WL_CONNECTED) {
            Serial.printf("attempting....\n");
            delay(500);
        
        }
        else
        {
            Serial.printf("ESP32 is now connected to WiFi\n");
            Serial.printf("IP if available: \n");
            Serial.println(WiFi.localIP());     //print ESP's IP addr.
            ESP32_HTTP_SRV.begin();              //Initiate server!
            break;
        }
        delay(2000*r);
        
    }

    
    
    if (frst_exec) {
        frst_exec = 0;
        goto WIFI_BEGIN_EDGE;
        
    }
   
}

void WiFi_connection_handler(void)
{
    //**************************************WEB Server Section*******************************
  WiFiClient CONNECTION = ESP32_HTTP_SRV.available();   // listen for incoming clients

  if (CONNECTION) {                             // if you get a CONNECTION,
    String INCOMING_STREAM = "";                // make a String to hold incoming data from the CONNECTION
    
    while (CONNECTION.connected()) {            // loop while the CONNECTION's connected
    
      if (CONNECTION.available()) {             // if there's bytes to read from the CONNECTION,

        char c = CONNECTION.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
    
        if (c == '\n') {                    // if the byte is a newline character
                                             //End of HTTP Request

      
          //If we have not sent HTTP response   
          if (INCOMING_STREAM.length() == 0) 
          {

            CONNECTION_SEND_HTTP_RESPONSE(CONNECTION);

            // break
            break;
          } 
           // if you got a newline, then clear INCOMING_STREAM:
          else INCOMING_STREAM = "";
        
        }
        //put incoming character into INCOMING_STREAM as long as it is not a \r
        else if (c != '\r') {  // if you got anything else but a carriage return character,
          INCOMING_STREAM += c;      // add it to the end of the INCOMING_STREAM
        }
        
        //Analyze the Incoming stream --> Act upon that
        CONNECTION_ANALYZE_HTTP_REQ(INCOMING_STREAM);
    
      }
    }
    // close the connection:
    CONNECTION.stop();
   }
}


void CONNECTION_SEND_HTTP_RESPONSE(WiFiClient connectxion)
{
    connectxion.println("HTTP/1.1 200 OK");          //http Init codes
    connectxion.println("Content-type:text/html");
    connectxion.println();                           //newline

    //HTML code-------------------------------//
    connectxion.print("<font color='white'>");
    connectxion.print("<body bgcolor = '#2E2E2E'>");
    char buFF[100];
    char * TitlE="CLIS";
    sprintf(buFF,"<title> %s </title>",TitlE);
    connectxion.print(buFF);
    connectxion.print("<a href=\"/BSIDER\">here</a>- BSIDE-R mode.<br>");
    connectxion.print("<a href=\"/BSIDEG\">here</a>- BSIDE-G mode.<br>");
    connectxion.print("<a href=\"/BSIDEB\">here</a>- BSIDE-B mode.<br>");
    connectxion.print("<a href=\"/BWHOLR\">here</a>- BWHOL-R mode.<br>");
    connectxion.print("<a href=\"/BWHOLG\">here</a>- BWHOL-G mode.<br>");
    connectxion.print("<a href=\"/BWHOLB\">here</a>- BWHOL-B mode.<br>");
    connectxion.print("<a href=\"/RBOW\">here</a> - RBOW mode.<br>");
    connectxion.print("<a href=\"/NONE\">here</a> - NONE.<br>");
    //-----------------------------------------//

    //End the response with /n:
    connectxion.println();
    

}


void CONNECTION_ANALYZE_HTTP_REQ(String inc_response)
{
        if (inc_response.endsWith("GET /BSIDER")) {BLINK_SIDES_COLOR=RED; INDICATE_M = BLINK_SIDES;}
        else if (inc_response.endsWith("GET /BSIDEG")){BLINK_SIDES_COLOR=GREEN; INDICATE_M = BLINK_SIDES;}
        else if (inc_response.endsWith("GET /BSIDEB")){BLINK_SIDES_COLOR=BLUE; INDICATE_M = BLINK_SIDES;}
        else if (inc_response.endsWith("GET /BWHOLR")){BLINK_WHOLE_COLOR=RED; INDICATE_M = BLINK_WHOLE;}
        else if (inc_response.endsWith("GET /BWHOLG")){BLINK_WHOLE_COLOR=GREEN; INDICATE_M = BLINK_WHOLE;}
        else if (inc_response.endsWith("GET /BWHOLB")){BLINK_WHOLE_COLOR=BLUE; INDICATE_M = BLINK_WHOLE;}
        else if (inc_response.endsWith("GET /RBOWR")) INDICATE_M = RAINBOW_WHOLE;
        else if (inc_response.endsWith("GET /NONE")) {BLINK_SIDES_COLOR=GREEN; INDICATE_M = BLINK_SIDES;INDICATE_M = NONE;}
}


void MODE_SERVICE (void)
{
        switch(INDICATE_M)
    {
        case NONE:break;
        case BLINK_SIDES:
            Serial.printf("Current mode is blink sides...\n");
            
            for (int r =0;r<BLINK_ROUNDS;r++)
            {
                set_long((LONG_CRGB_NUM-LONG_SIDE_NUM),LONG_CRGB_NUM,BLINK_SIDES_COLOR);
                set_short(0,SHORT_CRGB_NUM,BLINK_SIDES_COLOR);
                delay(BLINK_ON_PRD);

                clr_long_crgb(0,LONG_CRGB_NUM);  
                clr_short_crgb(0,SHORT_CRGB_NUM);     
                delay(BLINK_OFF_PRD);
            }            
            INDICATE_M = NONE;
            break;

        case BLINK_WHOLE:
            for (int r =0;r<BLINK_ROUNDS;r++)
            {
                set_long(0,LONG_CRGB_NUM,BLINK_WHOLE_COLOR);
                set_short(0,SHORT_CRGB_NUM,BLINK_WHOLE_COLOR);
                delay(BLINK_ON_PRD);

                clr_long_crgb(0,LONG_CRGB_NUM);  
                clr_short_crgb(0,SHORT_CRGB_NUM);     
                delay(BLINK_OFF_PRD);
            }  
            INDICATE_M = NONE;
            break;    


        case RAINBOW_WHOLE:
            if (RAINBOW_SHUFFLE_PRD_CNT >= RAINBOW_SHUFFLE_PRD)
            {
            long_rainbow(LONG_CRGB_NUM);
            short_rainbow(SHORT_CRGB_NUM);
            RAINBOW_SHUFFLE_PRD_CNT = 0;
            }
            break;    

    }

}























//-------------------------------------LOW layer functions----------------------//
//Init the color values
//Those values are never changing values
//Those values represent the default RGB color values


void SET_COLORS()
{
    //Set default color component values.

    COLOR_CONTENT_ARY[RED].R = 255, COLOR_CONTENT_ARY[0].G = 0,COLOR_CONTENT_ARY[0].B = 0;
    COLOR_CONTENT_ARY[GREEN].R = 0,   COLOR_CONTENT_ARY[1].G = 255,COLOR_CONTENT_ARY[1].B = 0;
    COLOR_CONTENT_ARY[BLUE].R = 0,   COLOR_CONTENT_ARY[2].G = 0,COLOR_CONTENT_ARY[2].B = 255;
    COLOR_CONTENT_ARY[YELLOW].R = 255, COLOR_CONTENT_ARY[3].G = 255,COLOR_CONTENT_ARY[3].B = 0;
    COLOR_CONTENT_ARY[LIME].R = 153, COLOR_CONTENT_ARY[4].G = 255,COLOR_CONTENT_ARY[4].B = 51;
    COLOR_CONTENT_ARY[ORANGE].R = 255, COLOR_CONTENT_ARY[5].G = 128,COLOR_CONTENT_ARY[5].B = 0;
    COLOR_CONTENT_ARY[MAGENTA].R = 255, COLOR_CONTENT_ARY[6].G = 0,COLOR_CONTENT_ARY[6].B = 255;
    COLOR_CONTENT_ARY[PURPLE].R = 127, COLOR_CONTENT_ARY[7].G = 0,COLOR_CONTENT_ARY[7].B = 255;
    COLOR_CONTENT_ARY[TURQUOISE].R = 0, COLOR_CONTENT_ARY[8].G = 255,COLOR_CONTENT_ARY[8].B = 255;
    COLOR_CONTENT_ARY[WHITE].R = 255, COLOR_CONTENT_ARY[8].G = 255,COLOR_CONTENT_ARY[8].B = 255;


    
    //RED_COMP.R=255, RED_COMP.G=0, RED_COMP.B=0;
    //GREEN_COMP.R=0, GREEN_COMP.G=255, GREEN_COMP.B=0;
    //BLUE_COMP.R=0, BLUE_COMP.G=0, BLUE_COMP.B=255; 
    //YELLOW_COMP.R=255, YELLOW_COMP.G=255, YELLOW_COMP.B=0; 
    
    //LIME_COMP.R=153, LIME_COMP.G=255, LIME_COMP.B=51; 
    
    //ORANGE_COMP.R=255, ORANGE_COMP.G=128, ORANGE_COMP.B=0; 
    
    //MAGENTA_COMP.R=255, MAGENTA_COMP.G=0, MAGENTA_COMP.B=255; 
    
    //PURPLE_COMP.R=127, PURPLE_COMP.G=0, PURPLE_COMP.B=255; 
    
    //TURQUOISE_COMP.R=0, TURQUOISE_COMP.G=255, TURQUOISE_COMP.B=255;  
}




//Mapping the colors components(RGB) of the colors given in PALLETE to new values
//The precent value is multiplied into each component of all PALLETE colors
void INIT_BRIGHTNESS(float percent)
{
   for (int i=0;i<PALLETE_ELEMENTS;i++)
   {
      //PALLETE[i]= LONG_CRGB.Color( COLOR_CONTENT_ARY[i].R * (percent/100), (uint32_t) COLOR_CONTENT_ARY[i].G * (percent/100), (uint32_t) COLOR_CONTENT_ARY[i].B * (percent/100));
     PALLETE[i]= LONG_CRGB.Color( (uint8_t)(COLOR_CONTENT_ARY[i].R *  (float)(percent/100.0)), (uint8_t)(COLOR_CONTENT_ARY[i].G * (float)(percent/100.0)), (uint8_t)(COLOR_CONTENT_ARY[i].B * (float)(percent/100.0)));
 
      //debug
      //PALLETE[i]= LONG_CRGB.Color(COLOR_CONTENT_ARY[i].R, COLOR_CONTENT_ARY[i].G, COLOR_CONTENT_ARY[i].B);
      Serial.printf("%i. R:%i------G:%i------B:%i\n",i,COLOR_CONTENT_ARY[i].R,COLOR_CONTENT_ARY[i].G,COLOR_CONTENT_ARY[i].B);


   }
      //Red Green Blue order
   //RED = LONG_CRGB.Color(RED_COMP.R * (precent/100), RED_COMP.G * (precent/100), RED_COMP.B * (precent/100));
   //GREEN = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //BLUE = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //YELLOW = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //LIME = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //ORANGE = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //MAGENTA = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //PURPLE = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
   //TURQUOISE = LONG_CRGB.Color(.R * (precent/100), .G * (precent/100), .B * (precent/100));
}





void long_rainbow (uint16_t number_leds)
{
    
    //-------------------LONG CRGB--------------------------//
    //loop for as many times as the number of leds. Don't loop the last leds (neighbor)
    //Because the inner loop takes care of it
    for (uint8_t n=0;n<(number_leds-LONG_NEIGHBOR_NUM);n+=LONG_NEIGHBOR_NUM)
    {
        //LONG_CRGB.setPixelColor(n,PALLETE[n]);
        //Randomize colors
        LONG_CRGB.setPixelColor(n,PALLETE[random(PALLETE_ELEMENTS)]);
       
        //take care  of our neighbors, if there are any.
        //Color them with the same color as n
        for (uint8_t u=0;u<LONG_NEIGHBOR_NUM;++u)
        {
            LONG_CRGB.setPixelColor(n+u,LONG_CRGB.getPixelColor(n));
            //LONG_CRGB.show();
            //delay_us(10);
        }
      
    }
      LONG_CRGB.show();
      delay_us(10);
}

void short_rainbow (uint16_t number_leds)
{
    //-------------------SHORT CRGB------------------------//
  //loop for as many times as the number of leds. Don't loop the last leds (neighbor)
    //Because the inner loop takes care of it
    for (uint8_t n=0;n<(number_leds);n++)
    {
        //SHORT_CRGB.setPixelColor(n,PALLETE[n]);
        //Randomize colors
        SHORT_CRGB.setPixelColor(n,PALLETE[random(PALLETE_ELEMENTS)]);
        
    }
     SHORT_CRGB.show();
    delay_us(10);
  
}



//Set specific leds in long CRGB to turn on
//Arg1: from led number index (0 is valid here)
//Arg2: to led number index (Don't use 0) 
//Arg3: The color which is to be index to PALLETE
void set_long(uint16_t from_idx,uint16_t to_idx,uint8_t clr_idx)
{
    for (uint16_t r=from_idx;r<to_idx;r++)
    {
        LONG_CRGB.setPixelColor(r,PALLETE[clr_idx]);

    }
        delay_us(1);
        LONG_CRGB.show();


}

//Set specific  leds in SHORT CRGB to turn on
//Arg1: from led number index (0 is valid here)
//Arg2: to led number index (Don't use 0) 
//Arg3: The color which is to be index to PALLETE
void set_short(uint16_t from_idx,uint16_t to_idx,uint8_t clr_idx)
{
    for (uint16_t r=from_idx;r<to_idx;r++)
    {
        SHORT_CRGB.setPixelColor(r,PALLETE[clr_idx]);
        
    }
     SHORT_CRGB.show();
     delay_us(5);
   
}



//Clears specific leds/pixels of a given crgb
void clr_long_crgb(uint16_t from_idx,uint16_t to_idx)
{
    for (int r=from_idx;r<to_idx;r++)
    {
        LONG_CRGB.setPixelColor(r,0,0,0);

        
    }
        LONG_CRGB.show();
        delay_us(1);
    
    
}

//Clears specific leds/pixels of a given crgb
void clr_short_crgb(uint16_t from_idx,uint16_t to_idx)
{
    for (int r=from_idx;r<to_idx;r++)
    {
        SHORT_CRGB.setPixelColor(r,0,0,0);
      
    }
        SHORT_CRGB.show();
        delay_us(1);   
}


void delay_us (uint32_t delay_val)
{
    delayMicroseconds(delay_val);
}


//-----------------------------End of LOW layer functions----------------------//


