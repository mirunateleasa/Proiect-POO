//!!!!!!!!THE FILES CONTAINING THE TABLES ARE BINARY AND THEY HAVE THE FOLLOWING NAME FORMAT: table_name.bin (ex:Studenti.bin)

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;

enum FileType { BIN, TXT, CSV };

class File
{
	string nameOfFile = "";
	FileType type = TXT;
	int noLines = 0;
	string* lines;
public:
	File(string NameOfFile)
	{
		this->nameOfFile = NameOfFile;
		int counter1 = 0, counter2 = 0;
		if (this->nameOfFile.substr(this->nameOfFile.find_first_of('.'), 4) == ".txt")
		{
			this->type = TXT;
		}
		if (this->nameOfFile.substr(this->nameOfFile.find_first_of('.'), 4) == ".bin")
		{
			this->type = BIN;
		}
		if (this->nameOfFile.substr(this->nameOfFile.find_first_of('.'), 4) == ".csv")
		{
			this->type = CSV;
		}
	}

	File()
	{

	}

	File(File& oldFile)
	{
		this->nameOfFile = oldFile.nameOfFile;
		this->type = oldFile.type;
		this->noLines = oldFile.noLines;
		for (int i = 1; i < oldFile.noLines; i++)
		{
			this->lines[i] = oldFile.lines[i];
		}
	}

	int getNoLines()
	{
		return this->noLines;
	}

	int setNoLines(int noLines)
	{
		this->noLines = noLines;
	}

		void deleteTable(int i)
	{
		int noTables = stoi(this->lines[0]) - 2;
		string* result = new string[noTables + 1];
		result[0] = to_string(noTables + 1);
		int j = 1, k = 1;
		while (j <= noTables + 1)
		{
			if (j != i)
			{
				result[k] = lines[j];
				k++;
			}
			j++;
		}
		delete[]lines;
		lines = new string[noTables + 1];
		lines = result;
		this->noLines = noTables + 1;
	}

	void addTable(string tableName)
	{
		int noTables = stoi(this->lines[0]) - 1;
		string* result = new string[noTables + 2];
		result[0] = to_string(noTables + 2);
		int j = 1;
		for (int i = 1; i <= noTables; i++)
		{
			result[i] = lines[i];
		}
		result[noTables + 1] = tableName;
		delete[]this->lines;
		this->noLines++;
		this->lines = new string[noTables + 3];
		for (int i = 0; i < noTables + 2; i++)
			lines[i] = result[i];
	}

	string getTheLine(int i)
	{
		return lines[i];
	}

	int searchFile(const char numeTabel[])
	{
		int i = 0;
		for (i = 0; i < this->noLines; i++)
		{
			if (strcmp(lines[i].c_str(), numeTabel) == 0)
			{
				return i;
				break;
			}
		}
		return -1;
	}

	void setContent(ifstream& File)
	{
		string line;
		getline(File, line);
		int i = stoi(line);
		this->noLines = i;
		lines = new string[100];
		lines[0] = line;
		i = 1;
		while (File.eof() == false)
		{
			getline(File, line);
			lines[i] = line;
			i++;
		}
	}

	void writeObjectAsFile(ofstream file)
	{

	}
};

class UsefulFunctions
{
public:
	const char* CAPS = "ABCDEFGHIKLMNOPRSTUVXYZ";
	const char* SIGNS = "(), ";
	const char* NoCAPS = "abcdefghijklmnoprstuvxyz";
	const char* NUMBERS = "0123456789";


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
		string result = str;
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

	static void writeStringToBin(ofstream& binFile, string str)
	{
		int dim = str.size() + 1;
		binFile.write((char*)&dim, sizeof(int));
		binFile.write(str.c_str(), dim * sizeof(char));
	}


	static void readStringFromBin(ifstream& binFile, string &str)
	{
		int dim;
		binFile.read((char*)&dim, sizeof(int));
		char buffer[1000];
		binFile.read(buffer, dim * sizeof(char));
		str = string(buffer);
	}

	bool isTabelInFile(fstream& textFile, string tableName)
	{
		//we consider the file to be open
		string table = ".";
		while (getline(textFile, table))
		{
			if (table == tableName)
			{
				return true;
			}
		}
		if (table == ".")
			return false;
	}


};


//DECI am introdus enum asta ca sa putem sa salvam type-ul atributului. ca sa nu ma mai bag eu peste codul tau ca pierdem timp sa stau sa 
//inteleg ce ai facut tu acolo si de ce, eu cred ca cea mai buna varianta e sa chemi constructorul asta cu (string) inauntru, nu ala default
//in TableColumn. Practic comenzile noastre o sa scoata un atribut, "Alice", sa zicem, si o sa se cheme constructorul ColumnAttribute("Alice")
//care ii atribuie lui attribute valoarea "Alice" (mrg fara "") si lui type valoarea STRING. 
//ALSO chestia asta putea fi facuta pt toata coloana si nu ar mai fi fost nevoie sa o facem in atribut, pt ca toata coloana e de acelasi type
//ALSO eu cred ca nu are rost sa salvam valoarea in sine a atributului cu tipul care e. Gen nu cred ca are rost sa declaram "int valoare"
//pt ca daca vrem sa comparam doua atribute, attribute1.value="12" si attribute2.value="23" sa zicem, putem sa comparam direct stringurile
//"12" cu "23" si attribute1.type cu attribute2.type (putem sa facem asta intr-un operator ==). 
//Practic daca au acelasi type si aceeasi valoare sunt egale, nu trebuie sa comparam in sine 12 cu 23
//pwp
enum AttributeType { INTEGER, FLOAT, STRING };

class ColumnAttribute {
	string value;
	AttributeType type;
	UsefulFunctions function;
public:

	ColumnAttribute(string Attribute)
	{
		this->value = Attribute;
		if (this->value.find(function.NUMBERS) != string::npos)
		{
			//means the attribute is a number. finding what type of number:
			if (this->value.find(",") != string::npos || this->value.find(".") != string::npos)
			{
				//means it's float
				this->type = FLOAT;
			}
			else
			{
				//means it's an integer
				this->type = INTEGER;
			}
		}
		else
		{
			//means it's a string
			this->type = STRING;
		}
	}

