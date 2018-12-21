#include "HAL.h"

void GPIO_Init(uint32_t GPIO_REG, GPIO_InitTypeDef *defs) {
	*((volatile uint32_t *)(RCC_BASE + RCC_AHB1_EN_R)) |= 1 << GPIO_REG;

	*((volatile unsigned int *)(GPIO_Bases[GPIO_REG] + GPIO_ModeR))  |= defs->GPIO_Mode << (2 * defs->GPIO_Pin);
	*((volatile unsigned int *)(GPIO_Bases[GPIO_REG] + GPIO_OTypeR)) |= defs->GPIO_Type;
	*((volatile unsigned int *)(GPIO_Bases[GPIO_REG] + GPIO_PUpDR))  |= defs->GPIO_PUpD << (2 * defs->GPIO_Pin);
	*((volatile unsigned int *)(GPIO_Bases[GPIO_REG] + GPIO_ODR))    |= (2 << defs->GPIO_Pin);
	*((volatile unsigned int *)(GPIO_Bases[GPIO_REG] + GPIO_BSRR))   |= (1 << defs->GPIO_Pin);
}
