#include <ExampleObject.h>

#include <iostream>

ExampleObject::ExampleObject() { /*EMPTY*/ }

ExampleObject::~ExampleObject() { /*EMPTY*/ }

void ExampleObject::Oncreate() {
    // Create the states.
    state_one_ = state_machine_.CreateState<StateOne>(this);
    state_two_ = state_machine_.CreateState<StateTwo>(this);

    // Push Intial State.
    state_machine_.PushState(state_one_);
}

void ExampleObject::Update() {
    // Update the State Machine.h
    UPDATE_STATEMACHINE(state_machine_);
}

void ExampleObject::StateOne::OnEntry() {
    std::cout << "StateOne-OnEntry()" << std::endl;
}

void ExampleObject::StateOne::OnUpdate() {
    std::cout << "StateOne-OnUpdate()" << std::endl;
    this->GetOwner()->state_machine_.PushState(this->GetOwner()->state_two_);
}

void ExampleObject::StateOne::OnExit() {
    std::cout << "StateOne-OnExit()" << std::endl;
}

void ExampleObject::StateTwo::OnEntry() {
    std::cout << "StateTwo-OnEntry()" << std::endl;

}
void ExampleObject::StateTwo::OnUpdate() {
    std::cout << "StateTwo-OnUpdate()" << std::endl;
    if (boolean) {
        boolean = false;
        this->GetOwner()->state_machine_.PopState();
    } else {
        boolean = true;
        this->GetOwner()->state_machine_.PopState();
    }
}

void ExampleObject::StateTwo::OnExit() {
    std::cout << "StateTwo-OnExit() - " << boolean << std::endl;
}