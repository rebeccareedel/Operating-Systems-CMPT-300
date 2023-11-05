#ifndef _SENDER_H_
#define _SENDER_H_

#include "list.h"

void Sender_signalNextSend(void);
void Sender_init(List* pList, char* host, char* port);
void Sender_shutdown(void);

#endif