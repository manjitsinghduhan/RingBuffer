

#include "UART.h"
#include "ringBuf.h"
#include "assert.h"

RingBuffer *rxBuf;
/******************************************************************************
* Function Name:  UART_init
**************************************************************************//**
*   @brief      init the uart with predefined BAURD rate, parity and STOP bit
*   @param[in] 	None
*   @param[out] None
*   @retval     None
*   @warning    None
*   @remark     None
*//***************************************************************************/
void UART_init()
{
	/*driver init of that UART e.g. UART 0*/

	/*init the Rx interrupt*/

	/*ring buffer init & asset to check that buffer is initialized properly*/
	assert(ringBufInit(rxBuf, RX_BUFF_SIZE));
}

/******************************************************************************
* Function Name:  UART_RxISR
**************************************************************************//**
*   @brief      UART Rx ISR routine which is configured such that the interrupt 
*		is generated when new data is present in the Register.
*   @param[in] 	None
*   @param[out] None
*   @retval     None
*   @warning    None
*   @remark     None
*//***************************************************************************/

void UART_RxISR(void)
{
	/*As we are going to read from a memory register so declaring it volatile*/
	 uint8_t *data;

	/*Read the data from memory mapped adddress*/
	data = (volatile unsigned char *) UART_READ_ADDR;

	/*write the char value in the ring buffer*/
	ringBufPut(rxBuf, data);

	/*clear the interrupt mask and if required enable interrupt again*/
}
