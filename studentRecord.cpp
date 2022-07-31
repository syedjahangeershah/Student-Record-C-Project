#include <iostream>
#include <fstream>
using namespace std;
void menu();
int lengthFinder(char const* word)
{
	int length = 0;
	for (int i = 0; word[i] != '\0'; i++, length++);
	return length;
}
void lowerToUpper(char* word)
{
	int length = lengthFinder(word);
	for (int i = 0; i < length; i++)
		if (word[i] >= 'a' && word[i] <= 'z')
			word[i] -= 32;
}
bool isOffered(char* code)
{
	int length = lengthFinder(code);
	ifstream read("courses.txt");
	char* input = new char[50];

	while (read >> input)
	{
		int compareLength = lengthFinder(input);
		if (length == compareLength)
		{
			int count = 0;
			for (int i = 0; i < length; i++)
				if (code[i] == input[i])
					count++;
			if (count == length)
				return true;
			else
				read.getline(input, 50);
		}
		else
			read.getline(input, 50);
	}
	read.close();
	return false;
}
bool checkIFAlreadyEnrolled(char const* word, char const* ID)
{
	int cLength = lengthFinder(word), idLength = lengthFinder(ID);

	ifstream read("studentRecord.txt");
	if (!read)
	{
		return false;
	}
	char* input = new char[50];
	while (read >> input)
	{
		int checkLength = lengthFinder(input);
		bool furtherCheck = false;
		if (idLength == checkLength)
		{
			int count = 0;
			for (int i = 0; i < idLength; i++)
				if (ID[i] == input[i])
					count++;
			if (count == idLength)
				furtherCheck = true;
		}
		if (furtherCheck)
		{
			read >> input;
			int checkClength = lengthFinder(input);
			if (cLength == checkClength)
			{
				int count = 0;
				for (int i = 0; i < cLength; i++)
					if (word[i] == input[i])
						count++;
				if (count == cLength)
					return true;
				else
					read >> input;
			}
			else
				read >> input;
		}
		else
			read >> input >> input;
	}
	read.close();
	return false;
}
void enrollCourses()
{
	char* cCode = new char[50], * cName = new char[50], section, * studentID = new char[50];
	int cHours;
	cin.ignore();
	cout << "\tEnter student ID : ";
	cin >> studentID;
	lowerToUpper(studentID);
	cout << "\n\tChoose a course from the following courses:\n";
	ifstream read("courses.txt");
	cout << "\t<............................................>\n"
		<< "\t Course Code\tCredit Hours\tCourse Name\n";
	while (read >> cCode)
	{
		read >> cHours;
		cout << "\t " << cCode << "\t\t" << cHours << "\t";
		read.getline(cName, 50);
		cout << cName << "\n";
	}
	cout << "\t<............................................>\n";
	read.close();
	cout << "\tEnter course Code : ";
	cin >> cCode;
	lowerToUpper(cCode);
	bool available = isOffered(cCode);
	if (available)
	{
		bool enrolled = checkIFAlreadyEnrolled(cCode, studentID);
		if (!enrolled)
		{
			cout << "\t" << "Course Code : " << cCode << "\n";

			cout << "\tEnter section : ";
			cin >> section;
			while (section != 'A' && section != 'a' && section != 'B ' && section != 'b' && section != 'c' && section != 'C' && section != 'D' && section != 'd' &&
				section != 'E' && section != 'e')
			{
				std::cout << "\tPlease Enter sections between A,B,C,D,E : ";
				std::cin >> section;
			}
			ofstream out("studentRecord.txt", ios::app);
			out << studentID << "\n"
				<< cCode << "\n"
				<< section << "\n";
			out.close();
			cout << "\tStudent Enrolled Successfully!\n";
		}
		else
			cout << "\tStudent already enrolled in this course.\n";
	}
	else
		cout << "\tSorry, this course is not available.\n";
}
void dropCourse()
{
	char* cCode = new char[50], * studentID = new char[50];
	int cHours;
	cin.ignore();
	cout << "\tEnter student ID : ";
	cin >> studentID;
	lowerToUpper(studentID);
	cout << "\tEnter course Code : ";
	cin >> cCode;
	lowerToUpper(cCode);

	int codeLength = lengthFinder(cCode), idLength = lengthFinder(studentID);
	bool dropped = false;
	ifstream read("studentRecord.txt");
	ofstream WRITE("tempFile.txt", ios::app);
	if (!read)
	{
		cout << "\t=== Student is not registered. ===\n";
		return;
	}
	char* input = new char[50];
	while (read >> input)
	{
		int checkLength = lengthFinder(input);
		bool furtherCheck = false;
		if (idLength == checkLength)
		{
			int count = 0;
			for (int i = 0; i < idLength; i++)
				if (studentID[i] == input[i])
					count++;
			if (count == idLength)
				furtherCheck = true;
		}
		if (furtherCheck)
		{
			read >> input;
			int checkClength = lengthFinder(input);
			if (codeLength == checkClength)
			{
				int count = 0;
				for (int i = 0; i < codeLength; i++)
					if (cCode[i] == input[i])
						count++;
				if (count == codeLength)
				{
					dropped = true;
					read >> input;
				}
				else
				{
					WRITE << studentID << "\n";
					WRITE << input << "\n";
					read >> input;
					WRITE << input << "\n";
				}
			}
			else
			{
				WRITE << studentID << "\n";
				WRITE << input << "\n";
				read >> input;
				WRITE << input << "\n";
			}
		}
		else
		{
			WRITE << input << "\n";
			read >> input;
			WRITE << input << "\n";
			read >> input;
			WRITE << input << "\n";
		}
	}
	WRITE.close();
	read.close();
	remove("studentRecord.txt");
	rename("tempFile.txt", "studentRecord.txt");
	if (dropped)
		cout << "\tDropped!\n";
	else
		cout << "\tStudent is not registered in this course!\n";
}
char* creditHourRead(char* courseCode);
void enrolledCourses();
bool verify(char* studentID, char* courseID);
void updateSection();
void totalStudents();
void enrolledOrNot();
int count(char* courseID, int& given, int mini);
void minimumEnrolingLilst();
bool overCount(char* courseID, char file[])
{
	ifstream read(file);
	if (!read)
		return false;
	char* input = new char[50];
	int length = lengthFinder(courseID);
	while (read >> input)
	{
		int count = 0;
		for (int i = 0; i < length; i++)
			if (courseID[i] == input[i])
				count++;
		if (count == length)
			return true;
	}
	read.close();
	return false;
}

