/* config_file.h
 * read param from config file
 * author: pangyemeng
 */


#ifndef __CONFIG_FILE_H__
#define __CONFIG_FILE_H__


bool CfgParamIsComment(char *line);
int CfgParamStr(const char *cfg_file, const char *param, char *ret_val, int rsize);
int CfgParamBool(const char *cfg_file, const char *param, bool *rval);
int CfgParamInt(const char *cfg_file, const char *param, long *rval);


#endif /* __CONFIG_FILE_H__ */
