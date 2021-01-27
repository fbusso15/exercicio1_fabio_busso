//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN // Inicio do Modelo


/* Exercicio 3 - Vari�vel X = Vendas que dependem de: Pre�o / Qualidade / Componente Ale�t�rio - N�vel do Objeto: FIRM */
EQUATION("X") 
	v[1]=V("Price");
	v[2]=VL("Price",1);
	if (v[2]>v[1]) {v[5]=(v[5]*-1);}
	else {v[5]=v[5];} 
	v[3]=V("Quality");
	v[4]=VL("Quality",1);
	v[5]=V("elasticity_price");									// 0 < "elasticity_price" < 1 - Parametro que Retorna a sensibilidade do Aumento das Vendas em rela��o a mudan�a nos Pre�o
	v[6]=V("elasticity_quality");							// 0 < "elasticity_quality" < 1 - Parametro que Retorna a sensibilidade do Aumento das Vendas em rela��o a mudan�a de Qualidade
RESULT(v[5]*(v[1]-v[2]) + v[6]*(v[3]-v[4])+(VL("X",1)))

/* Vari�vel que Retorna o Pre�o das Firmas - N�vel do Objeto: Firm */
EQUATION("Price")
		v[0]=VL("Price",1);
		v[1]=VL("Share_X",1)-VL("Share_X",2);
		if (v[1]>0) {v[2]=v[1];}
		else {v[2]=0;}
		v[3]=V("sensitivity_share"); // 0 < "sensitivity_price" < 1 - Parametro que Retorna o Aumento do pre�o em rela��o ao ganho de Market Share da Firma
RESULT((v[3]*v[2] + v[0]))

/* Vari�vel que Retorna a Qualidade das Firmas - N�vel do Objeto: Firm */
EQUATION("Quality")
		v[0]=VL("Quality",1);
		v[1]=RND;
		if (v[1]>0) {v[2]=v[1];}
		else {v[2]=0;}
RESULT(v[0]+v[2])

/* Vari�vel que Retorna a Soma de todos os X [O mesmo que utilizar a Macro (SUM("X"))] - N�vel do Objeto: SECTOR */
EQUATION("Sum_X") 
		v[0]=0;
		CYCLE(cur, "FIRM")
		{
			v[1]=VS(cur,"X");
			v[0]=v[0]+v[1];
		}
RESULT(v[0])

/* Vari�vel que Retorna a M�dia de todos os X [O mesmo que utilizar a Macro (AVE("X"))] - N�vel do Objeto: SECTOR */
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

/* Retorna o valor M�ximo de todos os X [O mesmo que utilizar a Macro (MAX("X"))] - N�vel do Objeto: SECTOR */
EQUATION("Max_X") 
		v[0]=0;
		CYCLE(cur, "FIRM")
		{
			v[1]=VS(cur,"X");
			if(v[1]>v[0])	v[0]=v[1]; 
			else v[0]=v[0];
		}
RESULT(v[0])

/* Participa��o de cada X em Rela��o ao valor total de todos os X [Seria igual a "Participa��o no Mercado de cada Firma"] - N�vel do Objeto: FIRM */
EQUATION("Share_X") 
RESULT((V("X")/V("Sum_X")))

/* Somat�rio das Participa��es de cada Firma [Deve somar 1 e o mesmo que utilizar (SUM(Share_X))] - N�vel do Objeto: SECTOR */
EQUATION("Sum_Share_X") 
		v[0]=0;
		CYCLE(cur, "FIRM")
		{
			v[1]=VS(cur,"Share_X");
			v[0]=v[0]+v[1];
		}
RESULT(v[0])

/* Encontrar a Firma com o Maior X a cada Per�odo (A L�der de Mercado) - N�vel do Objeto: SECTOR */
EQUATION("Leader")
		v[0]=V("Max_X");
		cur1=SEARCH_CND("X", v[0]);							 // O cur armazena um objeto especifico enquanto o v[] armazena um valor
		v[1]=SEARCH_INST(cur1);									 // Retorna a posi��o no objeto especificado
RESULT(v[1])

/* Cria um Rank das Firmas - N�vel do Objeto: SECTOR */
EQUATION("Rank")
		SORT("FIRM", "Share_X", "DOWN");
		v[0]=0; 
		CYCLE(cur, "FIRM")
		{
			v[0]=v[0]+1;
			WRITES(cur, "firm_rank", v[0]);
		}				
RESULT(0)

/* Equa��o para Entrada e Sa�da de Firmas */
EQUATION("EntryExit") 
		v[0]=V("switch_entry");
		if(v[0]==1)
		{
			cur=SEARCH_CND("firm_rank", 10); 			 // Deleta a firma com Posi��o no Rank das Firmas =10
			DELETE(cur);
			cur1=SEARCH_CND("firm_rank", 5);
			ADDOBJ_EX("FIRM", cur1); 							 // Cria novo objeto (No caso uma Firma). O [EX] cria o objeto com os valores do [cur1] (no caso a firma de rank =5)
		}
RESULT(0)


MODELEND // Fim do Modelo

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