	ColumnAttribute()
	{

	}

	void operator =(ColumnAttribute& newAttribute)
	{
		this->type = newAttribute.type;
		this->value = newAttribute.value;
	}

	string getValue()
	{
		return this->value;
	}

	void setAttributeString(string temp) {
		this->value = temp;
	}
	void setAttributeType(string type) {
		if (type == "FLOAT")
		{
			this->type = FLOAT;
		}
		if (type == "INTEGER")
		{
			this->type = INTEGER;
		}
		if (type == "STRING")
		{
			this->type = STRING;
		}
	}

	void writeAttirbuteToBin(ofstream& File)
	{
		//write the value (string)
		function.writeStringToBin(File, this->value);

		//write the type:
		//here, the type will not appear in the bin as enum (idk how to do this) => it will appear as a string.
		//the reading process will transform the string red from the file to an enum, so the type will never explicitly be other than enum to the user 
		if (this->type == FLOAT)
		{
			function.writeStringToBin(File, "FLOAT");
		}
		if (this->type == INTEGER)
		{
			function.writeStringToBin(File, "INTEGER");
		}
		if (this->type == STRING)
		{
			function.writeStringToBin(File, "STRING");
		}
	}

	void readAttributeFromBin(ifstream& File)
	{
	
		
		//reading the value (string)
		function.readStringFromBin(File, this->value);
		//reading the type (enum)
		//we read a string object from the bin file, as this is the way in which it has been written, and we transform it into an enum type
		//we need a buffer in which to read:
		string buffer;

		function.readStringFromBin(File, buffer);

		if (buffer == "FLOAT")
		{
			this->type = FLOAT;
		}
		if (buffer == "INTEGER")
		{
			this->type = INTEGER;
		}
		if (buffer == "STRING")
		{
			this->type = STRING;
		}

	}
	friend void operator <<(ostream& out, ColumnAttribute& attribute);
};

void operator <<(ostream& out, ColumnAttribute& attribute)
{
	out << endl;
	out << "Attribute value: " << attribute.value;
	out << " which is of type " << attribute.type;
}



class TableColumn {
	char columnName[100] = "";
	AttributeType columnType = INTEGER;
	int dimension = 0;
	string defaultValue = "";
	int noAttributes = 0;
	ColumnAttribute* attributes = nullptr;
	UsefulFunctions function;
public:
	TableColumn(const char* name, string type, int dimension, string defValue, int NoAttributes) {
		strcpy_s(this->columnName, 100, name);
		this->columnName[99] = '\0';
		if (this->defaultValue.find(function.NUMBERS) != string::npos)
		{
			//means the attribute is a number. finding what type of number:
			if (this->defaultValue.find(",") != string::npos || this->defaultValue.find(".") != string::npos)
			{
				//means it's float
				this->columnType = FLOAT;
			}
			else
			{
				//means it's an integer
				this->columnType = INTEGER;
			}
		}
		else
		{
			//means it's a string
			this->columnType = STRING;
		}
		this->dimension = dimension;
		this->defaultValue = defValue;
		//VALI: am adaugat nr de atribute pt ca nu putem sa avem un vector in binar fara sa stim exact dimensiunea (sau cel putin asa a zis Boja)
				//deci, in create o sa avem o functie care numara cate atribute are coloana 
				//aslo, de fiecare data cand facem un insert trebuie sa creasca nr de atribute
		this->noAttributes = NoAttributes;
	}

	TableColumn() {

	}
public:
	~TableColumn() {
		if (attributes != nullptr)
			delete[] attributes;
	}
	TableColumn(TableColumn& newColumn) {
		strcpy_s(this->columnName, 100, newColumn.columnName);
		this->columnName[99] = '\0';
		this->defaultValue = newColumn.defaultValue;
		this->columnType = newColumn.columnType;
		this->attributes = new ColumnAttribute[newColumn.dimension];
		for (int i = 0; i < newColumn.dimension; i++) {
			this->attributes[i] = newColumn.attributes[i];
		}
		this->dimension = newColumn.dimension;
	}
	void operator=(TableColumn& newColumn) {
		if (this != &newColumn) {
			if (this->attributes) {
				delete[] this->attributes;
			}
			strcpy(this->columnName, newColumn.columnName);
			this->defaultValue = newColumn.defaultValue;
			this->attributes = new ColumnAttribute[newColumn.noAttributes];
			this->columnType = newColumn.columnType;
			for (int i = 0; i < newColumn.noAttributes; i++) {

				this->attributes[i] = newColumn.attributes[i];
			}
			this->dimension = newColumn.dimension;
			this->noAttributes = newColumn.noAttributes;
		}

	}

	void operator <<(ColumnAttribute& attribute)
	{
		ColumnAttribute* newAttributes = new ColumnAttribute[this->noAttributes + 1];
		cout << this->noAttributes;
		for (int i = 0; i < this->noAttributes; i++)
		{
			cout << " "<<newAttributes[i];
			newAttributes[i] = this->attributes[i];
		}
		newAttributes[this->noAttributes] = attribute;
		this->noAttributes++;
		if (this->attributes)
			delete[]this->attributes;
		this->attributes = newAttributes;
	}
	void operator+(ColumnAttribute attribute) {
		ColumnAttribute* newAttributes = new ColumnAttribute[this->noAttributes + 1];
		for (int i = 0; i < this->dimension; i++)
		{
			newAttributes[i] = this->attributes[i];
			cout << endl << newAttributes[i];
		}
		newAttributes[this->dimension] = attribute; 
		this->dimension += 1;
		if (this->attributes) {
			delete[] this->attributes;
		}
		this->attributes = newAttributes;
	}

	void operator +=(ColumnAttribute& attribute)
	{
		*this << attribute;
	}

	ColumnAttribute *getAttribute(int i)
	{
		return &this->attributes[i];
	}

	int getNoAttributes()
	{
		return this->noAttributes;
	}


