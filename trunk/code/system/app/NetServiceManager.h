/*
 * NetServiceManager.h
 *
 *  Created on: Jul 5, 2013
 *      Author: Jeff
 */

#ifndef NETSERVICEMANAGER_H_
#define NETSERVICEMANAGER_H_

#include "AManagedTask.h"
#include "ethernetif.h"
#include "eth_bsp.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/autoip.h"
#include "services/TCPServer.h"
#include "services/FTPSession.h"

class NetServiceManager : public AManagedTask
{
public:
   NetServiceManager();
   void Run();
   bool HardwareInit();
   void OnNetIFStatusChange(bool up);
   virtual ~NetServiceManager();

private:
   struct netif NetIF;
   TCPServer<FTPSession> * FTPServer;
   bool NetIFUp;

   void LwIP_Init();

};

#endif /* NETSERVICEMANAGER_H_ */
