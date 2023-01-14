#include <ti/sysbios/knl/Clock.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/GPIO.h>
#include "Board.h"
#include <ti/posix/ccs/unistd.h>
#include <stddef.h>
#include <ti/sysbios/knl/Task.h>



/*ADS1147 Commands */
#define CMD_WAKEUP      0x01 //exit sleep mode
#define CMD_SLEEP       0x02 //enter sleep mode
#define CMD_SYNC        0x04 //synchronize the A/D conversion
#define CMD_RESET       0x06 //reset to power-up values
#define CMD_NoP         0xFF //no operation
#define CMD_RDATA       0x12 //read data once
#define CMD_RDATAC      0x14 //read data continuously
#define CMD_SDATAC      0x16 //stop reading data continuously
#define CMD_RREG        0x20 //read from register
#define CMD_WREG        0x40 //write to register
#define CMD_SYSOCAL     0x60 //system offset calibration
#define CMD_SYSGCAL     0x61 //system gain calibration
#define CMD_SELFOCAL    0x62 //self offset calibration

//Registers
#define REG_MUX0        0x00
#define REG_VBIAS       0x01
#define REG_MUX1        0x02
#define REG_SYS0        0x03
#define REG_OFC0        0x04
#define REG_OFC1        0x05
#define REG_OFC2        0x06
#define REG_FSC0        0x07
#define REG_FSC1        0x08
#define REG_FSC2        0x09
#define REG_IDAC0       0x0A
#define REG_IDAC1       0x0B
#define REG_GPIOCFG     0x0C
#define REG_GPIODIR     0x0D
#define REG_GPIODAT     0x0E



//Start pin
#define Start_Pin   CC2640R2_LAUNCHXL_DIO12
#define CS   CC2640R2_LAUNCHXL_SPI0_CSN
#define DRDY  CC2640R2_LAUNCHXL_SPI0_MISO
#define SCLK CC2640R2_LAUNCHXL_SPI0_CLK

static PIN_Handle ledPinHandle;


/*
 *  ======== mainThread ========
 */
/* 100 second delay */

void RESET_command()
{


    /* Call driver init functions */
    SPI_init();

    SPI_Handle handle;
    SPI_Params params;
    SPI_Transaction transaction;
    uint8_t txBuf[] = {CMD_RESET}; // Transmit buffer


    // Init SPI and specify non-default parameters
    SPI_Params_init(&params);
    params.bitRate     = 2700000;
    params.frameFormat = SPI_POL1_PHA1;
    params.mode        = SPI_MASTER;

    // Configure the transaction
    transaction.count = sizeof(txBuf);
    transaction.txBuf = txBuf;
    transaction.rxBuf = NULL;

    // Open the SPI and perform the transfer
    handle = SPI_open(CC2640R2_LAUNCHXL_SPI0, &params);



    SPI_transfer(handle, &transaction);


    SPI_close(handle);
}

void  SDATAC_command()
{

    /* Call driver init functions */
    SPI_init();

    SPI_Handle handle;
    SPI_Params params;
    SPI_Transaction transaction;
    uint8_t txBuf[] = {CMD_SDATAC}; // Transmit buffer


    // Init SPI and specify non-default parameters
    SPI_Params_init(&params);
    params.bitRate     = 2700000;
    params.frameFormat = SPI_POL1_PHA1;
    params.mode        = SPI_MASTER;

    // Configure the transaction
    transaction.count = sizeof(txBuf);
    transaction.txBuf = txBuf;
    transaction.rxBuf = NULL;

    // Open the SPI and perform the transfer
    handle = SPI_open(CC2640R2_LAUNCHXL_SPI0, &params);



    SPI_transfer(handle, &transaction);

    SPI_close(handle);

}

