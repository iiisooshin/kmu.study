import React from "react";
import Header from "./Header";
import TodoEditor from "./TodoEditor";
import TodoList from "./TodoList";



export default function App() {

    return(
        <div className="App">
            <Header></Header>
            <TodoEditor></TodoEditor>
            <TodoList></TodoList>
        </div>
    );
}