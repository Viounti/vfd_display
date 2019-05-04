//定义亮度
#define liang1 800  //800
#define liang2 680  //680
#define liang3 600  //600
#define liang4 480  //480
#define liang5 400  //400
#define liang6 280  //280
#define liang7 200  //200

//定义引脚
const int PT6311_EN =2;
const int PT6311_DATA =3;
const int PT6311_CLK =4;
const int PT6311_STB =5;

//定义数值
bool DATA_VAL;
int lightValue = 0;

//定义16进制
unsigned char zhuanpan = 0x00;
unsigned char liang = 0x0f;

char zp[]={0xff,0xdf,0xcf,0xc7,0xc3,0xc1,0xc0,0x40};//转盘组合显示
char zp1[]={0x20,0x10,0x08,0x04,0x02,0x01,0x40,0x80};//转盘定位显示

char net[]={0x20,0x10,0x08,0x04,0x02,0x01,0x40,0x80};//6红点 7文字

char ub[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};//USB定位显示
char us[]={0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff};//USB组合显示

char zx[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//前四位红点 0x10DVD 0x20REC右  0x40HDD 0x80REC左

const unsigned char table2[]={0x0f,0x65,0x2d};      
const unsigned char zhuanp[]={0x11,0x22,0x44,0x88}; //转盘数值
const unsigned char table0[]={0x77,0x12,0x6b,0x5b,0x1e,0x5d,0x7d,0x13,0x7f,0x5f,0x88};//数字不带冒号
const unsigned char table1[]={0xf7,0x92,0xeb,0xdb,0x9e,0xdd,0xfd,0x93,0xff,0xdf,0x08};//数字带冒号

//定义显示数字/米字对应的16进制
const unsigned char MM[][2]={         
        {0x31,  0x46},//0  
        {0x10,  0x02},//1
        {0xd1,  0x45},//2 
        {0xd1,  0x43},//3
        {0xf0,  0x03},//4
        {0xe1,  0x43},//5
        {0xe1,  0x47},//6
        {0x11,  0x02},//7
        {0xf1,  0x47},//8
        {0xf1,  0x43},//9
        {0x00,  0x00},//    10
        {0xc0,  0x01},// -  11 
        {0x88,  0x08},// /  12 
        {0xf1,  0x07},//A   13
        {0xd5,  0x52},//B   14
        {0x21,  0x44},//C   15
        {0x95,  0x52},//D   16
        {0xe1,  0x45},//E   17
        {0xe1,  0x05},//F   18
        {0x61,  0x46},//G   19
        {0xf0,  0x07},//H   20
        {0x85,  0x50},//I   21
        {0x10,  0x46},//J   22
        {0xa8,  0x25},//K   23
        {0x20,  0x44},//L   24
        {0xba,  0x06},//M   25
        {0xb2,  0x26},//N   26
        {0x31,  0x46},//O   27
        {0xf1,  0x05},//P   28
        {0x31,  0x66},//Q   29
        {0xf1,  0x25},//R   30
        {0xe1,  0x43},//S   31
        {0x85,  0x10},//T   32
        {0x30,  0x46},//U   33
        {0xa8,  0x0c},//V   34
        {0xb0,  0x2e},//W   35
        {0x8a,  0x28},//X   36
        {0x8a,  0x10},//Y   37
        {0x89,  0x48},//Z   38 
        {0xc4,  0x11},//+  39
 };

//数字缓存　米字缓存
unsigned char MZ[5]={10,10,10,10,10};  
unsigned char SZ[6]={0,0,0,0,0,0};  

//图标16进制
//四个图标
unsigned char AUTO[] ={0x00,0xff};
unsigned char EPG[] ={0x00,0xff};
unsigned char TRANS[] ={0x00,0xff};
unsigned char MAIL[] ={0x00,0xff};
unsigned char RATE[] ={0x00,0xff};
//USB
unsigned char USB1=0x00;
unsigned char USB2=0x00;
unsigned char USB3=0x00;
unsigned char USB4=0x00;
//方块
unsigned char AUTO1=0x00;
unsigned char EPG1=0x00;
unsigned char TRANS1=0x00;
unsigned char MAIL1=0x00;
unsigned char RATE1=0x00;
unsigned char TITLE1=0x00;
unsigned char CHP1=0x00;
unsigned char TRK1=0x00;
//network
unsigned char networkh=0x00;
unsigned char networkl=0x00;

//米字显示
void mz_display(int a,int b){
  for(int i = 0;i<5;i++){
    if(a==i){
      MZ[i]=table0[b];
  }
 }
}

//数字显示
void sz_dispaly(int a,int b){
  for(int i = 0;i<6;i++){
    if(a==i){
      SZ[i]=table0[b];
  }
 }
}
 
//清空数字
void clearsz(){
  for(int i=0;i<6;i++){
    SZ[i]=0x00;
  }
}

//清空米字
void clearmz(){
  for(int i=0;i<5;i++){
    MZ[i]=0x00;
  }
}

void vfd_display(){
  PT6311_3();       
       
  write_PT6311(MM[MZ[4]][0]);   
  write_PT6311(MM[MZ[4]][1]);   

  write_PT6311(0x00);   
  
  write_PT6311(MM[MZ[3]][0]);   
  write_PT6311(MM[MZ[3]][1]);   
  
  write_PT6311(TRK1);   //TRK
  
  write_PT6311(MM[MZ[2]][0]);
  write_PT6311(MM[MZ[2]][1]);

  write_PT6311(CHP1);   //CHP
  
  write_PT6311(MM[MZ[1]][0]);
  write_PT6311(MM[MZ[1]][1]);
  
  write_PT6311(RATE1);   //RATE
  
  write_PT6311(MM[MZ[0]][0]);
  write_PT6311(MM[MZ[0]][1]);
  
  write_PT6311(TITLE1);   //TITLE
  
  write_PT6311(SZ[0]);
  write_PT6311(SZ[5]);
  
  write_PT6311(TRANS1);   //TRANS
  
  write_PT6311(SZ[3]);
  write_PT6311(SZ[4]);
  
  write_PT6311(AUTO1);   //AUTO
  
  write_PT6311(SZ[1]);
  write_PT6311(SZ[2]);
  
  write_PT6311(EPG1);   //EPG
  
  write_PT6311(zhuanpan);   //转盘
  write_PT6311(zx);   //HDD REC DVD REC ....
  write_PT6311(USB1); 
  write_PT6311(USB3);   //USB 
  write_PT6311(USB2);   //USB 
  write_PT6311(USB4);   //USB
  write_PT6311(networkh);   //network上
  write_PT6311(networkl);   //network下
  write_PT6311(MAIL1);   //MAIL
  write_PT6311(0x00);       
  PT6311_4();
}

//芯片部分
void write_PT6311(unsigned char dat)
{
   unsigned char i;
   for(i=0;i<8;i++)     
   {
    DATA_VAL=dat&0x01;
    //DATA=CY;
    digitalWrite(PT6311_DATA, DATA_VAL);
    digitalWrite(PT6311_CLK, HIGH);//CLK=1;    
    digitalWrite(PT6311_CLK, LOW);//CLK=0;
    dat=dat>>1;
   } 
} 
void PT6311_1()   
 {
   digitalWrite(PT6311_STB, LOW);//PT6311_STB_LOW;
   digitalWrite(PT6311_STB, HIGH);//PT6311_STB_HIGH;
   write_PT6311(0x0a);
 }
void PT6311_2()   
 {               
   digitalWrite(PT6311_STB, LOW); //PT6311_STB_LOW;
   digitalWrite(PT6311_STB, HIGH);//PT6311_STB_HIGH;
   write_PT6311(0x40);     
 }
void PT6311_3()    
{
  digitalWrite(PT6311_STB, LOW); //PT6311_STB_LOW;
  digitalWrite(PT6311_STB, HIGH);//PT6311_STB_HIGH;
  write_PT6311(0xc0);
}


void PT6311_4()    
 {               
   digitalWrite(PT6311_STB, LOW); //PT6311_STB_LOW;
   digitalWrite(PT6311_STB, HIGH);//PT6311_STB_HIGH;
   write_PT6311(liang); //= 4 11/16  = 5 12/16   = 6 13/16  = 7 14/16       
 }  

//初始化部分
void setup(){
  //设置引脚模式
  pinMode(PT6311_EN, OUTPUT);
  pinMode(PT6311_DATA, OUTPUT);
  pinMode(PT6311_CLK, OUTPUT);
  pinMode(PT6311_STB, OUTPUT);
  
  digitalWrite(PT6311_EN, HIGH);//开启屏幕
  
  PT6311_1(); 
  PT6311_2(); 
  PT6311_3();
        
  for(int i=0;i<20;i++){
    write_PT6311(0x00); 
    write_PT6311(0x00);
 } 
  liang=0x8f; //设置亮度为0x8f
}


void loop(){  
  /*例程1-使用函数显示数字
  sz_display(0,0);//第一位为选位 第二位为显示数字 目前用语言描述为 在第0位（1个数字）显示0
  vfd_display();  //VFD更新显示，设定完数据之后使用此函数会更新显示
  */

  /*例程2-高级使用函数显示数字
  for(int i = 0;i<6;i++){
    for(int a = 0;a<10;a++){
      sz_display(i,a);
      vfd_display();
    }
  }
*/

  /*例程3-使用米字函数显示数字
  mz_display(0,1);//第一位为选为 第二位为显示字符 这里显示数字0-9 输入0-9即可
  vfd_display();
  */
  
  /*例程4-使用米字函显示字符
  mz_display(0,13);//13对应的是A 详情见最上面的表
  vfd_display();
  */

  /*例程5-使用16进制显示其他的图标
  zhuanpan = zp[1];//各种变量可以在vfd_display找到 这里是让转盘显示第一瓣 对应的16进制最上面的变量也定义了 直接使用即可
  vfd_display();
  */
} 
