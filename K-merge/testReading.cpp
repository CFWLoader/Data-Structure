#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	ifstream in("./datas/testSmall.dat");

	uint64_t num;

	while(!in.eof())
	{

		in >> num;

		cout << num << endl;

	}

	in.close();

	return 0;
}