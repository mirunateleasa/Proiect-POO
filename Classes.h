#pragma once
#include <iostream>
#include <string>
using namespace std;

//Exceptions:
class InvalidCommandException
{
	string description = "";
	int errCode = 0;
public:
	InvalidCommandException(string Description, int ErrCode)
	{
		this->description = Description;
		this->errCode = ErrCode;
	}

	InvalidCommandException()
	{

	}

	string getDescription()
	{
		return this->description;
	}

	int getErrCode()
	{
		return this->errCode;
	}
};


class UsefulFunctions
{
public:
	const char* CAPS = "ABCDEFGHIKLMNOPRSTUVXYZ";
	const char* SIGNS = "(), ";
	const char* NoCAPS = "abcdefghijklmnoprstuvxyz";
	string extract(string str, char a, char b, int& counter1, int& counter2) {
		
		string subString;
		counter1 = str.find_first_of(a);
		counter2 = str.find_first_of(b);
		subString = str.substr(counter1, counter2 - counter1);
		return subString;
	}

	bool findChars(string command, const char* chars) {
		int i = 0;
		int counter = 0;
		while (i < strlen(chars)) {
			for (int j = 0; j < command.length(); j++) {
				if (chars[i] == command[j])
					counter++;
			}
			i++;
		}
		if (counter)
			return true;
		else return false;
	}

	bool checkAsciiValue(string str, char a, char b) {
		int counter = 0;
		for (int i = 0; i < str.length(); i++)
			if (str[i]<a || str[i]>b)
				counter++;
		if (counter)
			return true;
		else return false;
	}

	int nrChars(string str, char a, int& counter) {
		counter = 0;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == a)
				counter++;
		}
		return counter;
	}

	string stringWithoutSpaces(string str) {
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		return str;
	}

	string subStringWithoutSpaces(string str)
	{
		int i = 0;
		string result=str;
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
			{
				i++;
			}
			str.erase(0, i);
		}
		result = str;
		return result;
	}

	string stringWithoutCommasOrSpaces(string str) {
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		int i = 0;
		while (i < str.length()) {
			if (str[i] == ',' && str[i + 1] == '(' && str[i - 1] == ')') {
				str.erase(i, 1);
				i--;
			}
			i++;
		}
		return str;
	}
};

class Command
{
	string name = "";
	string commandFirst = "";
	string commandSecond = "";
	UsefulFunctions function;

private:
	void setWords(string& name, string& commandFirst, string& commandSecond)
	{
		int counter1 = 0;
		int counter2 = 0;
		commandFirst = function.extract(name, name[0], ' ', counter1, counter2);
		name.erase(0, commandFirst.length() + 1);
		if (commandFirst == "CREATE" || commandFirst == "DROP" || commandFirst == "DISPLAY" || commandFirst == "INSERT")
		{
			commandSecond = function.extract(name, name[0], ' ', counter1, counter2);
			name.erase(0, commandSecond.length() + 1);
		}
	}

	void checkCommand(string commandFirst, string commandSecond)
	{
		if (commandSecond == "TABLE")
		{
			if (commandFirst != "CREATE" && commandFirst != "DROP" && commandFirst != "DISPLAY")
			{
				throw new InvalidCommandException("No such command!", 0);
			}
		}
		else {
			if (commandSecond == "INDEX")
			{
				if (commandFirst != "CREATE" && commandFirst != "DROP")
				{
					throw new InvalidCommandException("No such command!", 0);
				}
			}
			else {
				if (commandSecond == "")
				{
					if (commandFirst != "UPDATE" && commandFirst != "SELECT" && commandFirst != "DELETE")
					{
						throw new InvalidCommandException("No such command!", 0);
					}
				}
				else
				{
					if (commandSecond == "INTO")
					{
						if (commandFirst != "INSERT")
							throw new InvalidCommandException("No such command!", 0);
					}
					else throw new InvalidCommandException("No such command!", 0);
				}

			}
		}
	}

public:
	//setters & getters
	void setName(string commandName)
	{
		this->name = commandName;
		setWords(this->name, commandFirst, commandSecond);
		checkCommand(commandFirst, commandSecond);
	}
	string getName()
	{
		return this->name;
	}
	string getFirstWord()
	{
		return this->commandFirst;
	}
	string getSecondWord()
	{
		return this->commandSecond;
	}

