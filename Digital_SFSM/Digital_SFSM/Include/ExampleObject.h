#pragma once

#include <FiniteStateMachine.h>

class ExampleObject {
public:
    ExampleObject();
    ~ExampleObject();

    void Oncreate();
    void Update();

private:

    class StateOne : public State<ExampleObject> {
    public:
        void OnEntry();
        void OnUpdate();
        void OnExit();
    };

    class StateTwo : public State<ExampleObject> {
    public:
        void OnEntry();
        void OnUpdate();
        void OnExit();
    private:
        bool boolean;
    };

    StateOne* state_one_;
    StateTwo* state_two_;

    StateMachine<ExampleObject> state_machine_;

};