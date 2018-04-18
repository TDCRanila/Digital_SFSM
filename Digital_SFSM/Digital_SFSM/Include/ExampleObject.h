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
    private:
        void OnEntry() override;
        void OnUpdate() override;
        void OnExit() override;
    };

    class StateTwo : public State<ExampleObject> {
    private:
        void OnEntry() override;
        void OnUpdate() override;
        void OnExit() override;

        bool boolean;
    };

    StateOne* state_one_;
    StateTwo* state_two_;

    StateMachine<ExampleObject> state_machine_;

};