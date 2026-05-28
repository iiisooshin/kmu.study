import { Routes, Route } from 'react-router-dom';
import Home from '../ch09/Home'
import Todo from './pages/Todo'
import '../ch09/App.css'
import { useState, useEffect } from 'react';
import axios from "axios";

const API_URL = "http://localhost:3003/todos"


export default function App() {

    useEffect(() => {

        // 기존
        // const rawData = localStorage.getItem("todo");
        // if (!rawData) {
        //     return;
        // }

        // const localData = JSON.parse(rawData);
        // if (localData.length === 0) {
        //     return;
        // }

        // localData.sort((a, b) => Number(b.id) - Number(a.id));
        // idRef.current = localData[0].id + 1;
        // setTodo(localData);


        // 1. 처음 화면이 열릴 때 서버에서 Todo 목록 불러오기
        const getTodos = async() => {
            const res = await axios.get(API_URL);
            setTodo(res.data);
        };

        getTodos();
    }, [])



        const [todo, setTodo] = useState([]);
        // const idRef = useRef(0);
    
        // 기존
        // function onCreate(content) {
        //     const newItem = {
        //         id: idRef.current,
        //         isDone: false,
        //         content: content,
        //         createdDate: new Date().getTime(),
        //     };

        //     const newTodo = [newItem, ...todo];
        //     setTodo(newTodo);
        //     localStorage.setItem('todo', JSON.stringify(newTodo));
        //     idRef.current += 1;
        // }

        // 2. Create: 서버에 새 Todo 추가하기
        const onCreate = async (content) => {
            const newItem = {
                isDone: false,
                content: content,
                createdDate: new Date().getTime(),
            };


            const res = await axios.post(API_URL, newItem);
            setTodo((prevTodo) => [res.data, ...prevTodo]);
        }

    
        // 기존
        // function onUpdate(targetId) {
        //     const newTodo = todo.map((item) => 
        //         item.id === targetId
        //         ? {...item, isDone : !item.isDone}
        //         : item
        //     )
        //     setTodo(newTodo);
        //     localStorage.setItem('todo', JSON.stringify(newTodo));
        // }

        const onUpdate = async (targetId) => {
            const targetTodo = todo.find((item) => item.id === targetId);
            if (!targetTodo) return;

            const res = await axios.patch(`${API_URL}/${targetId}`, {
                isDone: !targetTodo.isDone,
            });

            setTodo(
                todo.map((item) =>
                    item.id === targetId ? res.data : item
                )
            );
        }
    
    
        // 기존
        // function onDelete(targetId) {
        //     const newTodo = todo.filter((item) => item.id !== targetId);
        //     setTodo(newTodo);
        //     localStorage.setItem('todo', JSON.stringify(newTodo));
        // }
    
        const onDelete = async (targetId) => {
            await axios.delete(`${API_URL}/${targetId}`);
            setTodo(todo.filter((item) => item.id !== targetId));
        };


    return(
        <div className="App">
            <Routes>
                <Route path='/' element={<Home onCreate={onCreate} onDelete={onDelete} onUpdate={onUpdate} todo={todo}></Home>}></Route>
                <Route path='/todo/:id' element={<Todo todo={todo}></Todo>}></Route>
            </Routes>

        </div>
    );
}
