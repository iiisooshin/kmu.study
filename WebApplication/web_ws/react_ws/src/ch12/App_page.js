import { Routes, Route } from 'react-router-dom';
import Home from '../ch09/Home'
import Todo from './pages/Todo'
import '../ch09/App.css'
import { useState, useRef, useEffect } from 'react';


export default function App() {

    useEffect(() => {
        const rawData = localStorage.getItem("todo");
        if (!rawData) {
            return;
        }

        const localData = JSON.parse(rawData);
        if (localData.length === 0) {
            return;
        }

        localData.sort((a, b) => Number(b.id) - Number(a.id));
        idRef.current = localData[0].id + 1;
        setTodo(localData);
    }, [])



        const [todo, setTodo] = useState([]);
        const idRef = useRef(0);
    
    
        function onCreate(content) {
            const newItem = {
                id: idRef.current,
                isDone: false,
                content: content,
                createdDate: new Date().getTime(),
            };

            const newTodo = [newItem, ...todo];
            setTodo(newTodo);
            localStorage.setItem('todo', JSON.stringify(newTodo));
            idRef.current += 1;
        }
    
    
        function onUpdate(targetId) {
            const newTodo = todo.map((item) => 
                item.id === targetId
                ? {...item, isDone : !item.isDone}
                : item
            )
            setTodo(newTodo);
            localStorage.setItem('todo', JSON.stringify(newTodo));
        }
    
    
        function onDelete(targetId) {
            const newTodo = todo.filter((item) => item.id !== targetId);
            setTodo(newTodo);
            localStorage.setItem('todo', JSON.stringify(newTodo));
        }
    
    
    return(
        <div className="App">
            <Routes>
                <Route path='/' element={<Home onCreate={onCreate} onDelete={onDelete} onUpdate={onUpdate} todo={todo}></Home>}></Route>
                <Route path='/todo/:id' element={<Todo todo={todo}></Todo>}></Route>
            </Routes>

        </div>
    );
}