	void writeColumnToBin(ofstream& File)
	{
		//write the name(char):
		File.write((char*)&this->columnName, sizeof(char) * sizeof(TableColumn::columnName));
		//write the columnType (aici o sa fac dupa ce rezolvi tu Vali cu constructorul in functie de tipul atributului (vezi mai sus))
		if (this->columnType == FLOAT)
		{
			function.writeStringToBin(File, "FLOAT");
		}
		if (this->columnType == INTEGER)
		{
			function.writeStringToBin(File, "INTEGER");
		}
		if (this->columnType == STRING)
		{
			function.writeStringToBin(File, "STRING");
		}

		//write the dimension(int):
		File.write((char*)&this->dimension, sizeof(int));

		//write the default value (string):
		UsefulFunctions::writeStringToBin(File, this->defaultValue);

		//write the array of attributes (the pointer to it):
		File.write((char*)&this->noAttributes, sizeof(int));
		for (int i = 0; i < this->noAttributes; i++)
		{
			attributes[i].writeAttirbuteToBin(File);
		}
	}

	void readColumnFromBin(ifstream& File)
	{

		//read the name(char):
		File.read((char*)&this->columnName, sizeof(TableColumn::columnName) * sizeof(char));
		//read the columnType (aici o sa fac dupa ce rezolvi tu Vali cu constructorul in functie de tipul atributului (vezi mai sus))
		string buffer;
		function.readStringFromBin(File, buffer);
		if (buffer == "FLOAT")
		{
			this->columnType = FLOAT;
		}
		if (buffer == "INTEGER")
		{
			this->columnType = INTEGER;
		}
		if (buffer == "STRING")
		{
			this->columnType = STRING;
		}
		//read the dimension(int):
		File.read((char*)&this->dimension, sizeof(int));

		//write the default value (string):
		UsefulFunctions::readStringFromBin(File, this->defaultValue);

		//read the array of attributes (the pointer to it):
		File.read((char*)&this->noAttributes, sizeof(int));
		if (this->attributes != nullptr)
			delete[]this->attributes;
		this->attributes = new ColumnAttribute[this->noAttributes];
		for (int i = 0; i <this->noAttributes; i++)
		{
			this->attributes[i].readAttributeFromBin(File);

		}
	}

	//setteri si getteri:
	void setName(string Name)
	{
		strcpy(this->columnName, Name.c_str());
	}

	void setType(string type)
	{
		if (type == "integer")
			this->columnType = INTEGER;
		if (type == "text")
			this->columnType = STRING;
		if (type == "float")
			this->columnType = FLOAT;
	}

	void setDim(int dim)
	{
		this->dimension = dim;
	}

	void setDefault(string def)
	{
		this->defaultValue = def;
	}

	string getName()
	{
		return this->columnName;
	}

	AttributeType getType()
	{
		return this->columnType;
	}

	int getDim()
	{
		return this->dimension;
	}

	string getDefault()
	{
		return this->defaultValue;
	}

	friend class Table;
	friend void operator <<(ostream& out, TableColumn &column);
};

void operator <<(ostream& out, TableColumn &column)
{
	out << endl << "Name: ";
	for (int i = 0; i < strlen(column.columnName); i++)
		out << column.columnName[i];
	out << endl << "Type: " << column.columnType;
	out << endl << "Dimension: " << column.dimension;
	out << endl << "Default Value: " << column.defaultValue;
	out << endl << "No of attributes: " << column.noAttributes;
	if (column.noAttributes > 0)
	{
		out << endl << "The attributes: ";
		for (int i = 0; i < column.noAttributes; i++)
		{
			out << column.attributes[i];
		}
	}
}


class Table {
	char tableName[100] = "";
	int noColumns = 0;
	TableColumn* columns = nullptr;

public:
	Table(const char* tableName) {
		//i think here we might some sort of validation ??? 
		strcpy_s(this->tableName, 100, tableName);
	}
	Table()
	{

	}

	~Table() {
		if (columns != nullptr)
			delete[] columns;
	}

	void setColumns(TableColumn* columns, int noColumns)
	{
		if (this->columns)
		{
			delete[]this->columns;
		}
		this->columns = new TableColumn[noColumns];
		for (int i = 0; i < noColumns; i++)
		{
			this->columns[i] = columns[i];
		}
		this->noColumns = noColumns;
	}

	char* getName()
	{
		return this->tableName;
	}

	Table(const Table& table) {
		strcpy_s(this->tableName, 100, table.tableName);
		this->tableName[99] = '\0';
		this->setColumns(table.columns, table.noColumns);
	}

	void operator=(const Table& table) {
		if (this != &table) {
			if (this->columns) {
				delete[] this->columns;
			}
			strcpy(this->tableName, table.tableName);
			this->columns = new TableColumn[table.noColumns];
			for (int i = 0; i < table.noColumns; i++) {
				this->columns[i] = table.columns[i];
			}
			this->noColumns = table.noColumns;
		}
	}
	void operator <<(TableColumn& column)
	{
		TableColumn* newColumns = new TableColumn[this->noColumns + 1];
		for (int i = 0; i < this->noColumns; i++)
		{
			newColumns[i] = this->columns[i];
		}
		newColumns[this->noColumns] = column;
		this->noColumns++;
		if (this->columns)
			delete[]this->columns;
		this->columns = newColumns;
	}

	void operator ()(TableColumn& column)
	{
		TableColumn* newColumns = new TableColumn[this->noColumns + 1];
		for (int i = 0; i < this->noColumns; i++)
		{
			newColumns[i] = this->columns[i];
		}
		newColumns[this->noColumns] = column;
		if (this->columns)
			delete[]this->columns;
		this->noColumns++;
		this->columns = newColumns;
	}

	int getNoColumns()
	{
		return this->noColumns;
	}

	TableColumn *getColumn(int i)
	{
		return &this->columns[i];
	}

	void operator +=(TableColumn& column)
	{
		*this << column;
	}

	void writeTableToBin(string tableName)
	{
		string fileName = tableName + ".bin";
		ofstream File(fileName, ios::out | ios::binary | ios::trunc);
		if (File.is_open())
		{
			//write the table name (char):
			File.write((char*)&this->tableName, sizeof(char) * sizeof(Table::tableName));
			//write the columns:
			File.write((char*)&this->noColumns, sizeof(int));
			for (int i = 0; i < this->noColumns; i++)
			{
				this->columns[i].writeColumnToBin(File);
			}

			File.close();
		}
		else
		{
			cout << "THE FILE IS NOT OPEN SO YOU CAN'T WRITE A TABLE IN IT! OPEN THE FILE!";
		}

	}