	//operators
	//operators
	string operator -(string substring)
	{
		string copy = this->name;
		copy = this->name.erase(0, substring.length());
		return copy;
	}
	Command operator=(Command command)
	{
		Command copy;
		copy.setName(command.name);
		string word1;
		string word2;
		copy.setWords(command.name, word1, word2);
		return copy;
	}
	Command operator--(int) {
		Command command;
		command = *this;
		this->name.erase(1, 6);
		return command;
	}
	Command operator--() {
		this->name.erase(0, 6);//variabile??);
		return *this;
	}
	bool operator ==(Command command) {
		if (this->getName() == command.getName()) {
			return true;
		}
		else {
			return false;
		}
	}
	friend void operator <<(ostream& out, Command command);
	friend void operator >>(istream& input, Command& command);
	friend string operator -(string string1, string string2);

};

//substracting a string from another string
string operator -(string string1, string string2)
{
	string result;
	result = string1.erase(string1[0], string2.length());
	return result;
}

//reading a command from a file
void readCommand(ifstream& file)
{
	char buffer[100];
	//aici depinde mult de cum vrea el sa citeasca comanda, daca da size-ul comenzii etc deci inca nu putem sa il facem? cred
}


//writing a command on the keyboard
void operator >>(istream& input, Command& command)
{
	cout << endl << "--------------------------------------";
	cout << endl << "Please enter command: ";
	string name;
	getline(input, name);
	command.setName(name);
}

//readin a command from the keyboard
void operator <<(ostream& out, Command command) {
	out << endl << "--------------------------------------";
	out << endl << "Operator Command:" << command.getName();
}

//THE COMMANDS

//1. DROP
//MERGE PENTRU TOATE EXEMPLELE
class DropCommand
{
	Command command;
	UsefulFunctions function;
public:
	DropCommand(Command command)
	{
		checkDrop(command.getName());

	}
private:
	void checkDrop(string commandName)
	{
		commandName = function.subStringWithoutSpaces(commandName);
		if (function.findChars(commandName, function.CAPS) == 1 || function.findChars(commandName, function.SIGNS) == 1 || function.findChars(commandName, function.NoCAPS) == 0 || function.findChars(commandName, " ")==true)
		{
			throw new InvalidCommandException("The DROP command has the wrong table name", 0);
		}
		else
		{
			cout << "DONE";
		}
	}
};

//2. DISPLAY
//MERGE PENTRU TOATE EXEMPLELE
class DisplayCommand
{
	Command command;
	string table_name = " ";
	UsefulFunctions function;
public:

	DisplayCommand(Command command)
	{
		checkDisplay(command.getName());
	}
private:
	void checkDisplay(string commandName)
	{
		commandName = function.subStringWithoutSpaces(commandName);
		if (function.findChars(commandName, function.CAPS) == 1 || function.findChars(commandName, function.SIGNS) == 1 || function.findChars(commandName, function.NoCAPS) == 0 || function.findChars(commandName, " ")==true)
		{
			throw new InvalidCommandException("The DISPLAY command has the wrong table name", 0);
		}
		else
		{
			cout << "DONE";
		}
	}
};

//3.CREATE
//NU MERGE PENTRU IF NOT EXIST
class CreateCommand
{
	Command command;
	UsefulFunctions function;
public:
	CreateCommand(Command command)
	{
		ValidareSerioasaCreate(command.getName());
	}
private:

