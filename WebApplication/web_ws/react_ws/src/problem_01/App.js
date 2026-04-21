import { useEffect, useState, useRef } from "react";


export default function App() {

    const [text, setText] = useState("");
    const [list, setList] = useState([]);
    const inputRef = useRef(null);

    const doneCounter = list.filter(item => item.done === true).length;
    const completionRate = list.length > 0 ? Math.round((doneCounter / list.length) * 100) : 0;
    const missionLeft = list.length - doneCounter;

    // 입력값 출력
    const handleOnChange = (e) => {
        setText(e.target.value);
    };

    // 체크박스 토글
    const checkboxOnChange = (id) => {
        setList(list.map(item => item.id === id ? { ...item, done: !item.done } : item));
    };


    // 추가 버튼
    const buttonOnClick = () => {
        if (text.trim() === "") {
            inputRef.current.focus();
            alert("미션을 입력하세요.")
        } else {
            setList([...list, {id:Date.now(), text:text.trim(), done:false}]);
            setText("");
            inputRef.current.focus();
        }
        
    };

    // Enter키로 추가
    const handleKeyDown = (e) => {
        if (e.key === "Enter") buttonOnClick();
    };


    // 초기화 버튼
    const buttonOnReset = () => {
        setList([]);
        setText("");
        inputRef.current.focus();
        alert("미션이 초기화되었습니다.")
    }

    // 미션 삭제
    const deleteMission = (id) => {
        setList(list.filter(item => item.id !== id));
    };

    // 완료 미션 삭제
    const deleteCompletedMissions = () => {
        
        if (doneCounter === 0) {
            alert("완료된 미션이 없습니다.");
            return;
        }

        if (window.confirm(`${doneCounter}개의 완료된 미션을 삭제하시겠습니까?`)) {
            setList(list.filter(item => !item.done));
        }
    };


    // 최초 실행 시 입력창 포커스
    useEffect(() => {
        inputRef.current.focus();
    }, []);


    // 타이틀 바꾸기
    useEffect(() => {
        if (list.length === 0) {
            document.title = "오늘의 미션 정복 앱";
        } else if (missionLeft === 0) {
            document.title = "오늘 미션 완료!";
        } else {
            document.title = `남은 미션 ${missionLeft}개`;
        }
    });


    return(
        <div>
            <h1>오늘의 미션 정복 앱</h1>
            <input
                type="text"
                value={text}
                onChange={handleOnChange}
                onKeyDown={handleKeyDown}
                ref={inputRef}
                placeholder="오늘의 미션 입력 (Enter)"
            />
            <button onClick={buttonOnClick}>추가</button>
            <button onClick={buttonOnReset}>초기화</button>
            <p>전체 미션 수 : {list.length}</p>
            <p>완료한 미션 수 : {doneCounter}</p>
            <p>정복률 : {completionRate}%</p>
            <h2>미션 목록</h2>
            <ul>
                {list.map((item) =>
                    <span style={{
                        textDecoration: item.done ? 'line-through' : 'none',
                        color: item.done ? '#888' : '#000'}}>
                            <li key={item.id}>
                                <input
                                    type="checkbox"
                                    checked={item.done}
                                    onChange={() => checkboxOnChange(item.id)}
                                    key={item.key} />
                                {item.text}
                                <button onClick={() => deleteMission(item.id)}>삭제</button>
                            </li>
                    </span>)
                }
            </ul>
            <button onClick={deleteCompletedMissions} disabled={doneCounter === 0}>완료한 미션 삭제</button>
        </div>
    );
}