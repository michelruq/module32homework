// ConsoleApplication1.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
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
    // ���������� ��������� GTest ��� ����������� ���-������� � �������
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

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.
