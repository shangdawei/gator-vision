#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__


#include "lwip/err.h"
#include "lwip/netif.h"

#ifdef __cplusplus
extern "C"
{
#endif


err_t ethernetif_init(struct netif *netif);
void low_level_MAC_init(void);


#ifdef __cplusplus
}
#endif

#endif 
