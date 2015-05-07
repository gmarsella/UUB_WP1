 /***************************************************************************/
 /**
 * @file xiicps_polled_master_example.c
 *
 * A design example of using the device in polled mode as master.
 *
 * The example uses buffer size 132. Please set the send buffer of the
 * Aardvark device to be continuous 64 bytes from 0x00 to 0x3F.
  *
  **************************************************************************/
 
 /***************************** Include Files ******************************/
 #include "xparameters.h"
 #include "xiicps.h"
 
 /************************** Constant Definitions **************************/
 
 /* The following constants map to the XPAR parameters created in the
  * xparameters.h file. They are defined here such that a user can easily
  * change all the needed parameters in one place. */
 #define IIC_DEVICE_ID    XPAR_XIICPS_0_DEVICE_ID
 
 #define IIC_SLAVE_ADDR   0x65     /* The slave address */
 #define IIC_SCLK_RATE    100000   /* tansfert frequency */
 #define BUFFER_SIZE 40            /* Tansmit and receive buffer size */
 
 /**************************** Type Definitions ****************************/
 
 /************************** Variable Definitions **************************/
 
 XIicPs Iic;    /**< Instance of the IIC Device */
 
 /* The following buffers are used to send and receive data with the IIC. */
 u8 SendBuffer[BUFFER_SIZE] = { 0x00, 0x20, /**< Buffer for Transmitting Data */
                                0x01, 0x00, 0xB4, 0x01, 0x02, 0x50, 0x40, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x6D, 0x02, 0x00, 0x00, 
                                0x99, 0x03, 0x32, 0x68, 0x00, 0x40, 0x02, 0x08}; 
 u8 RecvBuffer[BUFFER_SIZE] = { 0x00};;    /**< Buffer for Receiving Data */
 
 /*************************************************************************
 *
 * This function sends data and expects to receive data from slave as modular
 * of 64.
 *
 * This function uses interrupt-driven mode of the device.
 *
 * @param DeviceId is the Device ID of the IicPs Device and is the
 *    XPAR_<IICPS_instance>_DEVICE_ID value from xparameters.h
 *
 * @return  XST_SUCCESS if successful, otherwise XST_FAILURE.
 *
 * @note    None.
 *
 **************************************************************************/
 int IicPsInitClockGenerator(u16 DeviceId)
 {
  int Status;
  XIicPs_Config *Config;
  int Index;
 
  /* Initialize the IIC driver so that it's ready to use Look up the 
   * configuration in the config table, then initialize it. */
  Config = XIicPs_LookupConfig(DeviceId);
  if (NULL == Config) { return XST_FAILURE; }
 
  Status = XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress);
  if (Status != XST_SUCCESS) { return XST_FAILURE; }
 
  /* Perform a self-test to ensure that the hardware was built correctly. */
  Status = XIicPs_SelfTest(&Iic);
  if (Status != XST_SUCCESS) { return XST_FAILURE; }
 
  /* Set the IIC serial clock rate. */
  XIicPs_SetSClk(&Iic, IIC_SCLK_RATE);
  XIicPs_SetOptions(&Iic, XIICPS_REP_START_OPTION);
 
  /* Send the buffer using the IIC and ignore the number of bytes sent
   * as the return value since we are using it in interrupt mode. */
  while (XIicPs_BusIsBusy(&Iic)) { /* NOP */ }

  Status = XIicPs_MasterSendPolled(&Iic, SendBuffer,34, IIC_SLAVE_ADDR);
  if (Status != XST_SUCCESS) { return XST_FAILURE; }
//     Status = XIicPs_MasterRecvPolled(&Iic, RecvBuffer,1, IIC_SLAVE_ADDR);
//     if (Status != XST_SUCCESS) { return XST_FAILURE; }

//  printf("request ID %X\n\r",Config->BaseAddress);

//  XIicPs_MasterRead(&Iic, RecvBuffer,1, 0x65);
//  printf(" valeur lue : %d %d\n\r", RecvBuffer[0], RecvBuffer[1]);

