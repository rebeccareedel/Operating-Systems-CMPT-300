#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include "list.h"

void Receiver_init(List* pList, char* port);
void Receiver_shutdown(void);

#endif