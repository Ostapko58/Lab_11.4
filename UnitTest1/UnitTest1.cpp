#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_11.4/Lab_11.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Electr stud;
			Electr stud2;
			TimeSort(stud, 5, "start.bin");
			ifstream f("start.bin");
			ifstream g("finish.bin");
			for (int i = 0; i < 5; i++)
			{
				f.seekg(i * (long)sizeof(Electr)); // встановили вказівник
				f.read((char*)&stud, sizeof(Electr));
				g.seekg(i * (long)sizeof(Electr)); // встановили вказівник
				g.read((char*)&stud2, sizeof(Electr));
				Assert::AreEqual(stud.prizn, stud2.prizn);
				Assert::AreEqual(stud.time[0], stud2.time[0]);
				Assert::AreEqual(stud.time[1], stud2.time[1]);
			}

		}
	};
}
