#pragma once

/**
*   \file State.h
*
*   This file contains the implentation of the State class.
*
*   \author TDCRanila/Chan
*   \version 1.0
*
*/

/**
*   \class State
*   \bug No known bugs to be reported.
*
*   \pre Since State is an abstract class, make sure to implement the (pure) virtual functions in the derived class.
*   \pre State is a templated class, so make sure you specify the type. Type should be the owner of this State.
*
*   \brief State is an abstract base class. Make sure to implement the following;
*
*   OnEntry();  Gets called whenever a State gets pushed to the stack of the StateMachine.
*   OnUpdate(); Gets called whenever a State gets updated by the StateMachine.
*   OnExit();   Gets called whenever a State gets popped off the stack of the StateMachine.
*
*/
template <class T>
class State {
private:
    template <class T>
    friend class StateMachine;

protected:

	/** 
    *   Default State Constructor
    */
    State();

	/** 
    *   Default State Virtual Destructor
    */
    virtual ~State();

	/**
    *   Function returns a pointer to the owner.
    *   \return Pointer to the owner.
	*/
    T* GetOwner() const;

    /**
    *   Function returns a pointer of the owner's StateMachine.
    *   \return StateMachine Pointer to the owner's StateMachine.
    */
    StateMachine<T>* GetFSM() const;

private:

    /**
    *   Virtual OnEntry Function. Gets called whenever a State gets pushed to the stack of the StateMachine.
    */
    virtual void OnEntry();

    /**
    *   Pure Virtual OnUpdate Functoin. Gets called whenever a State gets updated by the StateMachine.
    */
    virtual void OnUpdate() = 0;

    /**
    *   Virtual OnExit Function. Gets called whenever a State gets popped off the stack of the StateMachine.
    */
    virtual void OnExit();

    /**
    *
    *virtual void IfFrom(State* _previousState);
    */

    /**
    *   Function used to construct the state before proper use.
    *   \tparam T* a_owner Pointer to the owner of the State/StateMachine.
    *   \param StateMachine* a_owner_state_machine Pointer to StateMachine of the owner.
    */
    void Construct(T* const a_owner, StateMachine<T>* const a_owner_state_machine);

	T* owner_;                                  /**< Pointer to the owner of this state. */
    StateMachine<T>* owner_state_machine_;      /**< Pointer to the StateMachine of the owner. */

};

#pragma region Inline Functions
	
template <class T>
inline State<T>::State() { /* Empty */ }

template <class T>
inline State<T>::~State() { /* Empty */ }

template <class T>
inline T* State<T>::GetOwner() const {
    return this->owner_;
}

template <class T>
inline StateMachine<T>* State<T>::GetFSM() const {
    return this->owner_state_machine_;
}

template <class T>
inline void State<T>::OnEntry() { /* Empty */ }

template <class T>
inline void State<T>::OnExit() { /* Empty */ }

template <class T>
inline void State<T>::Construct(T* const a_owner, StateMachine<T>* const a_owner_state_machine) {
    this->owner_                = a_owner;
    this->owner_state_machine_  = a_owner_state_machine;
}

#pragma endregion End of Inline Section