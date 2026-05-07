import React from "react";
import { useState, useRef } from "react";


export default function TodoEditor({onCreate}) {

    const [content, setContent] = useState("");
    const inputRef = useRef(null);

    const onChangeContent = (e) => {
        setContent(e.target.value);
    };

    const handleKeyDown = (e) => {
        if (e.key === "Enter") onSubmit();
    }

    const onSubmit = () => {

        if(content.trim() === "") {
            inputRef.current.focus();
            alert("할일을 입력하세요.")
        } else {
            onCreate(content);
            setContent("");
        }

    };


    return(
        <div className="TodoEditor">
            <h3>새로운 Todo 작성하기</h3>
            <div className="editor_wrapper">
                <input
                    value={content}
                    onChange={onChangeContent}
                    onKeyDown={handleKeyDown}
                    type="text"
                    ref={inputRef}
                    placeholder="새로운 Todo..."
                />
                <button onClick={onSubmit}>추가</button>
            </div>
        </div>
    );
}