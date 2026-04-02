import { useState } from "react";

function NumberOnly() {

    const [num, setNum] = useState("");

    function handleOnChange(e) {
        // const result = e.target.value.replace(/[^0-9]/g, '');
        // setNum(result);

        if(!isNaN(e.target.value)) {
            setNum(e.target.value);
        }
    }

    return(
        <div>
            <input value={num} onChange={handleOnChange}/>
        </div>
    );
}


export default NumberOnly;