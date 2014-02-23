#include<avr/io.h>

#define PORT_SET(PORT,BIT)   ((PORT) |=  (1<<(BIT)))
#define PORT_RESET(PORT,BIT) ((PORT) &= ~(1<<(BIT)))
#define TOGGLE_BIT(PORT,BIT) ((PORT) ^=  (1<<(BIT)))
#define DDR_SET(PORT,BIT)    ((PORT) |=  (1<<(BIT)))
#define DDR_RESET(PORT,BIT)  ((PORT) &= ~(1<<(BIT)))
#define DDR_BIT(PORT,BIT)    ((PORT) ^=  (1<<(BIT))) 

#define MOSI     3
#define MISO     4
#define SCK      5
#define SPI_DDR  DDRB
#define SPI_PORT PORTB
#define SPI_PIN  PINB

#define CSN      7
#define CSN_DDR  DDRB
#define CSN_PORT PORTB
#define CSN_OUT  DDR_SET(CSN_DDR,CSN)
#define CSN_IN   DDR_RESET(CSN_DDR,CSN)
#define CSN_H    PORT_SET(CSN_PORT,CSN)
#define CSN_L    PORT_RESET(CSN_PORT,CSN)

#define CE      6
#define CE_DDR  DDRB
#define CE_PORT PORTB 
#define CE_OUT  DDR_SET(CS_DDR,CE)
#define CE_IN   DDR_RESET(CS_DDR,CE)
#define CE_H    PORT_SET(CS_PORT,CE)
#define CE_L    PORT_RESET(CS_PORT,CE)

#define SPI_SEND  loop_until_bit_is_set(SPSR, SPIF)
#define SPI_DATA  SPDR

// initializing spi
void spiInit(void)
{
  // enabling spi
  SPCR |= (1<<SPE);
  // selecting master mode
  SPCR |= (1<<MSTR);
  // making pins output, the miso pin will be made input when spi is enabled
  SPI_DDR |= (1<<MOSI) | (1<<SCK);
}

// sending the data stored in the buffer.
void spiSendBuffer(uint8_t *buffer, uint8_t len)
{
  do
  {
    SPI_DATA = *buffer;
	SPI_SEND;
	buffer++;
  }while(len--);
}

// gets the data from the radio and stores in the buffer
void spiGetBuffer(uint8_t *buffer, uint8_t len)
{
  do
  {
    SPI_DATA = NOP;
	SPI_SEND;
	*buffer = SPI_DATA;
	buffer++;
  }while(len--);
}

// sends any command
uint8_t spiSendData(uint8_t data)
{
  uint8_t result;

  SPI_DATA = data;
  SPI_SEND;
  result = SPI_DATA;
  // returns the status
  return result;
}

