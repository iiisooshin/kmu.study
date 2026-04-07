import React from "react";
import { useState, useRef } from "react";

export default function CountUseref() {

    const [state, setState] = useState(0);
    let variable = 0;
    const ref = useRef(0);

    return(
        // state : 값이 변할 때 마다 리랜더링
        // var : 값이 변해도 초기화
        // ref : 값은 변하지만 바로 리랜더링 x
        <div>
            <p>State : {state}</p>
            <button onClick={() => setState(state + 1)}>State Up</button>

            <p>Variable : {variable}</p>
            <button onClick={() => variable + 1}>Var Up</button>

            <p>Ref : {ref.current}</p>
            <button onClick={() => {ref.current++; console.log(ref.current);}}>Ref Up</button>
        </div>
    );
}