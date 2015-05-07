/*
 *TEST AD 9628
 */

#include <stdio.h>
//#include "devcfg_header.h"
#include "xparameters.h"
#include "xscugic.h"
#include "xdevcfg.h"
#include "xdmaps.h"
#include "dmaps_header.h"
#include "xqspips.h"
#include "qspips_header.h"
#include "xspips.h"
#include "spips_header.h"
#include "xuartps.h"
#include "uartps_header.h"
int main() 
{
   static XScuGic intc;
   static XUartPs ps7_uart_0;
   Xil_ICacheEnable();
   Xil_DCacheEnable();

   {
     int Status;

     // INIZIALIZZAZIONE AD9628
     print("Inizializzazione AD 9628 : ");
     Status = SpiPs_Init_SPI(XPAR_PS7_SPI_1_DEVICE_ID);
     if (Status == 0) { print("OK from SPI..."); }  else { print("SPI FAILED"); }
     print("\r\n");
   }

//accendi led
unsigned int *led;
led = 0x41200000;
*led = 0xFFFFFFFF;


// test dei registri
//scrittura
/*     unsigned int *brama;
          brama = 0x40010000;
          int z;

printf( "Scrivo BRam su porta A ind. %X\r\n",brama);
     for ( z = 0; z < 4097; z++)
          {
            *brama = 0x0AAA0CCC;
         //   *brama = z;
         	 brama = brama + 1;
         }

*/
// Lettura continua canali ADC0 e ADC1
unsigned int *buffer1, *buffer2;
buffer1 = 0x40000000;
buffer2 = 0x40010000;
int ADC0A,ADC0B,ADC1A,ADC1B;

while(1)
{
       ADC0A = *buffer1;
       ADC0B = *buffer1&0x1fff;
       ADC1A = *buffer2;
       ADC1B = *buffer2&0x1fff;
       printf( "CH0=%X | CH1=%X  || CH0=%X | CH1=%X  ||\r\n",ADC0A>>16, ADC0B, ADC1A>>16, ADC1B);
       }


/*
// Lettura BRAM canali ADC0 e ADC1
unsigned int *buffer1, *buffer2;
buffer1 = 0x40000000;
buffer2 = 0x40010000;
int w,ADC0A,ADC0B,ADC1A,ADC1B;
printf( "-----   READ BRAM ADC0 and ADC1   -----\r\n\r");
//printf( "addr |         ADC0        ||       ADC1        |\r\n");
printf( "      ADC0       ||       ADC1        |\r\n");

for ( w = 0; w < 1096; w++)
       {
       ADC0A = *buffer1;
       ADC0B = *buffer1&0x1fff;
       ADC1A = *buffer2;
       ADC1B = *buffer2&0x1fff;
//       printf( "  %X =  CH0=%X | CH1=%X  || CH0=%X | CH1=%X  ||\r\n",w, ADC0A>>16, ADC0B, ADC1A>>16, ADC1B);
       printf( "CH0=%X | CH1=%X  || CH0=%X | CH1=%X  ||\r\n",ADC0A>>16, ADC0B, ADC1A>>16, ADC1B);
       buffer1 = buffer1 + 1;
       buffer2 = buffer2 + 1;
       }

*/
/*

//lettura BRAM ADC0
unsigned int *bramb;
          bramb = 0x40000000;
          int w,chanA,chanB;;
printf( "       ----- READ BRAM ADC0 -----\r\n\r\n");
//printf( "     addr -- CHA-CHB\r\n");
     for ( w = 0; w < 15; w++)
               {
    	 	 	 chanA = *bramb;
    	         chanB = *bramb&0x1fff;
    	         printf( "  %X = chanA %X chanB %X\r\n",bramb, chanA>>16, chanB);
              	 bramb = bramb + 1;
               }

     //lettura BRAM ADC1
     unsigned int *bramc;
               bramc = 0x40010000;
               int v;
     printf( "\r\n       ----- READ BRAM ADC1 -----\r\n\r\n");
          for ( v = 0; v < 15; v++)
                    {
        	         chanA = *bramc;
        	         chanB = *bramc&0x1fff;
                      printf( "  %X = chanA %X chanB %X\r\n",bramc, chanA>>16, chanB);
        	  bramc = bramc + 1;
                    }


unsigned int *registre_adc;
     registre_adc = 0x43c00000;
     int i;

     printf("\r\n Visualizzazione registri interni interfaccia ADC : \r\n");
     for ( i = 0; i < 16; i++)
     {
         printf( "  %X = %X \r\n",registre_adc, *registre_adc);
    	 registre_adc = registre_adc + 1;
     }
//##########################################################################################################

     printf( "Output ADC Channels\r\n ");
     unsigned int *registre_adc0;
          registre_adc0 = 0x43c00000;

         volatile unsigned int a;


     unsigned int *registre_adc1;
          registre_adc1 = 0x43c00004;
          volatile unsigned int b;


     while(1)
     {
    	 a = *registre_adc0;
    	 b = *registre_adc1;

//    	 printf( "%X",a);
    	 printf( "ADC0 = Channel A = %X,  Channel B = %X \r\n",a >>16,a & 0xffff);
//    	 printf( "%X",b);
    	 printf( "ADC1 = Channel A = %X,  Channel B = %X \r\n\r\n",b >>16,b & 0xffff);

    	 for( i = 0; i<50000000;i++)
    	 {
    		 registre_adc = 0x43C00000;
    	 }
     }

*/
     *led = 0x00000000;
   print("---Exiting main---\n\r");
   Xil_DCacheDisable();
   Xil_ICacheDisable();
   return 0;
}