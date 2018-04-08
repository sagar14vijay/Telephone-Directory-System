#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Win32Project1/Admin.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test1
{        
    TEST_CLASS(UnitTest1)
    {
    public:
        
        TEST_METHOD(TestMethodCheck1)
        {
            Assert::AreEqual(1, Admin::check("Admin", "Admin"));
        }
        TEST_METHOD(TestMethodCheck3)
        {
            Assert::AreEqual(0, Admin::check("admin", "Admin"));
        }
        TEST_METHOD(TestMethodCheck3)
        {
            Assert::AreEqual(0, Admin::check("admin", "admin"));
        }
        TEST_METHOD(TestMethodCheck3)
        {
            Assert::AreEqual(0, Admin::check("Admin", "admin"));
        }


        TEST_METHOD(TestMethodCheck3)
        {
            Assert::AreEqual(0, Admin::contactno("123456789"));
        }
        TEST_METHOD(TestMethodCheck3)
        {
            Assert::AreEqual(1, Admin::contactno("1234567890"));
        }
        TEST_METHOD(TestMethodCheck3)
        {
            Assert::AreEqual(0, Admin::contactno("12345678912"));
        }


        TEST_METHOD(TestMethodCheck3)
        {
            Assert::AreEqual(0, Admin::pancard("123456789"));
        }
        TEST_METHOD(TestMethodCheck3)
        {
            Assert::AreEqual(1, Admin::pancard("1234567890"));
        }
        TEST_METHOD(TestMethodCheck3)
        {
            Assert::AreEqual(0, Admin::pancard("12345678912"));
        }


        

    };
}