#ifndef __HAL_H__
#define __HAL_H__

#include <stdint.h>

#define RCC_BASE			0x40023800
#define RCC_AHB1_EN_R		0x30
#define RCC_APB1_EN_R		0x40

#define TIM6_DAC_IRQn		0x4

#define GPIO_Base			0x40020000

#define GPIO_ModeR			0x00
#define GPIO_OTypeR			0x04
#define	GPIO_OSpeedR		0x08
#define GPIO_PUpDR			0x0C
#define GPIO_IDR			0x10
#define	GPIO_ODR			0x14
#define	GPIO_BSRR			0x18
#define	GPIO_LCKR			0x1C
#define	GPIO_AFRL			0x20
#define GPIO_AFRH			0x24

#define GPIO_ModeR_In		0x00
#define GPIO_ModeR_Out		0x01
#define GPIO_ModeR_AF		0x02
#define GPIO_ModeR_An		0x03

#define GPIO_Type_PP		0x0
#define GPIO_Type_OD		0x1

#define GPIO_PUpDR_NO		0x00
#define GPIO_PUpDR_PU		0x01
#define GPIO_PUpDR_PD		0x10

#define GPIO_Pin_00			00
#define GPIO_Pin_01			01
#define GPIO_Pin_02			02
#define GPIO_Pin_03			03
#define GPIO_Pin_04			04
#define GPIO_Pin_05			05
#define GPIO_Pin_06			06
#define GPIO_Pin_07			07
#define GPIO_Pin_08			08
#define GPIO_Pin_09			09
#define GPIO_Pin_10			10
#define GPIO_Pin_11			11
#define GPIO_Pin_12			12
#define GPIO_Pin_13			13
#define GPIO_Pin_14			14
#define GPIO_Pin_15			15

#define TIM6_Base				0x40001000

#define TIMx_CR1				0x00
#define TIM_CR1_CEN				1 << 0
#define TIM_CR1_UpDis			1 << 1
#define TIM_CR1_UpReqSource		1 << 2
#define TIM_CR1_OnePulse		1 << 3
#define TIM_CR1_ARPE			1 << 7
#define TIM_CR1_UIF				1 << 11

#define TIMx_DIER				0x0C
#define	TIM_DIER_UIE			1 << 0
#define TIM_DIER_UDE			1 << 8

#define TIMx_SR					0x10
#define TIM_SR_UIF				1

#define TIMx_EGR				0x14
#define TIM_EGR_UG				1

#define TIMx_CNT				0x24
#define	TIM_CNT_UIFCPY			1 << 31

#define TIMx_PSC				0x28

#define TIMx_ARR				0x2C

enum {
	GPIOA = 0,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
	GPIOH,
	GPIOI,
	GPIOJ,
	GPIOK
};

static const uint32_t GPIO_Bases[] = {
		GPIO_Base + GPIOA * 0x400,
		GPIO_Base + GPIOB * 0x400,
		GPIO_Base + GPIOC * 0x400,
		GPIO_Base + GPIOD * 0x400,
		GPIO_Base + GPIOE * 0x400,
		GPIO_Base + GPIOF * 0x400,
		GPIO_Base + GPIOG * 0x400,
		GPIO_Base + GPIOH * 0x400,
		GPIO_Base + GPIOI * 0x400,
		GPIO_Base + GPIOJ * 0x400,
		GPIO_Base + GPIOK * 0x400,
};

typedef struct {
	uint32_t GPIO_Mode;
	uint32_t GPIO_Type;
	uint32_t GPIO_PUpD;
	uint32_t GPIO_Pin;
} GPIO_InitTypeDef;

void GPIO_Init(uint32_t, GPIO_InitTypeDef*);

#define __STATIC_INLINE static inline

#if defined ( __CC_ARM )
#define __ASM __asm
#else
#define __ASM asm
#endif

__STATIC_INLINE uint32_t __get_CONTROL(void) {
    #if defined ( __CC_ARM )
    register int __control_register __ASM("control");
    #else
    register int __control_register;
    __ASM volatile("MRS %0, CONTROL" : "=r" (__control_register));
    #endif
    return __control_register;
}

__STATIC_INLINE void __enable_irq(void) {
    __asm ("cpsie i" : : : "memory");
}

#endif /* HAL_H_ */
