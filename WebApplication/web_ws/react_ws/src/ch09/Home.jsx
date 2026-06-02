import React from "react";
import Header from "./Header";
import TodoEditor from "./TodoEditor";
import TodoList from "./TodoList";
// import { useState, useRef } from "react";



export default function Home({todo, onCreate, onDelete, onUpdate, onClearAll, onDeleteDone}) {


    return(
        <div className="App">
            <Header></Header>
            <TodoEditor onCreate={onCreate}></TodoEditor>
            <TodoList todo={todo} onUpdate={onUpdate} onDelete={onDelete} onClearAll={onClearAll} onDeleteDone={onDeleteDone}></TodoList>
        </div>
    );
}