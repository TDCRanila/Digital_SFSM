#pragma once

template <class T>
class State {
private:
    template <class T>
    friend class StateMachine;

protected:

	/** 
    */
	State() { /* Empty */ }

	/** 
    */
	virtual ~State() { /* Empty */ }

	/** 
	*/
    T* GetOwner() const;

    /**
    */
    StateMachine<T>* GetFSM() const;

private:

    /**
    */
    virtual void OnEntry() { /*EMPTY*/ }

    /**
    */
    virtual void OnUpdate() = 0;

    /**
    */
    virtual void OnExit() { /*EMPTY*/ }

    /**
    *
    *virtual void IfFrom(State* _previousState);
    */

    /**
    */
    void Construct(T* const a_owner, StateMachine<T>* const a_owner_state_machine);

	T* owner_;                                  /**< Pointer to the owner of this state. */
    StateMachine<T>* owner_state_machine_;      /**< Pointer to the state machine of the owner. */

};

#pragma region Inline Functions
					
template <class T>
inline T* State<T>::GetOwner() const {
    return this->owner_;
}

template <class T>
inline StateMachine<T>* State<T>::GetFSM() const {
    return this->owner_state_machine_;
}

template <class T>
inline void State<T>::Construct(T* const a_owner, StateMachine<T>* const a_owner_state_machine) {
    this->owner_                = a_owner;
    this->owner_state_machine_  = a_owner_state_machine;
}

#pragma endregion End of Inline Section