#include "System.h"

void System_Init_72MHZ(void)
{
	RCC->CR    |=  RCC_CR_HSEON;							// Enable HSE
	RCC->CFGR  |=  RCC_CFGR_PLLMULL9;						// Multiply PLL * 9
	RCC->CR    |=  RCC_CR_PLLON;							// Enable PLL
	FLASH->ACR |=  FLASH_ACR_LATENCY_2;						// 2 waiting cycles
	RCC->CFGR  |=  (RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1);	// Not Divide HPRE(AHB bus) and PPRE2(APB2 bus), PPRE1(APB1 bus) divide by 2
	RCC->CFGR  |=  RCC_CFGR_SW_PLL;							// Switch to PLL
	//RCC->CR    &= ~RCC_CR_HSION;							// Turn off HSI
}

void System_Init_48MHZ(void)
{
	RCC->CR    |=  RCC_CR_HSEON;							// Enable HSE
	RCC->CFGR  |=  RCC_CFGR_PLLMULL6;						// Multiply PLL * 6
	RCC->CR    |=  RCC_CR_PLLON;							// Enable PLL
	FLASH->ACR |=  FLASH_ACR_LATENCY_1;						// 1 waiting cycles
	RCC->CFGR  |=  (RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1);	// Not Divide HPRE(AHB bus) and PPRE2(APB2 bus), PPRE1(APB1 bus) divide by 2
	RCC->CFGR  |=  RCC_CFGR_SW_PLL;							// Switch to PLL
	RCC->CR    &= ~RCC_CR_HSION;							// Turn off HSI
}