	void createParamVandPars(string command, string& cName, string& cType, int& cDim, string& defaultVal) {
		// we strip the first column details by   ' ( '   ' ) ' 
		string editable = command.substr(command.find_first_not_of('('), command.find_last_of(')') - 1);
		string parametriiTabel;
		int counter;
		int contorEditable = 0;
		int limitEditable = function.nrChars(editable, ',', counter) + 1;
		if (function.nrChars(editable, ',', counter) != 3) {
			throw new InvalidCommandException("Too few terms inside the brackets", 0);
		}
		// we make sure we get rid of the spaces too 
		editable = function.stringWithoutSpaces(editable);
		// we  will now take every parameter to check if its the right data type 
		while (contorEditable < limitEditable) {
			parametriiTabel = editable.substr(0, editable.find_first_of(','));
			// for the first param we need a name so only text and after that we pass it to the cName
			if (contorEditable == 0) {
				if (function.checkAsciiValue(parametriiTabel, 'a', 'z') != 0) {
					throw new InvalidCommandException("Is not a text", 0);
				}
				else {
					cName = parametriiTabel;
					cout << endl;
					cout << endl << "** Primul parametrul este nume *" << cName << "* si este valid ";
				}
			}
			//for the 2nd param we need a text but this time denoting one of the types, check type and pass it to the cType 
			if (contorEditable == 1) {
				if (parametriiTabel == "text" || parametriiTabel == "integer" || parametriiTabel == "float") {
					cType = parametriiTabel;
					cout << endl;
					cout << endl << "** Parametrul al doilea este type*" << cType << "* si este valid ";
				}
				else {
					throw new InvalidCommandException("Second parameter has an error", 0);
				}

			}
			//for the 3rd param we need an integer, we check to see if only digits and convert string to int 
			if (contorEditable == 2) {
				if (function.checkAsciiValue(parametriiTabel, '0', '9') == 0) {
					cDim = stoi(parametriiTabel);
					cout << endl;
					cout << endl << "** Parametrul al treilea este int*" << cDim << "* si este valid ";
				}
				else {
					throw new InvalidCommandException("Wrong third parameter", 0);
				}
			}
			// here i dont know for sure what checks needs to be done but the passing to the cValue its made 
			if (contorEditable == 3) {
				if (parametriiTabel.find_first_of('’')) {
					parametriiTabel.erase(remove(parametriiTabel.begin(), parametriiTabel.end(), '’'), parametriiTabel.end());
				}
				defaultVal = parametriiTabel;
				cout << endl;
				cout << endl << "** Parametrul al 4 lea este default(string) *" << parametriiTabel << "* si este valid";
			}
			editable.erase(0, parametriiTabel.length() + 1);
			contorEditable++;
		}
	}

