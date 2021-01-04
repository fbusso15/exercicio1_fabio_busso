//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN


/*
Criando uma vari�vel "X" defasada um periodo a partir de um valor aleat�rio "RND" entre 0 e 1 multiplicado por uma constante "c" cujo valor tamb�m ser� aleat�rio (A partir da op��o random integer com intervalo entre [1 e 10]):
*/

EQUATION("X")
/*
Vari�vel X
*/

RESULT(VL("X",1) + (RND * V("c")))



MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
