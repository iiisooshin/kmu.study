import {useState} from "react";


function InputReset() {

    const [text, setText] = useState("");

    function handleOnReset() {
        setText("");
    }

    function handleOnChange(e) {
        setText(e.target.value);
    }

    return(
        <div>
            <input value={text} onChange={handleOnChange}/>
            <button onClick={handleOnReset}>초기화</button>
        </div>
    );
}


export default InputReset;