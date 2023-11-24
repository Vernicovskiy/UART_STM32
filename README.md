![Static Badge](https://img.shields.io/badge/Unic_Lab-green)
![Static Badge](https://img.shields.io/badge/STM32-red)
![GitHub last commit (by committer)](https://img.shields.io/github/last-commit/Vernicovskiy/STM32_TIM)
![GitHub Repo stars](https://img.shields.io/github/stars/Vernicovskiy/STM32_TIM)
![GitHub watchers](https://img.shields.io/github/watchers/Vernicovskiy/STM32_TIM)
![GitHub top language](https://img.shields.io/github/languages/top/Vernicovskiy/STM32_TIM)

## Кольцевой буфер

Кольцевой буфер - это специальный вид буфера, который используется для хранения и передачи данных между разными устройствами или процессами.

Кольцевой буфер имеет фиксированный размер и работает по принципу кольца, то есть когда он заполняется, он начинает перезаписывать старые данные новыми, как будто он замыкается на себя.

Кольцевой буфер тесно связан с структурой данных очередь, которая представляет собой набор элементов, упорядоченных по принципу FIFO (First In, First Out), то есть первым пришел - первым вышел. Очередь имеет два конца: начало и конец. В начало очереди можно добавлять новые элементы, а из конца очереди можно извлекать элементы. 

Кольцевой буфер можно рассматривать как реализацию очереди с ограниченным размером, где начало и конец очереди соединены в кольцо.

Кольцевой буфер обычно состоит из массива элементов и двух указателей: head и tail. Указатель head указывает на позицию, в которую можно записать новый элемент, а указатель tail указывает на позицию, из которой можно прочитать элемент. Когда буфер пуст, head и tail равны. Когда буфер заполнен, head и tail указывают на одну и ту же позицию, но с разным смыслом: head указывает на позицию, в которую можно записать новый элемент, а tail указывает на позицию, из которой можно прочитать старый элемент.

Для работы с кольцевым буфером обычно используются четыре операции: инициализация, запись, чтение и проверка. 

* Инициализация - это процесс создания буфера с заданным размером и установки указателей head и tail в начальное положение. 

```c
typedef struct
{
    uint8_t *buffer;
    uint16_t tail;
    uint16_t head;
    uint16_t size;

} RING_buffer_t;

void RING_Init(RING_buffer_t *ring, uint8_t *buf, uint16_t size)
	{
		ring->size = size;
		ring->buffer = buf;
		RING_Clear(ring);

	}

    	void RING_Clear(RING_buffer_t* buf)
	{
		buf->tail = 0;
		buf->head = 0;
	}
```


* Запись - это процесс добавления нового элемента в буфер по позиции head и сдвига указателя head на одну позицию вперед. Если буфер заполнен, то запись перезаписывает старый элемент новым и сдвигает указатель tail на одну позицию вперед. 
  
```c
void RING_Put(uint8_t symbol, RING_buffer_t* buf)
	{

		buf->buffer[buf->head++] = symbol;
		buf->count++; // Проверяем, не достигли ли конца буфера
		if (buf->head >= buf->size) buf->head = 0;

	}
```


* Чтение - это процесс извлечения элемента из буфера по позиции tail и сдвига указателя tail на одну позицию вперед. Если буфер пуст, то чтение возвращает нулевой элемент или сообщение об ошибке. Проверка - это процесс определения, пустой или заполненный буфер, или сколько в нем свободных или занятых элементов.
  
 ```c
uint8_t RING_Pop(RING_buffer_t *buf)
	{
		uint8_t retval = buf->buffer[buf->tail++];
		if (buf->tail >= buf->size) buf->tail = 0;
		return retval;
	}
```

https://en.wikipedia.org/wiki/Circular_buffer#/media/File:Circular_Buffer_Animation.gif






