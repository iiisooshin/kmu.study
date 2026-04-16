import React, {useEffect, useState, useRef} from "react";

export default function Timer() {
    
    const [time, setTime] = useState(0);
    const ref = useRef(0);


    useEffect(() => {

        console.log("Timer Started");

        const timerId = setInterval(() => {
            ref.current += 1;
            console.log(ref.current);
            setTime(ref.current);
            // setTime((prevTime) => prevTime + 1);
        }, 1000);

        return () => {
            clearInterval(timerId);
            console.log("Timer Stopped")
        }
    });
    
    return(
        <div>
            <p>{time}초</p>
        </div>
    );
}