int main()
{
	int choice;
	do
	{
		system("cls");
		menu();
		cout << "\tChoice : ";
		cin >> choice;
		if (choice == 1)
			enrollCourses();
		else if (choice == 2)
			dropCourse();
		else if (choice == 3)
			enrolledCourses();
		else if (choice == 4)
			updateSection();
		else if (choice == 5)
			totalStudents();
		else if (choice == 6)
			enrolledOrNot();
		else if (choice == 7)
			minimumEnrolingLilst();
		cout << "\tEnter 1 for MENU or 0 for Exit : ";
		cin >> choice;
		if (choice != 0 && choice != 1)
		{
			cout << "\tINVALID selection.";
			break;
		}
	} while (choice != 0);
	cout << "\tProgram Exited";
}
void menu()
{
	cout << "\t\t\t\tMENU\n"
		<< "<+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++>\n"
		<< "\tPress [1] for Enrollment of the Student in a Course\n"
		<< "\tPress [2] for drop a Specified Course\n"
		<< "\tPress [3] for Display Students Enrolled courses\n"
		<< "\tPress [4] for Update Section of Student for enrolled Course\n"
		<< "\tPress [5] for Display Total number of Students enrolled in particular course\n"
		<< "\tPress [6] for Display course not enrolled by any student\n"
		<< "\tPress [7] for Display the Student with minimum number of registered course\n"
		<< "\tPress [0] for Exit the Program\n"
		<< "<+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++>\n";
}