	void readTableFromBin(string fileName)
	{
		ifstream File;
		File.open(fileName, ios::in | ios::binary);
		if (File.is_open())
		{
			//read the table name (char):
			File.read((char*)&this->tableName, sizeof(Table::tableName) * sizeof(char));
			//read the columns:
			File.read((char*)&this->noColumns, sizeof(int));
			if (this->columns != nullptr)
				delete[]this->columns;
			this->columns = new TableColumn[noColumns];
			for (int i = 0; i < this->noColumns; i++)
			{
				this->columns[i].readColumnFromBin(File);

			}

			File.close();
	
		}
		else
		{
			cout << "THE FILE IS NOT OPEN SO YOU CAN'T READ A TABLE FROM IT! OPEN THE FILE!";
		}
	}

	friend class CreateCommand;
	friend void operator <<(ostream& out, Table& table);
};


void operator <<(ostream& out, Table& table)
{
	out << endl << "-------------------------------------" << endl << "TABLE: ";
	out << endl << "Name: ";
	for (int i = 0; i < strlen(table.tableName); i++)
	{
		out << table.tableName[i];
	}
	out << endl << "No of columns: " << table.noColumns;
	if (table.noColumns > 0)
	{
		for (int i = 0; i < table.noColumns; i++)
		{
			out << endl << endl << "COLUMN " << i << ": ";
			out << table.columns[i];
		}
	}
}

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

	void writeCommandToBin(ofstream& binFile)
	{
		UsefulFunctions::writeStringToBin(binFile, this->commandFirst);
		if (commandSecond != "")
		{
			UsefulFunctions::writeStringToBin(binFile, this->commandSecond);
		}
		UsefulFunctions::writeStringToBin(binFile, this->name);
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
void operator >>(ifstream& file, Command& command)
{
	string name;
	getline(file, name);
	command.setName(name);
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

//reading a command from the keyboard
void operator <<(ostream& out, Command command) {
	out << endl << "--------------------------------------";
	out << endl << "Operator Command:" << command.getName();
}



//THE COMMANDS

//1. DROP
//MERGE PENTRU TOATE EXEMPLELE DE SINTAXA
//FACE CE TREBUIE IN BAZA DE DATE
class DropCommand
{
	Command command;
	string tableName = "";
	UsefulFunctions function;
	File theDatabase;
public:
	DropCommand(Command command, File& theDatabase)
	{
		checkDrop(command.getName());
		this->theDatabase = theDatabase;
		doDrop(command.getName());
	}
private:
	void checkDrop(string commandName)
	{
		commandName = function.subStringWithoutSpaces(commandName);
		if (function.findChars(commandName, function.CAPS) == 1 || function.findChars(commandName, function.SIGNS) == 1 || function.findChars(commandName, function.NoCAPS) == 0 || function.findChars(commandName, " ") == true)
		{
			throw new InvalidCommandException("The DROP command has the wrong table name", 0);
		}
		else
		{
			this->tableName = commandName;
			cout << "The command is correct and we are now executing it: " << endl;;
		}
	}

	void doDrop(string tableName)
	{
		tableName = function.subStringWithoutSpaces(tableName);
		cout << "The table you want to drop is: " << tableName << endl;
		int pozitionInFile = this->theDatabase.searchFile(tableName.c_str());
		if (pozitionInFile == -1)
		{
			throw new InvalidCommandException("There is no tabel with this name to be dropped!", 0);
		}
		else
		{
			cout << endl << "BEFORE the command the database has the following tables: " << endl;
			for (int i = 1; i < this->theDatabase.getNoLines(); i++)
			{
				cout << this->theDatabase.getTheLine(i) << endl;
			}
			this->theDatabase.deleteTable(pozitionInFile);
			cout << endl << "AFTER the command the database has the following tables: " << endl << endl;
			for (int i = 1; i < this->theDatabase.getNoLines(); i++)
			{
				cout << endl << this->theDatabase.getNoLines();
				cout << this->theDatabase.getTheLine(i) << endl;
			}

			//removing the actual file
			string fileName = tableName + ".bin";
			remove(fileName.c_str());
			cout << endl << "Congrats! Your file <<" << fileName << ">> has been removed and the table <<" << tableName << ">> is no longer in the database!" << endl;
			createTheNewDatabase();
		}
	}
	void createTheNewDatabase()
	{
		fstream theNewDatabase;
		theNewDatabase.open("Database.txt", ios::out | ios::trunc | ios::in);
		int i = 0;
		cout << endl << "********AICI" << this->theDatabase.getNoLines();
		while (i < this->theDatabase.getNoLines())
		{
			theNewDatabase << this->theDatabase.getTheLine(i) << endl;
			i++;
		}

		while (theNewDatabase.eof() == false)
		{
			string line;
			getline(theNewDatabase, line);
		}
		cout << endl << "ajunge la final ";
	}
};

//2. DISPLAY
//MERGE PENTRU TOATE EXEMPLELE

class DisplayCommand
{
	Command command;
	string table_name = " ";
	UsefulFunctions function;
	File theDatabase;
public:
	DisplayCommand(Command command, File& theDatabase)
	{
		checkDisplay(command.getName());
		this->theDatabase = theDatabase;
		doDisplay(command.getName());
	}
private:
	void checkDisplay(string commandName)
	{
		commandName = function.subStringWithoutSpaces(commandName);
		if (function.findChars(commandName, function.CAPS) == 1 || function.findChars(commandName, function.SIGNS) == 1 || function.findChars(commandName, function.NoCAPS) == 0 || function.findChars(commandName, " ") == true)
		{
			throw new InvalidCommandException("The DISPLAY command has the wrong table name", 0);
		}
		else
		{
			cout << "The command is correct. We are now executing it: " << endl;
		}
	}
	void doDisplay(string commandName)
	{
		string tableName = commandName;
		function.subStringWithoutSpaces(tableName);
		cout << "The table you want to display is: " << tableName << endl;
		int pozitionInFile = this->theDatabase.searchFile(tableName.c_str());
		if (pozitionInFile == -1)
		{
			throw new InvalidCommandException("There is no tabel with this name to be displayed!", 0);
		}
		else
		{
			cout << endl << "Displaying the table..." << endl;
			string fileName = tableName + ".bin";

			Table theTable(tableName.c_str());

			theTable.readTableFromBin(fileName);

			cout << theTable;
		}
	}
};

//3.CREATE
//in constructor, dupa validare, adaugi o functie doCreate, care primeste parametrii pe care i-a scos Validare din comanda si construieste
//un fisier binar, cu titlul numeTabel.bin, care contine in ordine coloanele 
//also, doCreate adauga numele tabelului pe care il construiesti pe o linie noua (fara spatiu dupa) in fisierul txt theDatabase (care e deschis si cu in si cu out deci poti sa si citesti sa si scrii in el)
class CreateCommand
{
	Command command;
	UsefulFunctions function;
	File theDatabase;
	Table tabelCreat;
public:
	CreateCommand(Command command, File& theDatabase)
	{
		this->theDatabase = theDatabase;
		ValidareSerioasaCreate(command.getName(), this->tabelCreat);
		doCreate(command.getName());
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
				}
			}
			//for the 2nd param we need a text but this time denoting one of the types, check type and pass it to the cType 
			if (contorEditable == 1) {
				if (parametriiTabel == "text" || parametriiTabel == "integer" || parametriiTabel == "float") {
					cType = parametriiTabel;
				}
				else {
					throw new InvalidCommandException("Second parameter has an error", 0);
				}

			}
			//for the 3rd param we need an integer, we check to see if only digits and convert string to int 
			if (contorEditable == 2) {
				if (function.checkAsciiValue(parametriiTabel, '0', '9') == 0) {
					cDim = stoi(parametriiTabel);
				}
				else {
					throw new InvalidCommandException("Wrong third parameter", 0);
				}
			}
			// here i dont know for sure what checks needs to be The command is correct. We are now executing it:  but the passing to the cValue its made 
			if (contorEditable == 3) {
				if (parametriiTabel.find_first_of('’')) {
					parametriiTabel.erase(remove(parametriiTabel.begin(), parametriiTabel.end(), '’'), parametriiTabel.end());
				}
				defaultVal = parametriiTabel;
			}
			editable.erase(0, parametriiTabel.length() + 1);
			contorEditable++;
		}
	}

	void ValidareSerioasaCreate(string commanda, Table& tabelCreat) {// string& name, string& type, int& dim, string& value) {
		string newCommand = commanda;
		string editable = "";
		string parametriiTabel = "";
		string copyEditable = "";
		// parametrii ce vor putea fi dati si de sus cand doriti 
		string name = "";
		string type = "";
		int dim = 0;
		string value = "";
		// next
		// in order to check everything first we strip the table name until ( by any spaces in order to check it lexically 
		editable = newCommand.substr(0, newCommand.find_first_of('('));
		copyEditable = function.stringWithoutSpaces(editable);
		if (function.nrChars(copyEditable, 'I', dim) == 2)
		{
			int noLettersTableName = 0;
			noLettersTableName = copyEditable.find_first_of('I');
			if (copyEditable.compare(copyEditable.find_first_of('I'), 11, "IFNOTEXISTS") == 0 && copyEditable.length() == (noLettersTableName + 11)) {
				//VALI: aici faci verificarea in Database.txt sa vezi daca apare sau nu tableName (te folosesti de functia isTableInFile din Useful
								//(returneaza linia la care apare numele tabelului, daca e in txt sau -1 daca nu e in txt, ai exemplu in drop)
				copyEditable = copyEditable.erase(copyEditable.find_first_of('I'), 11);
				cout << endl << "copyEditable este:" << copyEditable;
				if (theDatabase.searchFile(copyEditable.c_str()) >= 0)
					throw new InvalidCommandException("wrong if not exists", 0);
			}
			else
				throw new InvalidCommandException("wrong if not exists", 0);
		}



		if (function.checkAsciiValue(copyEditable, 'a', 'z') != 0) {
			throw new InvalidCommandException("Wrong table name", 0);
		}
		else {
			//aici cred ca ajungi cu copyEditable ca numele tabelului, asa ca:
			strcpy(tabelCreat.tableName, copyEditable.c_str()); //am folosit c_str() ca sa transform string-ul (copyEditable) in char* (tableName). Gasesti functia pe google. 
			int counter;
			newCommand.erase(0, editable.length());
			if ((function.nrChars(newCommand, '(', counter) != function.nrChars(newCommand, ')', counter)) || ((function.nrChars(newCommand, '(', counter) + (function.nrChars(newCommand, ')', counter))) % 2 != 0)) {
				throw new InvalidCommandException("Wrong number of parantesis!", 0);
			}
			//after it was checked, if we have only one column we call the function once 
			else {
				if (function.nrChars(newCommand, '(', counter) == 1) {
					createParamVandPars(newCommand, name, type, dim, value);
					//aici atribui primei coloane valorile (nu cred ca aveai nevoie sa verifici daca e doar o coloana sau mai multe, dar nu mai are sens sa stergem acum:
					cout << "The command is correct. We are now executing it...";
					tabelCreat.noColumns = 1;
					TableColumn column;
					column.setName(name);
					//VALI aici e nevoie de setteri pt toate valorile coloanei. Daca ai timp, defineste-i tu in clasa coloana, te rog, sau spune-i lui Radu ms
					column.setType(type);
					column.setDim(dim);
					column.setDefault(value);

					//aici fac atribuirea coloanei nou create la tabel. Daca ai definit operatorul << corect, ar trebui sa mearga. 
					tabelCreat += column;
				}
				else   // else we will strip the columns by the commas and spaces dividing them and then call the functions one by one while also deleting from the command string
				{
					//aici o sa folosesc tabelCreate.noColumns pe post de contor, adica o sa inceapa de la 0 si o sa creasca de fiecare data cand gasesti o coloana noua:
					tabelCreat.noColumns = 0;
					newCommand = newCommand.substr(newCommand.find_first_of('(') + 1, newCommand.find_last_of(')') - 1);
					newCommand = function.stringWithoutCommasOrSpaces(newCommand);
					while (newCommand.length()) {
						parametriiTabel = newCommand.substr(0, newCommand.find_first_of(')') + 1);
						createParamVandPars(parametriiTabel, name, type, dim, value);
						//aici fac acelasi lucru ca mai sus, doar ca se va executa de mai multe ori. Nu e nevoie sa facem un vector de coloane pt ca nu vom avea nevoie de coloane in sine,
												//sunt doar intermediare ca sa putem adauga la tabel:
						TableColumn column;
						column.setName(name);
						//VALI aici e nevoie de setteri pt toate valorile coloanei. Daca ai timp, defineste-i tu in clasa coloana, te rog, sau spune-i lui Radu ms
						column.setType(type);
						column.setDim(dim);
						column.setDefault(value);
						//aici fac atribuirea coloanei nou create la tabel. Daca ai definit operatorul << corect, ar trebui sa mearga.
						tabelCreat += column;
						newCommand.erase(0, parametriiTabel.length());
					}
					cout << endl << "The command is correct. We are now executing it...";
				}
			}

		}
	}

	void doCreate(string commandName)
	{
		cout << tabelCreat;
		cout<< endl << endl;

		this->tabelCreat.writeTableToBin(this->tabelCreat.tableName);

		this->theDatabase.addTable(this->tabelCreat.tableName);
		createTheNewDatabase();
	}

	void createTheNewDatabase()
	{
		fstream theNewDatabase;
		theNewDatabase.open("Database.txt", ios::out | ios::trunc | ios::in);
		int i = 0;
		while (i < this->theDatabase.getNoLines())
		{
			theNewDatabase << this->theDatabase.getTheLine(i) << endl;
			i++;
		}

		while (theNewDatabase.eof() == false)
		{
			string line;
			getline(theNewDatabase, line);
		}
		theNewDatabase.close();
	}
};



