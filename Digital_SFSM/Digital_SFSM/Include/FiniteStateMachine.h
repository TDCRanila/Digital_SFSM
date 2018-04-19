#pragma once

#include <vector>

#include <State.h>

/**
*   \file FiniteStateMachine.h
*
*   This file contains the implentation of the StateMachine class.
*
*   \author TDCRanila/Chan
*   \version 1.0
*
*/

/**
*   \class StateMachine
*   \bug No known bugs to be reported.
*
*   \pre Use UPDATE_STATEMACHINE or Update(), to update the StateMachine class.
*   \pre StateMachine is a templated class, so make sure you specify the type. Type should be the owner of this StateMachine.
*   
*   \brief StateMachine Class is where the main implementation of the finite state machine lies.
*   The StateMachine manages/controls/updates the states that it owns.
*
*   The StateMachine contains memory of pushed/popped states. (The Stack)
*   Whenever the StateMachine gets updated, the topmost State gets updated.
*   When the stack is empty, no states will be updated.
*
*   When pushing a State, the State will be added on the top of the stack.
*   When popping a State, the topmost State will be removed from the stack.
*   
*   \note The stack of the StateMachine only holds pointers to states.
*   \note When creating new states, the State Machine keeps track of them and will eventually delete its tracked states whenever the StateMachine gets deleted.
*
*/
template <class T>
class StateMachine final {
public:

	/** 
    *   Default StateMachine Constructor 
    */
    StateMachine();

	/** 
    *   Default StateMachine Destructor ~ Deletes all tracked states.
    */
    ~StateMachine();

	/** 
    *   Function updates the current/latest State on the stack.
	*/
	void Update() const;

    /**
    *   Function locks or unlocks the StateMachine. Locking will prevent any changes being made for this StateMachine.
    *   Pushing, Popping, and Clearing of states will be prevented when locked.
    *   \param bool a_enabled Boolean specifies whether the StateMachine should be locked or not.
    */
    void SetLocked(bool a_locked);

    /**
    *   Function returns a boolean specifing whether the StateMachine is locked or not.
    *   \return bool Returns True ~ if the StateMachine is locked. False ~ if it isn't locked.
    */
    bool IsLocked() const;

    /**
    *   Function enables or disables the StateMachine. Disabling it will prevent it from updating.
    *   \param bool a_enabled Boolean specifies whether the StateMachine should be enabled or not.
    */
    void SetEnabled(bool a_enabled);

    /**
    *   Function returns a boolean specifing whether the StateMachine is disabled or not.
    *   \return bool Returns True ~ if the StateMachine is enabled. False ~ if it is disabled.
    */
    bool IsEnabled() const;

    /**
    *   Allocates/Creates a State for this StateMachine. The created State will be tracked by the StateMachine.
    *   \tparam S* a_state_pointer Pointer to a State pointer.
    *   \tparam T* a_owner Pointer to the owner of the State (pointer).
    */
    template <class S>
    void CreateState(S** a_state_pointer, T* a_owner);

	/**
    *   Function pushes a State on top of the stack. Also calls the entry/exit functions of the states.
    *   \param State* a_state Pointer to the State that you want to push on the stack.
    *   \param bool a_call_exit If True ~ Calls the OnExit() function of the previous State. If False ~ Ignores the call.
    *   \param bool a_call_entry If True ~ Calls the OnEntry() function of the newly pushed State. If False ~ Ignores the call.
	*/
	void PushState(State<T>* a_state, bool a_call_exit = true, bool a_call_entry = true);

	/**
    *   Function removes the topmost State of the stack. Also calls the entry/exit functions of the states.
    *   \param bool a_call_exit If True ~ Calls the OnExit() function of the State that is going to be removed from the stack. If False ~ Ignores the call.
    *   \param bool a_call_entry If True ~ Calls the OnEntry() function of the new topmost State on the stack. If False ~ Ignores the call.
	*/
	void PopState(bool a_call_exit = true, bool a_call_entry = true);

    /**
    *   Function clears the whole stack of the StateMachine.
    *   \note Doesn't deallocate the states. Only removes the pointer of the states of stacks.
    */
    void ClearStateStack() const;

    /**
    *   Function returns the topmost State on the stack of the StateMachine.
    *   \return Pointer to the State.
    */
    State<T>* GetCurrentState() const;

