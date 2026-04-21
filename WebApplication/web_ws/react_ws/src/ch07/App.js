import React, {useEffect, useState, useRef} from "react";

// 수정 필요

export default function App() {

    const [count, setCount] = useState(0);
    const [isRunning, setIsRunning] = useState(false);

    const intervalRef = useRef(null);
    const prevCountRef = useRef(0);


    useEffect(() => {
        if (isRunning) {
            intervalRef.current = setInterval(() => {setCount((prev) => prev + 1);}, 1000);
        } else {
            clearInterval(intervalRef.current);
        }

        return () => clearInterval(intervalRef.current);
    }, [isRunning]);



    useEffect(() => {
        console.log("현재 값 : ", count);
        prevCountRef.current = count;
    }, [count]);

    const handleReset = () => {
        setIsRunning(false);
        setCount(0);
    }
    
    
    return(
        <div>
            <h2>Timer</h2>
            <p>현재 : {count}</p>
            <p>이전 : {prevCountRef.current}</p>
            <button onClick={() => setIsRunning(true)}>Start</button>
            <button onClick={() => setIsRunning(false)}>Pause</button>
            <button onClick={handleReset}>Reset</button>
        </div>
    );
}