/*
 * init.h
 *
 *  Created on: Dec 29, 2015
 *      Author: pangyemeng
 */

#ifndef INIT_H_
#define INIT_H_

//Init capture packet modules
int InitCapModules();

//Init protocol tree
int InitProtModules();

//Init TCP/UDP stream Manage
int InitFlowModules();


#endif /* INIT_H_ */

#ifndef __CONFIG_H__
#define __CONFIG_H__

typedef struct _cfg_f cfg_f;
struct _cfg_f {
	char *interface;  /*eth0 */
	char *log_mode;   /*log screen or log file*/
	char *cap_module; /* pcap or pfring or dpdk */
};

#endif /* __CONFIG_H__ */
