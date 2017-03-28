

#include "UART.h"
#include "ringBuf.h"
#include "assert.h"

RingBuffer *rxBuf;

void UART_init()
{
	/*driver init of that UART e.g. UART 0*/

	/*init the Rx interrupt*/

	/*ring buffer init*/
	assert(ringBufInit(rxBuf, RX_BUFF_SIZE));
}



void UART_RxISR(void)
{
	/*As we are going to read from a memory register so declaring it volatile*/
	 uint8_t *data;

	data = (volatile unsigned char *) UART_READ_ADDR;

	/*write the char value in the ring buffer*/
	ringBufPut(rxBuf, data);

	/*clear the interrupt mask and if required enable interrupt again*/
}

