



#include "sql_server_driver.hpp"


Database_driver::Database_driver() {
	
}

Database_driver::~Database_driver() {
	delete this->con;
}




bool Database_driver::connect(string username,string passwd)
{
	bool error = false;
	try {
		sql::Driver* driver;
		sql::Connection* con;

	
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", username, passwd);
	this->con = con;
	}
	catch (sql::SQLException& e) {

		error = true;
		
	}

	return error;


}


/*

bool Database_driver::insert_creds(schema_creds& entry)
{
	bool error = false;
	try {
		sql::Statement* stmt;
    sql::PreparedStatement *pstmt;
		stmt = this->con->createStatement();
		stmt->execute("USE " + this->db_name);
		pstmt = this->con->prepareStatement("INSERT INTO"+this->cred_table+" VALUES(?,?,?,?)");
		pstmt->setString(1, entry.username);
		pstmt->setString(2,entry.password);
		pstmt->setString(3, entry.mobilenumber);
		pstmt->setInt(4,entry.status);
		pstmt->executeUpdate();
		delete pstmt;	
	}
	catch (sql::SQLException& e) {

		error = true;

	}

	return error;

}

bool Database_driver::add_friend(string username1, string username2)
{
	bool error = false;
	try {
		sql::Statement* stmt;
		stmt = this->con->createStatement();
		stmt->execute("USE " + this->db_name);
   

		bool already_present = already_friend(username1, username2);

		if (!already_present)
		{
     sql::PreparedStatement *pstmt;
			pstmt = this->con->prepareStatement("INSERT INTO" + this->friends_table + " VALUES(?,?)");
			pstmt->setString(1, username1);
			pstmt->setString(2, username2);
			
			pstmt->executeUpdate();
			pstmt->setString(2, username1);
			pstmt->setString(1, username2);
			pstmt->executeUpdate();

			delete pstmt;

		}

		
	}
	catch (sql::SQLException& e) {

		error = true;

	}

	return error;

}

friends Database_driver::get_friends_info(string username)
{
	friends return_result;
	bool error = false;
	try {
		sql::Statement* stmt;
   sql::PreparedStatement *pstmt;
		sql::ResultSet* res;
		stmt = this->con->createStatement();
		stmt->execute("USE " + this->db_name);
		pstmt = this->con->prepareStatement("SELECT C.username,C.status FROM CREDS C INNER JOIN FRIENDS F WHERE F.username1="+username+" AND F.username2=C.username");
		
		res = pstmt->executeQuery();
		while (res->next)
		{
			if (res->getInt("status") == true)
			{
				return_result->n_online++;
				return_result->online.push_back(res->getString("username"));
			}
			else
			{
				return_result->n_offline++;
				return_result->offline.push_back(res->getString("username"));

			}
		}
		delete pstmt;
		delete res;
	}
	catch (sql::SQLException& e) {

		error = true;

	}

	return return_result;

}

*/

/*

void run_query(string query,sql::Statement* &stmt)
{
  stmt->execute(query);
}

int main(void)
{
cout << endl;
cout << "Running 'SELECT 'Hello World!' AS _message'..." << endl;
sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet  *res;

driver = get_driver_instance();
con = driver->connect("tcp://127.0.0.1:3306", "root", "VARZZZ");

cout<<"driver connected"<<'\n';
stmt = con->createStatement();
stmt->execute("USE AIRHOCKEY");
res=stmt->executeQuery("SELECT * FROM test");
while (res->next()) {
  // You can use either numeric offsets...
  cout << "id = " << res->getInt(1); // getInt(1) returns the first column
  // ... or column names for accessing results.
  // The latter is recommended.
  cout << ", label = '" << res->getString("label") << "'" << endl;
}

return EXIT_SUCCESS;
}
 */

