#ifndef __NRF24_H
#define __NRF24_H

#include "stm32f10x.h"
#include "spi.h"
#include "Led.h"

//#define REG_SUMARY_NUM     (sizeof(regArr)/sizeof(regArr[0]))

/**********************/
/***** COMMAND MAP ****/
/**********************/

#define CMD_READ				 		0x00		//READ  COMMAND
#define CMD_WRITE				 		0x20		//WRITE COMMAND
#define CMD_R_RX_PL_WID	 		0x60		//READ  RX-payload width
#define CMD_R_RX_PAYLOAD 		0x61		//READ  RX-payload 	(Used in RXmode)
#define CMD_W_TX_PAYLOAD		0xA0		//WRITE TX-payload  (Used in TXmode)
#define CMD_W_ACK_PL	   		0xA8		//WRITE Payload to be transmitted together with ACK packet on PIPE(Used in RXmode)
#define CMD_W_TX_PL_NO_ACK  0xB0		//DISABLE AUTOACK on this specific packet (Used in TXmode)
#define CMD_FLUSH_TX				0xE1		//FLUSH TX FIFO			(Used in TXmode)
#define CMD_FLUSH_RX				0xE2		//FLUSH RX FIFO			(Used in RXmode)
#define CMD_REUSE_TX_PL			0xE3		//REUSE last transmitted payload

#define CMD_NOP         	  0xFF		//NO OPERATION

/**********************/
/**** REGISTER MAP ****/
/**********************/

#define REG_CONFIG			0x00		//Configuration Register
#define REG_EN_AA				0x01		//Enable "Auto-Acknowledgment"
#define REG_EN_RXADDR		0x02		//Enable RX Addresses
#define REG_SETUP_AW		0x03		//Setup of Address Widths
#define REG_SETUP_RETR	0x04		//Setup of Automatic Retransmission
#define REG_RF_CH				0x05		//RF Channel
#define REG_RF_SETUP		0x06		//RF Setup Register
#define REG_STATUS			0x07		//Status
#define REG_OBSERVE_TX	0x08		//Transmit observe register
#define REG_RPD					0x09		//Received Power Detector
#define REG_RX_ADDR_P0	0x0A		//Receive address data pipe0
#define REG_RX_ADDR_P1	0x0B		//Receive address data pipe1
#define REG_RX_ADDR_P2	0x0C		//Receive address data pipe2
#define REG_RX_ADDR_P3	0x0D		//Receive address data pipe3
#define REG_RX_ADDR_P4	0x0E		//Receive address data pipe4
#define REG_RX_ADDR_P5	0x0F		//Receive address data pipe5
#define REG_TX_ADDR			0x10		//Transmit address
#define REG_RX_PW_P0		0x11		// ---- ----- ----- ---- ----
#define REG_RX_PW_P1		0x12		// ---- ----- ----- ---- ----
#define REG_RX_PW_P2		0x13		// ---- ----- ----- ---- ----
#define REG_RX_PW_P3		0x14		// ---- ----- ----- ---- ----
#define REG_RX_PW_P4		0x15		// ---- ----- ----- ---- ----
#define REG_RX_PW_P5		0x16		// ---- ----- ----- ---- ----
#define REG_FIFO_STATUS	0x17		// FIFO Status register
#define REG_DYNPD				0x1C		// Enable dynamic payload length
#define REG_FEATURE			0x1D		// Feature Register

/**********************/
/**** PARAM DEFINE ****/
/**********************/

#define  RETR_ARD_250	0x00
#define  RETR_ARD_500	0x01
#define  RETR_ARD_750	0x02
#define RETR_ARD_1000	0x03
#define RETR_ARD_1250	0x04
#define RETR_ARD_1500	0x05
#define RETR_ARD_1750	0x06
#define RETR_ARD_2000	0x07
#define RETR_ARD_2250	0x08
#define RETR_ARD_2500	0x09
#define RETR_ARD_2750	0x0A
#define RETR_ARD_3000	0x0B
#define RETR_ARD_3250	0x0C
#define RETR_ARD_3500	0x0D
#define RETR_ARD_3750	0x0E
#define RETR_ARD_4000	0x0F

#define  RETR_ARC_0   0x00
#define  RETR_ARC_1   0x01
#define  RETR_ARC_2   0x02
#define  RETR_ARC_3   0x03
#define  RETR_ARC_4   0x04
#define  RETR_ARC_5   0x05
#define  RETR_ARC_6   0x06
#define  RETR_ARC_7   0x07
#define  RETR_ARC_8   0x08
#define  RETR_ARC_9   0x09
#define  RETR_ARC_10  0x0A
#define  RETR_ARC_11  0x0B
#define  RETR_ARC_12  0x0C
#define  RETR_ARC_13  0x0D
#define  RETR_ARC_14  0x0E
#define  RETR_ARC_15  0x0F

#define RETR_SETUP_VALUE(A,B) (A << 4) | (B << 0)

/**********************/

#define RF_SET_BR_1MBPS   0		  //(x0000xx0)
#define RF_SET_BR_2MBPS   1			//(x0001xx0)
#define RF_SET_BR_250KBPS 5			//(x0101xx0)

#define RF_SET_OP_18_DBM  0			//(x0xxx000)
#define RF_SET_OP_12_DBM  1			//(x0xxx010)
#define  RF_SET_OP_6_DBM  2			//(x0xxx100)	
#define  RF_SET_OP_0_DBM  3			//(x0xxx110)

#define RF_SETUP_VALUE(A,B) (A << 3) | (B << 1)

/**********************/
typedef struct{
  uint8_t config;
  uint8_t enAutoACK;
  uint8_t enRxAddr;
  uint8_t widthAddr;
  uint8_t autoRet;
  uint8_t channel;
  uint8_t setRF;
  uint8_t status;
//  uint8_t obsTX;
//  uint8_t RPD;
  uint8_t rxAddrP0[5];
  uint8_t rxAddrP1[5];
  uint8_t rxAddrP2[5];
  uint8_t rxAddrP3[5];
  uint8_t rxAddrP4[5];
  uint8_t rxAddrP5[5];
  uint8_t txAddr[5];
  uint8_t rxPayloadP0;
  uint8_t rxPayloadP1;
  uint8_t rxPayloadP2;
  uint8_t rxPayloadP3;
  uint8_t rxPayloadP4;
  uint8_t rxPayloadP5;
//  uint8_t statusFIFO;
  uint8_t DYNPD;
  uint8_t feature;
}t_nrfInfo;

extern t_nrfInfo sNRFInfo;


extern char* CheckNRF24(void);
extern void  ReadAllReg(void);
extern void ReadNRF24(uint8_t reg, uint8_t* buff, uint8_t len);
extern void  WriteNRF24(uint8_t reg, uint8_t* buff, uint8_t len);
extern void  InitNRF24(t_nrfInfo*);


#endif /* __NRF24_H */
