/*
 * config.h
 *
 *  Created on: Dec 29, 2015
 *      Author: root
 */

#ifndef CONFIG_H_
#define CONFIG_H_

typedef struct _cfg_f cfg_f;
struct _cfg_f {
	char interface[32];  /*eth0 */
	char log_mode[32];   /*log screen or log file*/
	char cap_module[32]; /* pcap or pfring or dpdk */
};

typedef struct _xml_cfg xml_cfg;
struct _xml_cfg{
	xmlChar* x_interface;
	xmlChar* x_log_mode;
	xmlChar* x_cap_module;
};

int InitCfg(const char *file_name);

#endif /* CONFIG_H_ */
