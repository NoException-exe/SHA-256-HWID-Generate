#include "HwidHash.h"
#include "./hwid/hwid.hpp"


using namespace std;



int main()
{
	hwid->pcInformation();
	cout << "SHA-256 HWID: " << hwid->hwidHash() << endl << endl;
	system("pause");
	return 0;
}
