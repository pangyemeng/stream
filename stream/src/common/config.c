/*
 * config.c
 *
 *  Created on: Dec 29, 2015
 *      Author: pangyemeng
 */

#include <libxml/parser.h>
#include <stdio.h>

#include "./include/config.h"

cfg_f *g_cfg = NULL;

void FreeXmlNode(xml_cfg *cfg);

int InitCfg(const char *file_name) {

	xmlDocPtr doc = NULL;
	xmlNodePtr cur_node = NULL;
	xmlNodePtr item_node = NULL;
	xml_cfg* p_xml_cfg = NULL;

	int xml_flag = 1;
	if (NULL == g_cfg) {
		g_cfg = (cfg_f *) malloc(sizeof(cfg_f));
		if (NULL == g_cfg) {
			printf("Malloc Error\n");
			return -1;
		}
		memset(g_cfg, '0', sizeof(g_cfg));
	}
	doc = xmlReadFile(CFG_FILE, "UTF-8", XML_PARSE_RECOVER);
	if (!doc) {
		fprintf(stderr, "Read configure file failed!\n");
		return -1;
	}
	cur_node = xmlDocGetRootElement(doc);
	if (!cur_node) {
		fprintf(stderr, "Empty configure file!\n");
		xmlFreeDoc(doc);
		return -1;
	}
	if (xmlStrcmp(cur_node->name, BAD_CAST "stream")) {
		fprintf(stderr, "Root node error!\n");
		xmlFreeDoc(doc);
		return 0;
	}
	item_node = cur_node->xmlChildrenNode;
	p_xml_cfg = (xml_cfg*) malloc(sizeof(xml_cfg));
	if (NULL == p_xml_cfg) {
		return -1;
	}
	memset(p_xml_cfg, 0, sizeof(xml_cfg));
	while (item_node) {
		if (item_node->type != XML_ELEMENT_NODE) {
			item_node = item_node->next;
			continue;
		}
		if (!xmlStrcmp(item_node->name, BAD_CAST "interface")) {
			p_xml_cfg->x_interface = xmlNodeGetContent(item_node);
			if (NULL == p_xml_cfg->x_interface) {
				xml_flag = 0;
			}
		}
		if (!xmlStrcmp(item_node->name, BAD_CAST "log_mode")) {
			p_xml_cfg->x_log_mode = xmlNodeGetContent(item_node);
			if (NULL == p_xml_cfg->x_log_mode) {
				xml_flag = 0;
			}
		}
		if (!xmlStrcmp(item_node->name, BAD_CAST "cap_module")) {
			p_xml_cfg->x_cap_module = xmlNodeGetContent(item_node);
			if (NULL == p_xml_cfg->x_cap_module) {
				xml_flag = 0;
			}
		}
		item_node = item_node->next;
	}
	xmlFreeDoc(doc);

	if (0 == xml_flag) {
		FreeXmlNode(p_xml_cfg);
		return 0;

	}

	snprintf(g_cfg->interface, 32, "%s", (const unsigned char *)p_xml_cfg->x_interface);
	printf("interface:%s\n", g_cfg->interface);
	snprintf(p_xml_cfg->log_mode, 32, "%s", (const unsigned char *)p_xml_cfg->x_log_mode);
	printf("log_mode:%s\n", g_cfg->log_mode);
	snprintf(g_cfg->cap_module, 32, "%s", (const unsigned char *)p_xml_cfg->x_cap_module);
	printf("cap_module:%s\n", g_cfg->cap_module);
	/* free memory */
	FreeXmlNode(p_xml_cfg);

	if (p_xml_cfg) {
		free(p_xml_cfg);
		p_xml_cfg = NULL;
	}
	return 0;
}

void FreeXmlNode(xml_cfg *cfg) {
	if (cfg->x_interface != NULL) {
		xmlFree(cfg->x_interface);
		cfg->x_interface = NULL;
	}
	if (cfg->x_log_mode != NULL) {
		xmlFree(cfg->x_log_mode);
		cfg->x_log_mode = NULL;
	}
	if (cfg->x_cap_module != NULL) {
		xmlFree(cfg->x_cap_module);
		cfg->x_cap_module = NULL;
	}

}
