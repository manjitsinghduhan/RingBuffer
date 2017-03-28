
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ringBuf.h"


/******************************************************************************
* Function Name:  ringBufInit
**************************************************************************//**
*   @brief      init the ring buffer
*   @param[in] 	buf: the ring buffer
*   @param[in]	size: the size of buffer. It should be power of 2
*   @param[out] true if initialize properly otherwise false
*   @retval     true if initialize properly otherwise false
*   @warning    None
*   @remark     size should be power of 2
*//***************************************************************************/
bool ringBufInit(RingBuffer *buf, uint16_t size)
{
	buf->data = (char *)calloc(size, sizeof(buf->data));

	/*check that the memory is allocated or not*/
	if(buf->data != NULL)
	{
		buf->bufMask = size - 1;
		buf->put_ptr = 0;
		buf->get_ptr = 0;
		buf->overflow = false;
		return true;
	}
	return false;
}

/******************************************************************************
* Function Name:  ringBufPut
**************************************************************************//**
*   @brief      write to ring buffer
*   @param[in] 	buf: the ring buffer
*   @param[in]	data: the data that should be written
*   @param[out] None
*   @retval     None
*   @warning    None
*   @remark     None
*//***************************************************************************/
void ringBufPut(RingBuffer *buf, uint8_t *data)
{
	/* Is buffer full? */
	if( isBufferFull(buf) )
	{
		/* Is going to overwrite the oldest byte */
		/* Increase tail index  */
		buf->overflow = true;
		buf->get_ptr = (buf->get_ptr + 1) & buf->bufMask;
	}
	/*write the data to buffer*/
	buf->data[buf->put_ptr] = data;

	/*increment the head index */
	buf->put_ptr = (buf->put_ptr + 1) & buf->bufMask;
}

/******************************************************************************
* Function Name:  ringBufGet
**************************************************************************//**
*   @brief      read from ring buffer
*   @param[in] 	buf: the ring buffer
*   @param[in]	data: the data that is read
*   @param[out] true if read successful otherwise false
*   @retval     None
*   @warning    None
*   @remark     None
*//***************************************************************************/
bool ringBufGet(RingBuffer *buf , char *data)
{
	/*if buffer is empty return false*/
	if(isBufferEmpty(buf))
	{
		return false;
	}

	/*read the data*/
	*data = buf->data[buf->get_ptr];

	/*increment the tail index */
	buf->get_ptr = (buf->get_ptr + 1) & buf->bufMask;

	return true;
}

/******************************************************************************
* Function Name:  flushBuffer
**************************************************************************//**
*   @brief      flush whole buffer i.e. reset all the parameters
*   @param[in] 	buf: the ring buffer
*   @param[out] None
*   @retval     None
*   @warning    All data will be vanished
*   @remark     None
*//***************************************************************************/
void flushBuffer(RingBuffer *buf)
{
	buf->put_ptr = 0;
	buf->get_ptr = 0;
	buf->overflow = false;
}
