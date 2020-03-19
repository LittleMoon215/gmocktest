#pragma once

#include <memory>
#include <list>
#include <map>
#include <iostream>

class IStateMachine;
class IStateMachineState
{
public:
    IStateMachineState() = default;
    virtual ~IStateMachineState() = default;

    IStateMachine & parent() const;
    virtual bool enter() = 0;
    virtual void onEnter() {};
    virtual bool leave() = 0;
    virtual void onLeave() {};
    virtual bool isEnterPossible() { return true; };
    virtual std::string stateName() const = 0;
    virtual bool handleEvent(std::string event);

};

class IStateMachine
{
public:
    class DefaultState : public IStateMachineState
    {
    public:
        bool enter() override { return true; }
        bool leave() override { return true; }
        std::string stateName() const override { return DefaultState::StateName; };
        static const std::string StateName;
        static const std::string EnterEvent;
    };

    IStateMachine();
    IStateMachine(std::shared_ptr<IStateMachineState>);
    virtual ~IStateMachine() = 0;

    void setTransition(std::string stateName, std::string event, std::shared_ptr<IStateMachineState>);

    template <typename From, typename To>
    void setTransition(std::shared_ptr<IStateMachineState> state)
    {
        setTransition(From::StateName, To::EnterEvent, state);
    }

    template <typename From>
    void setTransition(std::string event, std::shared_ptr<IStateMachineState> state)
    {
        setTransition(From::StateName, event, state);
    }

    virtual std::shared_ptr<IStateMachineState> currentState();
    virtual bool handleEvent(std::string event);

private:
    std::shared_ptr<IStateMachineState> m_defaultState = nullptr;
    std::shared_ptr<IStateMachineState> m_currentState = nullptr;
    std::map<std::string,
            std::map<std::string,
                    std::shared_ptr<IStateMachineState>
            >
    > m_transitionTable;
};

class StateMachine
        : public IStateMachine
{
public:
    class State
            : public IStateMachineState
                    , public IStateMachine
    {
    public:
        State() : IStateMachineState()
        {
        }

        bool handleEvent(std::string event) override
        {
            return IStateMachine::handleEvent(event);
        }

        bool leave() override
        {
            return IStateMachine::handleEvent("*");
        }

    };

    StateMachine(std::shared_ptr<IStateMachineState> defaultState);
    StateMachine();

};