	void ValidareSerioasaCreate(string commanda) {// string& name, string& type, int& dim, string& value) {
		string newCommand = commanda;
		string editable;
		string parametriiTabel;
		string copyEditable;
		// parametrii ce vor putea fi dati si de sus cand doriti 
		string name;
		string type;
		int dim;
		string value;
		// next
		// in order to check everything first we strip the table name until ( by any spaces in order to check it lexically 
		editable = newCommand.substr(0, newCommand.find_first_of('('));
		copyEditable = function.stringWithoutSpaces(editable);
		if (function.nrChars(copyEditable, 'I', dim) == 2)
		{
			int noLettersTableName = 0;
			noLettersTableName = copyEditable.find_first_of('I');
			if (copyEditable.compare(copyEditable.find_first_of('I'), 11, "IFNOTEXISTS") == 0 && copyEditable.length() == (noLettersTableName + 11)) {
				//here we should also check the str.substr(0,noLettersTable) with a table name to see if the table exists or not 
				copyEditable = copyEditable.erase(copyEditable.find_first_of('I'), 11);
				cout << endl << "We create new table " << copyEditable;
			}
		}
		
		if (function.checkAsciiValue(copyEditable, 'a', 'z') != 0) {
			throw new InvalidCommandException("Wrong table name", 0);
		}
		else {
			int counter;
			newCommand.erase(0, editable.length());
			if ((function.nrChars(newCommand, '(', counter) != function.nrChars(newCommand, ')', counter)) || ((function.nrChars(newCommand, '(', counter) + (function.nrChars(newCommand, ')', counter))) % 2 != 0)) {
				throw new InvalidCommandException("Wrong number of parantesis!", 0);
			}
			//after it was checked, if we have only one column we call the function once 
			else {
				if (function.nrChars(newCommand, '(', counter) == 1) {
					createParamVandPars(newCommand, name, type, dim, value);
					cout << "DONE!";
				}
				else   // else we will strip the columns by the commas and spaces dividing them and then call the functions one by one while also deleting from the command string
				{
					newCommand = newCommand.substr(newCommand.find_first_of('(') + 1, newCommand.find_last_of(')') - 1);
					newCommand = function.stringWithoutCommasOrSpaces(newCommand);
					while (newCommand.length()) {

						parametriiTabel = newCommand.substr(0, newCommand.find_first_of(')') + 1);
						createParamVandPars(parametriiTabel, name, type, dim, value);
						newCommand.erase(0, parametriiTabel.length());
					}
					cout << endl << "DONE!";
				}
			}

		}
	}
};


//4. SELECT
//MERGE PENTRU TOATE EXEMPLELE
class SelectCommand
{
	Command command;
	UsefulFunctions function;
public:
	SelectCommand(Command command)
	{
		checkSelect(command.getName());
	}
private:
	void checkSelect(string commandName)
	{
		int counter1 = 0, counter2 = 0;
		commandName = function.subStringWithoutSpaces(commandName);
		if (commandName[0] != 'A')
		{
			string selectedValues = function.extract(commandName, commandName[0], commandName[commandName.find_last_of(')') + 1], counter1, counter2);
			commandName.erase(0, selectedValues.length());
			//check the selected values
			if (selectedValues[0] != '(' || selectedValues[selectedValues.length() - 1] != ')' || selectedValues=="()")
			{
				throw new InvalidCommandException("Not a column", 0);
			}
			else
			{
				while (selectedValues != "(")
				{

					//check every column between ()
					int counter11 = 0, counter12 = 0;
					string column;
					if (selectedValues.find(',') != string::npos)
					{
						column = function.extract(selectedValues, selectedValues[1], selectedValues[selectedValues.find_first_of(',')], counter11, counter12);
					}
					else
					{
						column = function.extract(selectedValues, selectedValues[1], selectedValues[selectedValues.find_first_of(')')], counter11, counter12);
					}
					if (function.findChars(column, function.CAPS) == true || function.findChars(column, function.SIGNS) == true || function.findChars(column, " ") == true)
					{
						throw new InvalidCommandException("Not proper column name", 0);
					}
					selectedValues.erase(counter11, counter12);
					selectedValues = function.subStringWithoutSpaces(selectedValues);
				}
				commandName = function.subStringWithoutSpaces(commandName);
			}
		}
		else
		{
			counter1 = counter2 = 0;
			if (function.extract(commandName, commandName[0], commandName[3], counter1, counter2) != "ALL")
			{
				throw new InvalidCommandException("HASN't GOT FROM KEYWORD", 0);
			}
			commandName.erase(0, 3);
			commandName = function.subStringWithoutSpaces(commandName);
		}
		counter1 = counter2 = 0;
		if (function.extract(commandName, commandName[0], commandName[4], counter1, counter2) != "FROM")
		{
			throw new InvalidCommandException("HASN't GOT FROM KEYWORD", 0);
		}
		commandName.erase(0, 4);
		commandName = function.subStringWithoutSpaces(commandName);
		counter1 = counter2 = 0;
		string tableName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		if (function.findChars(tableName, function.CAPS) == true || function.findChars(tableName, function.SIGNS) == true || function.findChars(tableName, " ") == true)
		{
			throw new InvalidCommandException("Not proper table name", 0);
		}
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		if (commandName != "")
		{
			counter1 = counter2 = 0;
			if (function.extract(commandName, commandName[0], commandName[5], counter1, counter2) != "WHERE")
			{
				throw new InvalidCommandException("HASN't GOT WHERE KEYWORD", 0);
			}
			commandName.erase(counter1, counter2);
			commandName = function.subStringWithoutSpaces(commandName);
			counter1 = counter2 = 0;
			string column = function.extract(commandName, commandName[0], ' ', counter1, counter2);
			if (function.findChars(column, function.CAPS) == true || function.findChars(column, function.SIGNS) == true || function.findChars(column, " ") == true)
			{
				throw new InvalidCommandException("Not proper column name", 0);
			}
			commandName.erase(counter1, counter2);
			commandName = function.subStringWithoutSpaces(commandName);
			counter1 = counter2 = 0;
			if (function.extract(commandName, commandName[0], commandName[1], counter1, counter2) != "=")
			{
				throw new InvalidCommandException("HASN't GOT = SIGN", 0);
			}
			commandName.erase(counter1, counter2);
			commandName = function.subStringWithoutSpaces(commandName);
			counter1 = counter2 = 0;
			if (function.findChars(commandName, function.CAPS) == true || function.findChars(commandName, function.SIGNS) == true || function.findChars(commandName, " ") == true)
			{
				throw new InvalidCommandException("Not proper value name OR multiple conditions", 0);
			}
		}
		cout << "DONE!";
	}
};

