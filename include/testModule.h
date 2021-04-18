#ifndef TESTMODULE_H_
#define TESTMODULE_H_

/*
 * @Descripttion: Test whether the database transmission,
 *             image information connection and GPU are normal
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-24 23:28:02
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-18 23:18:53
 */

#include "my_common.h"

/**
 * @name: checkCamera
 * @msg: Test whether the image information of the camera can be received
 * @param:
 *                  [in] cam_id : The camera need to be test.
 * @return {if the camera is OK return true, else return false} 
 */

bool checkCamera(const int cam_id);

/**
 * @name: checkDatabse
 * @msg: Test whether the database can be connected smoothly
 * @param {NONE}
 * @return {}
 */
bool checkDatabase();

/**
 * @name: checkGPU
 * @msg: Test GPU availability
 * @param {*}
 * @return {*}
 */
bool checkGPU();

#endif









