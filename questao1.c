#include <at89x52.h>

#define COIN  P2_0
#define K     P2_1
#define T     P2_2
#define TEA   P2_5
#define COFEE P2_6
#define GLASS P2_7

int esperaBotao = 0;

void reiniciaMaquina(){
    esperaBotao -= 1;              // Decrementa a ação de uma moeda inserida
    TEA   = 0;
    COFFE = 0;
    GLASS = 0;
}

void main(){
    P2 = 0;    
    while(1){
        if(COIN == 1){              // A máquina espera até uma moeda ser inserida
            esperaBotao += 1;       // Para cada moeda, é esperado uma ação do usuário
        }
        
        if(esperaBotao){            // Máquina no estado "button"
            if(K == 1){             // Caso o botão de chá for pressionado
                TEA = 1;            // Serve chá
                GLASS = 1;
                reiniciaMaquina();
            }else if(T == 1){      // Caso o botão de café for pressionado
                COFEE = 1;         // Serve café
                GLASS = 1               
                reiniciaMaquina();
            }
        }
    }
}
