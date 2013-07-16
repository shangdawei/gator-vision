/*
 * TelnetConsole.h
 *
 *  Created on: Jul 15, 2013
 *      Author: Jeff
 */

#ifndef TELNETCONSOLE_H_
#define TELNETCONSOLE_H_

#include "TCPServer.h"

class TelnetConsole: public TCPServer
{
public:
   TelnetConsole();
   virtual ~TelnetConsole();
};

#endif /* TELNETCONSOLE_H_ */
