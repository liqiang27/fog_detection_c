#pragma once
/*
 * @Descripttion: write the result to database!
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-25 19:19:40
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-01 18:16:55
 */
#include "my_common.h"
#include <pqxx/pqxx>
using database_param = database_info;

class Database {
public:
    Database();
    ~Database();
    bool init();
    bool connect();
    void set_database_param(database_param& param);
    void write_result(const char* table_name, std::vector<result_format>& result);

private:
    database_param params;
    std::stringstream res;
    pqxx::connection* my_conn;
    pqxx::work* my_work;
};