//5. UPDATE
//MERGE PENTRU TOATE EXEMPLELE
class UpdateCommand
{
	Command command;
	UsefulFunctions function;
public:
	UpdateCommand(Command command)
	{
		checkUpdate(command.getName());
	}
private:
	void checkUpdate(string commandName)
	{
		//check table name
		int counter1 = 0, counter2 = 0;
		string tableName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		commandName.erase(counter1, counter2);
		commandName=function.subStringWithoutSpaces(commandName);
		if ((tableName.find("(") != tableName.npos) || (tableName.find(" ") != tableName.npos) || (tableName.find(",") != tableName.npos))
		{
			throw new InvalidCommandException("The UPDATE command has the wrong table name", 0);
		}
		//check SET KEYWORD
		counter1 = 0, counter2 = 0;
		string setKeyword = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		commandName.erase(counter1, counter2);
		commandName=function.subStringWithoutSpaces(commandName);
		if (setKeyword != "SET")
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the SET keyword", 0);
		}
		//check column name
		counter1 = 0, counter2 = 0;
		string columnName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		commandName.erase(counter1, counter2);
		commandName=function.subStringWithoutSpaces(commandName);
		if (function.findChars(columnName, function.CAPS) == 1 || function.findChars(columnName, function.SIGNS) == 1)
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the proper column name", 0);
		}
		//check =
		counter1 = 0, counter2 = 1;
		if (commandName[0] != '=')
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the EQUAL sign", 0);
		}
		commandName.erase(counter1, counter2);
		commandName=function.subStringWithoutSpaces(commandName);
		//check value to be changed
		counter1 = 0, counter2 = 0;
		string columnValue = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		commandName.erase(counter1, counter2);
		commandName=function.subStringWithoutSpaces(commandName);
		if (function.findChars(columnValue, function.SIGNS) == true)
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the proper column value sign", 0);
		}
		//check WHERE
		counter1 = 0, counter2 = 5;
		string WHERE = commandName.substr(0, 5);
		commandName.erase(counter1, counter2);
		commandName=function.subStringWithoutSpaces(commandName);
		if (WHERE != "WHERE")
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the WHERE keyword!", 0);
		}
		//check columnName to be changed
		counter1 = 0, counter2 = 0;
		columnName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		commandName.erase(counter1, counter2);
		commandName=function.subStringWithoutSpaces(commandName);
		if (function.findChars(columnName, function.CAPS) == 1 || function.findChars(columnName, function.SIGNS) == 1)
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the proper column name", 0);
		}
		//check equal AGAIN
		counter1 = 0, counter2 = 1;
		if (commandName[0] != '=')
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the EQUAL sign", 0);
		}
		commandName.erase(counter1, counter2);
		commandName=function.subStringWithoutSpaces(commandName);
		//check column value to be updated
		counter1 = 0, counter2 = 0;
		columnValue = function.extract(commandName, commandName[0], commandName[commandName.length()], counter1, counter2);
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		if (function.findChars(columnValue, function.SIGNS) == 1)
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the proper column value sign", 0);
		}
		cout << "DONE!";
	}
};

