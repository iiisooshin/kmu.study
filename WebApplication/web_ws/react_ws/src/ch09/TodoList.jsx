import React, {useState} from "react";
import TodoItem from "./TodoItem";


export default function TodoList({todo, onUpdate, onDelete}) {

    const [search, setSearch] = useState("");

    const onChangeSearch = (e) => {
        setSearch(e.target.value);
    };

    const getSearchResult = () => {
        return search === ""
        ? todo
        : todo.filter((item) => item.content.includes(search));
    };


    return(
        <div className="TodoList">
            <h3>Todo List</h3>
            <input
                className="searchbar"
                value={search}
                onChange={onChangeSearch}
                type="text"
                placeholder="검색어를 입력하세요"/>
            <div>
                {getSearchResult().map((item)=>(<TodoItem key={item.id} {...item} onUpdate={onUpdate} onDelete={onDelete}/>))}
            </div>
        </div>
    );
}