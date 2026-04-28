import React from "react";


export default function TodoEditor() {

    return(
        <div className="TodoEditor">
            <h3>새로운 Todo 작성하기</h3>
            <div className="editor_wrapper">
                <input type="text" placeholder="새로운 Todo..."/>
                <button>추가</button>
            </div>
        </div>
    );
}