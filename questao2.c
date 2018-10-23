#include<at89x52.h>

#define SENSOR_QUEDA P2_0
#define ESTEIRA_1    P2_1
#define ESTEIRA_2    P2_2

int MAX_CAIXA           = 10;   // quantidade máxima de produtos por caixa
int contador_interacoes = 0;    // contador para controle do timer
int contador_produto    = 0;    // contador de produtos inseridos na caixa

void atendeTimer() interrupt 1{
	TR0=0;
	TH0=0x3C;
	TL0=0xAF;
	TR0=1;
	
	contador_interacoes++;
	
	if(contador_interacoes == 20){   // A cada 1s um produto cai (a não ser que a esteira 2 esteja rodando)
		if(ESTEIRA_2 == 1){            // Esteira 1 irá andar por 1s enquanto a 2 espera por uma nova caixa
			ESTEIRA_1 = 1;               // Esteira 1 anda
			ESTEIRA_2 = 0;               // Esteira 2 para
		}else{
			contador_produto++; 
		}
		contador_interacoes = 0;
	}
	
	if(contador_produto == MAX_CAIXA){ // Se a caixa estiver cheia
		ESTEIRA_1 = 0;                   // Esteira 1 para
		ESTEIRA_2 = 1;                   // Esteira 2 anda
		contador_produto = 0;
	}
}

void main(){
	P2 = 0;
	
	EA=1;
	ET0=1;
	TMOD=1;
	TR0=1;
	
	ESTEIRA_1 = 1;                   // Esteira 1 começa andando
	ESTEIRA_2 = 0;                   // Esteira 2 começa parada
	
	while(1){
		//programa principal
	}
}
