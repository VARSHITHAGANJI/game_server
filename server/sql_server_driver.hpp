#pragma once


#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class schema_creds {
public:
	
	string username,password,mobile_number;
	int status;

};

class schema_players {
public:
	string username1, user1_ip, username2, user2_ip;
};

class err_msg {
public:
	bool error;
	string error_msg;
};

class friends {
public:
	friends()
	{
		this->n_online = 0;
		this->n_offline = 0;
	}

	bool error;
	string error_msg;

	int n_online, n_offline;
	vector<string> online;
	vector<string> offline;
};


class Database_driver {
public:
	Database_driver();
	~Database_driver();
	string db_name;
	err_msg connect(string username, string passwd);
	sql::Connection* con;
  err_msg insert_creds(schema_creds& entry);
  err_msg connect_user(string username,string passwd);
  string cred_table ;
	string friends_table;
	string ip_table;
 err_msg add_friend(string username1, string username2);
	friends get_friends_info(string username);
	err_msg insert_players(schema_players& entry);
	string get_ip(string username1);
	
	



};


Database_driver::Database_driver() {

    this->db_name="AIRHOCKEY";
    this->cred_table="CREDS";
    this->friends_table="FRIENDS";
	this->ip_table = "IP_FORWARD";
    
	
}

Database_driver::~Database_driver() {
	delete this->con;
}




err_msg Database_driver::connect(string username,string passwd)
{
	err_msg em;
	em.error = false;
	try {
		sql::Driver* driver;
		sql::Connection* con;

	
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", username, passwd);
	this->con = con;
	}
	catch (sql::SQLException& e) {

		em.error = true;
		em.error_msg = e.what();
		
	}

	return em;


}


err_msg Database_driver::insert_creds(schema_creds& entry)
{
	err_msg em;
	em.error = false;
	try {
		sql::Statement* stmt;
    sql::PreparedStatement *pstmt;
		stmt = this->con->createStatement();
   
		stmt->execute("USE " + this->db_name);
   
		
    pstmt = this->con->prepareStatement("INSERT INTO "+this->cred_table+" (UserName,Password,mob_no,Status) VALUES(?,?,?,?)");
		pstmt->setString(1, entry.username);
		pstmt->setString(2,entry.password);
		pstmt->setString(3, entry.mobile_number);
		pstmt->setInt(4,entry.status);
		pstmt->executeUpdate();
		delete pstmt;	
   
	}
	catch (sql::SQLException& e) {

		em.error = true;
		em.error_msg = e.what();
		//cout << '\t' << e.what()<<' '<<e.getErrorCode() << '\n';
   

	}

	return em;

}


err_msg Database_driver::connect_user(string username,string passwd)
{
	err_msg em;
	em.error = false;
	try {
		sql::Statement* stmt;
    sql::PreparedStatement *pstmt;
		stmt = this->con->createStatement();
   
		stmt->execute("USE " + this->db_name);
   
		
    pstmt = this->con->prepareStatement("UPDATE "+this->cred_table+" SET Status=1 WHERE UserName=? AND Password = ?");
		pstmt->setString(1, username);
		pstmt->setString(2,passwd);

		pstmt->executeUpdate();
		delete pstmt;	
   
	}
	catch (sql::SQLException& e) {

		em.error = true;
		em.error_msg = e.what();
		//cout << '\t' << e.what()<<' '<<e.getErrorCode() << '\n';
   

	}

	return em;

}

err_msg Database_driver::disconnect_user(string username,string passwd)
{
	err_msg em;
	em.error = false;
	try {
		sql::Statement* stmt;
    sql::PreparedStatement *pstmt;
		stmt = this->con->createStatement();
   
		stmt->execute("USE " + this->db_name);
   
		
    pstmt = this->con->prepareStatement("UPDATE "+this->cred_table+" SET Status=0 WHERE UserName=? AND Password = ?");
		pstmt->setString(1, username);
		pstmt->setString(2,passwd);

		pstmt->executeUpdate();
		delete pstmt;	
   
	}
	catch (sql::SQLException& e) {

		em.error = true;
		em.error_msg = e.what();
		//cout << '\t' << e.what()<<' '<<e.getErrorCode() << '\n';
   

	}

	return em;

}


string Database_driver::get_ip(string username1)
{
	string ans;
	try {
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* res;
		stmt = this->con->createStatement();
		stmt->execute("USE " + this->db_name);
		pstmt = this->con->prepareStatement("SELECT I.User2_IP FROM IP_FORWARD I WHERE I.User1= \'" + username1 + "\'");

		res = pstmt->executeQuery();


		 ans = res->getString("User2_IP");
		delete pstmt;
		delete res;
	}
	catch (sql::SQLException& e) {

		ans = "err:" + e.what();

	}
	return ans;

}



err_msg Database_driver::insert_players(schema_players& entry)
{
	err_msg em;
	em.error = false;
	try {
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		stmt = this->con->createStatement();

		stmt->execute("USE " + this->db_name);


		pstmt = this->con->prepareStatement("INSERT INTO " + this->ip_table + " (User1,User1_IP,User2,User2_IP) VALUES(?,?,?,?)");
		pstmt->setString(1, entry.username1);
		pstmt->setString(2, entry.user1_ip);
		pstmt->setString(3, entry.username2);
		pstmt->setString(4, entry.user2_ip);
		pstmt->executeUpdate();
		delete pstmt;

	}
	catch (sql::SQLException& e) {

		em.error = true;
		em.error_msg = e.what();
		//cout << '\t' << e.what()<<' '<<e.getErrorCode() << '\n';


	}

	return em;

}




err_msg Database_driver::add_friend(string username1, string username2)
{
	err_msg em;
	em.error = false;
	try {
		sql::Statement* stmt;
		stmt = this->con->createStatement();
		stmt->execute("USE " + this->db_name);
		sql::PreparedStatement *pstmt;
		pstmt = this->con->prepareStatement("INSERT INTO " + this->friends_table + " (User1,User2) VALUES(?,?)");
		pstmt->setString(1, username1);
		pstmt->setString(2, username2);
			
		pstmt->executeUpdate();
		pstmt->setString(2, username1);
		pstmt->setString(1, username2);
		pstmt->executeUpdate();

		delete pstmt;

		

		
	}
	catch (sql::SQLException& e) {

		em.error = true;
		em.error_msg = e.what();

	}

	return em;

}


friends Database_driver::get_friends_info(string username)
{
	friends return_result;
 
	return_result.error = false;
	try {
		sql::Statement* stmt;
		sql::PreparedStatement *pstmt;
		sql::ResultSet* res;
		stmt = this->con->createStatement();
		stmt->execute("USE " + this->db_name);
		pstmt = this->con->prepareStatement("SELECT C.username,C.status FROM CREDS C INNER JOIN FRIENDS F WHERE F.User1= \'"+username+"\' AND F.User2=C.username");
		
		res = pstmt->executeQuery();
  
  
		while (res->next())
		{

       
			if (res->getInt(2) == 1)
			{
      
				return_result.n_online++;
				return_result.online.push_back(res->getString("username"));
			}
			else
			{
				return_result.n_offline++;
				return_result.offline.push_back(res->getString("username"));

			}
		}
		delete pstmt;
		delete res;
	}
	catch (sql::SQLException& e) {

		return_result.error = true;
		return_result.error_msg = e.what();

	}
 

 
 

	return return_result;

}


