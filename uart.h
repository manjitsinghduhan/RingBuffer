
#ifndef UART_H_
#define UART_H_

/*the size of buffers should be power of 2*/
#define RX_BUFF_SIZE 	256


/*Assigning some random address to avoid the compile error
 * used UART_READ_ADDR as per requirement */
#define UART_READ_ADDR 0x30610000

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
void UART_init();


#endif /* UART_H_ */
