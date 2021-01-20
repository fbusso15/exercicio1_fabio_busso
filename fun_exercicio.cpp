//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN // Inicio do Modelo


/* Variável "X" defasada um periodo a partir de um valor aleatório "RND" entre 0 e 1 multiplicado por uma constante "c" - Nível do Objeto: FIRM */
EQUATION("X") 
RESULT(VL("X",1) + (RND * V("c")))

/* Variável que Retorna a Soma de todos os X [O mesmo que utilizar a Macro (SUM("X"))] - Nível do Objeto: SECTOR */
EQUATION("Sum_X") 
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X");
	v[0]=v[0]+v[1];
}
RESULT(v[0])

/* Variável que Retorna a Média de todos os X [O mesmo que utilizar a Macro (AVE("X"))] - Nível do Objeto: SECTOR */
EQUATION("Ave_X") 
v[0]=0;
v[2]=0;
CYCLE(cur, "FIRM")
{
	v[3]=VS(cur,"X");
	v[0]=v[0]+v[3];
}
v[1]=COUNT_ALL("FIRM");
if(v[1]!=0) v[2]=v[0]/v[1];	
else v[2]=0;
RESULT(v[2])

/* Retorna o valor Máximo de todos os X [O mesmo que utilizar a Macro (MAX("X"))] - Nível do Objeto: SECTOR */
EQUATION("Max_X") 
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X");
	if(v[1]>v[0])	v[0]=v[1]; 
	else v[0]=v[0];
}
RESULT(v[0])

/* Participação de cada X em Relação ao valor total de todos os X [Seria igual a "Participação no Mercado de cada Firma"] - Nível do Objeto: FIRM */
EQUATION("Share_X") 
RESULT((V("X")/V("Sum_X")))

/* Somatório das Participações de cada Firma [Deve somar 1 e o mesmo que utilizar (SUM(Share_X))] - Nível do Objeto: SECTOR */
EQUATION("Sum_Share_X") 
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"Share_X");
	v[0]=v[0]+v[1];
}
RESULT(v[0])

/* Exercicio Desafio - Encontrar a Firma com o Maior X a cada Período (A Líder de Mercado) - Nível do Objeto: SECTOR */
EQUATION("Leader")
v[0]=V("Max_X");
cur1=SEARCH_CND("X", v[0]);			// o cur armazena um objeto especifico enquanto o v[] armazena um valor
v[1]=SEARCH_INST(cur1);					// retorna a posição no objeto especificado
RESULT(v[1])

/* Exercicio 2.1 - Criar um Rank das Firmas - Nível do Objeto: SECTOR */
EQUATION("Rank")
SORT("FIRM", "Share_X", "DOWN");
v[0]=0; 
CYCLE(cur, "FIRM")
{
	v[0]=v[0]+1;
	WRITES(cur, "firm_rank", v[0]);
}				
RESULT(0)


MODELEND // Fim do Modelo

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
