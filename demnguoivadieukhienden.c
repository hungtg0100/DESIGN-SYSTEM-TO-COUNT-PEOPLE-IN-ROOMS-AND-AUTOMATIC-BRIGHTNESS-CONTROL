#include <demnguoi.h>

void encoder_xu_ly()
{
   if (muc1==1)
   {
      if (nho_cb1==0)
      { 
         if(muc2==0)
         {
            so_dem++;
            if (so_dem>99)
            {
               so_dem=0;
            }
         }
      }
      nho_cb1=1;
   }
   if (muc1==0)
   {
      nho_cb1=0;
   }
   
   if (muc2==1)
   {
      if (nho_cb2==0)
      {
         if(muc1==0)
         {
            so_dem--;
            if (so_dem>99)
            {
               so_dem=99;
            }
         }
      }
      nho_cb2=1;
   }
   if (muc2==0)
   {
      nho_cb2=0;
   }
   write_eeprom(0, so_dem);
}

void ir_sensor()
{
      set_adc_channel(1);
      delay_us(25);
      ty_le_cb1=read_adc()*0.097; // doc ty lê % tín hieu tu mat thu hông ngoai (0-100); gia tri adc max=1023; 0,097=100/1023;   
      if(ty_le_cb1>30) // khi ty le dan cua mat thu lon hon nguong (70) thì do là muc 1, tuc khong co vat can            
      {                             
         muc1=1; // xac dinh muc 1;
      }                        
      if(ty_le_cb1<10) // khi ty le dan cua mat thu nho hon nguong (30) thì do là muc 0, tuc co vat can 
      {
         muc1=0; // xac dinh muc 0; 
      }
      
      set_adc_channel(2);
      delay_us(25);
      ty_le_cb2=read_adc()*0.097; // doc ty lê % tín hieu tu mat thu hông ngoai (0-100); gia tri adc max=1023; 0,097=100/1023;    
      if(ty_le_cb2>30) // khi ty le dan cua mat thu lon hon nguong (70) thì do là muc 1, tuc khong co vat can            
      {                             
         muc2=1; // xac dinh muc 1;

      }                        
      if(ty_le_cb2<10) // khi ty le dan cua mat thu nho hon nguong (30) thì do là muc 0, tuc co vat can 
      { 
         muc2=0; // xac dinh muc 0; 
      }
      if(so_dem_nho!=so_dem) // neu muc = 1 và co vat can // tuc vat can da di qua cam bien
      {                     
         so_dem_nho=so_dem;                                          
         write_eeprom(0, so_dem_nho); // ghi so dem vao EEPROM tai dia chi 0  
      }
}
void rheostat()
{
      set_adc_channel(0);
      delay_us(25);
      ty_le_bt=read_adc()*0.097; // doc ty lê % tín hieu tu mat thu hông ngoai (0-100); gia tri adc max=1023; 0,097=100/1023; 
      
}
void LightSensor()
{
      set_adc_channel(3);
      delay_us(25);
      ty_le_as=read_adc(); // doc ty lê % tín hieu tu mat thu hông ngoai   
      
}
void button()
{
      if(input(pin_d0)==0) // khi nút reset so dem duoc nhan
      {                    
         so_dem=0; // dat so dem ve 0;
         write_eeprom(0, so_dem); // ghi so dem vao EEPROM tai dia chi 0  
         while(input(pin_d0)==0); // tao vong lap chowf nut duoc nha 
      }                        
      if(input(pin_d1)==0) // khi nut giam duoc nhan 
      {                      
         so_dem--; // giam gia tri so dem
         if(so_dem>99) // neu so dem > 99
         {
            so_dem=99; // nap lai so dem = 99
         }
         write_eeprom(0, so_dem); // ghi so dem vao EEPROM tai dia chi 0 
         while(input(pin_d1)==0); // tao vong lap chowf nut duoc nha  
      } 
      if(input(pin_d3)==0)
      {                         
         so_dem++; // tang gia tri so dem
         if(so_dem>99) // neu so dem > 99                             
         {
            so_dem=0; // nap lai so dem = 0
         }
         write_eeprom(0, so_dem); // ghi so dem vao EEPROM tai dia chi 0  
         while(input(pin_d3)==0); // tao vong lap chowf nut duoc nha 
      }
      if(input(pin_d2)==0)
      {                          
        a=~a;
        lcd_gotoxy(1,2);
        printf(lcd_putc,"mode:%d",a);
        while(input(pin_d2)==0); // tao vong lap chowf nut duoc nha
      }
      if(a==0)
      {
         if(so_dem==0)
         {
            set_pwm1_duty(0);
         }
         else
         { 
            set_pwm1_duty(ty_le_as);
            ht_as=100-(ty_le_as*0.097);
            lcd_gotoxy(8,2);
            printf(lcd_putc,"Bri:%2lu",ht_as);
         }
         
      }
      else 
      {
         if(so_dem==0)
         {
            set_pwm1_duty(0);

         }
         else
         {
            set_pwm1_duty(ty_le_bt*10);
            lcd_gotoxy(8,2);
            printf(lcd_putc,"Bri:%2lu",ht_as);
         }
      }
}
void main() // chuong trinh chinh  
{  
   setup_timer_2(T2_DIV_BY_16,255,1);    
   setup_ccp1(CCP_PWM);
   so_dem=read_eeprom(0); // doc so dem cu duoc luu trong eeprom tai dia chi 0           
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4); // thiêt lap kenh ADC AN0 lam ngo vao ADC dung de doc tin hieu tu mat thu hong ngoai
   setup_adc(ADC_CLOCK_INTERNAL); // thiet lap xung cap cho ADC là xung noi                                                                  
   lcd_init();//khoi tao lcd
   lcd_putc('\f');//xoa trang man hinh lcd
   while(TRUE) // vong lap vo han 
   {  
      lcd_gotoxy(1,1);
      printf(lcd_putc,"SO NGUOI:%02lu ",so_dem);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"mode:%d",a);
      while(count==100)
      {
         LightSensor();
         count=0;
      }
      ir_sensor();
      button();
      encoder_xu_ly();
      rheostat();
      count++;
   }         
}

