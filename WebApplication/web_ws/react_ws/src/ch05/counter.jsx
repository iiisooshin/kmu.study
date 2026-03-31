import React, {useState} from "react";

function Counter(props){
    const [count, setCount] = useState(0);

    function plus(){
        setCount(count + 1);
        console.log(count);
    }

    return(
        <div>
            <p>총 {count}번 클릭.</p>
            <button onClick={plus}>클릭</button>
        </div>
    );
}

export default Counter;