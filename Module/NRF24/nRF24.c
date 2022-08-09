#include "nRF24.h"

/*
	uint8_t ch = 50;
	uint8_t plSize = 32;
	uint8_t rfSet = RF_SETUP_VALUE(RF_SET_BR_2MBPS,RF_SET_OP_0_DBM);
	uint8_t config = 8;
	uint8_t autoACK = 0x3F;
	uint8_t allRX = 0x3F;
	uint8_t retrVal = RETR_SETUP_VALUE(RETR_ARD_1250,RETR_ARC_15);
	uint8_t dynamicVAL = 0;
*/


t_nrfInfo sNRFInfo = {
#ifdef NRF_TX_MODE
												.config 		 = 0x0A,
#elif defined NRF_RX_MODE
												.config 		 = 0x0B,
#endif
												.enAutoACK 	 = 0x01,
												.enRxAddr 	 = 0x01,
												.autoRet		 = RETR_SETUP_VALUE(RETR_ARD_1250,RETR_ARC_15),
												.channel  	 = 115,
												.setRF    	 = RF_SETUP_VALUE(RF_SET_BR_1MBPS,RF_SET_OP_0_DBM),
												.status 		 = 0x70,
												.rxAddrP0		 = {0xE7,0xB1,0xB2,0xA1,0xA2},
												.txAddr			 = {0xE7,0xB1,0xB2,0xA1,0xA2},
												.rxPayloadP0 = 1,
												.rxPayloadP1 = 32,
												.rxPayloadP2 = 32,
												.rxPayloadP3 = 32,
												.rxPayloadP4 = 32,
												.rxPayloadP5 = 32,
												.DYNPD			 = 0
};

uint8_t CheckNRF24(void)
{
	uint8_t command[2] = {
													(CMD_READ | REG_SETUP_AW), 
													 CMD_NOP
											 };
	
	spiSend(command, 2, READ_MODE);									 
											 
	return (command[1] >= 1 && command[1] <=3) ? 1 : 0;
}

void ReadAllReg(void)
{	
	uint8_t regArr[] = {
												REG_CONFIG,2,
												REG_EN_AA,2,
												REG_EN_RXADDR,2,
												REG_SETUP_AW,2,
												REG_SETUP_RETR,2,
												REG_RF_CH,2,
												REG_RF_SETUP,2,
												REG_STATUS,2,
												REG_OBSERVE_TX,2,
												REG_RPD,2,
		
												REG_RX_ADDR_P0,6,
	     									REG_RX_ADDR_P1,6,
												REG_RX_ADDR_P2,6,
												REG_RX_ADDR_P3,6,
												REG_RX_ADDR_P4,6,
												REG_RX_ADDR_P5,6,
												REG_TX_ADDR,6,
		
												REG_RX_PW_P0,2,
												REG_RX_PW_P1,2,
												REG_RX_PW_P2,2,
												REG_RX_PW_P3,2,
												REG_RX_PW_P4,2,
												REG_RX_PW_P5,2,
												REG_FIFO_STATUS,2,
												REG_DYNPD,2,
												REG_FEATURE,2};

	uint8_t command[16] = {0};
	
	for(uint8_t i = 0; i < sizeof(regArr);i+=2)
		{
			command[0] = (regArr[i] | CMD_READ);
			command[1] = (CMD_NOP);
			
			spiSend(command, regArr[i+1] , READ_MODE);
			
			SEND("%02x --> %02x\r\n",regArr[i],command[1])
		}
		SEND("\r\n")
}

void WriteNRF24(uint8_t reg, uint8_t* buff, uint8_t len)
{
	uint8_t temp = (CMD_WRITE | reg);
	
	CS_LOW
	t_spiSend(&temp, 1, WRITE_MODE);
	if(len > 0) t_spiSend(buff,len, WRITE_MODE);
	CS_HIGH
}

uint8_t ReadNRF24(uint8_t reg, uint8_t* buff, uint8_t len)
{	
	uint8_t temp = (CMD_READ | reg);
	
	CS_LOW
	t_spiSend(&temp, 1, READ_MODE);
	t_spiSend(buff,len, READ_MODE);
	CS_HIGH
	
	return temp;
}

void InitNRF24(t_nrfInfo* param)
{
	t_nrfInfo* pNRFInfo = param;
	
	WriteNRF24(REG_RF_CH,&(pNRFInfo->channel),1);

	WriteNRF24(REG_RX_PW_P0,&(pNRFInfo->rxPayloadP0),1);
	WriteNRF24(REG_RX_PW_P1,&(pNRFInfo->rxPayloadP1),1);
	WriteNRF24(REG_RX_PW_P2,&(pNRFInfo->rxPayloadP2),1);
	WriteNRF24(REG_RX_PW_P3,&(pNRFInfo->rxPayloadP3),1);
	WriteNRF24(REG_RX_PW_P4,&(pNRFInfo->rxPayloadP4),1);
	WriteNRF24(REG_RX_PW_P5,&(pNRFInfo->rxPayloadP5),1);
	
	WriteNRF24(REG_RX_ADDR_P0,(pNRFInfo->rxAddrP0),5);
	WriteNRF24(REG_TX_ADDR,(pNRFInfo->txAddr),5);

	WriteNRF24(REG_RF_SETUP,&(pNRFInfo->setRF),1);
	WriteNRF24(REG_CONFIG,&(pNRFInfo->config),1);
	WriteNRF24(REG_EN_AA,&(pNRFInfo->enAutoACK),1);
	WriteNRF24(REG_EN_RXADDR,&(pNRFInfo->enRxAddr),1);
	WriteNRF24(REG_SETUP_RETR,&(pNRFInfo->autoRet),1);
	
	WriteNRF24(REG_DYNPD,&(pNRFInfo->DYNPD)  ,1);
	
	WriteNRF24(REG_STATUS,&(pNRFInfo->status),1);
}