//  XIicPs_MasterSend(&Iic, SendBuffer,2, IIC_SLAVE_ADDR);
//  if (Status != XST_SUCCESS) { print("mauvaise reception\n\r"); }
//  else { print("reception OK\n\r");}
//  
//   /* Verify received data is correct. */
//    for(Index = 0; Index < BUFFER_SIZE; Index ++) {
//  
//     /* Aardvark as slave can only set 64 bytes for output */
//     if (RecvBuffer[Index] != Index % 64) { return XST_FAILURE; }
//   }
 
  return XST_SUCCESS;
 }



 /*****************************************************************************/
 /* This function prepares a device to transfers as a master.
 *
 * @param	InstancePtr is a pointer to the XIicPs instance.
 *
 * @param	Role specifies whether the device is sending or receiving.
 *
 * @return  - XST_SUCCESS if everything went well.
 *		    - XST_FAILURE if bus is busy.
 *
 * @note	Interrupts are always disabled, device which needs to use
 *		    interrupts needs to setup interrupts after this call.
 *
 ****************************************************************************/
 static int XIicPs_MasterSetup(XIicPs *InstancePtr, int Role)
 {
 	u32 ControlReg;
 	u32 BaseAddr;
 	u32 EnabledIntr = 0x0;

 	Xil_AssertNonvoid(InstancePtr != NULL);

 	BaseAddr = InstancePtr->Config.BaseAddress;
 	ControlReg = XIicPs_ReadReg(BaseAddr, XIICPS_CR_OFFSET);

 	/* Only check if bus is busy when repeated start option is not set. */
 	if ((ControlReg & XIICPS_CR_HOLD_MASK) == 0)
 	{
 		if (XIicPs_BusIsBusy(InstancePtr)) { return XST_FAILURE; }
 	}

 	/* Set up master, AckEn, nea and also clear fifo. */
 	ControlReg |= XIICPS_CR_ACKEN_MASK | XIICPS_CR_CLR_FIFO_MASK |
 		 	XIICPS_CR_NEA_MASK | XIICPS_CR_MS_MASK;

 	if (Role == RECVING_ROLE) {
 		ControlReg |= XIICPS_CR_RD_WR_MASK;
 		EnabledIntr = XIICPS_IXR_DATA_MASK |XIICPS_IXR_RX_OVR_MASK;
 	}else {
 		ControlReg &= ~XIICPS_CR_RD_WR_MASK;
 	}
 	EnabledIntr |= XIICPS_IXR_COMP_MASK | XIICPS_IXR_ARB_LOST_MASK;

 	XIicPs_WriteReg(BaseAddr, XIICPS_CR_OFFSET, ControlReg);

 	XIicPs_DisableAllInterrupts(BaseAddr);

 	return XST_SUCCESS;
 }
 

 /*****************************************************************************/
 /**
 * This function initiates an interrupt-driven receive in master mode.
 *
 * It sets the transfer size register so the slave can send data to us.
 * The rest of the work is managed by interrupt handler.
 *
 * @param	InstancePtr is a pointer to the XIicPs instance.
 * @param	MsgPtr is the pointer to the receive buffer.
 * @param	ByteCount is the number of bytes to be received.
 * @param	SlaveAddr is the address of the slave we are receiving from.
 *
 * @return	None.
 *
 * @note		This receive routine is for interrupt-driven transfer only.
 *
 ****************************************************************************/
 void XIicPs_MasterRead(XIicPs *InstancePtr, u8 *MsgPtr, int ByteCount, u16 SlaveAddr)
 {
 	u32 BaseAddr;

 	/* Assert validates the input arguments. */
 	Xil_AssertVoid(InstancePtr != NULL);
 	Xil_AssertVoid(MsgPtr != NULL);
 	Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);
 	Xil_AssertVoid(XIICPS_ADDR_MASK >= SlaveAddr);

 	BaseAddr = InstancePtr->Config.BaseAddress;
 	InstancePtr->RecvBufferPtr = MsgPtr;
 	InstancePtr->RecvByteCount = ByteCount;
 	InstancePtr->CurrByteCount = ByteCount;
 	InstancePtr->SendBufferPtr = NULL;
 	InstancePtr->IsSend = 0;
 	InstancePtr->UpdateTxSize = 0;

 	/* Initialize for a master receiving role. */
 	XIicPs_MasterSetup(InstancePtr, RECVING_ROLE);

 	/* Do the address transfer to signal the slave. */
 	XIicPs_WriteReg(BaseAddr, XIICPS_ADDR_OFFSET, SlaveAddr);
 	XIicPs_WriteReg(BaseAddr, XIICPS_DATA_OFFSET, SlaveAddr+1);

 	/* Setup the transfer size register so the slave knows how much to send to us. */
 	if (ByteCount > XIICPS_MAX_TRANSFER_SIZE)
 	{
 	  XIicPs_WriteReg(BaseAddr, XIICPS_TRANS_SIZE_OFFSET,XIICPS_MAX_TRANSFER_SIZE);
 	  InstancePtr->CurrByteCount = XIICPS_MAX_TRANSFER_SIZE;
 	  InstancePtr->UpdateTxSize = 1;
 	}
 	else
 	{
 	  XIicPs_WriteReg(BaseAddr, XIICPS_TRANS_SIZE_OFFSET, ByteCount);
 	}

 	return XST_SUCCESS;

// 	XIicPs_EnableInterrupts(BaseAddr,
// 		XIICPS_IXR_NACK_MASK | XIICPS_IXR_DATA_MASK |
// 		XIICPS_IXR_RX_OVR_MASK | XIICPS_IXR_COMP_MASK |
// 		XIICPS_IXR_ARB_LOST_MASK);
 }