//6.DELETE
//MERGE PENTRU TOATE EXEMPLELE
class DeleteCommand {

	Command command;
	UsefulFunctions function;
public:
	DeleteCommand(Command command)
	{
		checkDelete(command.getName());
	}
private:
	void checkDelete(string commandName)  // "table_name WHERE column_name = value"
	{
		int counter1 = 0, counter2 = 0;
		//check FROM keyword
		if (function.extract(commandName, commandName[0], ' ', counter1, counter2) != "FROM")
		{
			throw new InvalidCommandException("The DELETE hasn't got the KEYWORD FROM", 0);
		}
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		//check table name
		counter1 = counter2 = 0;
		string tableName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		{
			if (function.findChars(tableName, function.CAPS) == 1 || function.findChars(tableName, function.SIGNS) == 1)
			{
				throw new InvalidCommandException("The DELETE hasn't got the proper table name", 0);
			}
		}
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		//set and check keyword WHERE
		counter1 = 0;
		counter2 = 0;
		string keyWord = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		if (keyWord != "WHERE")
		{
			throw new InvalidCommandException("The DELETE hasn't got the KEYWORD", 0);
		}
		//check column name
		counter1 = 0;
		counter2 = 0;
		string columnName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		if (function.findChars(columnName, function.CAPS) == 1 || function.findChars(columnName, function.SIGNS) == 1)
		{
			throw new InvalidCommandException("The DELETE command hasn't got the proper column name", 0);
		}
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		//check =
		counter1 = 0, counter2 = 1;
		if (commandName[0] != '=')
		{
			throw new InvalidCommandException("The DELETE command hasn't got the EQUAL sign", 0);
		}
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		//check value to be changed
		string columnValue = commandName;
		if (function.findChars(columnValue, function.SIGNS) == 1)
		{
			throw new InvalidCommandException("The DELETE command hasn't got the proper column value sign", 0);
		}
		cout << "DONE!";
	}
};

//7.INSERT
//7.INSERT
class InsertCommand
{
	//o fac eu pe asta
	Command command;
	UsefulFunctions function;
public:
	InsertCommand(Command command) {
		insertValidation(command.getName());
	}
private:


