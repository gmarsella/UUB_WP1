/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * 
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */

#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "scugic_header.h"
#include "xdevcfg.h"
#include "devcfg_header.h"
#include "xdmaps.h"
#include "dmaps_header.h"
#include "xemacps.h"
#include "xemacps_example.h"
#include "emacps_header.h"
#include "xiicps.h"
#include "iicps_header.h"
#include "xqspips.h"
#include "qspips_header.h"
#include "xscutimer.h"
#include "scutimer_header.h"
#include "xscuwdt.h"
#include "scuwdt_header.h"
#include "xspips.h"
#include "spips_header.h"
#include "xuartps.h"
#include "uartps_header.h"
int main() 
{
   static XScuGic intc;
//   static XEmacPs ps7_ethernet_0;
   static XScuTimer ps7_scutimer_0;
   static XScuWdt ps7_scuwdt_0;
   static XUartPs ps7_uart_0;
   Xil_ICacheEnable();
   Xil_DCacheEnable();
   print("---Entering main---\n\r");
   

   {
      int Status;
      
      print("\r\n Running ScuGicSelfTestExample() for ps7_scugic_0...\r\n");
      
      Status = ScuGicSelfTestExample(XPAR_PS7_SCUGIC_0_DEVICE_ID);
      
      if (Status == 0) { print("ScuGicSelfTestExample PASSED\r\n"); }
      else { print("ScuGicSelfTestExample FAILED\r\n");  }
   } 
	
   {
       int Status;

       Status = ScuGicInterruptSetup(&intc, XPAR_PS7_SCUGIC_0_DEVICE_ID);
       if (Status == 0) { print("ScuGic Interrupt Setup PASSED\r\n"); }
       else { print("ScuGic Interrupt Setup FAILED\r\n"); }
   }
   

   {
      int Status;
      
      print("\r\n Running DcfgSelfTestExample() for ps7_dev_cfg_0...\r\n");
      
      Status = DcfgSelfTestExample(XPAR_PS7_DEV_CFG_0_DEVICE_ID);
      
      if (Status == 0) { print("DcfgSelfTestExample PASSED\r\n"); }
      else { print("DcfgSelfTestExample FAILED\r\n"); }
   }
   

   {
      int Status;
      
      print("\r\n Running XDmaPs_Example_W_Intr() for ps7_dma_s...\r\n");
      
      Status = XDmaPs_Example_W_Intr(&intc,XPAR_PS7_DMA_S_DEVICE_ID);
      
      if (Status == 0) { print("XDmaPs_Example_W_Intr PASSED\r\n"); }
      else { print("XDmaPs_Example_W_Intr FAILED\r\n"); }
   }
   
 /*  {
      int Status;

      print("\r\n Running Interrupt Test  for ps7_ethernet_0...\r\n");
      
      Status = EmacPsDmaIntrExample(&intc, &ps7_ethernet_0, \
                                 XPAR_PS7_ETHERNET_0_DEVICE_ID, \
                                 XPAR_PS7_ETHERNET_0_INTR);
	
      if (Status == 0) { print("EmacPsDmaIntrExample PASSED\r\n"); }
      else { print("EmacPsDmaIntrExample FAILED\r\n"); }

   }
 */

   {
      int Status;
      
      print("\r\n Running IicPsSelfTestExample() for ps7_i2c_0... I2C slow control\r\n");
      
      Status = IicPsSelfTestExample(XPAR_PS7_I2C_0_DEVICE_ID);
      
      if (Status == 0) { print("IicPsSelfTestExample PASSED\r\n"); }
      else { print("IicPsSelfTestExample FAILED\r\n"); }
   }
   

   {
      int Status;
      
      print("\r\n Running IicPsSelfTestExample() for ps7_i2c_1... I2C clock generator\r\n");
      
      Status = IicPsSelfTestExample(XPAR_PS7_I2C_1_DEVICE_ID);
      
      if (Status == 0) { print("IicPsSelfTestExample PASSED\r\n"); }
      else { print("IicPsSelfTestExample FAILED\r\n"); }

   }
   

   {
      int Status;
      
      print("\r\n Running QspiSelfTestExample() for ps7_qspi_0...\r\n");
      
      Status = QspiPsSelfTestExample(XPAR_PS7_QSPI_0_DEVICE_ID);
      
      if (Status == 0) { print("QspiPsSelfTestExample PASSED\r\n"); }
      else { print("QspiPsSelfTestExample FAILED\r\n"); }
   }
   

   {
      int Status;
      
      print("\r\n Running ScuTimerPolledExample() for ps7_scutimer_0...  : ");
      Status = ScuTimerPolledExample(XPAR_PS7_SCUTIMER_0_DEVICE_ID);
      if (Status == 0) { print("PASSED\r\n"); }
      else { print("FAILED\r\n"); }

      print("\r\n Running Interrupt Test  for ps7_scutimer_0...  : ");
      Status = ScuTimerIntrExample(&intc, &ps7_scutimer_0, \
                                 XPAR_PS7_SCUTIMER_0_DEVICE_ID, \
                                 XPAR_PS7_SCUTIMER_0_INTR);
	
      if (Status == 0) { print("PASSED\r\n"); }
      else { print("FAILED\r\n"); }
   }
   
   {
      int Status;

      print("\r\n Running Interrupt Test  for ps7_scuwdt_0...\r\n");
      Status = ScuWdtIntrExample(&intc, &ps7_scuwdt_0, \
                                 XPAR_PS7_SCUWDT_0_DEVICE_ID, \
                                 XPAR_PS7_SCUWDT_0_INTR);
	
      if (Status == 0) { print("ScuWdtIntrExample PASSED\r\n"); }
      else { print("ScuWdtIntrExample FAILED\r\n"); }
   }

   {
      int Status;
      
      print("\r\n Running SpiPsSelfTestExample() for ps7_spi_0...\r\n");
      Status = SpiPsSelfTestExample(XPAR_PS7_SPI_0_DEVICE_ID);
      if (Status == 0) { print("SpiPsSelfTestExample PASSED\r\n"); }
      else { print("SpiPsSelfTestExample FAILED\r\n"); }
   }
   
/*   {
      int Status;
      
      print("\r\n Running SpiPsSelfTestExample() for ps7_spi_1...\r\n");
      Status = SpiPsSelfTestExample(XPAR_PS7_SPI_1_DEVICE_ID);
      if (Status == 0) { print("SpiPsSelfTestExample PASSED\r\n"); }
      else { print("SpiPsSelfTestExample FAILED\r\n"); }
   }
 */
   {
      int Status;

      print("\r\nRunning UartPsPolledExample() for ps7_uart_0...\r\n");
      Status = UartPsPolledExample(XPAR_PS7_UART_0_DEVICE_ID);
      if (Status == 0) { print("UartPsPolledExample PASSED\r\n"); }
      else { print("UartPsPolledExample FAILED\r\n"); }

      print("\r\n Running Interrupt Test for ps7_uart_0...\r\n");
      Status = UartPsIntrExample(&intc, &ps7_uart_0, \
                                  XPAR_PS7_UART_0_DEVICE_ID, \
                                  XPAR_PS7_UART_0_INTR);
      if (Status == 0) { print("UartPsIntrExample PASSED\r\n"); }
      else { print("UartPsIntrExample FAILED\r\n"); }
   }

   {
     int Status;

     // initialise le circuit clock generator CDEL913
     XIicPs_ResetHw(XPAR_XIICPS_1_BASEADDR);
     print("\r\n Initialisation de ... I2C clock generator : ");
     Status = IicPsInitClockGenerator(XPAR_PS7_I2C_1_DEVICE_ID);
     if (Status == 0) { print("OK"); } else { print("FAILED"); }
     print("\r\n");

     // initialise les circuits ADC9628
     print(" Initialisation de ... ADC 9628 : ");
     Status = SpiPs_Init_SPI(XPAR_PS7_SPI_1_DEVICE_ID);
     if (Status == 0) { print("OK"); }  else { print("FAILED"); }
     print("\r\n");

   }

   // test des registres
     unsigned int *registre_adc;
     registre_adc = 0x43C00000;
     int i;

     printf("\r\n Affichage des registres interne de INTERFACE_UUB : \r\n");
     for ( i = 0; i < 16; i++)
     {
         printf( "  %X = %X \r\n",registre_adc, *registre_adc);
    	 registre_adc = registre_adc + 1;
     }
     
     registre_adc = 0x43C00000;
     while(1)
     {
    	 printf( "  Channel A = %X,  Channel B = %X \r\n ",*registre_adc >>16,*registre_adc && 0xffff);


    	 for( i = 0; i<50000000;i++)
    	 {
    		 registre_adc = 0x43C00000;
    	 }
     }

   // Peripheral Test will not be run for uart_1 because it has been selected
   // as the STDOUT device

   print("---Exiting main---\n\r");
   Xil_DCacheDisable();
   Xil_ICacheDisable();
   return 0;
}
