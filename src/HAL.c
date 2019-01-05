#include "HAL.h"

void GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef *defs) {
	*((volatile uint32_t *)(RCC_BASE + RCC_AHB1_EN_R)) |= 1 << GPIO_GET_INDEX(GPIOx);

	GPIOx->MODER  |= defs->Mode << (2 * defs->Pin);
	GPIOx->OTYPER |= defs->Type;
	GPIOx->PUPDR  |= defs->Pull << (2 * defs->Pin);
	GPIOx->ODR    |= (2 << defs->Pin);
	GPIOx->BSRR   |= (1 << defs->Pin);
}