    /**
    *   Function returns the specfied State with the template parameters if it is currently present on the stack.
    *   \note If it isn't present on the stack, function returns nullptr.
    *   \note If multiple classes of this type are present on the stack. Function returns the first instance that it can find on the stack.
    *   \return Pointer to the specified State type.
    */
    template <class S>
    S* GetState() const;

    /**
    *   Function returns vector of pointers to the states of the specified type if they are currently present on the stack.
    *   \note If there are no states of the type present on the stack, function returns an empty vector.
    *   \return Vector of pointers to the specified State type.
    */
    template <class S>
    std::vector<S*> GetStatesByType() const;

    /**
    *   Function returns a State with the specified index on the stack.
    *   \note If it cannot find a State with this index, it returns nullptr. (For instance, vector out of range or negative number.)
    *   \param size_t a_index Index that you want to search for in the stack.
    *   \return Pointer to the State with this index.
    */
    State<T>* GetStateByIndex(size_t a_index) const;

private:

    bool enabled_;                          /**< Boolean specifies whether the StateMachine is enabled or not. */
    bool locked_;                           /**< Boolean specifies whether the StateMachine is locked or not. */

	std::vector<State<T>*> state_stack_;    /**< Vector of all the states that this StateMachine currently holds in its stack memory. */
    std::vector<State<T>*> tracked_states_; /**< Vector of all states tracked by this StateMachine. These states will get deleted on destroy of the state machine */ 

};

#pragma region Macros

#define UPDATE_STATEMACHINE(a_state_machine) a_state_machine.Update();

#define NEW_STATEMACHINE(a_state_machine) a_state_machine = new StateMachine();

#define DESTROY_STATEMACHINE(a_state_machine)   \
if (a_state_machine != nullptr) {               \
    delete a_state_machine;                     \
    a_state_machine = nullptr;                  \
}

#pragma endregion End of Macro Section

#pragma region Implementation - StateMachine

template <class T>
inline StateMachine<T>::StateMachine() :
    enabled_(true),
    locked_(false)
{
    /* Empty */
}

template <class T>
inline StateMachine<T>::~StateMachine() {
    // Delete all tracked states.
    for (auto& state : tracked_states_) {
        if (state != nullptr) {
            delete state;
            state = nullptr;
        }
    }
}

template <class T>
inline void StateMachine<T>::Update() const {
    // Update ~ Only if the StateMachine is enabled and if there is a valid state on the stack.
    if (!enabled_) { return; }
    if (State<T>* current_state = GetCurrentState()) {
        current_state->OnUpdate();
    }
}

template <class T>
inline void StateMachine<T>::SetLocked(bool a_locked) {
    this->locked_ = a_locked;
}

template <class T>
inline bool StateMachine<T>::IsLocked() const {
    return this->locked_;
}

template <class T>
inline void StateMachine<T>::SetEnabled(bool a_enabled) {
    this->enabled_ = a_enabled;
}

template <class T>
inline bool StateMachine<T>::IsEnabled() const {
    return this->enabled_;
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
    // Check if locked
    if (this->locked_) { return; }

	// Old State ~ Call OnExit()
	if ((a_call_exit) && (!state_stack_.empty())) {
		State<T>* exit_state = this->state_stack_.back();
		_ASSERT(exit_state);
        exit_state->OnExit();
	}

	// New State ~ Calls OnEntry()
	_ASSERT(a_state);
    this->state_stack_.push_back(a_state);
	if (a_call_entry) {
        a_state->OnEntry();
	}
}

template <class T>
inline void StateMachine<T>::PopState(bool a_call_exit, bool a_call_entry) {
    // Check if locked
    if (this->locked_) { return; }

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
    // Check if locked
    if (this->locked_) { return; }

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
template <class S>
std::vector<S*> StateMachine<T>::GetStatesByType() const {
    std::vector<S*> temp_vector;
    for (auto& state_it : state_stack_) {
        if (S* state = dynamic_cast<S*>(state_it)) {
            temp_vector.push_back(state);
        }
    }

    return temp_vector;
}

template <class T>
inline State<T>* StateMachine<T>::GetStateByIndex(size_t a_index) const {
    if (a_index > this->state_stack_.size()) {
        return nullptr;
    } else {
        return this->state_stack_[a_index];
    }
}

#pragma endregion Inline Function Defines