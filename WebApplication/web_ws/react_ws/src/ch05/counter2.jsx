import React, {useState} from "react";
import Even from "./even";

function Counter2(props) {

    const [count, setCount] = useState(0);


    function plus() {
        setCount(count + 1);
        console.log(count);
    }
    
    function minus() {
        setCount(count - 1);
        console.log(count);
    }

    function multiply() {
        setCount(count * 2);
        console.log(count);
    }

    function divide() {
        setCount(count / 2);
        console.log(count);
    }

    


    return(
        <div className="Counter2">
            <p>현재 값: {count}</p>
            <Even number={count}></Even>
            <button onClick={plus}>+</button>
            <button onClick={minus}>-</button>
            <button onClick={multiply}>x2</button>
            <button onClick={divide}>/2</button>

        </div>
    );

}

export default Counter2;