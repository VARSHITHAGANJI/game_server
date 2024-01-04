#pragma once

#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include "sql_server_driver.hpp"

using namespace std;

class Packet{
    public:
        string message;
        vector<string> parse_packet(string me);
    protected:
        char type;
        string operation;
        string from;
        string to;
        string data;


}

Packet::Packet(string m)
{
    this.message = m;
    vector<string> parts = this->parse_packet(m);
    this.type = parts[0][0];
    this->operation  = parts[1];
    this->from = parts[2];
    this->to = parts[3];
    this->data = parts[4];

}

vector<string> Packet::parse_packet(string me)
{
   
    vector<string> res;
    string delim = "\n";
    string token = "";
    for (int i = 0; i < me.size(); i++) {
        bool flag = true;
        for (int j = 0; j < delim.size(); j++) {
            if (me[i + j] != delim[j]) flag = false;
        }
        if (flag) {
            if (token.size() > 0) {
                res.push_back(token);
                token = "";
                i += delim.size() - 1;
            }
        } else {
            token += me[i];
        }
    }
    res.push_back(token);
    return res;


}


class Login:public Packet{

    public:
        Database_driver drive_in;
        

    private:
        err_msg create_account();
        err_msg connect();
        err_msg disconnect();
        err_msg add_friends();
        err_msg req_friends();
        err_msg res_friends();
        friends get_friends();


}

Login::Login(string m,Database_driver drive_in)
{
    Packet(string m);
    this.drive_in = drive_in

}

err_msg Login::create_account()
{
    vector<string> details = this->parse_packet(this->data); //username , password, mobilenumber
    schema_creds entry;
    entry.mobile_number = details[0];
    entry.username = details[1];
    entry.password = details[2];
    entry.status = details[3];
    err_msg result = driver_in.insert_creds(entry);
    return result;
}

err_msg Login::connect()
{
    vector<string> details = this->parse_packet(this->data);
    
    err_msg result = this.drive_in->connect_user(details[0],details[1]);
    return result;
}

err_msg Login::disconnect()
{
    vector<string> details = this->parse_packet(this->data);
    
    err_msg result = this.drive_in->disconnect_user(details[0],details[1]);
    return result;
}

err_msg Login::add_friends()
{
    vector<string> details = this->parse_packet(this->data); //username , password, mobilenumber
   
    
    err_msg result = this.driver_in.add_friend(details[0],details[1]);
    return result;
}


friends Login::get_friends()
{
    friends result = this.driver_in.get_friends_info(this.data);

    return friends;

}

err_msg Login::req_friends()
{
    err_msg result;
    return result;
}

err_msg Login::res_friends()
{
    err_msg result;
    return result;
}


class Game:public Packet()
{
    
    public:
        Database_driver drive_in;
        

    private:
        err_msg req_game();
        err_msg res_game();
        err_msg start_game();
        err_msg end_game();
        err_msg forward_coords();
        



}

Game::Game(string m,Database_driver drive_in)
{
    Packet(string m);
    this.drive_in = drive_in

}

err_msg Game::req_game()
{

    string p = "G\n"+"req_game\n"+this.from+"\n"+this.to+"\n"+"null";
    



}




