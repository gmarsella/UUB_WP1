
/*****************************************************************************/
/**
* @file xspi_init_ADC.c
**
* @note
*
* None.
*
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xparameters.h"  /* EDK generated parameters */
#include "xspips.h"       /* SPI device driver */
#include "xil_printf.h"

/************************** Constant Definitions *****************************/

// The following constant defines the slave select signal that is used to select
// the EEPROM device on the SPI bus, this signal is typically connected to the 
// chip select of the device
 
//#define SPI_SELECT 0x00

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

XSpiPs Spi;

#define SPI_SELECT_DAC  0x06
#define SPI_SELECT_ADC0 0x05
#define SPI_SELECT_ADC1 0x03
#define read_buffer_size 10                 // size of the SPI read buffer
#define write_buffer_size 10                // size of the SPI write buffer
u8 ReadBuffer[read_buffer_size]   = {0x00}; // SPI read buffer initialize to 0
u8 WriteBuffer[write_buffer_size] = {0x00}; // SPI write buffer initialize to 0

/*****************************************************************************
*
* The purpose of this function is to illustrate how to use the XSpiPs
* device driver in polled mode. This test writes and reads data from a
* serial EEPROM. The serial EEPROM part must be present in the hardware
* to use this example.
*
* @param  SpiInstancePtr is a pointer to the Spi Instance.
* @param  SpiDeviceId is the Device Id of Spi.
*
* @return XST_SUCCESS if successful else XST_FAILURE.
*
* @note
*
* This function calls functions which contain loops that may be infinite
* if interrupts are not working such that it may not return. If the device
* slave select is not correct and the device is not responding on bus it will
* read a status of 0xFF for the status register as the bus is pulled up.
*
*****************************************************************************/
int SpiPs_Init_SPI(u16 SpiDeviceId)
{
  int Status;
  XSpiPs_Config *SpiConfig;

  /* Initialize the SPI driver so that it's ready to use */
  SpiConfig = XSpiPs_LookupConfig(SpiDeviceId);
  if (NULL == SpiConfig) { return XST_FAILURE; }

  Status = XSpiPs_CfgInitialize(&Spi, SpiConfig, SpiConfig->BaseAddress);
  if (Status != XST_SUCCESS) { return XST_FAILURE; }

  // Perform a self-test to check hardware build
  Status = XSpiPs_SelfTest(&Spi);
  if (Status != XST_SUCCESS) { return XST_FAILURE; }

  // Set the SCLK frequency to SPI_REF_CLK / XSPIPS_CLK_PRESCALE_xx
  XSpiPs_SetClkPrescaler(&Spi, XSPIPS_CLK_PRESCALE_32);

  //************************************************
  // Initialize the DAC component
  //************************************************

  // Set the Spi device as a master ( is slave by default).
  XSpiPs_SetOptions(&Spi, XSPIPS_MASTER_OPTION |
		                  XSPIPS_FORCE_SSELECT_OPTION |
		                  XSPIPS_DECODE_SSELECT_OPTION |
		                  XSPIPS_CLK_PHASE_1_OPTION);
  // Write value data into DAC "CLOCK Generator"
  WriteBuffer[0] = 0x08;
  WriteBuffer[1] = 0x00;
  XSpiPs_SetSlaveSelect(&Spi, SPI_SELECT_DAC);    // Assert the chip select
  XSpiPs_PolledTransfer(&Spi, WriteBuffer, ReadBuffer, 2);

  //************************************************
  // Initialize The ADC0 component
  //************************************************

  // Set the Spi device as a master ( is slave by default).
  XSpiPs_SetOptions(&Spi, XSPIPS_MASTER_OPTION |
		                  XSPIPS_FORCE_SSELECT_OPTION |
		                  XSPIPS_DECODE_SSELECT_OPTION);
  // Write config data into ADC0 Chip
  WriteBuffer[0] = 0x00;                            // writing cycle
  WriteBuffer[1] = 0x14;                            // address register
  WriteBuffer[2] = 0xA1;                            // data to write
  XSpiPs_SetSlaveSelect(&Spi, SPI_SELECT_ADC0);     // Assert the chip select
  XSpiPs_PolledTransfer(&Spi, WriteBuffer, ReadBuffer, 3);

  //************************************************
  // Initialize The ADC1 component
  //************************************************

  // Write config data into ADC1 Chip
  WriteBuffer[0] = 0x00;
  WriteBuffer[1] = 0x14;
  WriteBuffer[2] = 0xA1;
  XSpiPs_SetSlaveSelect(&Spi, SPI_SELECT_ADC1);     // Assert the chip select
  XSpiPs_PolledTransfer(&Spi, WriteBuffer, ReadBuffer, 3);


  return XST_SUCCESS;
}

