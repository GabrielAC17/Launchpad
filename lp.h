#ifndef lp_h
#define lp_h

bool GPIOExport(int pino);
bool GPIODirection(int pino, int direcao);
bool GPIOWrite(int pino, int valor);
bool GPIORead(int pino);
bool GPIOUnexport(int pino);

#endif
