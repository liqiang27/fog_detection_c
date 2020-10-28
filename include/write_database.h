#ifndef WRITE_DATABASE_H_
#define WRITE_DATABASE_H_

#include <iostream>
#include <cstdlib>

#include <pqxx/pqxx>

typedef struct database_params_
{
    const char* db_name;
    const char* user;
    const char* password;
    const char* host_address;
    const char* port;
}database_param;

typedef struct result_format_
{
    std::string img_name;
    int class_id;
}result_format;

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
