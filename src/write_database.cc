#include "write_database.h"
#include <memory.h>

using namespace std;
using namespace pqxx;

Database::Database() {

}

Database::~Database() {
    my_conn->disconnect();
    delete my_conn;
    delete my_work;
}

bool Database::init() {

}

void Database::set_database_param(database_param& param) {
    this->params.db_name = params.db_name;
    this->params.host_address = params.host_address;
    this->params.password = params.password;
    this->params.port = params.port;
    this->params.user = params.user;
}

bool Database::connect() {
    char str[64];
    memset(str, 0, 64*sizeof(char));
    sprintf(str, "dbname=%s user=%s password=%s hostaddr=%s port=%s", params.db_name, params.user, params.password, params.host_address, params.port);
    my_conn = new pqxx::connection(str);
    my_work = new pqxx::work(*my_conn);
}

void Database::write_result(const char* table_name, vector<result_format>& result) {
    res.clear();
    res << "insert into " << table_name << " values";
    for(int i = 0; i < result.size(); i++) {
        if(i == 0) {
            res << "('" << result[i].img_name << "', '" << result[i].class_id << "')";
        }
        else {
            res << ",("  << result[i].img_name << "', '" << result[i].class_id << "')";
        }
    }
    my_work->exec(res);
    my_work->commit();
}
