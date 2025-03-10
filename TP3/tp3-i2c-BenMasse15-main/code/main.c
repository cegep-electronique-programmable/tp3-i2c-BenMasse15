/**

  @Nom du fichier
    main.c

  @Auteur
    < À compléter>
   
  @Sommaire
    Programme qui écrit à l?écran I2C

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#define ADDRESSE_I2C_ECRAN  40			//0x28
#define ADDRESSE_I2C_EEPROM 80          //0x50 0b1010+000 parce que les pins A0,A1 et A2 sont à GND
/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    uint8_t message[20];
    uint8_t addr[2] = {0x00, 0x00};
    uint16_t rising_edge_button = 0;
    uint16_t falling_edge_button = 0;
    uint16_t button_Time;
    message[0]='0';
    message[1]='1';
    message[2]='2';
    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    while (1)
    {
        
        message[0]='H';
        message[1]='i';
        message[2]='!';
        while(I2C_Open(ADDRESSE_I2C_ECRAN) == I2C_BUSY);    //Passage de l'adresse
        I2C_SetBuffer(message, 3);                          //Passage des données
        I2C_MasterOperation(0);                             //Démarrer une opération d'écriture
        while (I2C_Close() == I2C_BUSY);                   	//Attendre que l'opération soit complète    

        __delay_ms(1000);
        
        
        // ÉCriture de deux octets de données à la EEPROM
        while (I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY); // passage de l?adresse I2C
        I2C_SetBuffer(addr, 2);  //Sets up the data buffer to use, and number of bytes to transfer donc on envoi 2 byte a l'adresse 0x00
        I2C_MasterOperation(0);           //opération d?écriture pour l?adresse interne
        while (I2C_Close() == I2C_BUSY);

        while (I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY); // ouvrir pour ecrire
        I2C_SetBuffer((void *)message, 3); //passage du tampon et du nombre de //lectures à faire
        I2C_MasterOperation(0);            //opération d?écriture pour l?adresse interne
        while (I2C_Close() == I2C_BUSY);   

        
        __delay_ms(5);

        //Lecture de 3 octets de la EEPROM
        while (I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY);
        I2C_SetBuffer(addr, 2);                            // Passage de l'adresse interne sur 2 octets
        I2C_MasterOperation(0);                            // Opération d'écriture pour l?adresse interne
        while (I2C_Close() == I2C_BUSY);
        
        while(I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY);	//passage de l?adresse I2C
        I2C_SetBuffer(message, 3);			//passage du tampon et du nombre de //lectures à faire
        I2C_MasterOperation(1);		//opération de lecture
        while (I2C_Close() == I2C_BUSY);
        __delay_ms(5);

    }
    
}