//4. SELECT
//MERGE PENTRU TOATE EXEMPLELE
class SelectCommand
{
	Command command;
	UsefulFunctions function;
	File theDatabase;
	string tableName = "", selectedValues = "", filter = "", filterValue = "";
public:
	SelectCommand(Command command, File& theDatabase)
	{
		checkSelect(command.getName(), this->tableName, this->selectedValues, this->filter, this->filterValue);
		this->theDatabase = theDatabase;
		doSelect(command.getName());
	}
private:
	void checkSelect(string commandName, string& tableName, string& theSelectedValues, string& filter, string& filterValue)
	{
		int counter1 = 0, counter2 = 0;
		commandName = function.subStringWithoutSpaces(commandName);
		if (commandName[0] != 'A')
		{
			theSelectedValues = function.extract(commandName, commandName[0], commandName[commandName.find_last_of(')') + 1], counter1, counter2);
			string selectedValues = theSelectedValues;
			commandName.erase(0, selectedValues.length());
			//check the selected values
			if (selectedValues[0] != '(' || selectedValues[selectedValues.length() - 1] != ')' || selectedValues == "()")
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
				throw new InvalidCommandException("HASN't GOT ALL KEYWORD", 0);
			}
			theSelectedValues = function.extract(commandName, commandName[0], commandName[3], counter1, counter2);
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
		tableName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
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
			filter = column;
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
			filterValue = commandName;
			if (function.findChars(commandName, function.CAPS) == true || function.findChars(commandName, function.SIGNS) == true || function.findChars(commandName, " ") == true)
			{
				throw new InvalidCommandException("Not proper value name OR multiple conditions", 0);
			}
		}
		cout << "The command is correct. We are now executing it..." << endl;
	}

	void doSelect(string commandName)
	{
		cout << endl << "We are selecting the following columns: " << this->selectedValues;
		cout << endl << "From the table called: " << this->tableName;
		if (this->filter == "")
			cout << endl << "There is no filter. Taking all the attributes...";
		else {
			cout << endl << "Filtering by column: " << this->filter;
			cout << endl << "With the value: " << this->filterValue;
		}

		int pozitionInFile = this->theDatabase.searchFile(tableName.c_str());
		if (pozitionInFile == -1)
		{
			throw new InvalidCommandException("Sorry, there is no table with this name to select from!", 0);
		}
		else
		{
			string fileName = tableName + ".bin";

			Table theTable(tableName.c_str());
			theTable.readTableFromBin(fileName);

		//extracting the names of the columns that you want to display:
			string* value = new string[theTable.getNoColumns()];
			int i = 0;
			if (selectedValues != "ALL")
			{
				int j = 0;
				selectedValues.erase(0, 1);
				selectedValues.erase(selectedValues.find_last_of(')'), 1);
				while (selectedValues != "")
				{
					int counter1 = 0, counter2 = 0;
					if (selectedValues.find(',') != string::npos)
					{
						value[j] = function.extract(selectedValues, selectedValues[0], ',', counter1, counter2);
						selectedValues.erase(counter1, counter2 + 1);
					}
					else
					{
						value[j] = selectedValues;
						selectedValues = "";
					}
					j++;
				}
				i = j;
			}

			else
			{
				for (int i = 0; i < theTable.getNoColumns(); i++)
				{
					value[i] =(*theTable.getColumn(i)).getName();
				}
				i = theTable.getNoColumns();
			}
			
		//using the filter to find the rows you want to display
			if (filter == "")
			{
				for (int j = 0; j < i; j++)
				{
					cout <<endl<< "------------------------------";
					displaySomeColumns(theTable, value[j]);
				}
			}
			else
			{
				for (int j = 0; j < i; j++)
				{
					cout << endl << "------------------------------";
					displaySomeColumns(theTable, value[j]);
				}
			}
			
		}
	}

	void displaySomeAttributes(TableColumn& theColumn, string filterValue)
	{
		if (filterValue != "No filter")
		{
			for (int i = 0; i < theColumn.getNoAttributes(); i++)
			{
				if ((*theColumn.getAttribute(i)).getValue() == filterValue)
				{
					cout << (*theColumn.getAttribute(i));
				}
			}
		}
		else
		{
			for (int i = 0; i < theColumn.getNoAttributes(); i++)
			{
					cout << (*theColumn.getAttribute(i));
			}
		}
	}

	void displaySomeColumns(Table &theTable, string value)
	{
			for (int i = 0; i < theTable.getNoColumns(); i++)
			{
				if ((*theTable.getColumn(i)).getName() == value)
				{
					cout << endl<< "DISPLAYING THE COLUMN: "<<(*theTable.getColumn(i)).getName();
					displaySomeAttributes(*theTable.getColumn(i), "No filter");

				}			
			}
		
	}

};

