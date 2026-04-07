import { useRef, useState } from "react";
import "./style.css";

export default function SearchUseref() {

    const [text, setText] = useState("");
    const refInput = useRef(null);
    console.log(refInput);

    function handleOnChange(e) {
        setText(e.target.value);
    }

    function handleOnClick() {
        if(text.length < 8) {
            alert("8글자 이상 입력하세요.");
            refInput.current.focus();
        } else {
            setText("");
        }
    }

    return(
        <div>
            <p>반갑습니다!</p>
            <p className="web">웹어플리케이션 구축</p>

            <div className="container">
                <div className="item1 item">1</div>
                <div className="item2 item">2</div>
                <div className="item3 item">3</div>
                <div className="item4 item">4</div>
                <div className="item5 item">5</div>
            </div>


            <input value={text} type="text" ref={refInput} onChange={handleOnChange}/>
            <button onClick={handleOnClick}>Done</button>
        </div>
    );
}