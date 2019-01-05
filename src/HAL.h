#ifndef __HAL_H__
#define __HAL_H__

#include <stdint.h>

#define __IO				volatile

#define PERIPH_BASE			((uint32_t)0x40000000)

#define AHB1PERIPH_BASE		(PERIPH_BASE + 0x00020000)

#define GPIOA_BASE			(AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE			(AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE			(AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASE			(AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASE			(AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASE			(AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASE			(AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASE			(AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASE			(AHB1PERIPH_BASE + 0x2000)
#define GPIOJ_BASE			(AHB1PERIPH_BASE + 0x2400)
#define GPIOK_BASE			(AHB1PERIPH_BASE + 0x2800)

typedef struct {
	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PUPDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t LCKR;
	__IO uint32_t AFR[2];
} GPIO_TypeDef;

#define GPIOA				((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB				((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC				((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD				((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE				((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF				((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG				((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH				((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI				((GPIO_TypeDef *) GPIOI_BASE)
#define GPIOJ				((GPIO_TypeDef *) GPIOJ_BASE)
#define GPIOK				((GPIO_TypeDef *) GPIOK_BASE)

#define GPIO_GET_INDEX(__GPIOx__)   (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                              ((__GPIOx__) == (GPIOB))? 1U :\
                                              ((__GPIOx__) == (GPIOC))? 2U :\
                                              ((__GPIOx__) == (GPIOD))? 3U :\
                                              ((__GPIOx__) == (GPIOE))? 4U :\
                                              ((__GPIOx__) == (GPIOF))? 5U :\
                                              ((__GPIOx__) == (GPIOG))? 6U :\
                                              ((__GPIOx__) == (GPIOH))? 7U :\
                                              ((__GPIOx__) == (GPIOI))? 8U :\
                                              ((__GPIOx__) == (GPIOJ))? 9U : 10U)

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

#define RCC_BASE			0x40023800
#define RCC_AHB1_EN_R		0x30
#define RCC_APB1_EN_R		0x40

#define TIM6_DAC_IRQn		0x4

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

typedef struct {
	uint32_t Pin;
	uint32_t Mode;
	uint32_t Type;
	uint32_t Pull;
	uint32_t Speed;
	uint32_t Alternate;
} GPIO_InitTypeDef;

void GPIO_Init(GPIO_TypeDef *, GPIO_InitTypeDef*);

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