//5. UPDATE
//MERGE PENTRU TOATE EXEMPLELE
class UpdateCommand
{
	Command command;
	UsefulFunctions function;
	File theDatabase;
	string tableName = "", columnToChange = "", valueToChange = "", filter = "", filterValue = "";
public:
	UpdateCommand(Command command, File& theDatabase)
	{
		checkUpdate(command.getName(), this->tableName, this->columnToChange, this->valueToChange, this->filter, this->filterValue);
		this->theDatabase = theDatabase;
		doUpdate(command.getName());
	}
private:
	void checkUpdate(string commandName, string& tableName, string& columnToChange, string& valueToChange, string& filter, string& filterValue)
	{
		//check table name
		int counter1 = 0, counter2 = 0;
		tableName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		if ((tableName.find("(") != tableName.npos) || (tableName.find(" ") != tableName.npos) || (tableName.find(",") != tableName.npos))
		{
			throw new InvalidCommandException("The UPDATE command has the wrong table name", 0);
		}
		//check SET KEYWORD
		counter1 = 0, counter2 = 0;
		string setKeyword = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		if (setKeyword != "SET")
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the SET keyword", 0);
		}
		//check column name
		counter1 = 0, counter2 = 0;
		string columnName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		columnToChange = columnName;
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
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
		commandName = function.subStringWithoutSpaces(commandName);
		//check value to be changed
		counter1 = 0, counter2 = 0;
		string columnValue = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		valueToChange = columnValue;
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		if (function.findChars(columnValue, function.SIGNS) == true)
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the proper column value sign", 0);
		}
		//check WHERE
		counter1 = 0, counter2 = 5;
		string WHERE = commandName.substr(0, 5);
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		if (WHERE != "WHERE")
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the WHERE keyword!", 0);
		}
		//check columnName to be changed
		counter1 = 0, counter2 = 0;
		columnName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
		filter = columnName;
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		if (function.findChars(columnName, function.CAPS) == 1 || function.findChars(columnName, function.SIGNS) == 1)
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the proper column name", 0);
		}
		//check equal AGAIN
		counter1 = 0, counter2 = 1;
		function.subStringWithoutSpaces(commandName);
		if (commandName[0] != '=')
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the EQUAL sign", 0);
		}
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		//check column value to be updated
		counter1 = 0, counter2 = 0;
		columnValue = function.extract(commandName, commandName[0], commandName[commandName.length()], counter1, counter2);
		filterValue = columnValue;
		commandName.erase(counter1, counter2);
		commandName = function.subStringWithoutSpaces(commandName);
		if (function.findChars(columnValue, function.SIGNS) == 1)
		{
			throw new InvalidCommandException("The UPDATE command hasn't got the proper column value sign", 0);
		}
		cout << "The command is correct. We are now executing it..." << endl;
	}

	void doUpdate(string commandName)
	{
		cout << endl << "The table you want to update is: " << this->tableName;
		cout << endl << "The column you want to update is: " << this->columnToChange;
		cout << endl << "The value you want to use for update is: " << this->valueToChange;
		cout << endl << "The column you want to use as filter is: " << this->filter;
		cout << endl << "The value to filter by is: " << this->filterValue;
		int pozitionInFile = this->theDatabase.searchFile(tableName.c_str());
		if (pozitionInFile == -1)
		{
			throw new InvalidCommandException("Sorry, there is no table with this name to be updated!", 0);
		}
		else
		{
			//de facut dupa create
		}
	}
};

