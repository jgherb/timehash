/*
* TimeHash (thash)
* www.noscio.ml/timehash
* @author: Julius Herb (noscio@web.de)
* @version: 1.0 (2016_01_05)
*/

/* For sockaddr_in */
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>
/* For gethostbyname */
#include <netdb.h>

#include <unistd.h>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include "md5.h"
using namespace std;
using boost::asio::ip::tcp;
char* getCmdOption(char**, char**, const std::string&);
bool cmdOptionExists(char**, char**, const std::string&);
std::string ReplaceAll(std::string, const std::string&, const std::string&);

//Einstiegspunkt
int main(int argc, char* argv[])
{
    MD5 md5;
    bool tooFewArguments = true;
    char* path;
    if(cmdOptionExists(argv, argv+argc, "-h"))
    {
        tooFewArguments = false;
        cout << "TimeHash (thash) by Noscio." << endl << "www.noscio.ml | noscio@web.de" << endl << endl << "Usage: " << endl << "Check files with thash-public-keys stored in a file (for example 'hashfile.txt'):" << endl << "    " << "thash -f hashfile.txt" << endl << "Create a new dataset in the thash database (for example 'file.txt':" << endl << "    " << "thash -c file.txt" << endl;
    }
    if(cmdOptionExists(argv, argv+argc, "-f"))
    {
        tooFewArguments = false;
        path = getCmdOption(argv, argv + argc, "-f");
        string line;
        ifstream myfile (path);
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                md5.Init();
                stringstream rstream;
                size_t pos = line.find(" ");
                string thash = line.substr(0,pos);
                string fpath = line.substr(pos+1);
                string str(fpath);
                char * writable = new char[str.size() + 1];
                std::copy(str.begin(), str.end(), writable);
                writable[str.size()] = '\0'; // don't forget the terminating 0
                string hash(md5.digestFile(writable));
                // don't forget to free the string after finished using it
                delete[] writable;
                str.clear();
                stringstream ss;
                ss << "/test.php?k=" << thash << "&f=" << hash;
                //cout << ss.str().c_str() << endl;
                try
                {
                    boost::asio::io_service io_service;
    
                    // Get a list of endpoints corresponding to the server name.
                    tcp::resolver resolver(io_service);
                    tcp::resolver::query query("thash.square7.de", "http");
                    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
                    tcp::resolver::iterator end;

                    // Try each endpoint until we successfully establish a connection.
                    tcp::socket socket(io_service);
                    boost::system::error_code error = boost::asio::error::host_not_found;
                    while (error && endpoint_iterator != end)
                    {
                        socket.close();
                        socket.connect(*endpoint_iterator++, error);
                    }
                    if (error)
                    {
                        throw boost::system::system_error(error);
                    }
                    // Form the request. We specify the "Connection: close" header so that the  
                    // server will close the socket after transmitting the response. This will  
                    // allow us to treat all data up until the EOF as the content.
                    boost::asio::streambuf request;
                    std::ostream request_stream(&request);
                    request_stream << "GET " << ss.str().c_str() << " HTTP/1.0\r\n";
                    request_stream << "Host: " << "thash.square7.de" << "\r\n";
                    request_stream << "Accept: */*\r\n";
                    request_stream << "Connection: close\r\n\r\n";
    
                    // Send the request.
                    boost::asio::write(socket, request);
    
                    // Read the response status line.
                    boost::asio::streambuf response;
                    boost::asio::read_until(socket, response, "\r\n");
                
                    // Check that response is OK.
                    std::istream response_stream(&response);
                    std::string http_version;
                    response_stream >> http_version;
                    unsigned int status_code;
                    response_stream >> status_code;
                    std::string status_message;
                    std::getline(response_stream, status_message);
                    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
                    {
                        std::cout << "Invalid response\n";
                        return 1;
                    }
                    if (status_code != 200)
                    {
                        std::cout << "Response returned with status code " << status_code   << "\n";
                        return 1;
                    }
                    // Read the response headers, which are terminated by a blank line.
                    boost::asio::read_until(socket, response, "\r\n\r\n");
    
                    // Process the response headers.
                    std::string header;
                    while (std::getline(response_stream, header) && header != "\r")
                    //std::cout << header << "\n";
                    //std::cout << "\n";
    
                    // Write whatever content we already have to output.
                    if (response.size() > 0)
                    {
                        rstream << &response;
                    }
                    // Read until EOF, writing data to output as we go.
                    while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
                    {
                        rstream << &response;
                        if (error != boost::asio::error::eof)
                        {
                            throw boost::system::system_error(error);
                        }
                    }
                    hash.clear();
                }   
                catch (std::exception& e)
                {
                    std::cout << "Exception: " << e.what() << "\n";
                }
                size_t found=rstream.str().find("true1");
                if (found!=std::string::npos)
                {
                    cout << fpath << ": valide" << endl;
                }
                else
                {
                    cout << fpath << ": not valide" << endl;
                    //cout << "Hash: " << hash << " ; Path: " << fpath << endl;
                }
            }
            myfile.close();
        }
        else
        {
            cout << "ERROR: Unable to open file" << endl;
            return -1;
        }
    }
    if(cmdOptionExists(argv, argv+argc, "-c"))
    {
        tooFewArguments = false;
        path = getCmdOption(argv, argv + argc, "-c");
        stringstream rstream;
        stringstream ss1;
        ss1 << path;
        string str = ss1.str();
        char * writable = new char[str.size() + 1];
        std::copy(str.begin(), str.end(), writable);
        writable[str.size()] = '\0'; // don't forget the terminating 0
        string hash(md5.digestFile(writable));
        // don't forget to free the string after finished using it
        delete[] writable;
        stringstream ss;
        ss << "/create.php?f=" << hash;
        //cout << ss.str().c_str() << endl;
        try
        {
                boost::asio::io_service io_service;

                // Get a list of endpoints corresponding to the server name.
                tcp::resolver resolver(io_service);
                tcp::resolver::query query("thash.square7.de", "http");
                tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
                tcp::resolver::iterator end;

                // Try each endpoint until we successfully establish a connection.
                tcp::socket socket(io_service);
                boost::system::error_code error = boost::asio::error::host_not_found;
                while (error && endpoint_iterator != end)
                {
                    socket.close();
                    socket.connect(*endpoint_iterator++, error);
                }
                if (error)
                {
                        throw boost::system::system_error(error);
                    }
                    // Form the request. We specify the "Connection: close" header so that the  
                    // server will close the socket after transmitting the response. This will  
                    // allow us to treat all data up until the EOF as the content.
                    boost::asio::streambuf request;
                    std::ostream request_stream(&request);
                    request_stream << "GET " << ss.str().c_str() << " HTTP/1.0\r\n";
                    request_stream << "Host: " << "thash.square7.de" << "\r\n";
                    request_stream << "Accept: */*\r\n";
                    request_stream << "Connection: close\r\n\r\n";
    
                    // Send the request.
                    boost::asio::write(socket, request);
    
                    // Read the response status line.
                    boost::asio::streambuf response;
                    boost::asio::read_until(socket, response, "\r\n");
                
                    // Check that response is OK.
                    std::istream response_stream(&response);
                    std::string http_version;
                    response_stream >> http_version;
                    unsigned int status_code;
                    response_stream >> status_code;
                    std::string status_message;
                    std::getline(response_stream, status_message);
                    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
                    {
                        std::cout << "Invalid response\n";
                        return 1;
                    }
                    if (status_code != 200)
                    {
                        std::cout << "Response returned with status code " << status_code   << "\n";
                        return 1;
                    }
                    // Read the response headers, which are terminated by a blank line.
                    boost::asio::read_until(socket, response, "\r\n\r\n");
    
                    // Process the response headers.
                    std::string header;
                    while (std::getline(response_stream, header) && header != "\r")
                    //std::cout << header << "\n";
                    //std::cout << "\n";
    
                    // Write whatever content we already have to output.
                    if (response.size() > 0)
                    {
                        rstream << &response;
                    }
                    // Read until EOF, writing data to output as we go.
                    while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
                    {
                        rstream << &response;
                        if (error != boost::asio::error::eof)
                        {
                            throw boost::system::system_error(error);
                        }
                    }
                }   
                catch (std::exception& e)
                {
                    std::cout << "Exception: " << e.what() << "\n";
                }
                size_t found=rstream.str().find("public key: ");
                string output = rstream.str().substr(found);
                cout << ReplaceAll(output,string("<br>"),string("\n")) << endl;
        }
        if(tooFewArguments)
        {
            cout << "ERROR: too few arguments!" << endl;
        }
    
    return 0; 
}
char* getCmdOption(char ** begin, char ** end, const string & option)
{
    char ** itr = find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}
bool cmdOptionExists(char** begin, char** end, const string& option)
{
    return find(begin, end, option) != end;
}
std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
