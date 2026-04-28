import React from "react";


export default function Header() {

    return(
        <div className="Header">
            <h3>오늘은</h3>
            <h1>{new Date().toLocaleDateString('ko-KR', 
                { year: 'numeric', month: 'long', day: 'numeric' })}</h1>
        </div>
    );
}