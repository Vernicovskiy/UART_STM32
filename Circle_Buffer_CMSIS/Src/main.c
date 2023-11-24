#include "main.h"

RING_buffer_t ring_Rx;





 void USART1_IRQHandler (void){

	 if (USART1->SR & USART_SR_RXNE){

	 RING_Put( USART1->DR, &ring_Rx);

	 }
 }




int main(void)
{
	const uint16_t size = 255;
	uint8_t Circle_Buffer[size];
	RING_Init(&ring_Rx, Circle_Buffer, size) ;


  // Настраиваем порт A для работы с USART2
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Включаем тактирование порта A
  GPIOA->MODER |= GPIO_MODER_MODER5_0; /* set pin to output mode */
  GPIOA->MODER |= GPIO_MODER_MODER9_1; // Устанавливаем режим альтернативной функции для пина PA9 (TX)
  GPIOA->MODER |= GPIO_MODER_MODER10_1;
  GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL9_2 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_0); // Выбираем альтернативную функцию 7 (USART1) для пина PA9
  GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL10_2 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_0); // Выбираем альтернативную функцию 7 (USART1) для пина PA9
  // Настраиваем USART1 для передачи данных
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Включаем тактирование USART1
  USART1->BRR = 0x683; // Устанавливаем скорость передачи 9600 бод при частоте 16 МГц
  USART1->CR1 |= USART_CR1_TE; // Включаем передатчик
  USART1->CR1 |= USART_CR1_RE;
  USART1->CR1 |= USART_CR1_RXNEIE;
  NVIC_EnableIRQ(USART1_IRQn);
  USART1->CR1 |= USART_CR1_UE; // Включаем USART1




  while (1){
	  if (ring_Rx.tail != ring_Rx.head){
	  USART1->DR = RING_Pop(&ring_Rx);
	  }



}
}






