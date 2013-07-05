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
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/autoip.h"

class NetServiceManager : public AManagedTask
{
public:
   NetServiceManager();
   void Run();
   bool HardwareInit();
   virtual ~NetServiceManager();

private:
   struct netif NetIF;

   void LwIP_Init();

};

#endif /* NETSERVICEMANAGER_H_ */
