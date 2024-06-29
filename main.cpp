// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class DBConnectionInterface
{
public:
    DBConnectionInterface()
    {}

    virtual ~DBConnectionInterface()
    {}

    virtual void Open() = 0;
    virtual void Close() = 0;
    virtual void execQuery() = 0;
};

class classThatUsesDB
{
public:
    classThatUsesDB(DBConnectionInterface* dbConnection) : usedConnection(dbConnection)
    {}
    void openConnection()
    {
        usedConnection->Open();
    }

    void useConnection()
    {
        usedConnection->execQuery();
    }

    void closeConnection()
    {
        usedConnection->Close();
    }

private:
    DBConnectionInterface* usedConnection;
};

class MockConnection : public DBConnectionInterface {
public:
    // пользуемся макросами GTest для определения мок-методов в объекте
    MOCK_METHOD(void, Open, (), (override));
    MOCK_METHOD(void, execQuery, (), (override));
    MOCK_METHOD(void, Close, (), (override));
};

TEST(ConnectionTest, testOpen)
{
    MockConnection mdbconnection;
    classThatUsesDB oClassThatUsesDB(&mdbconnection);

    EXPECT_CALL(mdbconnection, Open).Times(::testing::AtLeast(1));
   
    oClassThatUsesDB.openConnection();

}

TEST(ConnectionTest, testUseConnection)
{
    MockConnection mdbconnection;
    classThatUsesDB oClassThatUsesDB(&mdbconnection);

    EXPECT_CALL(mdbconnection, execQuery).Times(::testing::AtLeast(1));

    oClassThatUsesDB.useConnection();

}

TEST(ConnectionTest, testClose)
{
    MockConnection mdbconnection;
    classThatUsesDB oClassThatUsesDB(&mdbconnection);

    EXPECT_CALL(mdbconnection, Close).Times(::testing::AtLeast(1));

    oClassThatUsesDB.closeConnection();
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
