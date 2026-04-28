import React from "react";
import TodoItem from "./TodoItem";


export default function TodoList() {

    return(
        <div className="TodoList">
            <h3>Todo List</h3>
            <input className="searchbar" type="text" placeholder="검색어를 입력하세요"/>
            <div>
                <TodoItem></TodoItem>
                <TodoItem></TodoItem>
                <TodoItem></TodoItem>
                <TodoItem></TodoItem>
            </div>
        </div>
    );
}