// --- Mapeamento de Hardware ---
#define  led1    10             //LED1 ligado no pino digital 10
#define  led2    11             //LED2 ligado no pino digital 11
#define  led3    12             //LED3 ligado no pino digital 12
#define  botao1   5             //Botão 1 ligado no pino digital 5
#define  botao2   6             //Botão 2 ligado no pino digital 6
#define  botao3   7             //Botão 3 ligado no pino digital 7
#define  piezo    8             //Transdutor ligado no pino digital 8


// --- Constantes Auxiliares ---
#define  nota_C4  262           //Frequência nota Dó  262Hz
#define  nota_E4  330           //Frequência nota Mí  330Hz
#define  nota_G4  392           //Frequência nota Sol 392Hz


// --- Protótipo das Funções Auxiliares ---
void output1();
void output2();
void output3();
void memoryClear();
void start();
void gameOver();
void complete();
void check(byte number);          //função para verificar se o botão pressionado é o correto


// --- Variávei Globais ---
byte memory[20];                  //vetor que determina as posições de memória
byte count = 0x00;                //variável para contagem dos botões pressionados
int level = 0x01;                 //variável para indicar os níveis 
boolean wait = 0x00;         //variável para aguardar o pressionar de um botão


// --- Configurações Iniciais ---
void setup()
{  
    
    pinMode(led1, OUTPUT);            //LED1 é saída digital
    pinMode(led2, OUTPUT);            //LED2 é saída digital
    pinMode(led3, OUTPUT);            //LED3 é saída digital
    pinMode(botao1, INPUT_PULLUP);    //Botão 1 é entrada com resistor de pull-up interno
    pinMode(botao2, INPUT_PULLUP);    //Botão 2 é entrada com resistor de pull-up interno
    pinMode(botao3, INPUT_PULLUP);    //Botão 3 é entrada com resistor de pull-up interno
    pinMode(piezo, OUTPUT);           //Transdutor é saída digital
    
    digitalWrite(led1, LOW);          //Desliga LED1 
    digitalWrite(led2, LOW);          //Desliga LED2
    digitalWrite(led3, LOW);          //Desliga LED3
    noTone(piezo);                    //Desliga piezo
    
        
    memoryClear();                    //limpa memória
    
    
} //end setup


// --- Loop Infinito ---
void loop()
{
     start();                  //chama função de inicialização

  for(int i = 0; i < level; i++)
  {
    byte rand = random(1, 4); // gera valores randômicos entre 1 e 3
    memory[i] = rand;        // vetor de memória recebe um número aleatório
            
            
    switch(rand)                     //Switch para demonstrar qual botão deve ser pressionado
    {
       case 0x01: output1(); break;  //caso num igual a 1, pisca led1
       case 0x02: output2(); break;  //caso num igual a 2, pisca led2
       case 0x03: output3(); break;  //caso num igual a 3, pisca led3
       
    } //end switch
    
    
    wait = 0x01;                     //seta variável wait  
    
  } //end for
  
 
  while(wait)                        //aguarda até que um botão seja pressionado
  {
  
        if(!digitalRead(botao1))     //botão 1 pressionado?
        {                            //sim...
        
            output1();               //aciona LED1
            
            check(0x01);             //verifica se foi pressionado corretamente
                    
        } //end if B1
        
        if(!digitalRead(botao2))     //botão 2 pressionado?
        {                            //sim...
        
            output2();               //aciona LED2
            
            check(0x02);             //verifica se foi pressionado corretamente
                          
        } //end if B2
        
        if(!digitalRead(botao3))     //botão 3 pressionado?
        {                            //sim...
        
            output3();               //aciona LED3
            
            check(0x03);             //verifica se foi pressionado corretamente
                      
        } //end if B3
        
        
  } //end while
  
  
  
} //end loop

 
void output1()   //aciona LED1 com nota Dó
{
   digitalWrite(led1, HIGH);
   tone(piezo, nota_C4);
   delay(300);
   digitalWrite(led1, LOW);
   noTone(piezo);
   delay(300);
   
} //end output1


void output2()   //aciona LED2 com nota Mí
{
   digitalWrite(led2, HIGH);
   tone(piezo, nota_E4);
   delay(300);
   digitalWrite(led2, LOW);
   noTone(piezo);
   delay(300);
   
} //end output2


void output3()  //aciona LED3 com nota Sol
{
   digitalWrite(led3, HIGH);
   tone(piezo, nota_G4);
   delay(300);
   digitalWrite(led3, LOW);
   noTone(piezo);
   delay(300);
   
} //end output3


void start()    //sinaliza o início de um novo nível
{
  
  for(int j=0; j<5; j++)  //repete 5 vezes
  {
    digitalWrite(led1, HIGH); 
    digitalWrite(led2,  LOW);
    digitalWrite(led3,  LOW);
    delay(100);
    digitalWrite(led1,  LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3,  LOW);
    delay(100);
    digitalWrite(led1,  LOW); 
    digitalWrite(led2,  LOW);
    digitalWrite(led3, HIGH);
    delay(100);
    
  } //end for
  
  digitalWrite(led3, LOW); //apaga led3 (último a ser acionado)
  
  delay(500); //aguarda 500ms
         
} //end start


void gameOver()    //função para reiniciar o jogo em caso de erro
{
   start();        //chama função de reinicialização
   level = 0x01;   //reinicia no nível 1
   wait  = 0x00;   //limpa wait
   count = 0x00;   //reinicia contador
   
} //end gameOver

 
void memoryClear()        //função para limpar memória
{
   for(int i = 0; i < 20; i++) memory[i] = 0; //todas as posições do vetor de memória recebem o valor zero
    
} //end memoryClear

 
void complete()             //função que indica conclusão do nível
{    
        if(level == count)  //level é igual a count?
        {                   //sim...
        
          wait  = 0x00;     //limpa wait para invalidar laço while
          count = 0x00;     //reinicia o contador
          memoryClear();    //limpa memória
          level++;          //avança para o próximo nível
        } 
        
} //end complete


void check(byte number)           //função para verificar se o botão pressionado é o correto
{
   if(memory[count] == number)    //verifica posição de memória
   {          
         count++;                 //Incrementa contador        
         complete();              //Chama função que indica nível completo
         
   } //end if
   
   else gameOver(); //se o botão for errado, reinicia


} //end check