void enrolledCourses()
{
	char* studentId = new char[50];
	cout << "\tEnter student ID : ";
	cin >> studentId;
	lowerToUpper(studentId);
	int length = lengthFinder(studentId);
	
	ifstream read("studentRecord.txt");
	if (!read)
	{
		cout << "\tStudent is not enrolled in any course!\n";
		return;
	}
	char* input = new char[50];
	bool enrolled = false, printHeading = true;
	while (read >> input)
	{
		int checkLength = lengthFinder(input);
		if (length == checkLength)
		{
			int count = 0;
			for (int i = 0; i < length; i++)
				if (studentId[i] == input[i])
					count++;
			if (count == length)
			{
				enrolled = true;
				char* coureseCode = new char[50], * section = new char, * creadHours = new char[50];
				read >> coureseCode;
				read >> section;
				creadHours = creditHourRead(coureseCode);
				if (printHeading)
				{
					cout << "\tCourse Code\tCredit hours\tSection\n";
					printHeading = false;
				}
				char c;
				if (*(section) >= 'a' && *(section) <= 'z')
					c = *(section)-32;
				else
					c = *(section);
				cout << "\t" << coureseCode << "\t" << creadHours << "\t\tSection " << c << "\n";
			}
			else
			{
				read >> input >> input;
			}
		}
		else
			read >> input >> input;
	}

	if (!enrolled)
		cout << "\tStudent is not enrolled in any course!\n";
}
char* creditHourRead(char* courseCode)
{
	int length = lengthFinder(courseCode);
	ifstream read("courses.txt");
	char* input = new char[50];
	while (read >> input)
	{
		int cLength = lengthFinder(input);
		if (length == cLength)
		{
			int count = 0;
			for (int i = 0; i < length; i++)
				if (courseCode[i] == input[i])
					count++;
			if (count == length)
			{
				read >> input;
				read.close();
				return input;
			}
		}
	}
	return NULL;
}
bool verify(char* studentID, char* courseID)
{
	int idLength = lengthFinder(studentID), courseIdLength = lengthFinder(courseID);

	ifstream read("studentRecord.txt");
	if (!read)
	{
		cout << "\tStudent is not enrolled in any course!\n";
		return false;
	}
	char* input = new char[50];
	while (read >> input)
	{
		int inputLength = lengthFinder(input);
		if (idLength == inputLength)
		{
			int count = 0;
			for (int i = 0; i < idLength; i++)
				if (studentID[i] == input[i])
					count++;
			if (count == idLength)
			{
				read >> input;
				inputLength = lengthFinder(input);
				if (courseIdLength == inputLength)
				{
					count = 0;
					for (int i = 0; i < courseIdLength; i++)
						if (courseID[i] == input[i])
							count++;
					if (count == courseIdLength)
					{
						return true;
					}
					else
						read >> input;
				}
			}
			else
				read >> input >> input;
		}
		else
			read >> input >> input;
	}
	read.close();
	return false;
}

