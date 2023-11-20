# SHA-256 HWID HASH GENERATOR

was used [PicoSHA2.h](https://github.com/okdshin/PicoSHA2.git) to generate the SHA-256 Hash


## Main

```cpp
﻿#include "HwidHash.h"
#include "./hwid/hwid.hpp"

using namespace std;

int main()
{
	hwid->pcInformation(); //show all pc information
	cout << "SHA-256 HWID: " << hwid->hwidHash() << endl << endl; //show HWID Hash
	system("pause");
	return 0;
}

```

output using hwid->pcInformation() function

```
Computer Name: DESKTOP-BCNTVQD
Cpu Name: AMD Ryzen 7 5800X 8-Core Processor
Gpu Name: NVIDIA GeForce RTX 3070
MAC Address: D6:8E:D7:D4:6C:91
Ram: 32690
```

output using hwid->hwidHash() function
```
d1c5c7ce90f5b41f5461bf3f8920bc4aa7fd514f10b3aa7f21c8ee79086aaa1f
```

