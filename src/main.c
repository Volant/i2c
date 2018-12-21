#include "HAL.h"

#include <stdint.h>

int main();

void __main(void) {
    main();
}

int main(void) {

	__enable_irq();

	GPIO_InitTypeDef gpio_init;

	gpio_init.GPIO_Mode = GPIO_ModeR_Out;
	gpio_init.GPIO_Type = GPIO_Type_PP;
	gpio_init.GPIO_PUpD = GPIO_PUpDR_PU;
	gpio_init.GPIO_Pin  = GPIO_Pin_07;
	GPIO_Init(GPIOB, &gpio_init);

//	#define DBGMCU_APB1_FZ  0xE0042008
//	#define DBG_TIM0_STOP 	1 << 5
//	*((volatile uint32_t*)(DBGMCU_APB1_FZ)) |= DBG_TIM0_STOP;


#define NVIC_ISER0 0xE000E100
#define NVIC_ISER1 0xE000E104
#define NVIC_ISER2 0xE000E108
#define NVIC_ISER3 0xE000E10C
#define NVIC_ISER4 0xE000E110
#define NVIC_ISER5 0xE000E114
#define NVIC_ISER6 0xE000E118
#define NVIC_ISER7 0xE000E11C

#define NVIC_ICER0 0xE000E180
#define NVIC_ICER1 0xE000E184
#define NVIC_ICER2 0xE000E188
#define NVIC_ICER3 0xE000E18C
#define NVIC_ICER4 0xE000E190
#define NVIC_ICER5 0xE000E194
#define NVIC_ICER6 0xE000E198
#define NVIC_ICER7 0xE000E19C


	uint32_t en_addr = NVIC_ISER1;


	// 70 - 16 = 54; 54 - 32 = 22
	*((volatile uint32_t*)(NVIC_ISER1)) |= 1 << 22;

	*((volatile uint32_t*)(RCC_BASE + RCC_APB1_EN_R)) |= 1 << TIM6_DAC_IRQn;

    uint32_t tim6_psc = TIM6_Base + TIMx_PSC;

    // Настраиваем делитель что таймер тикал 1000 раз в секунду
	*((volatile uint32_t*)(tim6_psc)) = 24000 - 1;

    // Чтоб прерывание случалось раз в секунду
	*((volatile uint32_t*)(TIM6_Base + TIMx_ARR)) = 1000;
	
    //разрешаем прерывание от таймера
	*((volatile uint32_t*)(TIM6_Base + TIMx_DIER)) |= TIM_DIER_UIE;
	
    // Начать отсчёт!
	*((volatile uint32_t*)(TIM6_Base + TIMx_CR1)) |= TIM_CR1_CEN;

	*((volatile uint32_t*)(TIM6_Base + TIMx_SR)) &= ~(TIM_SR_UIF);

	*((volatile uint32_t*)(TIM6_Base + TIMx_EGR)) |= TIM_EGR_UG;

	//	NVIC_EnableIRQ(TIM6_DAC_IRQn); //Разрешение TIM6_DAC_IRQn прерывания

//	uint32_t addr = TIM6_Base + TIMx_SR;

	//Инвертируем состояние светодиодов
	*((volatile unsigned int *)(GPIO_Bases[GPIOB] + GPIO_ODR)) ^= (1 << GPIO_Pin_00);
	*((volatile unsigned int *)(GPIO_Bases[GPIOB] + GPIO_ODR)) ^= (1 << GPIO_Pin_00);

	uint32_t status_reg = *((volatile uint32_t*)(TIM6_Base + TIMx_SR));

	while(1);

	return 0;
}

void TIM6_DAC_IRQHandler(void) {

	//Сбрасываем флаг UIF
	*((volatile uint32_t*)(TIM6_Base + TIMx_SR)) &= ~TIM_SR_UIF;

	//Инвертируем состояние светодиодов
	*((volatile unsigned int *)(GPIO_Bases[GPIOB] + GPIO_ODR)) ^= (1 << GPIO_Pin_07);

	//	GPIOC->ODR ^= (GPIO_Pin_9 | GPIO_Pin_8);
}