//6.DELETE
//MERGE PENTRU TOATE EXEMPLELE
class DeleteCommand {

	Command command;
	UsefulFunctions function;
	File theDatabase;
	string tableName = "", columnName = "", columnValue = "";
public:
	DeleteCommand(Command command, File& theDatabase)
	{
		checkDelete(command.getName(), this->tableName, this->columnName, this->columnValue);
		this->theDatabase = theDatabase;
		doDelete(command.getName());
	}
private:
	void checkDelete(string commandName, string& tableName, string& columnName, string& columnValue)  // "table_name WHERE column_name = value"
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
		tableName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
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
		columnName = function.extract(commandName, commandName[0], ' ', counter1, counter2);
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
		columnValue = commandName;
		if (function.findChars(columnValue, function.SIGNS) == 1)
		{
			throw new InvalidCommandException("The DELETE command hasn't got the proper column value sign", 0);
		}
		cout << "The command is correct. We are now executing it..." << endl;
	}

	void doDelete(string commandName)
	{
		cout << endl << "The table you want to delete from is: " << this->tableName;
		cout << endl << "The column you want to delete from is: " << this->columnName;
		cout << endl << "The value you want to delete is: " << this->columnValue;
		int pozitionInFile = this->theDatabase.searchFile(tableName.c_str());
		if (pozitionInFile == -1)
		{
			throw new InvalidCommandException("Sorry, there is no table with this name to delete from!", 0);
		}
		else
		{
			//de facut dupa create
		}
	}
};

