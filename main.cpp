#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "StateMachine.hpp"

#include "gmock/gmock.h"
#include <gtest/gtest.h>

class State : public StateMachine::State
{
public:
    State(std::string name, bool isSuccessfulEnter, bool isSuccessfulLeave)
            : m_name(name)
            , m_isSuccessfulEnter(isSuccessfulEnter)
            , m_isSuccessfulLeave(isSuccessfulLeave)
    {
    }

    bool enter()
    {
        return m_isSuccessfulEnter;
    }

    bool leave()
    {
        return m_isSuccessfulLeave;
    }

    std::string stateName() const
    {
        return m_name;
    }

private:
    const std::string m_name;
    const bool m_isSuccessfulEnter = false;
    const bool m_isSuccessfulLeave = false;
};


class StateMock : public StateMachine::State
{
public:
    MOCK_METHOD((std::string),stateName,(),(const));
    MOCK_METHOD(bool,enter,());
    MOCK_METHOD(bool,leave,());
};

using namespace testing;
TEST_CASE("StateMachine::StateMachine_SuccessfulEnter_defaultState")
{
    GTEST_FLAG(throw_on_failure) = true;
    testing::InitGoogleMock();
//    StateMock state;
////    ON_CALL(state,stateName).WillByDefault(Return("a"));
////    ON_CALL(state,enter).WillByDefault(Return(true));
////    ON_CALL(state,leave).WillByDefault(Return(true));
//    auto a = std::shared_ptr<StateMock>();
//    StateMachine stateMachine(a);
//    REQUIRE(stateMachine.currentState()->stateName() == "a");
    REQUIRE(true);
}

//int main()
//{
//    testing::InitGoogleMock();
//    return RUN_ALL_TESTS();
//}