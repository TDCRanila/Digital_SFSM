#pragma once


template <class T>
class State {
public:

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

protected:
	friend T;

	/** 
    */
	State() { /* Empty */ }

	/** 
    */
	virtual ~State() { /* Empty */ }

	/** 
	*/
    T* GetOwner() const;

private:
    template <class T>
    friend class StateMachine;

    /**
    */
    void Construct(T* const a_owner);

	T* owner_; /**< Pointer to the owner of this state. */

};

#pragma region Inline Functions
					
template <class T>
inline T* State<T>::GetOwner() const {
    return this->owner_;
}

template <class T>
inline void State<T>::Construct(T* const a_owner) {
    this->owner_ = a_owner;
}

#pragma endregion End of Inline Section