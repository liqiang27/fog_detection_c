#pragma once
/*
 * @Descripttion:  read config.json
 * @version: 1.0
 * @Author: lstron
 * @Date: 2021-03-24 20:28:36
 * @LastEditors: Lstron
 * @LastEditTime: 2021-03-31 15:41:51
 */
#include "my_common.h"

/**
 * @name: checKConfigfile
 * @msg: Check if the config.json file exists. if the file exist return true, 
 * @param {void}
 * @return {bool}
 */
bool checkConfigfile();


/**
 * @name: readConfig
 * @msg: reading config.json from a  fixed path, and then saving these information to some static parameters.
 * @param {void}
 * @return {bool}
 */
bool readConfig();





