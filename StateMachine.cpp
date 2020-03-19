#include "StateMachine.hpp"

//#include "Loggers.hpp"

bool IStateMachineState::handleEvent(std::string event)
{
    return false;
}

bool IStateMachine::handleEvent(std::string event)
{
    bool hasCurrentState = static_cast<bool>(m_currentState);
    if (m_currentState)
    {
        std::string currentStateName = m_currentState->stateName();
        if (m_transitionTable[currentStateName][event] or event == "*")
        {
            std::shared_ptr<IStateMachineState> newState;

            if (event == "*")
            {
                newState = m_defaultState;
            }
            else
            {
                newState = m_transitionTable[currentStateName][event];
            }

            if (newState->isEnterPossible())
            {
                // Пробуем выйти из старого состояния
                if (m_currentState->leave())
                {
                    m_currentState->onLeave();
                    // Пробуем войти в новое состояние
                    if (newState->enter())
                    {
                        m_currentState = newState;
                        newState->onEnter();
                        return true;
                    }
                    else
                    {
                        // Выходим из нового состояния, так как вход был не удачным
                        newState->leave();
                        // Входим в старое состояния
                        m_currentState->enter();
                    }
                }
                else
                {
                    // Входим в старое состояния, так как выход был не удачным
                    m_currentState->enter();
                }
            }
        }
        else
        {
            return m_currentState->handleEvent(event);
        }
    }

    return false;
}

void IStateMachine::setTransition(std::string stateName, std::string event, std::shared_ptr<IStateMachineState> state)
{
    m_transitionTable[stateName][event] = state;
}

IStateMachine::IStateMachine(std::shared_ptr<IStateMachineState> defaultState)
        : m_defaultState(defaultState)
        , m_currentState(m_defaultState)
{
//    setTransition(StateMachine::DefaultState::StateName, "*", m_defaultState);
    m_defaultState->enter();
}

IStateMachine::IStateMachine()
        : IStateMachine::IStateMachine(std::make_shared<DefaultState>())
{
}

StateMachine::StateMachine(std::shared_ptr<IStateMachineState> defaultState)
        : IStateMachine::IStateMachine(defaultState)
{
}

StateMachine::StateMachine()
        : IStateMachine::IStateMachine()
{
}

IStateMachine::~IStateMachine()
{
    m_currentState->leave();
}

std::shared_ptr<IStateMachineState> IStateMachine::currentState()
{
    return m_currentState;
}

const std::string StateMachine::DefaultState::StateName = "STATE_MACHINE_DEFAULT_STATE";
const std::string StateMachine::DefaultState::EnterEvent = "*";