		void insertValidation(string Command) {
		string newCommand = Command;
		string editable;
		string parametriiTabel;
		string copyEditable;

		int noParam = 0;
		int startPoint = 0;
		int numberOfParam = 4; // ATENTIE !! ACEST NUMAR SE VA PRIMI DIN CREATE TABLE la APELARE CUMVA

		//validare paranteze 
		if (function.nrChars(newCommand, '(', noParam) != 1 && function.nrChars(newCommand, ')', noParam) != 1) {
			throw new InvalidCommandException("paranteze gresite ", 0);
		}

		editable = newCommand.substr(0, newCommand.find_first_of('('));
		copyEditable = function.stringWithoutSpaces(editable);

		//aici in parametrii avem numele tabelului: studenti
		parametriiTabel = copyEditable.substr(0, copyEditable.find_first_of('V'));
		if (parametriiTabel.length() == 0)
			throw new InvalidCommandException("nu exista nume tabe ", 0);
		else
			cout << endl << "Numele tabelului in care se vor face modificari este " << parametriiTabel;

		//aici putem face o validare daca exista tabelul sau nu  , nu voi mai face validare pt corectitudinea tabelului pt ca ar trb deja sa fie creat deci sa existe deci ajunge doar o comparatie simpla
		//
		//acum facem o validare lexicografica pt VALUES -

		if (copyEditable.compare(copyEditable.find_first_of('V'), 6, "VALUES") == 0 && copyEditable.length() == (parametriiTabel.length() + 6)) {
			cout << endl << "Validare reusita pana la paranteza";
		}
		else {
			throw new InvalidCommandException("wrong command ", 0);
		}

		newCommand.erase(0, editable.length()); // newCommand devine (1,"John","1001")
		editable = newCommand.substr(newCommand.find_first_not_of('('), newCommand.find_last_of(')') - 1); //editable devine 1,"John","10001"
		editable = function.stringWithoutSpaces(editable);  // se elimina spatiile desi in cerinta reiese ca nu ar exista spatii 
		noParam = function.nrChars(editable, ',', noParam) + 1;  // in functie de nr de virgule primim nr parametrii  no=3

		// AICI MAI ESTE NEVOIE DE O VALIDARE CARE SA VERIFICE DACA NUMARUL COLOANELOR RESPECTA NUMARUL VIRGULELOR + 1 CARE SE VA AFLA IN FUNCTIE DE VALOAREA DIN CREATE A TABELULUI 
		// INSERT INTO studenti VALUES (1,”John” ”1001”)  -- exemplul ruleaza desi e gresit.

		// now we go parameter by parameter
		while (startPoint < noParam) {
			parametriiTabel = editable.substr(0, editable.find_first_of(','));
			int temp = 0;
			if (function.nrChars(parametriiTabel, '"', temp)) {
				string temp = parametriiTabel.substr(1, parametriiTabel.find_last_of('"') - 1);
				cout << endl << "Parametrul tabel la iteratie " << startPoint << " este " << temp << " si este tip string";
			}
			else {
				float value;
				string temporary = parametriiTabel;
				if (function.nrChars(temporary, '.', temp) > 1)
					throw new InvalidCommandException("too many points", 0);
				else if (function.nrChars(temporary, '.', temp) == 1) {
					temporary = temporary.erase(temporary.find_first_of('.'), 1);
				}
				if (function.checkAsciiValue(temporary, '0', '9')) {
					throw new InvalidCommandException("nu este string dar are litere", 0);
				}
				else {
					value = stof(parametriiTabel);
					cout << endl << "Parametrul tabel la iteratie " << startPoint << " este floatul " << value;
				}
			}
			editable.erase(0, parametriiTabel.length() + 1);
			startPoint++;
		}

	}
};


//PARSER-UL
class Parser
{
	Command command;
//	UsefulFunctions function;
	string name = command.getName();
	string FirstWord = "";
	string SecondWord = "";
public:

	Parser(Command command)
	{
		this->FirstWord = command.getFirstWord();
		this->SecondWord = command.getSecondWord();
	}
	void Parse(Command command)
	{
		if (FirstWord == "CREATE")
		{
			CreateCommand object(command);
		}
		if (FirstWord == "DROP")
		{
			DropCommand object(command);
		}
		if (FirstWord == "DELETE")
		{
			DeleteCommand object(command);
		}
		if (FirstWord == "DISPLAY")
		{
			DisplayCommand object(command);
		}
		if (FirstWord == "UPDATE")
		{
			UpdateCommand object(command);
		}
		if (FirstWord == "SELECT")
		{
			SelectCommand object(command);
		}
		if (FirstWord == "INSERT")
		{
			InsertCommand object(command);
		}
	}

	friend class DisplayCommand;
};


