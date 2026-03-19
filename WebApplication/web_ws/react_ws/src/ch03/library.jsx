import React from "react";
import Book from "./book";

function Library() {
    return(
        <div>
            <Book name="자바스크립트 끝내기" price={30000}></Book>
            <Book name="리액트 시작하기" price={50000}></Book>
        </div>
    );
}

export default Library;