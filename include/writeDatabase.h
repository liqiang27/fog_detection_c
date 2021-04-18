#ifndef WRITEDATABASE_H_
#define WRITEDATABASE_H_
/*
 * @Descripttion: write the result to database!
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-25 19:19:40
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-18 23:02:16
 */
#include <pqxx/pqxx>
#include "my_common.h"

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
#endif

