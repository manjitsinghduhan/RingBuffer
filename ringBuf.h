
#ifndef RINGBUF_H_
#define RINGBUF_H_


#include <stdint.h>

/**
 * Structure holds a ring buffer.
 * The buffer contains a buffer array
 * the size mask of the buffer
 * index to head and tail of the ring buffer
 * overflow flag
 */

typedef struct ringbuffer
{
	uint8_t *data;   		/*data pinter*/
	uint16_t bufMask;		/*size mask*/
	uint16_t put_ptr;		/*buffer head index*/
	uint16_t get_ptr;		/*buffer tail index*/
	bool overflow;			/*status of buff overflow*/
}RingBuffer;

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
bool ringBufInit(RingBuffer *buf, uint16_t size);

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
void ringBufPut(RingBuffer *buf, uint8_t *data);

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
bool ringBufGet(RingBuffer *buf, char *data);

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
void flushBuffer(RingBuffer *buf);

/******************************************************************************
* Function Name:  isBufferEmpty
**************************************************************************//**
*   @brief      check if the buffer is empty or not
*   @param[in] 	buf: the ring buffer
*   @param[out] true if buffer is empty otherwise false
*   @retval     None
*   @warning    None
*   @remark     None
*//***************************************************************************/
inline bool isBufferEmpty(RingBuffer *buf)
{
	return (buf->put_ptr == buf->get_ptr);
}

/******************************************************************************
* Function Name:  isBufferFull
**************************************************************************//**
*   @brief      check if the buffer is full or not
*   @param[in] 	buf: the ring buffer
*   @param[out] true if buffer is full otherwise false
*   @retval     None
*   @warning    None
*   @remark     None
*//***************************************************************************/

inline bool isBufferFull(RingBuffer *buf)
{
	return ( ( (buf->put_ptr - buf->get_ptr) & buf->bufMask) == buf->bufMask);
}


/******************************************************************************
* Function Name:  isBufferoverflow
**************************************************************************//**
*   @brief      check if the buffer is overflow or not
*   @param[in] 	buf: the ring buffer
*   @param[out] true if buffer is overflow otherwise false
*   @retval     None
*   @warning    None
*   @remark     None
*//***************************************************************************/
inline bool isBufferOverflow(RingBuffer *buf)
{
	return  buf->overflow;
}


/******************************************************************************
* Function Name:  resetBufferOverflow
**************************************************************************//**
*   @brief      rese tBuffer Overflow flag
*   @param[in] 	buf: the ring buffer
*   @param[out] None
*   @retval     None
*   @warning    None
*   @remark     None
*//***************************************************************************/
inline void resetBufferOverflow(RingBuffer *buf)
{
	buf->overflow = false;
}


#endif /* RINGBUF_H_ */
