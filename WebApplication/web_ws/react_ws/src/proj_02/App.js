import React, {useState, useRef, useEffect} from "react";
import './App.css'


export default function App() {


    const [text, setText] = useState("");
    const [list, setList] = useState([]);
    const refInput = useRef(null);


    useEffect(() => {
        refInput.current.focus();
    }, []);


    const handleOnChange = (e) => {
        setText(e.target.value);
    };


    const handleOnAdd = () => {
        if(text.trim() === "") {
            refInput.current.focus();
        } else {
            setList([...list, text.trim()]);
            setText("");
            refInput.current.focus();
        }
    };
    

    const handleKeyDown = (e) => {
        if (e.key === "Enter") handleOnAdd();
    }



    return(
        <div>
            <h2>할 일 입력기</h2>
            <p>총 항목 수 : {list.length}개</p>

            <div>
                <h3>ToDo</h3>
                <input value={text} ref={refInput} type="text" onChange={handleOnChange} onKeyDown={handleKeyDown} placeholder="input todos"/>
                <button onClick={handleOnAdd}>Add</button>
            </div>

            <ul>
                {list.length === 0 ? (
                        <p>아직 할 일이 없어요</p>
                    ) : (
                        list.map((item, i) => <li key={i}>{item}</li>)
                )}
            </ul>

        </div>
    );
}