#include <Adafruit_NeoPixel.h>



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
#define BLACK       10

#define PERIOD  3000                //period in program cycle in ms
#define BLINK_ON_PRD    90          //On time ms
#define BLINK_OFF_PRD   200         //off time in ms

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


uint32_t RED_C,GREEN_C,BLUE_C,YELLOW_C,LIME_C,ORANGE_C,MAGENTA_C,PURPLE_C,TURQUOISE_C,WHITE_C,BLACK_C;
uint32_t PALLETE []={RED_C,GREEN_C,BLUE_C,YELLOW_C,LIME_C,ORANGE_C,MAGENTA_C,PURPLE_C,TURQUOISE_C,WHITE_C,BLACK_C};
int PALLETE_ELEMENTS = sizeof(PALLETE)/sizeof(PALLETE[0]);        //return num of elements

typedef struct COLOR_CONTENT {
     uint32_t R,G,B;
};
//RED_COMP,GREEN_COMP,
//BLUE_COMP,YELLOW_COMP,LIME_COMP,
//ORANGE_COMP,MAGENTA_COMP,PURPLE_COMP,TURQUOISE_COMP;

//Array of structs
COLOR_CONTENT COLOR_CONTENT_ARY[9];

float DEF_PALLETE_BRIGHTNESS = 5.0; //Global color brightness in %, 0-100


void init();
void INIT_BRIGHTNESS(float);
void SET_COLORS(void);
void long_rainbow(uint16_t);
void short_rainbow(uint16_t);
void set_long(uint16_t, uint16_t, uint8_t );
void set_short(uint16_t, uint16_t, uint8_t);
void clr_long_crgb(uint16_t,uint16_t);
void clr_short_crgb(uint16_t,uint16_t);
void delay_us (uint32_t);
//-------------------------End of Declaration--------------------------//


void setup() {
 
    void init ();

}


void loop()
{
    uint8_t i=0;
    Serial.printf("Program is in loop\n");
    //INDICATE(INDICATE_M);
    Serial.printf("Current Mode is %i\n",INDICATE_M);
    Serial.printf("You have %i Elements in your Pallete\n",PALLETE_ELEMENTS);
    Serial.printf("Printing your PAllete's int values: \n");
    
    for (int u=0;u<PALLETE_ELEMENTS;u++)
    {
        Serial.printf("-->%u\n",PALLETE[u]);
               
    }
    //debug
    //Serial.printf("Printing Magneta int value now: %i\n",Magenttta);
    //Serial.printf("Poll: Current color value is: %i\n",LONG_CRGB.getPixelColor(11));
    
    Serial.printf("Printing the RED_COMP:%i,%i,%i\n",COLOR_CONTENT_ARY[i].R,COLOR_CONTENT_ARY[i].G,COLOR_CONTENT_ARY[i].B);
    Serial.printf("------------------------------------------\n");
    



    switch(INDICATE_M)
    {
        case NONE:break;
        case BLINK_SIDES:
            Serial.printf("Current mode is blink sides...\n");
            



            set_long((LONG_CRGB_NUM-LONG_SIDE_NUM),LONG_CRGB_NUM,RED);
            set_short(0,SHORT_CRGB_NUM,RED);
            delay(BLINK_ON_PRD);

            clr_long_crgb(0,LONG_CRGB_NUM);  
            clr_short_crgb(0,SHORT_CRGB_NUM);     
            delay(BLINK_OFF_PRD);
            

            set_long((LONG_CRGB_NUM-LONG_SIDE_NUM),LONG_CRGB_NUM,RED);
            set_short(0,SHORT_CRGB_NUM,RED);
            delay(BLINK_ON_PRD);

            clr_long_crgb(0,LONG_CRGB_NUM);
            clr_short_crgb(0,SHORT_CRGB_NUM);        
            delay(BLINK_OFF_PRD);

            set_long((LONG_CRGB_NUM-LONG_SIDE_NUM),LONG_CRGB_NUM,RED);
            set_short(0,SHORT_CRGB_NUM,RED);
            delay(BLINK_ON_PRD);

            clr_long_crgb(0,LONG_CRGB_NUM);
            clr_short_crgb(0,SHORT_CRGB_NUM);        
            delay(BLINK_OFF_PRD);
            break;


        case RAINBOW_WHOLE:
            long_rainbow(LONG_CRGB_NUM);
            short_rainbow(SHORT_CRGB_NUM);
            break;    

    }

    //Light the sides of the long CRGB
   
    //Light whole short
    

    
    //long_rainbow(LONG_CRGB_NUM);
    //short_rainbow(SHORT_CRGB_NUM);
    delay(PERIOD);

 
  
    delay(PERIOD);



    //INIT_BRIGHTNESS(10.0);
    
    i++;
    if (i>99)i=0;
  
}






void init()
{
    delay(1000);
    pinMode(LONG_CRGB_P, OUTPUT);
    pinMode(SHORT_CRGB_P, OUTPUT);
    Serial.begin(115200);
    Serial.printf("Initiating the MCU.....\n");
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
    COLOR_CONTENT_ARY[BLACK].R = 0, COLOR_CONTENT_ARY[8].G = 0,COLOR_CONTENT_ARY[8].B = 0;


    
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
      Serial.printf("Test %i\n",( (uint8_t)(COLOR_CONTENT_ARY[i].R * (float)(percent/100.0))));

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
        delay_us(5);
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
        LONG_CRGB.show();
        delay_us(1);
        
    }
    
    
}

//Clears specific leds/pixels of a given crgb
void clr_short_crgb(uint16_t from_idx,uint16_t to_idx)
{
    for (int r=from_idx;r<to_idx;r++)
    {
        SHORT_CRGB.setPixelColor(r,0,0,0);
        SHORT_CRGB.show();
        delay_us(1);
        
        
    }
   
    
}


void delay_us (uint32_t delay_val)
{
    delayMicroseconds(delay_val);
}


//-----------------------------End of LOW layer functions----------------------//


