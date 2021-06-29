# 10 builtin hooks
[[cs_learning]]
previosuly state was tightly coupled with a class constructor (component)
complex nested tree of components

## useState
handle reactive data
rerender
arg = default state
`const [value, setValue] = useState(0)`

## useEffect
component lifecycle
1. mounted
2. did update
3. unmount

```
useEffect(() => console.log('hello'));
useEffect(() => console.log('hello'), []); // no deps
useEffect(() => console.log('hello'), [state]); // rerun on state change
useEffect(() => {
console.log('hello')
return () => console.log('teardown')
}, [state]); // teardown function / cleanup
```

## useContext
context provider -> consumer

## useRef
mutable value that does not rerender UI
or get HTML elements from the DOM

## useReducer
![File:Ngrx-redux-pattern-diagram.png - Wikimedia Commons](https://upload.wikimedia.org/wikipedia/commons/0/06/Ngrx-redux-pattern-diagram.png)
redux pattern
```
const reducer = (state, action) => {
	if (action.type === 'inc') {
		return state + 1;
	}
}

const [state, dispatch] = useReducer(reducer, 0);

<button onClick={() => dispatch({type: 'inc'})}/>
```

## useMemo
memoise the value, pass the dependencies

## useCallback
memoise an entire function
each time the component is rerendered a new fn obj is created
prevent unnecessary rerenders due to function obj changes

## useImperativeHandle

## useLayoutEffect
after render but before update to screen
calc scroll pos, etc

## useDebugValue
helps while building custom hooks