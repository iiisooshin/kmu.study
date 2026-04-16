import React, {useState} from "react";
import Timer from "./Timer";

export default function App() {

    const [start, setStart] = useState(false);
    const [interval, setInterval] = useState(false);


    function buttonOnStart() {
        setStart(true);
    }
    
    function buttonOnReset() {
        setStart(false);
    }
    
    function buttonOnPause() {
        setInterval(true);
    }
    
    function Interval() {
        <div>
            <p>{}</p>
        </div>
    }
    
    
    return(
        <div>
            <h2>Timer</h2>
            {start && <Timer />}
            <button onClick={buttonOnStart}>Start</button>
            <button onClick={buttonOnPause}>Pause</button>
            <button onClick={buttonOnReset}>Reset</button>
            {interval && <Interval />}
        </div>
    );
}