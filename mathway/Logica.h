#ifndef LOGICA_H  // guardas de cabeçalho, impedem inclusões cíclicas
#define LOGICA_H


extern int baz;    // declaração de uma variável global
// como é global, valor inicial é zero.

int logica(char tipo,int nivel,int op,int n1,int n2);

#endif