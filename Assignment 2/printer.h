#ifndef _PRINTER_H_
#define _PRINTER_H_

#include "list.h"

void Printer_signalNextWrite();
void Printer_init(List* pList);
void Printer_shutdown(void);

#endif