void updateSection()
{
	char* studentId = new char[50], * courseID = new char[50];
	cout << "\tEnter student ID : ";
	cin >> studentId;
	lowerToUpper(studentId);
	int length = lengthFinder(studentId);
	cout << "\tEnter course ID : ";
	cin >> courseID;
	lowerToUpper(courseID);
	int courseIdLength = lengthFinder(courseID);
	bool chekcIfavailable = verify(studentId, courseID);
	if (chekcIfavailable)
	{
		cout << "\tEnter new Section : ";
		char section;
		cin >> section;
		while (section != 'A' && section != 'a' && section != 'B ' && section != 'b' && section != 'c' && section != 'C' && section != 'D' && section != 'd' &&
			section != 'E' && section != 'e')
		{
			std::cout << "\tPlease Enter sections between A,B,C,D,E : ";
			std::cin >> section;
		}
		ifstream read("studentRecord.txt");
		ofstream WRITE("tempFile.txt", ios::app);
		
		char* input = new char[50];
		while (read >> input)
		{
			int checkLength = lengthFinder(input);
			bool furtherCheck = false;
			if (length == checkLength)
			{
				int count = 0;
				for (int i = 0; i < length; i++)
					if (studentId[i] == input[i])
						count++;
				if (count == length)
					furtherCheck = true;
			}
			if (furtherCheck)
			{
				read >> input;
				int checkClength = lengthFinder(input);
				if (courseIdLength == checkClength)
				{
					int count = 0;
					for (int i = 0; i < courseIdLength; i++)
						if (courseID[i] == input[i])
							count++;
					if (count == courseIdLength)
					{
						WRITE << studentId << "\n"
							<< courseID << "\n";
						read >> input;
						WRITE<< section << "\n";
					}
					else
					{
						WRITE << studentId << "\n";
						WRITE << input << "\n";
						read >> input;
						WRITE << input << "\n";
					}
				}
				else
				{
					WRITE << studentId << "\n";
					WRITE << input << "\n";
					read >> input;
					WRITE << input << "\n";
				}
			}
			else
			{
				WRITE << input << "\n";
				read >> input;
				WRITE << input << "\n";
				read >> input;
				WRITE << input << "\n";
			}
		}
		WRITE.close();
		read.close();
		remove("studentRecord.txt");
		rename("tempFile.txt", "studentRecord.txt");
		cout << "\tUpdated!\n";
	}
	else
	{
		cout << "\tNot such ID found in the Record\n";
	}
}
void totalStudents()
{
	char* courseID = new char[50];
	cout << "\tEnter course Code : ";
	cin >> courseID;
	lowerToUpper(courseID);
	int length = lengthFinder(courseID);

	int totalCount = 0;
	bool available = isOffered(courseID);
	if (available)
	{
		ifstream read("studentRecord.txt");
		char* input = new char[50];
		while (read >> input)
		{
			read >> input;
			int inputLength = lengthFinder(courseID);
			if (length == inputLength)
			{
				int count = 0;
				for (int i = 0; i < length; i++)
					if (courseID[i] == input[i])
						count++;
				if (count == length)
				{
					totalCount++;
					read >> input;
				}
				else
					read >> input;
			}
			else
				read >> input;
		}
		if (totalCount == 0)
			cout << "\t" << courseID << " is not enrolled by any student\n";
		else
			cout << "\tTotal enrolled students for this course are: " << totalCount << "\n";
		read.close();
	}
	else
		cout << "\t" << courseID << " does not exist in Student Record\n";
}
void minimumEnrolingLilst()
{
	char* course = new char[50];
	int minimum = 0, given = 1;
	ifstream read("studentRecord.txt");
	if (!read)
	{
		cout << "\tNo course found\n";
		return;
	}
	char* input = new char[50];
	for (int i = 0; read >> input; i++)
	{
		read >> input;
		if (i == 0)
		{
			minimum = count(input, given, minimum);
			int cc = 0;
			for (int j = 0; j < lengthFinder(input); j++)
			{
				course[j] = input[j];
				cc++;
			}
			course[cc] = '\0';
			read >> input;
		}
		else
		{
			int compare = count(input, given, minimum);

			if (compare)
			{
				if (compare < minimum)
				{
					minimum = compare;
					int cc = 0;
					for (int j = 0; j < lengthFinder(input); j++)
					{
						course[j] = input[j];
						cc++;
					}
					course[cc] = '\0';
				}
				read >> input;
			}
			else
				read >> input;
		}
	}
	cout << "\t" << course << " has registered only " << minimum << " courses.\n";
	remove("temp.txt");

}
int count(char* courseID, int& given, int mini)
{
	char file[] = "temp.txt";
	bool alreadyCounted = false;
	if (given > 1)
	{
		alreadyCounted = overCount(courseID, file);
	}
	if (!alreadyCounted)
	{
		given++;
		int length = lengthFinder(courseID);
		ifstream read("studentRecord.txt");
		ofstream out("temp.txt", ios::app);
		char* input = new char[50];
		int miniCount = 0;
		while (read >> input)
		{
			read >> input;
			int inputLength = lengthFinder(input);
			if (length == inputLength)
			{
				int count = 0;
				for (int i = 0; i < length; i++)
					if (courseID[i] == input[i])
						count++;
				if (count == length)
				{
					miniCount++;
					out << input << "\n";
					read >> input;
				}
				else
					read >> input;
			}
			else
				read >> input;
		}
		read.close();
		return miniCount;
	}
	else
		return false;
}
void enrolledOrNot()
{
	char* courseID = new char[50];
	cout << "\tEnter ID : ";
	cin >> courseID;
	lowerToUpper(courseID);
	int length = lengthFinder(courseID);
	bool available = isOffered(courseID);
	if (available)
	{
		bool availableIf = true;
		ifstream read("studentRecord.txt");
		char* input = new char[50];
		while (read >> input)
		{
			read >> input;
			int inputLength = lengthFinder(input);
			if (length == inputLength)
			{
				int count = 0;
				for (int i = 0; i < length; i++)
					if (courseID[i] == input[i])
						count++;
				if (count == length)
				{
					read >> input;
					availableIf = false;
				}
			}
			else
				read >> input;
			if (!availableIf)
				break;
			read >> input;
		}
		if (availableIf)
			cout << "\t" << courseID << " is not enrolled by any student\n";
		else
			cout << "\tNo course found\n";
		read.close();
	}
	else
		cout << "\t" << courseID << " does not exist in Student Record\n";

}