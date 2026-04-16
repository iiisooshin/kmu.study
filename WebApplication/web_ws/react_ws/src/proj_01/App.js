import { useState, useEffect } from "react";
import Viewer from "./Viewer";
import Controller from "./Controller";
import './App.css'
import Even from "./Even";
import Timer from "./Timer";

export default function App() {

    const [count, setCount] = useState(0);
    const [text, setText] = useState("");
    const [start, setStart] = useState(false);
    

    function handleSetCount(value) {
        setCount(count + value);
    }

    function handleSetText(e) {
        setText(e.target.value);
    }

    function buttonOnClick() {
            setStart(!start);
        }

    // useEffect(() => {
    //     console.log("count 업데이트!")
    // }, [count]);

    // useEffect(() => {
    //     console.log("text 업데이트!")
    // }, [text]);

    // 1. 컴포넌트 마운트 시점
    useEffect(() => {
        console.log("컴포넌트 Mount")
    }, []);
    
    // 2. 컴포넌트 업데이트 시점
    useEffect(() => {
        console.log("컴포넌트 Update")
    });

    // 3. count 제거 시점
    useEffect(() => {
        console.log("count 업데이트")
        return () => {
            console.log("count 제거")
        }
    }, [count]);

    // 4. 의존성 값 업데이트
    // useEffect(() => {
    //     console.log("값 업데이트", count, text)
    // }, [count, text])
    
    

    return(
        <div className="App">
            <h1>Counter App</h1>
            <div>
                <input value={text} onChange={handleSetText} />
                <p>{text}</p>
            </div>
            <div>
                <Viewer count={count}></Viewer>
                {count % 2 === 0 && <Even />}
            </div>
            <div>
                <Controller handleSetCount={handleSetCount}></Controller>
            </div>
            <div>
                <h2>Timer</h2>
                {start &&<Timer />}
                <button onClick={buttonOnClick}>Timer</button>
            </div>
        </div>
    );
}