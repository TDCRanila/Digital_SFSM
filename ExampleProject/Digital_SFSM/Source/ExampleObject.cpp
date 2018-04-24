#include <ExampleObject.h>

#include <iostream>

ExampleObject::ExampleObject() { /*EMPTY*/ }

ExampleObject::~ExampleObject() { /*EMPTY*/ }

void ExampleObject::Oncreate() {
    // Create the states.
    state_machine_.CreateState(&this->state_one_, this);
    state_machine_.CreateState(&this->state_two_, this);

    // Push Intial State.
    std::cout << "#FSM Start - Pushing State - StateOne#" << std::endl;
    state_machine_.PushState(state_one_);
}

void ExampleObject::Update() {
    // Update the StateMachine.
    UPDATE_STATEMACHINE(this->state_machine_);
}

void ExampleObject::StateOne::OnEntry() {
    std::cout << "StateOne-OnEntry()" << std::endl;
}

void ExampleObject::StateOne::OnUpdate() {
    std::cout << "StateOne-OnUpdate()" << std::endl;
    std::cout << "#Pushing State - StateTwo#" << std::endl;
    this->GetFSM()->PushState(this->GetOwner()->state_two_);
}

void ExampleObject::StateOne::OnExit() {
    std::cout << "StateOne-OnExit()" << std::endl;
}

void ExampleObject::StateOne::IfFrom(State<ExampleObject>* const a_previous_state, bool a_push_event) {

    std::cout << "StateOne-IfFrom() - ";
    if (a_push_event) {
        std::cout << "Called during Push Event" << std::endl;
    } else {
        std::cout << "Called during Pop Event" << std::endl;
    }

    // Check ~ If StateOne.
    if (State<ExampleObject>* previous_state = dynamic_cast<ExampleObject::StateOne*>(a_previous_state)) {
        std::cout << "StateOne-IfFrom() - StateOne is previous state." << std::endl;
    }

    // Check ~ If StateTwo.
    if (State<ExampleObject>* previous_state = dynamic_cast<ExampleObject::StateTwo*>(a_previous_state)) {
        std::cout << "StateOne-IfFrom() - StateTwo is previous state." << std::endl;
    }
}

void ExampleObject::StateTwo::OnEntry() {
    std::cout << "StateTwo-OnEntry()" << std::endl;
}

void ExampleObject::StateTwo::OnUpdate() {
    std::cout << "StateTwo-OnUpdate()" << std::endl;
    if (boolean_) {
        boolean_ = false;
        std::cout << "#Popping State#" << std::endl;
        this->GetFSM()->PopState();
    } else {
        boolean_ = true;
    }
}

void ExampleObject::StateTwo::OnExit() {
    std::cout << "StateTwo-OnExit() - BooleanValue: " << boolean_ << std::endl;
}

void ExampleObject::StateTwo::IfFrom(State<ExampleObject>* const a_previous_state, bool a_push_event) {
    
    std::cout << "StateTwo-IfFrom() - ";
    if (a_push_event) {
        std::cout << "Called during Push Event" << std::endl;
    } else {
        std::cout << "Called during Pop Event" << std::endl;
    }

    // Check ~ If StateOne.
    if (State<ExampleObject>* previous_state = dynamic_cast<ExampleObject::StateOne*>(a_previous_state)) {
        std::cout << "StateTwo-IfFrom() - StateOne is previous state." << std::endl;
    }

    // Check ~ If StateTwo.
    if (State<ExampleObject>* previous_state = dynamic_cast<ExampleObject::StateTwo*>(a_previous_state)) {
        std::cout << "StateTwo-IfFrom() - StateTwo is previous state." << std::endl;
    }
}