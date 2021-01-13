//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN // Inicio do Modelo


/* Vari�vel "X" defasada um periodo a partir de um valor aleat�rio "RND" entre 0 e 1 multiplicado por uma constante "c" - N�vel do Objeto: FIRM */
EQUATION("X") 
RESULT(VL("X",1) + (RND * V("c")))

/* Vari�vel que Retorna a Soma de todos os X [O mesmo que utilizar a Macro (SUM("X")] - N�vel do Objeto: SECTOR */

EQUATION("Sum_X") 
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X");
	v[0]=v[0]+v[1];
}
RESULT(v[0])

/* Vari�vel que Retorna a M�dia de todos os X [O mesmo que utilizar a Macro (AVE("X")] - N�vel do Objeto: SECTOR */
EQUATION("Ave_X") 
v[0]=0;
v[2]=0;
CYCLE(cur, "FIRM")
{
	v[3]=VS(cur,"X");
	v[0]=v[0]+v[3];
	v[1]= COUNT_ALLS(cur,"FIRM");
}
if(v[1]!=0) v[2]=v[0]/v[1];	
else v[2]=0;
RESULT(v[2])

/* Retorna o valor M�ximo de todos os X [O mesmo que utilizar a Macro (MAX("X")] - N�vel do Objeto: SECTOR */
EQUATION("Max_X") 
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X");
	if(v[1]>v[0])	v[0]=v[1]; 
	else v[0]=v[0];
}
RESULT(v[0])

/* Participa��o de cada X em Rela��o ao valor total de todos os X [Seria igual a "Participa��o no Mercado de cada Firma"] - N�vel do Objeto: SECTOR */
EQUATION("Share_X") 
RESULT((V("X")/V("Sum_X")))

/* Somat�rio das Participa��es de cada Firma [Deve somar 1] - N�vel do Objeto: SECTOR */
EQUATION("Sum_Share_X") 
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"Share_X");
	v[0]=v[0]+v[1];
}
RESULT(v[0])

/* Exercicio Desafio - Encontrar a Firma com o Maior X a cada Per�odo (A L�der de Mercado) - N�vel do Objeto: SECTOR */

EQUATION("Leader")
v[0]=0;
v[1]=0;
CYCLE(cur, "FIRM")
{
	v[2]=VS(cur,"Share_X");
	v[3]=VS(cur,"IdFirm");
	if(v[2]>v[0]) {v[0]=v[2]; v[1]=v[3];}
	else
	{v[0]=0; v[1]=v[1];}
}
RESULT(v[1])


MODELEND // Fim do Modelo

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
