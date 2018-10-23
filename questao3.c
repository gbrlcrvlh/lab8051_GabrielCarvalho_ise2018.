#include<at89x52.h>

#define CAMERA_0          P2_0
#define CAMERA_1          P2_1
#define CAMERA_2          P2_2
#define CAMERA_3          P2_3
#define ALARME            P2_4
#define SENSOR_PRESENCA_0 P3_0
#define SENSOR_PRESENCA_1 P3_1
#define SENSOR_PRESENCA_2 P3_2
#define SENSOR_PRESENCA_3 P3_3


int contador_interacoes = 0;              // Contador para controle do timer
int habilita_gravacao   = 0;

void atendeTimer() interrupt 1{
	TR0=0;
	TH0=0x3C;
	TL0=0xAF;
	TR0=1;
	
	contador_interacoes++;
	
	if(contador_interacoes % 60 == 0){      // Inicia o vídeo com a gravação desabilitada
		habilita_gravacao = 0;
	}
	
	if(contador_interacoes <= 60){         // Entre 0s e 3s mostra CAMERA_0
		CAMERA_3 = 0;                        // Desativa câmera anterior
		CAMERA_0 = 1;                        // Ativa câmera atual
		if(SENSOR_PRESENCA_0 == 1){          // Verifica se o sensor está ativo
			ALARME = 1;                        // Se sim, dispara alarme
			habilita_gravacao = 1;             // Habilita a gravação da câmera até a prox camera ser mostrada
		}
	}else if(contador_interacoes <= 120){  // entre 3s e 6s mostra CAMERA_1
		CAMERA_0 = 0;
		CAMERA_1 = 1;
		if(SENSOR_PRESENCA_1 == 1){
			ALARME = 1;
			habilita_gravacao = 1;
		}
	}else if(contador_interacoes <= 180){  // entre 6s e 9s mostra CAMERA_2
		CAMERA_1 = 0;
		CAMERA_2 = 1;
		if(SENSOR_PRESENCA_2 == 1){
			ALARME = 1;
			habilita_gravacao = 1;
		}
	}else if(contador_interacoes <= 240){  // entre 9s e 12s mostra CAMERA_3
		CAMERA_2 = 0;
		CAMERA_3 = 1;
		if(SENSOR_PRESENCA_3 == 1){
			ALARME = 1;
			habilita_gravacao = 1;
		}
	}
	
	if(contador_interacoes == 240){
		contador_interacoes = 0;
	}
}

void main(){
	P2 = 0;
	P3 = 0;
	
	EA=1;
	ET0=1;
	TMOD=1;
	TR0=1;
		
	while(1){
		//programa principal
	}
}
