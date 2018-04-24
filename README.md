# **Digital's C++ Header-Only Stack-Based Finite State Machine** 
This Finite State Machine utilised **State-Based functionality** to manage its states. (This type of StateMachine is also called a SFSM.) 

[_More information on SFSM's can be found here._](https://gamedevelopment.tutsplus.com/tutorials/finite-state-machines-theory-and-implementation--gamedev-11867)

Currently the states have **_OnEntry()_**, **_OnUpdate()_**, **_OnExit()_**, and **_IfFrom()_** functionality implemented. 

The SFSM is written in C++, is **header only**, currently exists out of **two files** and has (Doxygen) **documentation**.

---

## **Basic Usage:**
To use the SFSM, the user has to create a StateMachine and the States with functionality. Both the StateMachine and the States must be inside of a Class. To then update the StateMachine, the user has to call the **Update()** function or **UPDATE_STATEMACHINE** macro.

Since this SFSM uses templates, the States can easily get to their Owner class or Owner StateMachine with the **GetOwner()** and **GetFSM()** functions. Both functions return a pointer to their objects.

- _**CreateState()**_; Constructs a State, so that the StateMachine can use it. (Allocated State will be tracked by the StateMachine. When the StateMachine gets destroyed, the states will as well.)<br><br>
- _**Push()**_; Pushes a State on the stack and will be the topmost State after the push.
- _**Pop()**_; Removes/Pops the topmost State of the stack.
- _**ClearStateStack()**_; Removes all States of the Stack.<br><br>
- _**SetEnabled()**_; Enables/Disables the StateMachine.
    - When the StateMachine is disabled, the StateMachine will not update its States until it gets enabled.
-  _**SetLocked()**_; Locks/Unlocks the StateMachine.
    - When the StateMachine is locked, the StateMachine will continue to update its States, but you cannot Push a State, Pop a State, or Clear the stack, until the StateMachine gets unlocked.

[_Here you can find a code example on how to use the system._](/ExampleProject/Digital_SFSM/Include/ExampleObject.h)

---

## **Notes:** 
- Pushing/Popping/Clearing States only adds/removes a pointer of the State to the Stack of the StateMachine.
- The functions OnEntry(), OnExit(), and IfFrom() function get immediately called when either pushing or popping states.
- The call order When pushing a State; **OnExit()** of top most State > **Push** new topmost State > **OnEntry()** of new topmost State, **IfFrom()** of new topmost State. 
- The call order when popping; **OnExit()** of topmost State > **Pop** of topmost State > **OnEntry()** of new topmost State, **IfFrom()** of new State.

--- 
## **License:** 
Digital's C++ Header-Only Stack-Based Finite State Machine is licensed under the **Apache License 2.0**.

[_Here you can find more information about the license._](/LICENSE)