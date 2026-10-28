/*!
 * @defgroup SPI
 * @brief Synchronous serial communication
 <table>
<caption id="TLV5616pins2">SPI-DAC pins </caption>
<tr><th>Pin <th>Function  <th>Description
<tr><td>PB18 <td>SPI0 SCLK <td>DAC SPI clock (SPI)   
<tr><td>PA8  <td>SPI0 CS   <td>DAC SPI CS     
<tr><td>PB17 <td>SPI0 PICO <td>DAC SPI data (SPI)    
</table>
 * @{*/
/**
 * @file      TLV5616.h
 * @brief     Synchronous serial communication
 * @details   SPI uses a chip select, clock, and data out. 
  * This interface can be used for the TLV5616 DAC
 * \image html SPIinterface.png  width=500px
 * @version   ECE445L
 * @author    Daniel Valvano and Jonathan Valvano
 * @copyright Copyright 2026 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      June 28, 2026
 <table>
<caption id="TLV5616pins2">SPI-DAC pins </caption>
<tr><th>Pin <th>Function  <th>Description
<tr><td>PB18 <td>SPI0 SCLK <td>DAC SPI clock (SPI)   
<tr><td>PA8  <td>SPI0 CS   <td>DAC SPI CS     
<tr><td>PB17 <td>SPI0 PICO <td>DAC SPI data (SPI)  
</table>
  ******************************************************************************/
#ifndef __TLV5616_H__
#define __TLV5616_H__

/**
 * Initialize TLV5616 using SPI0 for 8 MHz baud clock
 * 16-bit data
 * using busy-wait synchronization.
 * Calls Clock_Freq to get bus clock
 * - PA8 SPI0_CS0
 * - PB18 SPI0_SCK
 * - PB17 SPI0_PICO
 * @note SPI0,SPI1 in power domain PD1 SysClk equals bus CPU clock
 * @param data initial value to DAC
 * @return none 
 * @brief initialize TLV5616
 */
void TLV5616_Init(uint32_t data);

/**
 * Output 16-bit data to TLV5616 using SPI0.
 * @param data is an 16-bit data to be transferred
 * @return none 
 * @brief Output data
 */
void TLV5616_Out(uint32_t data);


/**
 * Output 16-bit data to SPI port, nonblocking.
 * @param code is an 16-bit data to be transferred
 * @return none 
 * @brief Output data, nonblocking
 * Send data to TLV5616 12-bit DAC without
 * waiting for a response.  This is useful
 * in audio applications where DAC outputs
 * are relatively infrequent and where the
 * DAC response is meaningless.  Since the
 * state of the FIFO is not checked before
 * sending, data may be lost.
*/
#define TLV5616_OutNonBlocking(code) SPI0->TXDATA = code|0x4000;
; 

#endif // __TLV5616_H__
/** @}*/