#pragma once

#include <StateMachine.h>

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
        void IfFrom(State<ExampleObject>* const a_previous_state, bool a_push_event) override;

    };

    class StateTwo : public State<ExampleObject> {
    private:
        void OnEntry() override;
        void OnUpdate() override;
        void OnExit() override;
        void IfFrom(State<ExampleObject>* const a_previous_state, bool a_push_event) override;

        bool boolean_;
    };

    StateOne* state_one_;
    StateTwo* state_two_;

    StateMachine<ExampleObject> state_machine_;

};