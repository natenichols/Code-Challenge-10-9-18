#include <iostream>
#include <map>
#include <string>
#include <iostream>
#include <functional>
#include <fstream>
#include <stdexcept>

//
// supporting tools and software
//
// Validate and test your json commands
// https://jsonlint.com/

// RapidJSON : lots and lots of examples to help you use it properly
// https://github.com/Tencent/rapidjson
//

// std::function
// std::bind
// std::placeholders
// std::map
// std::make_pair

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

bool g_done = false;

//
// TEST COMMANDS
//
auto help_command = R"(
 {"command":"help","payload": {"usage":"Enter json command in 'command':'<command>','payload': { // json payload of arguments }"}}
)";

auto exit_command = R"(
 {"command":"exit","payload": {"reason":"Exiting program on user request."}}
)";

auto power_command = R"(
 {"command":"calcPower","payload": {"voltage": 10, "current": 2}}
)";

auto log_command = R"(
 {"command":"logValue","payload": {"data":[1,2,3,4]}}
)";

class Controller {
public:
    bool help(rapidjson::Value &payload)
    {
        cout << "Controller::help: command: \n";

        cout << payload["usage"].GetString() << endl;

        return true;
    }

    bool exit(rapidjson::Value &payload)
    {
        cout << "Controller::exit: command: \n";

        g_done = true;

	cout << payload["reason"].GetString() << endl;

        return true;
    }

    //my Commands
    //reads voltage and current measurements from terminal and computes power
    bool calcPower(rapidjson::Value &payload)
    {
	cout << "Controller::calcPower: command: \n";

	int voltage = payload["voltage"].GetInt();
	int current = payload["current"].GetInt();

	cout << "Voltage: " << voltage << "\tCurrent: " << current << endl;
	cout << "Power computed is: " << current * voltage << endl;

	return true;
    }

    //takes an array and outputs it to a csv (i.e. to graph in excel or something)
    bool logValue(rapidjson::Value &payload)
    {
	cout << "Controller::logValue: command: \n";
	
	ofstream outFile;
	outFile.open("myData.csv", std::fstream::app);

	for(SizeType i = 0; i < payload["data"].Size(); i++){
	    outFile << payload["data"][i].GetInt() << endl;
	}
	outFile.close();
	
	cout << "Data has been logged to myData.csv" << endl;
	
    }

    // implement 2-3 more commands
};

// gimme ... this is actually tricky
	// Note: Had to include functional library, because std::function takes a function as a type
// Bonus Question: why did I type cast this?
	//The bool isn't really a type cast its denoting the return type of the function which takes parameters(rapidjson::Value)
	//This is done because the methods being assigned to the Handler return bool values
typedef std::function<bool(rapidjson::Value &)> CommandHandler;

class CommandDispatcher {
public:
    // ctor - need impl
    CommandDispatcher()
    {
	
    }

    // dtor - need impl
    virtual ~CommandDispatcher()
    {
        // question why is it virtual? Is it needed in this case?
		//No, becuase nothing is inheriting from this Class
    }

    bool addCommandHandler(std::string command, CommandHandler handler)
    {
        cout << "CommandDispatcher: addCommandHandler: " << command << std::endl;

	//maps a command to a certain controller method (through a commandhandler)
        command_handlers_[command] = handler;	

        return true;
    }

    bool dispatchCommand(std::string command_json)
    {
        cout << "COMMAND: " << command_json << endl;

	//rapidjson object parses the command
        Document doc;
	
	//Throws runtime error if parsing does not work
	if(doc.Parse<0>(command_json.c_str()).HasParseError())
		throw(std::runtime_error("INVALID COMMAND"));

	//Throws error if there is no command in the json
	if(!doc.HasMember("command"))
		throw(std::runtime_error("ERROR: NO COMMAND IN JSON"));

	std::string command = doc["command"].GetString();

	//Throws error if the json command not in command_handlers_
	if(command_handlers_.find(command) == command_handlers_.end())
		throw(std::runtime_error("ERROR: NO COMMANDHANDLER FOR THIS COMMAND"));
	
	//calls the commandhandler associated with the command and passes in the payload
	command_handlers_[command](doc["payload"]);

        return true;
    }
private:

    // gimme ...
    std::map<std::string, CommandHandler> command_handlers_;

    // another gimme ...
    // Question: why delete these?

    // delete unused constructors
    CommandDispatcher (const CommandDispatcher&) = delete;
    CommandDispatcher& operator= (const CommandDispatcher&) = delete;
};

int main()
{
    std::cout << "COMMAND DISPATCHER: STARTED" << std::endl;

    CommandDispatcher command_dispatcher;
    Controller controller;                 // controller class of functions to "dispatch" from Command Dispatcher

    // Implement
    // add command handlers in Controller class to CommandDispatcher using addCommandHandler
 
    //placeholder so parameters can be passed in later
    using std::placeholders::_1;
	
    //create and add Commandhandlers for Controller.exit
    CommandHandler exit_handler = std::bind(&Controller::exit, controller, _1);
    command_dispatcher.addCommandHandler("exit", exit_handler);

    //create and add Commandhandlers for Controller.help
    CommandHandler help_handler = std::bind(&Controller::help, controller, _1);
    command_dispatcher.addCommandHandler("help", help_handler);

    //create and add CommandHandlers for Controller.calcpower
    CommandHandler power_handler = std::bind(&Controller::calcPower, controller, _1);
    command_dispatcher.addCommandHandler("calcPower", power_handler);

    //create and add CommandHandlers for Controller.logValue
    CommandHandler log_handler = std::bind(&Controller::logValue, controller, _1);
    command_dispatcher.addCommandHandler("logValue", log_handler);


    // gimme ...
    // command line interface
    string command;
    while( ! g_done ) {
        cout << "COMMANDS: {\"command\":\"exit\", \"payload\":{\"reason\":\"User requested exit.\"}}\n";
        cout << "\tenter command : ";
        getline(cin, command);
	try{
        	command_dispatcher.dispatchCommand(command);
	}
	catch(std::runtime_error &rte){
		cout << rte.what() << endl;
	}
    }

    std::cout << "COMMAND DISPATCHER: ENDED" << std::endl;
    return 0;
}
