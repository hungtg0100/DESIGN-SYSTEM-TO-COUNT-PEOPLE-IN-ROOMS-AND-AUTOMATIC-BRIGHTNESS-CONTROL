#include <16F877A.h> // dinh kem thu vien dinh nghia cua PIC16F877A
#device ADC=10 // dat ADC o che do 10 bit 
#FUSES HS // su dung thach anh ngoai lam bo giao dông\
#use delay(clock=20000000) // su dung thach anh 20M
#define LCD_RS_PIN         PIN_B7   // Cac ket noi C.LCD voi vi dieu khien.
#define LCD_RW_PIN         PIN_B6
#define LCD_ENABLE_PIN     PIN_B5
#define LCD_DATA4          PIN_B4
#define LCD_DATA5          PIN_B3   
#define LCD_DATA6          PIN_B2
#define LCD_DATA7          PIN_B1
#include <lcd.c>

unsigned int16 so_dem; // khai bao bien gia tri so dem duoc 
int1 a=0;
int1 muc1=0; // muc xac dinh cua cam bien
int1 muc2=0; // muc xac dinh cua cam bien
int8 so_dem_nho;
int8 nho_cb1=0;
int8 nho_cb2=0;
int8 ty_le_cb1; // ty le cam bien dan 
int8 ty_le_cb2; // ty le cam bien dan
int8 ht_as; 
int16 ty_le_bt;
int16 ty_le_as;
unsigned int8 count=0;

