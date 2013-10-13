/*
 * NetServiceManager.cpp
 *
 *  Created on: Jul 5, 2013
 *      Author: Jeff
 */

#include "NetServiceManager.h"

NetServiceManager::NetServiceManager()
{
   NetIFUp = false;
   FTPServer = new TCPServer<FTPSession>(2,2);

   FTPServer->Create("FTPServer",1000,2);
}

void NetServiceManager::OnNetIFStatusChange(bool up)
{
   // If the network interface came up, start the servers
   if (up)
   {
      FTPServer->Start(ntohl(NetIF.ip_addr.addr), 21);
   }
   // If the network interface went down, stop the servers
   else
   {
      FTPServer->Stop();
   }
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

   /* Registers the default network interface. */
   netif_set_default(&NetIF);

   /* When the netif is fully configured this function must be called. */
   dhcp_start(&NetIF);

}

void NetServiceManager::Run()
{
   // Monitor NetIF status
   // When network status changes, bring the servers up or down
   while (true)
   {
      bool status = ((NetIF.flags & NETIF_FLAG_UP) != 0) && ((NetIF.flags & NETIF_FLAG_LINK_UP) != 0);
      if ( NetIFUp != status )
      {
         NetIFUp = status;
         OnNetIFStatusChange(status);
      }

      Delay(10);
   }
}


