//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN


/*
Criando uma variável "X" defasada um periodo a partir de um valor aleatório "RND" entre 0 e 1 multiplicado por uma constante "c" cujo valor também será aleatório (A partir da opção random integer com intervalo entre [1 e 10]):
*/

EQUATION("X")
/*
Variável X
*/

RESULT(VL("X",1) + (RND * V("c")))



MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
