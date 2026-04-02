import React, {useState} from "react";

function InputText() {

    const [text, setText] = useState();

    function handleOnChange(e) {
        console.log(e.target.value);
        setText(e.target.value);
    }


    return(
        <div>
            <input value={text} onChange={handleOnChange}/>
            <p>{text}</p>
        </div>
    );
}

export default InputText;