void WREG_RREG_SYNC_command()
{

    /* Call driver init functions */
    SPI_init();

    SPI_Handle handle;
    SPI_Params params;
    SPI_Transaction transaction;
    uint8_t txBuf[] = {CMD_WREG,REG_SYS0,REG_VBIAS,REG_MUX0,REG_SYS0,0x42,CMD_RREG,REG_SYS0,0x04}; // Transmit buffer


    // Init SPI and specify non-default parameters
    SPI_Params_init(&params);
    params.bitRate     = 2700000;
    params.frameFormat = SPI_POL1_PHA1;
    params.mode        = SPI_MASTER;

    // Configure the transaction
    transaction.count = sizeof(txBuf);
    transaction.txBuf = txBuf;
    transaction.rxBuf = NULL;

    // Open the SPI and perform the transfer
    handle = SPI_open(CC2640R2_LAUNCHXL_SPI0, &params);




        SPI_transfer(handle, &transaction);

        SPI_close(handle);

}

void RDATA_command()
{

    /* Call driver init functions */
    SPI_init();

    SPI_Handle handle;
    SPI_Params params;
    SPI_Transaction transaction;
    uint8_t txBuf[] = {CMD_RDATA}; // Transmit buffer


    // Init SPI and specify non-default parameters
    SPI_Params_init(&params);
    params.bitRate     = 2700000;
    params.frameFormat = SPI_POL1_PHA1;
    params.mode        = SPI_MASTER;

    // Configure the transaction
    transaction.count = sizeof(txBuf);
    transaction.txBuf = txBuf;
    transaction.rxBuf = NULL;

    // Open the SPI and perform the transfer
    handle = SPI_open(CC2640R2_LAUNCHXL_SPI0, &params);




        SPI_transfer(handle, &transaction);
        SPI_close(handle);

}

void  SCLK_16_command()
{

    /* Call driver init functions */
    SPI_init();

    SPI_Handle handle;
    SPI_Params params;
    SPI_Transaction transaction;
    uint32_t txBuf[] = {0b10101010101010101010101010101010}; // Transmit buffer


    // Init SPI and specify non-default parameters
    SPI_Params_init(&params);
    params.bitRate     = 2700000;
    params.frameFormat = SPI_POL1_PHA1;
    params.mode        = SPI_MASTER;

    // Configure the transaction
    transaction.count = sizeof(txBuf);
    transaction.txBuf = txBuf;
    transaction.rxBuf = NULL;

    // Open the SPI and perform the transfer
    handle = SPI_open(CC2640R2_LAUNCHXL_SPI0, &params);



    SPI_transfer(handle, &transaction);

    SPI_close(handle);

}


void SLEEP_Command()
{

    /* Call driver init functions */
    SPI_init();

    SPI_Handle handle;
    SPI_Params params;
    SPI_Transaction transaction;
    uint8_t txBuf[] = {CMD_SLEEP}; // Transmit buffer


    // Init SPI and specify non-default parameters
    SPI_Params_init(&params);
    params.bitRate     = 2700000;
    params.frameFormat = SPI_POL1_PHA1;
    params.mode        = SPI_MASTER;

    // Configure the transaction
    transaction.count = sizeof(txBuf);
    transaction.txBuf = txBuf;
    transaction.rxBuf = NULL;

    // Open the SPI and perform the transfer
    handle = SPI_open(CC2640R2_LAUNCHXL_SPI0, &params);



        SPI_transfer(handle, &transaction);

        SPI_close(handle);


}

void *mainThread(void *arg0)
{

    usleep(1600);

    PIN_setOutputValue(ledPinHandle, Start_Pin, 1);
    PIN_setOutputValue(ledPinHandle, CS, 0);
    Task_sleep (0.01 * (1000 / Clock_tickPeriod));  //10ns delay


    RESET_command();
    usleep(600);
    SDATAC_command();
    WREG_RREG_SYNC_command();
    usleep(1.7); //sclk
    PIN_setOutputValue(ledPinHandle, CS, 1);//serial interface reset

    while(DRDY==0){

        PIN_setOutputValue(ledPinHandle, CS, 0);
        Task_sleep (0.01 * (1000 / Clock_tickPeriod));
        RDATA_command();
        SCLK_16_command();
        usleep(1.7);
        PIN_setOutputValue(ledPinHandle, CS, 1);

    }

    PIN_setOutputValue(ledPinHandle, CS, 0);
    Task_sleep (0.01 * (1000 / Clock_tickPeriod));
    SLEEP_Command();


   return(0);
    }
