/*
 * NetServiceManager.cpp
 *
 *  Created on: Jul 5, 2013
 *      Author: Jeff
 */

#include "NetServiceManager.h"

NetServiceManager::NetServiceManager()
{
   FTPServer = new TCPServer<FTPSession>(2,2);
}

NetServiceManager::~NetServiceManager()
{

}

bool NetServiceManager::HardwareInit()
{
   ETH_BSP_Config();
   low_level_MAC_init();
   LwIP_Init();


   return true;
}

void NetServiceManager::LwIP_Init()
{
   struct ip_addr ipaddr;
   struct ip_addr netmask;
   struct ip_addr gw;

   // Create tcp_ip stack thread
   tcpip_init(NULL, NULL);

   // Try DHCP, then fall back to AutoIP
   ipaddr.addr = 0;
   netmask.addr = 0;
   gw.addr = 0;

   //IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
   //IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
   //IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);


   netif_add(&NetIF, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);

   /*  Registers the default network interface. */
   netif_set_default(&NetIF);

   /* When the netif is fully configured this function must be called. */
   netif_set_up(&NetIF);
   dhcp_start(&NetIF);

}

void NetServiceManager::Run()
{
   // Nothing to do yet, just return
   this->Delete();
}

