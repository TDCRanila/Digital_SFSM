#pragma once

#include <vector>

#include <State.h>

template <class T>
class StateMachine final {
public:

	/** 
    *   Default StateMachine Constructor 
    */
	StateMachine()	{ /* Empty */ }

	/** 
    *   Default StateMachine Destructor
    */
    ~StateMachine();

	/** 
	*/
	void Update() const;

    /**
    */
    template <class S>
    void CreateState(S** a_state_pointer, T* a_owner);

	/**
	*/
	void PushState(State<T>* a_state, bool a_caLL_exit = true, bool a_call_entry = true);

	/**
	*/
	void PopState(bool a_call_exit = true, bool a_call_entry = true);

    /**
    */
    void ClearStateStack() const;

    /**
    */
    State<T>* GetCurrentState() const;

    /**
    */
    template <class S>
    S* GetState() const;

    /**
    */
    State<T>* GetStateByIndex(int a_index) const;

private:

	std::vector<State<T>*> state_stack_;    /**< All the states that this StateMachine currently holds in its stack memory. */
    std::vector<State<T>*> tracked_states_; /**< All the states tracked by this StateMachine. These states will get deleted on destroy of the state machine */ 

};

#pragma region Macros

#define UPDATE_STATEMACHINE(a_state_machine) a_state_machine.Update();

#define DESTROY_STATEMACHINE(a_state_machine)   \
if (a_state_machine != nullptr) {               \
    delete a_state_machine;                     \
    a_state_machine = nullptr;                  \
}

#pragma endregion End of Macro Section

#pragma region Implementation - StateMachine

template <class T>
inline StateMachine<T>::~StateMachine() {
    // Delete all tracked states;
    for (auto& state : tracked_states_) {
        if (state != nullptr) {
            delete state;
            state = nullptr;
        }
    }
}

template <class T>
inline void StateMachine<T>::Update() const {
    // Update ~ Only if we have a valid state on the stack.
    if (State<T>* current_state = GetCurrentState()) {
        current_state->OnUpdate();
    }
}

template <class T>
template <class S>
inline void StateMachine<T>::CreateState(S** a_state_pointer, T* a_owner) {
    // Check if the state already has been created ~ If not create it.
    if (S* state = GetState<S>()) {
        (*a_state_pointer) = state;
        return; // State already exists ~ Return pointer to it.
    } else {
        (*a_state_pointer) = new S();
        (*a_state_pointer)->Construct(a_owner, this);
        this->tracked_states_.push_back(*a_state_pointer);
        return;
    }

}

template <class T>
inline void StateMachine<T>::PushState(State<T>* a_state, bool a_call_exit, bool a_call_entry) {
	// Old State ~ Exit 
	if ((a_call_exit) && (!state_stack_.empty())) {
		State<T>* exit_state = this->state_stack_.back();
		_ASSERT(exit_state);
        exit_state->OnExit();
	}

	// New State ~ Entry
	_ASSERT(a_state);
    this->state_stack_.push_back(a_state);
	if (a_call_entry) {
        a_state->OnEntry();
	}
}

template <class T>
inline void StateMachine<T>::PopState(bool a_call_exit, bool a_call_entry) {
    // Check ~ Don't pop if there are no states on the stack.
	if (this->state_stack_.empty()) { return; }
	
    // Old State ~ Calls OnExit()
    if (a_call_exit) {
		State<T>* exit_state = this->state_stack_.back();
		_ASSERT(exit_state);
		exit_state->OnExit();
	}
	this->state_stack_.pop_back();
 
    // Check ~ Don't call OnEntry() when there are no states left on the stack.
	if (this->state_stack_.empty()) { return; }

    // New State ~ Calls OnEntry()
    if (a_call_entry) {
		State<T>* entry_state = this->state_stack_.back();
		_ASSERT(entry_state);
        entry_state->OnEntry();
	}
}

template <class T>
inline void StateMachine<T>::ClearStateStack() const {
    this->state_stack_.clear();
}

template <class T>
inline State<T>* StateMachine<T>::GetCurrentState() const {
    if (state_stack_.empty()) {
        return nullptr;
    } else {
        return this->state_stack_.back();
    }
}

template <class T>
template <class S>
inline S* StateMachine<T>::GetState() const {
    for (auto& state_it : state_stack_) {
        if (S* state = dynamic_cast<S*>(state_it)) {
            return state;
        }
    }

    return nullptr;
}

template <class T>
inline State<T>* StateMachine<T>::GetStateByIndex(int a_index) const {
    if (a_index > this->state_stack_.size()) {
        return nullptr;
    } else {
        return this->state_stack_[a_index];
    }
}

#pragma endregion Inline Function Defines