//7.INSERT
//7.INSERT
class InsertCommand
{
	Command command;
	UsefulFunctions function;
	File theDatabase;
	Table theTable;
public:
	InsertCommand(Command command, File& theDatabase) 
	{
		insertValidation(command.getName(), theTable);
		this->theDatabase = theDatabase;
		doInsert(command.getName());
	}
private:
	void insertValidation(string Command, Table& table) {
		// trebuie sa am noColumns .
		string newCommand = Command;
		string editable;
		string parametriiTabel;
		string copyEditable;

		int noParam = 0;
		int startPoint = 0;
		// se pune conditia in DO insert
		//int numberOfParam = theTable.getNoColumns(); // ATENTIE !! ACEST NUMAR SE VA PRIMI DIN CREATE TABLE la APELARE CUMVA
		////validare pt nr de parametrii primiti care trb sa fie egal cu nr de coloane
		//if(function.findChars(newCommand, ',')!= numberOfParam)
		//	throw 

		//validare paranteze 
		if (function.nrChars(newCommand, '(', noParam) != 1 && function.nrChars(newCommand, ')', noParam) != 1) {
			throw new InvalidCommandException("paranteze gresite ", 0);
			cout << "paranteze gresite";
		}

		editable = newCommand.substr(0, newCommand.find_first_of('('));
		copyEditable = function.stringWithoutSpaces(editable);

		//aici in parametrii avem numele tabelului: studenti
		parametriiTabel = copyEditable.substr(0, copyEditable.find_first_of('V'));
		if (parametriiTabel.length() == 0)
		{
			throw new InvalidCommandException("nu exista nume tabe ", 0);
			cout << "nu exista nume tabe";
		}
		else
			cout << endl << "Numele tabelului in care se vor face modificari este " << parametriiTabel;

		string fileName = parametriiTabel + ".bin";

		Table newTable(parametriiTabel.c_str());

		newTable.readTableFromBin(fileName);
		cout << newTable;

		if (copyEditable.compare(copyEditable.find_first_of('V'), 6, "VALUES") == 0 && copyEditable.length() == (parametriiTabel.length() + 6)) {
			cout << endl << "Validare reusita pana la paranteza";
		}
		else {
			throw new InvalidCommandException("wrong command ", 0);
			cout << "wrong command ";
		}

		newCommand.erase(0, editable.length()); // newCommand devine (1,"John","1001")
		editable = newCommand.substr(newCommand.find_first_not_of('('), newCommand.find_last_of(')') - 1); //editable devine 1,"John","10001"
		editable = function.stringWithoutSpaces(editable);  // se elimina spatiile desi in cerinta reiese ca nu ar exista spatii 
		noParam = function.nrChars(editable, ',', noParam) + 1;  // in functie de nr de virgule primim nr parametrii  no=3

		// AICI MAI ESTE NEVOIE DE O VALIDARE CARE SA VERIFICE DACA NUMARUL COLOANELOR RESPECTA NUMARUL VIRGULELOR + 1 CARE SE VA AFLA IN FUNCTIE DE VALOAREA DIN CREATE A TABELULUI 
		// INSERT INTO studenti VALUES (1,”John” ”1001”)  -- exemplul ruleaza desi e gresit.

		// now we go parameter by parameter
		ColumnAttribute attribute;
		int i = 0;
		while (i<newTable.getNoColumns()) {
			parametriiTabel = editable.substr(0, editable.find_first_of(','));
			int temp = 0;
			if (function.nrChars(parametriiTabel, '"', temp)) {
				string temp = parametriiTabel.substr(1, parametriiTabel.find_last_of('"') - 1);
				//cout << endl << "Parametrul tabel la iteratie " << startPoint << " este " << temp << " si este tip string";
				// variabila temp este columnAttribute Value

				attribute.setAttributeString(temp);
				attribute.setAttributeType("STRING");

			}
			else {
				float value;
				string temporary = parametriiTabel;
				if (function.nrChars(temporary, '.', temp) > 1)
				{
					cout << "too many points";
					throw new InvalidCommandException("too many points", 0);
					
				}
				else if (function.nrChars(temporary, '.', temp) == 1) {
					temporary = temporary.erase(temporary.find_first_of('.'), 1);
				}
				else if (function.nrChars(temporary, '.', temp) == 0)
					if (function.checkAsciiValue(temporary, '0', '9') == 0)
					{
						attribute.setAttributeString(parametriiTabel);
						attribute.setAttributeType("INTEGER");
					}
				//23.5 -> 235

				if (function.checkAsciiValue(temporary, '0', '9')) {
					cout << "nu este string dar are litere";
					throw new InvalidCommandException("nu este string dar are litere", 0);
				}
				else {
					value = stof(parametriiTabel);
					//cout << endl << "Parametrul tabel la iteratie " << startPoint << " este floatul " << value;
					string value1 = to_string(value);
					attribute.setAttributeString(value1);
					attribute.setAttributeType("FLOAT");
					// variabila parametriiTable este columnAttribute Value (string)
				}

			}
			editable.erase(0, parametriiTabel.length() + 1);
			startPoint++;

			*newTable.getColumn(i) += attribute;
			i++;
		}
		table = newTable;
	}

	void doInsert(string commandName)
	{
		this->theTable.writeTableToBin(this->theTable.getName());
	}
};



//PARSER-UL
class Parser
{
	Command command;
	UsefulFunctions function;
	string name = command.getName();
	string FirstWord = "";
	string SecondWord = "";
	File theDatabase;
public:

	Parser(Command command, File& theDatabase)
	{
		this->FirstWord = command.getFirstWord();
		this->SecondWord = command.getSecondWord();
		this->theDatabase = theDatabase;
	}
	void Parse(Command command)
	{
		if (FirstWord == "CREATE")
		{
			CreateCommand object(command, this->theDatabase);
		}
		if (FirstWord == "DROP")
		{
			DropCommand object(command, this->theDatabase);
		}
		if (FirstWord == "DELETE")
		{
			DeleteCommand object(command, this->theDatabase);
		}
		if (FirstWord == "DISPLAY")
		{
			DisplayCommand object(command, this->theDatabase);
		}
		if (FirstWord == "UPDATE")
		{
			UpdateCommand object(command, this->theDatabase);
		}
		if (FirstWord == "SELECT")
		{
			SelectCommand object(command, this->theDatabase);
		}
		if (FirstWord == "INSERT")
		{
			InsertCommand object(command, this->theDatabase);
		}
	}

	friend class DisplayCommand;
};


// The classes for data

class UtilTable {
public:
	static void setTable() {

	}
};
